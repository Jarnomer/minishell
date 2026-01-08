"""Main test runner for minishell."""

import os
import re
import signal
import subprocess
import tempfile
import time
from pathlib import Path
from typing import Optional

from config import (
    Config, Colors, TestCase, TestResult,
    ExecutionResult, ValgrindResult
)


class TestRunner:
    """Executes tests and compares results against bash."""
    
    def __init__(self, config: Config):
        self.config = config
        self.results: list[TestResult] = []
        self.test_num = 0
        self._setup_test_env()
    
    def _setup_test_env(self):
        """Create isolated test environment."""
        self.test_dir = Path(tempfile.mkdtemp(prefix="minishell_"))
        self.infile = self.test_dir / "infile"
        self.outfile_ms = self.test_dir / "outfile_minishell"
        self.outfile_ref = self.test_dir / "outfile_bash"
        
        # Create default infile with test content
        self.infile.write_text("line1\nline2\nline3\nalpha\nbeta\ngamma\n")
    
    def cleanup(self):
        """Remove test environment."""
        import shutil
        if self.test_dir.exists():
            shutil.rmtree(self.test_dir)
    
    def run_command(
        self,
        shell_path: str,
        command: str,
        timeout: Optional[float] = None,
        env: Optional[dict] = None,
        cwd: Optional[Path] = None,
        use_c_flag: bool = False
    ) -> ExecutionResult:
        """Execute a command in a shell and capture results."""
        
        timeout = timeout or self.config.timeout
        cwd = cwd or self.test_dir
        
        # Build environment
        run_env = os.environ.copy()
        if env:
            run_env.update(env)
        
        try:
            # For bash, use -c flag. For minishell, pipe to stdin
            if use_c_flag:
                shell_cmd = [shell_path, "-c", command]
                stdin_input = None
            else:
                shell_cmd = [shell_path]
                # Add newline to ensure command is executed, then exit
                stdin_input = (command + "\nexit\n").encode()
            
            proc = subprocess.Popen(
                shell_cmd,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                cwd=cwd,
                env=run_env,
                preexec_fn=os.setsid  # New process group for clean killing
            )
            
            try:
                stdout, stderr = proc.communicate(input=stdin_input, timeout=timeout)
                exit_code = proc.returncode
                
                # Check for crash signals
                crashed = False
                sig = None
                if exit_code < 0:
                    sig = -exit_code
                    crashed = sig in (signal.SIGSEGV, signal.SIGBUS, signal.SIGABRT)
                elif exit_code >= 128:
                    sig = exit_code - 128
                    crashed = sig in (signal.SIGSEGV, signal.SIGBUS, signal.SIGABRT)
                
                return ExecutionResult(
                    stdout=stdout.decode("utf-8", errors="replace"),
                    stderr=stderr.decode("utf-8", errors="replace"),
                    exit_code=exit_code if exit_code >= 0 else 128 + (-exit_code),
                    crashed=crashed,
                    signal=sig
                )
                
            except subprocess.TimeoutExpired:
                # Kill entire process group
                os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
                proc.wait()
                return ExecutionResult(
                    stdout="",
                    stderr="",
                    exit_code=-1,
                    timed_out=True
                )
                
        except Exception as e:
            return ExecutionResult(
                stdout="",
                stderr=str(e),
                exit_code=-1
            )
    
    def run_minishell(
        self,
        command: str,
        timeout: Optional[float] = None,
        env: Optional[dict] = None
    ) -> ExecutionResult:
        """Run command in minishell (piped to stdin)."""
        ms_path = str(self.config.minishell_path.resolve())
        return self.run_command(ms_path, command, timeout, env, use_c_flag=False)
    
    def run_bash(
        self,
        command: str,
        timeout: Optional[float] = None,
        env: Optional[dict] = None
    ) -> ExecutionResult:
        """Run command in bash for reference (using -c flag)."""
        return self.run_command(self.config.bash_cmd, command, timeout, env, use_c_flag=True)
    
    def check_valgrind(self, command: str, env: Optional[dict] = None) -> ValgrindResult:
        """Run minishell under valgrind and parse output."""
        
        if not self.config.valgrind.available or not self.config.valgrind.enabled:
            return ValgrindResult()
        
        ms_path = str(self.config.minishell_path.resolve())
        
        # Build valgrind command - pipe to minishell stdin
        valgrind_cmd = self.config.valgrind.build_flags() + [
            "--log-fd=2",  # Output to stderr
            ms_path
        ]
        
        run_env = os.environ.copy()
        if env:
            run_env.update(env)
        
        stdin_input = (command + "\nexit\n").encode()
        
        try:
            proc = subprocess.run(
                [self.config.valgrind.cmd] + valgrind_cmd,
                input=stdin_input,
                capture_output=True,
                timeout=self.config.timeout * 10,  # Valgrind is slow
                cwd=self.test_dir,
                env=run_env
            )
            output = proc.stderr.decode("utf-8", errors="replace")
            
            return self._parse_valgrind_output(output)
            
        except subprocess.TimeoutExpired:
            return ValgrindResult(raw_output="Valgrind timed out")
        except Exception as e:
            return ValgrindResult(raw_output=str(e))
    
    def _parse_valgrind_output(self, output: str) -> ValgrindResult:
        """Parse valgrind output for leaks and fd issues."""
        
        result = ValgrindResult(raw_output=output)
        
        # Parse definitely lost
        match = re.search(r"definitely lost: ([\d,]+) bytes", output)
        if match:
            result.definitely_lost = int(match.group(1).replace(",", ""))
        
        # Parse indirectly lost
        match = re.search(r"indirectly lost: ([\d,]+) bytes", output)
        if match:
            result.indirectly_lost = int(match.group(1).replace(",", ""))
        
        # Parse open file descriptors
        match = re.search(r"FILE DESCRIPTORS: (\d+) open", output)
        if match:
            result.open_fds = int(match.group(1))
        else:
            # Count individual fd reports (excluding stdin/stdout/stderr)
            fd_matches = re.findall(r"Open file descriptor (\d+):", output)
            result.open_fds = len([fd for fd in fd_matches if int(fd) > 2])
        
        # Determine if there are leaks
        result.has_leaks = (
            result.definitely_lost > 0 or 
            result.indirectly_lost > 0
        )
        
        return result
    
    def check_zombies(self, command: str, env: Optional[dict] = None) -> int:
        """Check for zombie processes during execution."""
        
        ms_path = str(self.config.minishell_path.resolve())
        run_env = os.environ.copy()
        if env:
            run_env.update(env)
        
        stdin_input = (command + "\nexit\n").encode()
        
        try:
            proc = subprocess.Popen(
                [ms_path],
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                cwd=self.test_dir,
                env=run_env
            )
            
            # Send command
            proc.stdin.write(stdin_input)
            proc.stdin.flush()
            
            # Wait a bit for children to spawn
            time.sleep(0.15)
            
            # Check for zombies
            zombie_count = 0
            try:
                ps_result = subprocess.run(
                    ["ps", "--ppid", str(proc.pid), "-o", "stat="],
                    capture_output=True,
                    timeout=1
                )
                states = ps_result.stdout.decode().strip().split("\n")
                zombie_count = sum(1 for s in states if "Z" in s)
            except Exception:
                pass
            
            # Clean up
            try:
                proc.wait(timeout=self.config.timeout)
            except subprocess.TimeoutExpired:
                proc.kill()
                proc.wait()
            
            return zombie_count
            
        except Exception:
            return 0
    
    def _strip_prompt(self, output: str, command: str = "") -> str:
        """Remove shell prompts and echoed commands from output for comparison."""
        # First, remove all ANSI escape sequences
        ansi_escape = re.compile(r'\x1b\[[0-9;]*m')
        output_clean = ansi_escape.sub('', output)
        
        lines = output_clean.split('\n')
        cleaned = []
        
        cmd_stripped = command.strip()
        
        for line in lines:
            # Remove prompt pattern from start of line
            line = re.sub(r'^minishell\$ ', '', line)
            
            # Remove prompt from end of line
            line = re.sub(r'minishell\$ exit$', '', line)
            line = re.sub(r'minishell\$ $', '', line)
            line = re.sub(r'minishell\$$', '', line)
            
            # Skip the echoed command itself
            if cmd_stripped and line.strip() == cmd_stripped:
                continue
            # Skip the 'exit' command we inject
            if line.strip() == 'exit':
                continue
            
            cleaned.append(line)
        
        # Remove trailing empty lines
        while cleaned and not cleaned[-1].strip():
            cleaned.pop()
        # Remove leading empty lines  
        while cleaned and not cleaned[0].strip():
            cleaned.pop(0)
        
        return '\n'.join(cleaned)
    
    def compare_outputs(
        self,
        ms_result: ExecutionResult,
        ref_result: ExecutionResult,
        command: str = "",
        check_stderr: bool = False
    ) -> tuple[bool, bool]:
        """Compare minishell output to bash output."""
        
        # Normalize outputs
        ms_stdout = self._strip_prompt(ms_result.stdout, command).rstrip()
        ref_stdout = ref_result.stdout.rstrip()
        
        stdout_match = ms_stdout == ref_stdout
        
        # For stderr, we often just check presence/absence of error
        stderr_match = True
        if check_stderr:
            ms_has_error = bool(ms_result.stderr.strip())
            ref_has_error = bool(ref_result.stderr.strip())
            stderr_match = ms_has_error == ref_has_error
        
        return stdout_match, stderr_match
    
    def compare_files(self, file1: Path, file2: Path) -> bool:
        """Compare two output files."""
        if not file1.exists() and not file2.exists():
            return True
        if not file1.exists() or not file2.exists():
            return False
        return file1.read_bytes() == file2.read_bytes()
    
    def run_test(self, test: TestCase) -> TestResult:
        """Execute a single test case."""
        
        self.test_num += 1
        
        # Setup test files
        for filename, content in test.setup_files.items():
            (self.test_dir / filename).write_text(content)
        
        # Clear output files
        self.outfile_ms.unlink(missing_ok=True)
        self.outfile_ref.unlink(missing_ok=True)
        
        # Determine timeout
        timeout = test.timeout or self.config.timeout
        
        # Build environment
        env = test.env_vars.copy() if test.env_vars else None
        
        # Run in both shells
        ms_result = self.run_minishell(test.command, timeout, env)
        ref_result = self.run_bash(test.command, timeout, env)
        
        # Compare outputs
        stdout_match, stderr_match = self.compare_outputs(
            ms_result, ref_result,
            command=test.command,
            check_stderr=test.expect_error
        )
        
        # Compare exit codes
        if test.expected_exit is not None:
            exit_match = ms_result.exit_code == test.expected_exit
        else:
            exit_match = ms_result.exit_code == ref_result.exit_code
        
        # Compare output files if redirections were used
        outfile_match = True
        if ">" in test.command:
            outfile_match = self.compare_files(self.outfile_ms, self.outfile_ref)
        
        # Check valgrind (optional)
        valgrind_result = None
        if not test.skip_valgrind and self.config.valgrind.enabled:
            valgrind_result = self.check_valgrind(test.command, env)
        
        # Check zombies for pipeline tests
        zombie_count = 0
        if "|" in test.command:
            zombie_count = self.check_zombies(test.command, env)
        
        result = TestResult(
            name=test.name,
            category=test.category,
            command=test.command,
            minishell=ms_result,
            reference=ref_result,
            stdout_match=stdout_match if not test.skip_stdout_check else True,
            stderr_match=stderr_match,
            exit_code_match=exit_match,
            outfile_match=outfile_match,
            valgrind=valgrind_result,
            zombie_count=zombie_count
        )
        
        self.results.append(result)
        return result
    
    def run_tests(self, tests: list[TestCase]) -> list[TestResult]:
        """Run multiple tests."""
        results = []
        for test in tests:
            if test.bonus and not self.config.bonus_enabled:
                continue
            result = self.run_test(test)
            results.append(result)
        return results
    
    def get_summary(self) -> dict:
        """Get test results summary."""
        passed = sum(1 for r in self.results if r.passed)
        failed = len(self.results) - passed
        
        by_category = {}
        for r in self.results:
            if r.category not in by_category:
                by_category[r.category] = {"passed": 0, "failed": 0}
            if r.passed:
                by_category[r.category]["passed"] += 1
            else:
                by_category[r.category]["failed"] += 1
        
        return {
            "total": len(self.results),
            "passed": passed,
            "failed": failed,
            "by_category": by_category
        }


class TestPrinter:
    """Handles test output formatting."""
    
    def __init__(self, config: Config):
        self.config = config
    
    def print_header(self, title: str):
        """Print section header."""
        width = 70
        pad = (width - len(title) - 2) // 2
        line = "=" * width
        
        print(f"\n{Colors.PURPLE}{line}{Colors.RESET}")
        print(f"{Colors.PURPLE}|{' ' * pad}{Colors.BOLD_GREEN}{title}{Colors.RESET}"
              f"{' ' * pad}{Colors.PURPLE} |{Colors.RESET}")
        print(f"{Colors.PURPLE}{line}{Colors.RESET}\n")
    
    def print_result(self, result: TestResult, test_num: int):
        """Print test result in compact format."""
        
        # Compact status line
        if result.passed:
            print(f"{Colors.BOLD_PURPLE}TEST {test_num:3d}: ✅ {Colors.RESET}"
                  f"{Colors.CYAN}{result.command}{Colors.RESET}")
        else:
            print(f"\n{Colors.BOLD_RED}TEST {test_num:3d}: 💢 {Colors.RESET}"
                  f"{Colors.YELLOW}{result.command}{Colors.RESET}")
            self._print_verbose_failure(result)
    
    def _print_verbose_failure(self, result: TestResult):
        """Print detailed failure information."""
        separator = "=" * 50
        print(f"\n{Colors.BOLD_RED}{separator}{Colors.RESET}\n")
        
        # ANSI escape pattern for cleaning display output
        ansi_escape = re.compile(r'\x1b\[[0-9;]*m')
        
        # Show what failed
        failures = []
        if not result.exit_code_match:
            failures.append(f"Exit code: minishell={result.minishell.exit_code} bash={result.reference.exit_code}")
        
        if not result.stdout_match:
            # Strip ANSI codes and prompts for display
            ms_out = ansi_escape.sub('', result.minishell.stdout)
            cmd_stripped = result.command.strip()
            
            lines = []
            for line in ms_out.split('\n'):
                # Remove prompt from start
                line = re.sub(r'^minishell\$ ', '', line)
                # Remove prompt from end
                line = re.sub(r'minishell\$ exit$', '', line)
                line = re.sub(r'minishell\$ $', '', line)
                line = re.sub(r'minishell\$$', '', line)
                # Skip echoed command and exit
                if line.strip() == cmd_stripped or line.strip() == 'exit':
                    continue
                if line:
                    lines.append(line)
            ms_out = '\n'.join(lines).rstrip()
            
            ref_out = result.reference.stdout.rstrip()
            failures.append(f"Stdout mismatch:\n  Minishell: {repr(ms_out)}\n  Bash:      {repr(ref_out)}")
        
        if not result.outfile_match and ">" in result.command:
            failures.append("Output file mismatch")
        
        if result.minishell.crashed:
            sig_name = signal.Signals(result.minishell.signal).name if result.minishell.signal else "UNKNOWN"
            failures.append(f"Crashed with signal: {sig_name}")
        
        if result.minishell.timed_out:
            failures.append("Timed out")
        
        if result.valgrind and not result.valgrind.passed:
            if result.valgrind.has_leaks:
                failures.append(f"Memory leaks: {result.valgrind.definitely_lost} bytes definitely lost")
            if result.valgrind.open_fds > 3:
                failures.append(f"Open file descriptors: {result.valgrind.open_fds}")
        
        if result.zombie_count > 0:
            failures.append(f"Zombie processes: {result.zombie_count}")
        
        for failure in failures:
            print(f"{Colors.YELLOW}{failure}{Colors.RESET}")
        
        print(f"\n{Colors.BOLD_RED}{separator}\n{Colors.RESET}")
    
    def print_summary(self, summary: dict, test_count: int):
        """Print final summary."""
        self.print_header("SUMMARY")
        
        print(f"{Colors.BOLD_BLUE}Tests run:{Colors.RESET}    {test_count}")
        print(f"{Colors.BOLD_BLUE}Tests passed:{Colors.RESET} {Colors.ok(str(summary['passed']))}")
        print(f"{Colors.BOLD_BLUE}Tests failed:{Colors.RESET} {Colors.ko(str(summary['failed']))}")
        
        if summary["by_category"]:
            print(f"\n{Colors.BOLD_BLUE}By category:{Colors.RESET}")
            for cat, counts in summary["by_category"].items():
                print(f"  {cat}: {Colors.ok(str(counts['passed']))} passed, "
                      f"{Colors.ko(str(counts['failed']))} failed")
        
        print()
        if summary["failed"] == 0:
            print(f"{Colors.ok('All tests passed!')}")
        else:
            print(f"{Colors.warn(f'See {self.config.log_file} for details.')}")
        print()


class TestLogger:
    """Logs detailed test results to file."""
    
    def __init__(self, config: Config):
        self.config = config
        self.log_path = config.log_file
        # Clear log file
        self.log_path.write_text("")
    
    def log_result(self, result: TestResult):
        """Log a test result if it failed."""
        if result.passed:
            return
        
        with open(self.log_path, "a") as f:
            f.write(f"TEST: {result.name} [{result.category}]\n")
            f.write("=" * 60 + "\n")
            f.write(f"Command: {result.command}\n")
            f.write(f"Status: {result.status}\n\n")
            
            f.write(f"Exit codes: minishell={result.minishell.exit_code} "
                   f"bash={result.reference.exit_code}\n")
            
            if not result.stdout_match:
                f.write(f"\nMinishell stdout:\n{result.minishell.stdout}\n")
                f.write(f"\nBash stdout:\n{result.reference.stdout}\n")
            
            if result.minishell.stderr:
                f.write(f"\nMinishell stderr:\n{result.minishell.stderr}\n")
            
            if result.valgrind and not result.valgrind.passed:
                f.write(f"\nValgrind output:\n{result.valgrind.raw_output}\n")
            
            f.write("\n" + "=" * 60 + "\n\n")