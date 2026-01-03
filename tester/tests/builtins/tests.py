"""Builtin command tests for minishell."""

from config import TestCase

# === Echo Tests ===
ECHO_TESTS = [
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
        name="echo -n then text",
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
        name="echo with quotes",
        command='echo "hello world"',
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
        name="pwd ignore args",
        command="pwd ignored args",
        category="builtins/pwd"
    ),
]

# === Cd Tests ===
CD_TESTS = [
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
        name="cd home tilde",
        command="cd ~ && pwd",
        category="builtins/cd",
        bonus=True  # Tilde expansion might be bonus
    ),
    TestCase(
        name="cd relative path",
        command="cd /tmp && cd .. && pwd",
        category="builtins/cd",
        bonus=True
    ),
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
        name="cd dash previous",
        command="cd /tmp && cd /var && cd - && pwd",
        category="builtins/cd",
        bonus=True
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
    # Tests without && (pipe version)
    TestCase(
        name="cd then pwd pipe",
        command="cd /tmp | pwd",  # pwd runs in subshell, shows original dir
        category="builtins/cd"
    ),
]

# === Export Tests ===
EXPORT_TESTS = [
    TestCase(
        name="export no args",
        command="export",
        category="builtins/export",
        skip_stdout_check=True  # Output varies by environment
    ),
    TestCase(
        name="export simple var",
        command="export TESTVAR=hello && echo $TESTVAR",
        category="builtins/export",
        bonus=True
    ),
    TestCase(
        name="export empty value",
        command="export TESTVAR= && echo $TESTVAR",
        category="builtins/export",
        bonus=True
    ),
    TestCase(
        name="export no value",
        command="export TESTVAR && export | grep TESTVAR",
        category="builtins/export",
        bonus=True,
        skip_stdout_check=True
    ),
    TestCase(
        name="export multiple vars",
        command="export A=1 B=2 && echo $A $B",
        category="builtins/export",
        bonus=True
    ),
    TestCase(
        name="export invalid identifier",
        command="export 1VAR=test",
        category="builtins/export",
        expect_error=True
    ),
    TestCase(
        name="export invalid identifier dash",
        command="export VAR-NAME=test",
        category="builtins/export",
        expect_error=True
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
    TestCase(
        name="export append value",
        command="export TESTVAR=hello && export TESTVAR+=world && echo $TESTVAR",
        category="builtins/export",
        bonus=True  # += might not be required
    ),
]

# === Unset Tests ===
UNSET_TESTS = [
    TestCase(
        name="unset existing var",
        command="export TESTVAR=hello && unset TESTVAR && echo $TESTVAR",
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
        command="export A=1 B=2 && unset A B && echo $A $B",
        category="builtins/unset",
        bonus=True
    ),
    TestCase(
        name="unset no args",
        command="unset",
        category="builtins/unset"
    ),
    TestCase(
        name="unset PATH",
        command="unset PATH && ls",
        category="builtins/unset",
        expect_error=True
    ),
    TestCase(
        name="unset invalid identifier",
        command="unset 1VAR",
        category="builtins/unset",
        expect_error=True
    ),
]

# === Env Tests ===
ENV_TESTS = [
    TestCase(
        name="env basic",
        command="env",
        category="builtins/env",
        skip_stdout_check=True  # Output varies
    ),
    TestCase(
        name="env with grep",
        command="env | grep PATH",
        category="builtins/env"
    ),
    TestCase(
        name="env has HOME",
        command="env | grep HOME",
        category="builtins/env"
    ),
    TestCase(
        name="env has USER",
        command="env | grep USER",
        category="builtins/env"
    ),
    TestCase(
        name="env after export",
        command="export TESTVAR=hello && env | grep TESTVAR",
        category="builtins/env",
        bonus=True
    ),
    TestCase(
        name="env ignores args",
        command="env ignored args | wc -l",
        category="builtins/env",
        skip_stdout_check=True  # Line count varies
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
        name="exit 256 wraps",
        command="exit 256",
        category="builtins/exit",
        expected_exit=0  # 256 % 256 = 0
    ),
    TestCase(
        name="exit negative",
        command="exit -1",
        category="builtins/exit",
        expected_exit=255  # -1 wraps to 255
    ),
    TestCase(
        name="exit non-numeric",
        command="exit abc",
        category="builtins/exit",
        expect_error=True,
        expected_exit=2  # bash returns 2 for non-numeric
    ),
    TestCase(
        name="exit too many args",
        command="exit 1 2",
        category="builtins/exit",
        expect_error=True
    ),
    TestCase(
        name="exit large number",
        command="exit 9999999999999999999",
        category="builtins/exit",
        expect_error=True,
        expected_exit=2
    ),
    TestCase(
        name="exit in pipe",
        command="exit 42 | echo hello",
        category="builtins/exit"
        # Exit in pipe runs in subshell, doesn't exit main shell
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


def get_builtin_tests_by_command(command: str) -> list[TestCase]:
    """Get builtin tests filtered by command name."""
    command_map = {
        "echo": ECHO_TESTS,
        "pwd": PWD_TESTS,
        "cd": CD_TESTS,
        "export": EXPORT_TESTS,
        "unset": UNSET_TESTS,
        "env": ENV_TESTS,
        "exit": EXIT_TESTS,
    }
    return command_map.get(command, [])