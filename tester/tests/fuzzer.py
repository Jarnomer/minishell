"""Fuzzer module for generating random minishell test cases.

Generates pseudo-random commands combining various shell features
to stress-test the minishell implementation.
"""

import random
import string
from typing import Optional

from config import TestCase


class MinishellFuzzer:
    """Generates random test cases for minishell."""

    # === Building Blocks ===
    BUILTINS = ["echo", "cd", "pwd", "export", "unset", "env", "exit"]
    EXTERNALS = ["cat", "ls", "grep", "wc", "true", "false", "head", "tail", "tr"]
    
    SIMPLE_WORDS = [
        "hello", "world", "test", "foo", "bar", "baz", "qux",
        "alpha", "beta", "one", "two", "three", "file", "data",
    ]
    
    NUMERIC_WORDS = ["0", "1", "42", "123", "255", "256", "-1"]
    
    SPECIAL_WORDS = [
        "", ".", "..", "-", "--", "-n", "-l", "-a", "-la",
        "a b", "hello world", "  spaces  ",
    ]
    
    SAFE_PATHS = [
        "/tmp", "/etc/hostname", "/dev/null", "/etc/passwd",
        "/bin/echo", "/bin/ls", "/usr/bin/wc",
    ]
    
    READABLE_FILES = ["/etc/hostname", "/etc/passwd", "/dev/null"]
    
    ENV_VARS = ["USER", "HOME", "PATH"]
    SPECIAL_VARS = ["?", "NONEXISTENT_VAR_12345", ""]
    
    ECHO_FLAGS = ["-n", "-nnn", "-nnnn", ""]
    
    PIPE_OP = "|"
    REDIR_OUT = ">"
    REDIR_APPEND = ">>"
    REDIR_IN = "<"
    
    BONUS_AND = "&&"
    BONUS_OR = "||"

    # === Category Weights ===
    CATEGORY_WEIGHTS = {
        "simple_builtin": 20,
        "simple_external": 15,
        "echo_flags": 10,
        "quotes_double": 10,
        "quotes_single": 10,
        "quotes_mixed": 5,
        "expansion_var": 10,
        "expansion_exit": 5,
        "pipe_simple": 8,
        "pipe_chain": 5,
        "redir_out": 8,
        "redir_in": 5,
        "redir_append": 5,
        "redir_combined": 3,
        "syntax_error": 10,
        "edge_case": 5,
    }

    BONUS_WEIGHTS = {
        "logical_and": 8,
        "logical_or": 8,
        "logical_mixed": 5,
        "subshell_simple": 5,
        "subshell_pipe": 3,
        "subshell_logical": 3,
    }

    SYNTAX_ERROR_GENERATORS = [
        "unclosed_single_quote",
        "unclosed_double_quote",
        "pipe_at_start",
        "pipe_at_end",
        "double_pipe",
        "redir_no_target",
        "redir_to_redir",
        "redir_to_pipe",
        "empty_redir",
    ]

    BONUS_SYNTAX_ERRORS = [
        "and_at_start",
        "and_at_end",
        "or_at_start",
        "or_at_end",
        "double_and",
        "empty_parens",
        "unclosed_paren",
    ]

    def __init__(self, seed: Optional[int] = None, include_bonus: bool = False):
        """Initialize the fuzzer.
        
        Args:
            seed: Random seed for reproducibility (None for random)
            include_bonus: Whether to include bonus features (&&, ||, ())
        """
        if seed is None:
            seed = random.randint(0, 2**31 - 1)
        self.seed = seed
        self.rng = random.Random(seed)
        self.include_bonus = include_bonus
        self._build_weights()

    def _build_weights(self):
        """Build the weighted category list."""
        self.categories = []
        self.weights = []
        
        for cat, weight in self.CATEGORY_WEIGHTS.items():
            self.categories.append(cat)
            self.weights.append(weight)
        
        if self.include_bonus:
            for cat, weight in self.BONUS_WEIGHTS.items():
                self.categories.append(cat)
                self.weights.append(weight)

    # === Atomic Generators ===

    def random_word(self) -> str:
        """Generate a random simple word."""
        return self.rng.choice(self.SIMPLE_WORDS)

    def random_words(self, min_count: int = 1, max_count: int = 4) -> list[str]:
        """Generate a list of random words."""
        count = self.rng.randint(min_count, max_count)
        return [self.random_word() for _ in range(count)]

    def random_numeric(self) -> str:
        """Generate a random numeric string."""
        return self.rng.choice(self.NUMERIC_WORDS)

    def random_env_var(self) -> str:
        """Generate a random environment variable reference.
        
        Note: Only returns variables that expand to empty or $? for predictable tests.
        USER/HOME/PATH are avoided as they vary between environments.
        """
        if self.rng.random() < 0.5:
            return "$?"
        return "$NONEXISTENT_VAR_12345"

    def random_quoted_double(self, content: Optional[str] = None) -> str:
        """Generate a double-quoted string."""
        if content is None:
            if self.rng.random() < 0.3:
                content = "hello $? there"
            elif self.rng.random() < 0.5:
                content = " ".join(self.random_words(1, 3))
            else:
                content = self.random_word()
        return f'"{content}"'

    def random_quoted_single(self, content: Optional[str] = None) -> str:
        """Generate a single-quoted string."""
        if content is None:
            if self.rng.random() < 0.3:
                content = f"$USER $HOME"
            else:
                content = " ".join(self.random_words(1, 3))
        return f"'{content}'"

    def random_argument(self) -> str:
        """Generate a random command argument."""
        choice = self.rng.random()
        if choice < 0.5:
            return self.random_word()
        elif choice < 0.7:
            return self.random_quoted_double()
        elif choice < 0.85:
            return self.random_quoted_single()
        else:
            return self.random_numeric()

    def random_arguments(self, min_count: int = 0, max_count: int = 4) -> str:
        """Generate random arguments as a string."""
        count = self.rng.randint(min_count, max_count)
        if count == 0:
            return ""
        args = [self.random_argument() for _ in range(count)]
        return " ".join(args)

    def random_filename(self) -> str:
        """Generate a random safe filename for redirections."""
        base = self.rng.choice(["outfile", "testfile", "tmpfile", "result"])
        suffix = self.rng.choice(["", "_1", "_2", "_test"])
        return f"{base}{suffix}"

    def random_readable_file(self) -> str:
        """Generate a path to a readable file."""
        return self.rng.choice(self.READABLE_FILES)

    def random_builtin(self) -> str:
        """Generate a random builtin command name."""
        return self.rng.choice(self.BUILTINS)

    def random_external(self) -> str:
        """Generate a random external command name."""
        return self.rng.choice(self.EXTERNALS)

    # === Command Generators ===

    def gen_simple_builtin(self) -> tuple[str, bool]:
        """Generate a simple builtin command."""
        builtin = self.random_builtin()
        
        if builtin == "echo":
            args = self.random_arguments(0, 4)
            cmd = f"echo {args}".strip()
        elif builtin == "cd":
            if self.rng.random() < 0.3:
                cmd = "cd"
            else:
                cmd = f"cd {self.rng.choice(['/tmp', '/', '..', '.'])}"
        elif builtin == "pwd":
            cmd = "pwd"
        elif builtin == "export":
            var = f"TESTVAR_{self.rng.randint(1, 100)}"
            val = self.random_word()
            cmd = f"export {var}={val}"
        elif builtin == "unset":
            cmd = f"unset TESTVAR_{self.rng.randint(1, 100)}"
        elif builtin == "env":
            cmd = "env | grep -c PATH"
        elif builtin == "exit":
            if self.rng.random() < 0.5:
                cmd = f"exit {self.rng.randint(0, 255)}"
            else:
                cmd = "exit"
        else:
            cmd = builtin
        
        return cmd, False

    def gen_simple_external(self) -> tuple[str, bool]:
        """Generate a simple external command."""
        external = self.random_external()
        
        if external == "cat":
            cmd = f"cat {self.random_readable_file()}"
        elif external == "ls":
            flag = self.rng.choice(["", "-l", "-a", "-la"])
            path = self.rng.choice(["/tmp", ".", ""])
            cmd = f"ls {flag} {path}".strip()
        elif external == "grep":
            pattern = self.random_word()
            cmd = f"echo '{pattern} test' | grep {pattern}"
        elif external == "wc":
            flag = self.rng.choice(["-l", "-c", "-w"])
            cmd = f"echo hello world | wc {flag}"
        elif external in ["true", "false"]:
            cmd = external
        elif external == "head":
            cmd = f"head -1 {self.random_readable_file()}"
        elif external == "tail":
            cmd = f"tail -1 {self.random_readable_file()}"
        elif external == "tr":
            cmd = "echo hello | tr 'a-z' 'A-Z'"
        else:
            cmd = external
        
        return cmd, True  # skip_stdout_check for variable output

    def gen_echo_flags(self) -> tuple[str, bool]:
        """Generate echo with various flag combinations."""
        flag = self.rng.choice(self.ECHO_FLAGS)
        args = self.random_arguments(1, 3)
        
        if flag:
            cmd = f"echo {flag} {args}"
        else:
            cmd = f"echo {args}"
        
        return cmd, False

    def gen_quotes_double(self) -> tuple[str, bool]:
        """Generate command with double quotes."""
        content_type = self.rng.random()
        
        if content_type < 0.3:
            content = "hello $? world"
        elif content_type < 0.5:
            content = "value:$NONEXISTENT_VAR_12345:end"
        elif content_type < 0.7:
            content = "   spaces   "
        elif content_type < 0.85:
            content = "special | > < chars"
        else:
            content = " ".join(self.random_words(2, 4))
        
        cmd = f'echo "{content}"'
        return cmd, False

    def gen_quotes_single(self) -> tuple[str, bool]:
        """Generate command with single quotes."""
        content_type = self.rng.random()
        
        if content_type < 0.4:
            content = "$USER $HOME $PATH"
        elif content_type < 0.7:
            content = "| > < & *"
        else:
            content = " ".join(self.random_words(2, 3))
        
        cmd = f"echo '{content}'"
        return cmd, False

    def gen_quotes_mixed(self) -> tuple[str, bool]:
        """Generate command with mixed quote styles."""
        patterns = [
            ('echo "hello"\'world\'', False),
            ('echo \'single\'"double"', False),
            ('echo "a"\'b\'"c"\'d\'', False),
            ('echo ""\'\'""', False),
            (f'echo "user:"\'$USER\'":end"', False),
            ('echo "say"' + "'" + '"hello"' + "'", False),
        ]
        cmd, skip = self.rng.choice(patterns)
        return cmd, skip

    def gen_expansion_var(self) -> tuple[str, bool]:
        """Generate variable expansion tests.
        
        Uses only deterministic patterns to avoid environment differences.
        """
        patterns = [
            ("echo $NONEXISTENT_VAR_12345", False),
            ('echo "$NONEXISTENT_VAR_12345"', False),
            ("echo hello$NONEXISTENT_VAR_12345 world", False),
            ('echo "value:$NONEXISTENT_VAR_12345:end"', False),
            ("echo '$NONEXISTENT_VAR_12345'", False),  # Literal, no expansion
        ]
        cmd, skip = self.rng.choice(patterns)
        return cmd, skip

    def gen_expansion_exit(self) -> tuple[str, bool]:
        """Generate exit status expansion tests."""
        patterns = [
            ("echo $?", False),
            ('echo "$?"', False),
            ("echo '$?'", False),
            ("echo $?$?", False),
            ('echo "exit:$?"', False),
        ]
        cmd, skip = self.rng.choice(patterns)
        return cmd, skip

    def gen_pipe_simple(self) -> tuple[str, bool]:
        """Generate simple pipe command."""
        patterns = [
            "echo hello | cat",
            "echo hello world | wc -w",
            "echo test | cat | cat",
            "pwd | cat",
            f"cat {self.random_readable_file()} | head -1",
            "echo hello | grep hello",
            "echo hello | grep nonexistent",
        ]
        cmd = self.rng.choice(patterns)
        return cmd, False

    def gen_pipe_chain(self) -> tuple[str, bool]:
        """Generate longer pipe chains."""
        length = self.rng.randint(3, 5)
        parts = ["echo hello world test"]
        
        for _ in range(length - 1):
            part = self.rng.choice(["cat", "cat", "wc -w", "head -1"])
            parts.append(part)
        
        cmd = " | ".join(parts)
        return cmd, False

    def gen_redir_out(self) -> tuple[str, bool]:
        """Generate output redirection."""
        filename = self.random_filename()
        content = self.random_word()
        
        patterns = [
            f"echo {content} > {filename}",
            f"echo hello world > {filename}",
            f"> {filename}",
            f"pwd > {filename}",
        ]
        
        cmd = self.rng.choice(patterns)
        return cmd, True  # Creates file, output varies

    def gen_redir_in(self) -> tuple[str, bool]:
        """Generate input redirection."""
        infile = self.random_readable_file()
        
        patterns = [
            f"cat < {infile}",
            f"wc -l < {infile}",
            f"head -1 < {infile}",
        ]
        
        cmd = self.rng.choice(patterns)
        return cmd, True  # Output varies by file

    def gen_redir_append(self) -> tuple[str, bool]:
        """Generate append redirection."""
        filename = self.random_filename()
        content = self.random_word()
        
        cmd = f"echo {content} >> {filename}"
        return cmd, True

    def gen_redir_combined(self) -> tuple[str, bool]:
        """Generate combined redirections."""
        infile = self.random_readable_file()
        outfile = self.random_filename()
        
        patterns = [
            f"cat < {infile} > {outfile}",
            f"< {infile} cat > {outfile}",
            f"> {outfile} < {infile} cat",
            f"wc -l < {infile} > {outfile}",
        ]
        
        cmd = self.rng.choice(patterns)
        return cmd, True

    def gen_syntax_error(self) -> tuple[str, bool]:
        """Generate intentional syntax errors."""
        error_type = self.rng.choice(self.SYNTAX_ERROR_GENERATORS)
        
        errors = {
            "unclosed_single_quote": "echo 'hello",
            "unclosed_double_quote": 'echo "hello',
            "pipe_at_start": "| echo hello",
            "pipe_at_end": "echo hello |",
            "double_pipe": "echo hello | | cat",
            "redir_no_target": self.rng.choice([
                "echo hello >",
                "cat <",
                "echo hello >>",
            ]),
            "redir_to_redir": "echo > < file",
            "redir_to_pipe": self.rng.choice([
                "echo hello > |",
                "cat < |",
            ]),
            "empty_redir": self.rng.choice([">", "<", ">>"]),
        }
        
        cmd = errors.get(error_type, "| |")
        return cmd, False

    def gen_edge_case(self) -> tuple[str, bool]:
        """Generate edge case commands."""
        cases = [
            ("echo", False),
            ("echo ''", False),
            ('echo ""', False),
            ("echo '' ''", False),
            ('echo "" ""', False),
            ("   echo hello   ", False),
            ("echo    hello    world", False),
            ("echo -n", False),
            ("echo hello$", False),
            ('echo "$"', False),
            ("echo $", False),
            ('echo "hello""world"', False),
            ("echo 'hello''world'", False),
        ]
        cmd, skip = self.rng.choice(cases)
        return cmd, skip

    # === Bonus Generators ===

    def gen_logical_and(self) -> tuple[str, bool]:
        """Generate && logical operator commands."""
        patterns = [
            ("true && echo success", False),
            ("false && echo nope", False),
            ("echo first && echo second", False),
            ("true && true && echo all", False),
            ("true && false && echo nope", False),
        ]
        cmd, skip = self.rng.choice(patterns)
        return cmd, skip

    def gen_logical_or(self) -> tuple[str, bool]:
        """Generate || logical operator commands."""
        patterns = [
            ("false || echo fallback", False),
            ("true || echo nope", False),
            ("false || false || echo finally", False),
            ("true || false || echo nope", False),
        ]
        cmd, skip = self.rng.choice(patterns)
        return cmd, skip

    def gen_logical_mixed(self) -> tuple[str, bool]:
        """Generate mixed logical operators."""
        patterns = [
            ("false && echo no || echo fallback", False),
            ("true && false || echo recovered", False),
            ("false || true && echo success", False),
            ("true && echo yes || echo no", False),
        ]
        cmd, skip = self.rng.choice(patterns)
        return cmd, skip

    def gen_subshell_simple(self) -> tuple[str, bool]:
        """Generate simple subshell commands."""
        patterns = [
            ("(echo hello)", False),
            ("(pwd)", True),
            ("(true)", False),
            ("(false)", False),
            ("(echo hello world)", False),
        ]
        cmd, skip = self.rng.choice(patterns)
        return cmd, skip

    def gen_subshell_pipe(self) -> tuple[str, bool]:
        """Generate subshell with pipes."""
        patterns = [
            ("(echo hello) | cat", False),
            ("echo hello | (cat)", False),
            ("(echo hello) | (cat)", False),
            ("(echo test | cat)", False),
        ]
        cmd, skip = self.rng.choice(patterns)
        return cmd, skip

    def gen_subshell_logical(self) -> tuple[str, bool]:
        """Generate subshell with logical operators."""
        patterns = [
            ("(true && echo yes)", False),
            ("(false || echo fallback)", False),
            ("(false) || echo recovered", False),
            ("(true) && echo success", False),
            ("(true || false) && echo yes", False),
        ]
        cmd, skip = self.rng.choice(patterns)
        return cmd, skip

    def gen_bonus_syntax_error(self) -> tuple[str, bool]:
        """Generate bonus syntax errors."""
        error_type = self.rng.choice(self.BONUS_SYNTAX_ERRORS)
        
        errors = {
            "and_at_start": "&& echo hello",
            "and_at_end": "echo hello &&",
            "or_at_start": "|| echo hello",
            "or_at_end": "echo hello ||",
            "double_and": "echo a && && echo b",
            "empty_parens": "()",
            "unclosed_paren": "(echo hello",
        }
        
        cmd = errors.get(error_type, "()")
        return cmd, False

    # === Main Generation Interface ===

    def _get_generator(self, category: str):
        """Get the generator function for a category."""
        generators = {
            "simple_builtin": self.gen_simple_builtin,
            "simple_external": self.gen_simple_external,
            "echo_flags": self.gen_echo_flags,
            "quotes_double": self.gen_quotes_double,
            "quotes_single": self.gen_quotes_single,
            "quotes_mixed": self.gen_quotes_mixed,
            "expansion_var": self.gen_expansion_var,
            "expansion_exit": self.gen_expansion_exit,
            "pipe_simple": self.gen_pipe_simple,
            "pipe_chain": self.gen_pipe_chain,
            "redir_out": self.gen_redir_out,
            "redir_in": self.gen_redir_in,
            "redir_append": self.gen_redir_append,
            "redir_combined": self.gen_redir_combined,
            "syntax_error": self.gen_syntax_error,
            "edge_case": self.gen_edge_case,
            # Bonus
            "logical_and": self.gen_logical_and,
            "logical_or": self.gen_logical_or,
            "logical_mixed": self.gen_logical_mixed,
            "subshell_simple": self.gen_subshell_simple,
            "subshell_pipe": self.gen_subshell_pipe,
            "subshell_logical": self.gen_subshell_logical,
        }
        return generators.get(category)

    def _is_syntax_error_category(self, category: str) -> bool:
        """Check if category generates syntax errors."""
        return category == "syntax_error"

    def _is_bonus_category(self, category: str) -> bool:
        """Check if category is a bonus feature."""
        return category in self.BONUS_WEIGHTS

    def generate_test(self, test_num: int) -> TestCase:
        """Generate a single random test case.
        
        Args:
            test_num: Test number for naming
            
        Returns:
            A TestCase object
        """
        # Select category based on weights
        category = self.rng.choices(self.categories, weights=self.weights, k=1)[0]
        
        # Get generator and create command
        generator = self._get_generator(category)
        if generator is None:
            cmd, skip = "echo fallback", False
        else:
            cmd, skip = generator()
        
        # Determine if this is a syntax error test
        is_syntax_error = self._is_syntax_error_category(category)
        
        # Build test case
        test = TestCase(
            name=f"fuzz_{test_num:04d}_{category}",
            command=cmd,
            category=f"fuzzer/{category}",
            expect_error=is_syntax_error,
            expected_exit=2 if is_syntax_error else None,
            skip_stdout_check=skip,
            skip_valgrind=True,  # Fuzzer tests skip valgrind by default
            bonus=self._is_bonus_category(category),
        )
        
        return test

    def generate_tests(self, count: int) -> list[TestCase]:
        """Generate multiple random test cases.
        
        Args:
            count: Number of tests to generate
            
        Returns:
            List of TestCase objects
        """
        tests = []
        for i in range(count):
            test = self.generate_test(i + 1)
            tests.append(test)
        return tests

    def get_seed_info(self) -> str:
        """Get seed information for reproducibility."""
        return f"{self.seed}"