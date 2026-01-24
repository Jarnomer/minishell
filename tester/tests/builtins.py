"""Builtin command tests for minishell."""

from config import TestCase

# === Echo Tests ===
ECHO_TESTS = [
    # Basic functionality
    TestCase(
        name="echo basic",
        command="echo hello",
        category="builtins/echo"
    ),
    TestCase(
        name="echo multiple args",
        command="echo hello world",
        category="builtins/echo"
    ),
    TestCase(
        name="echo no args",
        command="echo",
        category="builtins/echo"
    ),
    # -n flag handling
    TestCase(
        name="echo -n flag",
        command="echo -n hello",
        category="builtins/echo"
    ),
    TestCase(
        name="echo -n multiple args",
        command="echo -n hello world",
        category="builtins/echo"
    ),
    TestCase(
        name="echo -n no args",
        command="echo -n",
        category="builtins/echo"
    ),
    TestCase(
        name="echo multiple -n flags",
        command="echo -n -n -n hello",
        category="builtins/echo"
    ),
    TestCase(
        name="echo -nnnn flag",
        command="echo -nnnn hello",
        category="builtins/echo"
    ),
    TestCase(
        name="echo -nnn no args",
        command="echo -nnn",
        category="builtins/echo"
    ),
    # -n flag edge cases
    TestCase(
        name="echo -n then text -n",
        command="echo -n hello -n",
        category="builtins/echo"
    ),
    TestCase(
        name="echo invalid flag -x",
        command="echo -x hello",
        category="builtins/echo"
    ),
    TestCase(
        name="echo -nnnx invalid",
        command="echo -nnnx hello",
        category="builtins/echo"
    ),
    TestCase(
        name="echo just dash",
        command="echo -",
        category="builtins/echo"
    ),
    TestCase(
        name="echo double dash",
        command="echo --",
        category="builtins/echo"
    ),
    TestCase(
        name="echo -n- invalid",
        command="echo -n- hello",
        category="builtins/echo"
    ),
    # With quotes
    TestCase(
        name="echo with double quotes",
        command='echo "hello world"',
        category="builtins/echo"
    ),
    TestCase(
        name="echo with single quotes",
        command="echo 'hello world'",
        category="builtins/echo"
    ),
    TestCase(
        name="echo empty string",
        command='echo ""',
        category="builtins/echo"
    ),
    TestCase(
        name="echo mixed args",
        command='echo hello "world" \'foo\'',
        category="builtins/echo"
    ),
]

# === Pwd Tests ===
PWD_TESTS = [
    TestCase(
        name="pwd basic",
        command="pwd",
        category="builtins/pwd"
    ),
    TestCase(
        name="pwd after cd",
        command="cd /tmp && pwd",
        category="builtins/pwd",
        bonus=True  # Requires &&
    ),
    TestCase(
        name="pwd ignores args",
        command="pwd ignored args",
        category="builtins/pwd"
    ),
    TestCase(
        name="pwd ignores flags",
        command="pwd -L -P",
        category="builtins/pwd"
    ),
]

# === Cd Tests ===
CD_TESTS = [
    # Basic navigation (with && for verification - bonus)
    TestCase(
        name="cd absolute path",
        command="cd /tmp && pwd",
        category="builtins/cd",
        bonus=True
    ),
    TestCase(
        name="cd home no args",
        command="cd && pwd",
        category="builtins/cd",
        bonus=True
    ),
    TestCase(
        name="cd relative path",
        command="cd /tmp && cd .. && pwd",
        category="builtins/cd",
        bonus=True
    ),
    TestCase(
        name="cd dot",
        command="cd . && pwd",
        category="builtins/cd",
        bonus=True
    ),
    TestCase(
        name="cd dotdot",
        command="cd /tmp && cd .. && pwd",
        category="builtins/cd",
        bonus=True
    ),
    # Error cases (no && needed)
    TestCase(
        name="cd nonexistent",
        command="cd /nonexistent_dir_12345",
        category="builtins/cd",
        expect_error=True
    ),
    TestCase(
        name="cd too many args",
        command="cd /tmp /var",
        category="builtins/cd",
        expect_error=True
    ),
    TestCase(
        name="cd file not dir",
        command="cd /etc/hostname",
        category="builtins/cd",
        expect_error=True
    ),
    TestCase(
        name="cd no permission",
        command="cd /root",
        category="builtins/cd",
        expect_error=True
    ),
    # Pipe test (no && needed)
    TestCase(
        name="cd in pipe",
        command="cd /tmp | pwd",  # pwd runs in subshell
        category="builtins/cd"
    ),
]

# === Export Tests ===
EXPORT_TESTS = [
    # Basic functionality
    TestCase(
        name="export no args shows env",
        command="export | head -5",
        category="builtins/export",
        skip_stdout_check=True  # Output varies
    ),
    TestCase(
        name="export simple var",
        command="export TESTVAR=hello && echo $TESTVAR",
        category="builtins/export",
        bonus=True
    ),
    TestCase(
        name="export empty value",
        command="export TESTVAR= && echo \"[$TESTVAR]\"",
        category="builtins/export",
        bonus=True
    ),
    TestCase(
        name="export multiple vars",
        command="export A=1 B=2 && echo $A $B",
        category="builtins/export",
        bonus=True
    ),
    TestCase(
        name="export with underscore",
        command="export _VAR=test && echo $_VAR",
        category="builtins/export",
        bonus=True
    ),
    TestCase(
        name="export value with spaces",
        command='export TESTVAR="hello world" && echo $TESTVAR',
        category="builtins/export",
        bonus=True
    ),
    TestCase(
        name="export overwrite",
        command="export TESTVAR=first && export TESTVAR=second && echo $TESTVAR",
        category="builtins/export",
        bonus=True
    ),
    # Error cases
    TestCase(
        name="export invalid start digit",
        command="export 1VAR=test",
        category="builtins/export",
        expect_error=True
    ),
    TestCase(
        name="export invalid dash",
        command="export VAR-NAME=test",
        category="builtins/export",
        expect_error=True
    ),
    TestCase(
        name="export no name",
        command="export =value",
        category="builtins/export",
        expect_error=True
    ),
    TestCase(
        name="export empty string",
        command='export ""',
        category="builtins/export",
        expect_error=True
    ),
]

# === Unset Tests ===
UNSET_TESTS = [
    TestCase(
        name="unset existing var",
        command="export TESTVAR=hello && unset TESTVAR && echo \"[$TESTVAR]\"",
        category="builtins/unset",
        bonus=True
    ),
    TestCase(
        name="unset nonexistent var",
        command="unset NONEXISTENT_VAR_12345",
        category="builtins/unset"
    ),
    TestCase(
        name="unset multiple vars",
        command="export A=1 B=2 && unset A B && echo \"[$A][$B]\"",
        category="builtins/unset",
        bonus=True
    ),
    TestCase(
        name="unset no args",
        command="unset",
        category="builtins/unset"
    ),
    TestCase(
        name="unset PATH then ls",
        command="unset PATH && ls",
        category="builtins/unset",
        expect_error=True
    ),
    # Error cases - unset typically silently ignores invalid identifiers
    TestCase(
        name="unset invalid identifier",
        command="unset 1VAR",
        category="builtins/unset"
        # Note: bash doesn't error on this, just ignores it
    ),
]

# === Env Tests ===
ENV_TESTS = [
    TestCase(
        name="env basic",
        command="env | wc -l",
        category="builtins/env",
        skip_stdout_check=True  # Count varies
    ),
    TestCase(
        name="env shows PATH",
        command="env | grep -c PATH",
        category="builtins/env"
    ),
    TestCase(
        name="env shows HOME",
        command="env | grep -c HOME",
        category="builtins/env"
    ),
    TestCase(
        name="env shows USER",
        command="env | grep -c USER",
        category="builtins/env"
    ),
    TestCase(
        name="env after export",
        command="export TESTVAR=hello && env | grep TESTVAR",
        category="builtins/env",
        bonus=True
    ),
    TestCase(
        name="env with args error",
        command="env arg1 arg2",
        category="builtins/env",
        expect_error=True  # Your implementation errors on args
    ),
]

# === Exit Tests ===
EXIT_TESTS = [
    TestCase(
        name="exit basic",
        command="exit",
        category="builtins/exit"
    ),
    TestCase(
        name="exit zero",
        command="exit 0",
        category="builtins/exit",
        expected_exit=0
    ),
    TestCase(
        name="exit one",
        command="exit 1",
        category="builtins/exit",
        expected_exit=1
    ),
    TestCase(
        name="exit 42",
        command="exit 42",
        category="builtins/exit",
        expected_exit=42
    ),
    TestCase(
        name="exit 255",
        command="exit 255",
        category="builtins/exit",
        expected_exit=255
    ),
    TestCase(
        name="exit 256 wraps to 0",
        command="exit 256",
        category="builtins/exit",
        expected_exit=0
    ),
    TestCase(
        name="exit 257 wraps to 1",
        command="exit 257",
        category="builtins/exit",
        expected_exit=1
    ),
    TestCase(
        name="exit negative",
        command="exit -1",
        category="builtins/exit",
        expected_exit=255
    ),
    TestCase(
        name="exit non-numeric",
        command="exit abc",
        category="builtins/exit",
        expect_error=True,
        expected_exit=2
    ),
    TestCase(
        name="exit too many args",
        command="exit 1 2",
        category="builtins/exit",
        expect_error=True
    ),
    TestCase(
        name="exit large overflow",
        command="exit 9999999999999999999",
        category="builtins/exit",
        expect_error=True,
        expected_exit=2
    ),
    TestCase(
        name="exit negative overflow",
        command="exit -9999999999999999999",
        category="builtins/exit",
        expect_error=True,
        expected_exit=2
    ),
    TestCase(
        name="exit with plus sign",
        command="exit +5",
        category="builtins/exit",
        expected_exit=5
    ),
    TestCase(
        name="exit in pipe",
        command="exit 42 | echo hello",
        category="builtins/exit"
        # Exit in pipe runs in subshell
    ),
]


def get_all_builtin_tests() -> list[TestCase]:
    """Return all builtin tests."""
    return (
        ECHO_TESTS +
        PWD_TESTS +
        CD_TESTS +
        EXPORT_TESTS +
        UNSET_TESTS +
        ENV_TESTS +
        EXIT_TESTS
    )