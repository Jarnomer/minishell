"""Configuration for minishell tester."""

import shutil
from pathlib import Path
from dataclasses import dataclass, field
from typing import Optional


# === Colors ===
class Colors:
    RED = "\033[0;31m"
    GREEN = "\033[0;32m"
    YELLOW = "\033[0;33m"
    BLUE = "\033[0;34m"
    PURPLE = "\033[0;35m"
    CYAN = "\033[0;36m"

    BOLD_RED = "\033[1;31m"
    BOLD_GREEN = "\033[1;32m"
    BOLD_YELLOW = "\033[1;33m"
    BOLD_BLUE = "\033[1;34m"
    BOLD_PURPLE = "\033[1;35m"
    BOLD_CYAN = "\033[1;36m"

    RESET = "\033[0m"

    @classmethod
    def ok(cls, text: str) -> str:
        return f"{cls.BOLD_GREEN}{text}{cls.RESET}"

    @classmethod
    def ko(cls, text: str) -> str:
        return f"{cls.BOLD_RED}{text}{cls.RESET}"

    @classmethod
    def warn(cls, text: str) -> str:
        return f"{cls.BOLD_YELLOW}{text}{cls.RESET}"

    @classmethod
    def info(cls, text: str) -> str:
        return f"{cls.CYAN}{text}{cls.RESET}"

    @classmethod
    def title(cls, text: str) -> str:
        return f"{cls.BOLD_PURPLE}{text}{cls.RESET}"


@dataclass
class ValgrindConfig:
    """Valgrind configuration."""

    enabled: bool = True
    check_leaks: bool = True
    check_fds: bool = True
    track_children: bool = True
    suppression_file: Optional[Path] = None

    @property
    def cmd(self) -> Optional[str]:
        return shutil.which("valgrind")

    @property
    def available(self) -> bool:
        return self.cmd is not None

    def build_flags(self) -> list[str]:
        flags = []
        if self.check_leaks:
            flags.extend(["--leak-check=full", "--show-leak-kinds=all"])
        if self.check_fds:
            flags.append("--track-fds=yes")
        if self.track_children:
            flags.append("--trace-children=yes")
        if self.suppression_file and self.suppression_file.exists():
            flags.append(f"--suppressions={self.suppression_file}")
        flags.append("--error-exitcode=42")
        return flags

    def build_cmd(self, target_cmd: list[str]) -> list[str]:
        if not self.available or not self.enabled:
            return target_cmd
        return [self.cmd] + self.build_flags() + target_cmd


@dataclass
class Config:
    """Main configuration."""

    # Paths
    minishell_path: Path = field(default_factory=lambda: Path("./minishell"))
    test_dir: Path = field(default_factory=lambda: Path("/tmp/minishell_test"))
    log_file: Path = field(default_factory=lambda: Path("minishell_test.log"))

    # Execution
    timeout: float = 0.5
    reference_shell: str = "bash"

    # Valgrind
    valgrind: ValgrindConfig = field(default_factory=ValgrindConfig)

    # Test selection
    categories: list[str] = field(default_factory=list)
    bonus_enabled: bool = False

    # Output
    verbose: bool = False
    color_enabled: bool = True

    def __post_init__(self):
        self.test_dir.mkdir(parents=True, exist_ok=True)

    @property
    def bash_cmd(self) -> Optional[str]:
        return shutil.which(self.reference_shell)

    @property
    def timeout_cmd(self) -> Optional[str]:
        return shutil.which("timeout")


# === Result Types ===
@dataclass
class ExecutionResult:
    """Result of running a single command."""

    stdout: str
    stderr: str
    exit_code: int
    timed_out: bool = False
    crashed: bool = False
    signal: Optional[int] = None


@dataclass
class ValgrindResult:
    """Valgrind analysis result."""

    has_leaks: bool = False
    definitely_lost: int = 0
    indirectly_lost: int = 0
    open_fds: int = 0
    raw_output: str = ""

    @property
    def passed(self) -> bool:
        return not self.has_leaks and self.open_fds <= 3


@dataclass
class TestResult:
    """Complete test result."""

    name: str
    category: str
    command: str

    # Execution results
    minishell: ExecutionResult
    reference: ExecutionResult

    # Comparisons
    stdout_match: bool = False
    stderr_match: bool = False
    exit_code_match: bool = False
    outfile_match: bool = True

    # Memory
    valgrind: Optional[ValgrindResult] = None

    # Zombies
    zombie_count: int = 0

    @property
    def passed(self) -> bool:
        base_pass = (
            self.exit_code_match
            and self.stdout_match
            and self.outfile_match
            and not self.minishell.crashed
            and self.zombie_count == 0
        )
        if self.valgrind:
            return base_pass and self.valgrind.passed
        return base_pass

    @property
    def status(self) -> str:
        if self.passed:
            return "OK"
        reasons = []
        if not self.exit_code_match:
            reasons.append("exit")
        if not self.stdout_match:
            reasons.append("stdout")
        if not self.outfile_match:
            reasons.append("outfile")
        if self.minishell.crashed:
            reasons.append("crash")
        if self.zombie_count > 0:
            reasons.append("zombies")
        if self.valgrind and not self.valgrind.passed:
            reasons.append("leaks" if self.valgrind.has_leaks else "fds")
        return f"KO ({', '.join(reasons)})"


# === Test Definition ===
@dataclass
class TestCase:
    """Definition of a single test."""

    name: str
    command: str = ""  # Single command
    commands: list[str] = field(default_factory=list)  # Multi-command
    category: str = "general"

    # Expected behavior
    expected_exit: Optional[int] = None  # None = match bash
    expect_error: bool = False

    # Setup
    setup_files: dict[str, str] = field(default_factory=dict)  # filename -> content
    env_vars: dict[str, str] = field(default_factory=dict)

    # Flags
    skip_valgrind: bool = False
    skip_stdout_check: bool = False
    bonus: bool = False

    # Timeout override
    timeout: Optional[float] = None

    def get_display_command(self) -> str:
        """Get command string for display purposes."""
        if self.commands:
            return " ; ".join(self.commands)
        return self.command

    def get_stdin_input(self) -> str:
        """Get the input to send to shell stdin."""
        if self.commands:
            return "\n".join(self.commands)
        return self.command

    def is_multi_command(self) -> bool:
        """Check if this is a multi-command test."""
        return len(self.commands) > 0

