"""Execution tests for minishell - command resolution, PATH, permissions."""

from config import TestCase

# === Basic Execution ===
EXEC_BASIC_TESTS = [
    TestCase(
        name="run ls", command="ls", category="execution/basic", skip_stdout_check=True
    ),
    TestCase(
        name="run cat file", command="cat /etc/hostname", category="execution/basic"
    ),
    TestCase(
        name="run true", command="true", category="execution/basic", expected_exit=0
    ),
    TestCase(
        name="run false", command="false", category="execution/basic", expected_exit=1
    ),
    TestCase(
        name="run with args",
        command="ls -la /tmp",
        category="execution/basic",
        skip_stdout_check=True,
    ),
]

# === Absolute Path Execution ===
EXEC_ABSOLUTE_TESTS = [
    TestCase(
        name="absolute path /bin/ls",
        command="/bin/ls /tmp",
        category="execution/absolute",
        skip_stdout_check=True,
    ),
    TestCase(
        name="absolute path /bin/echo",
        command="/bin/echo hello",
        category="execution/absolute",
    ),
    TestCase(
        name="absolute path /bin/cat",
        command="/bin/cat /etc/hostname",
        category="execution/absolute",
    ),
    TestCase(
        name="absolute path /usr/bin/wc",
        command="/usr/bin/wc -c /etc/hostname",
        category="execution/absolute",
        skip_stdout_check=True,
    ),
    TestCase(
        name="absolute path /usr/bin/env",
        command="/usr/bin/env | grep PATH",
        category="execution/absolute",
    ),
    TestCase(
        name="double slash in absolute path",
        command="//bin//echo hello",
        category="execution/absolute",
    ),
    TestCase(
        name="multiple slashes in path",
        command="///bin///echo hello",
        category="execution/absolute",
    ),
]

# === Relative Path Execution ===
EXEC_RELATIVE_TESTS = [
    TestCase(
        name="relative path dot slash",
        commands=["cd /bin", "./echo hello"],
        category="execution/relative",
    ),
    TestCase(
        name="relative path dot dot slash",
        commands=["cd /usr/bin", "../bin/echo hello"],
        category="execution/relative",
    ),
    TestCase(
        name="relative ls current dir",
        commands=["cd /bin", "./ls /tmp"],
        category="execution/relative",
        skip_stdout_check=True,
    ),
]

# === Command Not Found (exit 127) ===
EXEC_NOT_FOUND_TESTS = [
    TestCase(
        name="nonexistent command",
        command="nonexistent_command_12345",
        category="execution/not_found",
        expect_error=True,
        expected_exit=127,
    ),
    TestCase(
        name="typo command",
        command="echoo hello",
        category="execution/not_found",
        expect_error=True,
        expected_exit=127,
    ),
    TestCase(
        name="nonexistent absolute path",
        command="/nonexistent/path/cmd",
        category="execution/not_found",
        expect_error=True,
        expected_exit=127,
    ),
    TestCase(
        name="nonexistent in bin",
        command="/bin/nonexistent_cmd_12345",
        category="execution/not_found",
        expect_error=True,
        expected_exit=127,
    ),
    TestCase(
        name="empty command from var",
        command="$UNSET_VAR_12345",
        category="execution/not_found",
    ),
    TestCase(
        name="dot dot as command",
        command="..",
        category="execution/not_found",
        expect_error=True,
        expected_exit=127,
    ),
    TestCase(
        name="empty quotes command",
        command="''",
        category="execution/not_found",
        expect_error=True,
        expected_exit=127,
    ),
    TestCase(
        name="space in quotes command",
        command="'   '",
        category="execution/not_found",
        expect_error=True,
        expected_exit=127,
    ),
]

# === Permission Denied (exit 126) ===
EXEC_PERMISSION_TESTS = [
    TestCase(
        name="no execute permission",
        command="/etc/passwd",
        category="execution/permissions",
        expect_error=True,
        expected_exit=126,
    ),
    TestCase(
        name="directory as command",
        command="/tmp",
        category="execution/permissions",
        expect_error=True,
        expected_exit=126,
    ),
    TestCase(
        name="directory with trailing slash",
        command="/tmp/",
        category="execution/permissions",
        expect_error=True,
        expected_exit=126,
    ),
    TestCase(
        name="bin directory with trailing slash",
        command="/bin/",
        category="execution/permissions",
        expect_error=True,
        expected_exit=126,
    ),
]

# === PATH Resolution ===
EXEC_PATH_TESTS = [
    TestCase(
        name="command from PATH",
        command="ls --version",
        category="execution/path",
        skip_stdout_check=True,
    ),
    TestCase(
        name="which finds command",
        command="which ls",
        category="execution/path",
        skip_stdout_check=True,
    ),
    TestCase(
        name="multiple commands from PATH",
        command="cat /etc/hostname | grep -c ''",
        category="execution/path",
    ),
]

# === PATH Edge Cases (Multi-command) ===
EXEC_PATH_EDGE_TESTS = [
    TestCase(
        name="unset PATH builtin still works",
        commands=["unset PATH", "echo hello"],
        category="execution/path_edge",
    ),
    TestCase(
        name="unset PATH external cmd fails",
        commands=["unset PATH", "ls"],
        category="execution/path_edge",
        expect_error=True,
        expected_exit=127,
    ),
    TestCase(
        name="unset PATH absolute still works",
        commands=["unset PATH", "/bin/echo hello"],
        category="execution/path_edge",
    ),
    TestCase(
        name="empty PATH external cmd fails",
        commands=["export PATH=", "ls"],
        category="execution/path_edge",
        expect_error=True,
        expected_exit=127,
    ),
    TestCase(
        name="empty PATH absolute still works",
        commands=["export PATH=", "/bin/echo hello"],
        category="execution/path_edge",
    ),
    TestCase(
        name="empty PATH builtin works",
        commands=["export PATH=", "pwd"],
        category="execution/path_edge",
    ),
]

# === Dot Files/Directories ===
EXEC_DOT_TESTS = [
    TestCase(
        name="ls dot", command="ls .", category="execution/dot", skip_stdout_check=True
    ),
    TestCase(
        name="ls dot dot",
        command="ls ..",
        category="execution/dot",
        skip_stdout_check=True,
    ),
    TestCase(
        name="cat dot slash file",
        command="cat ./Makefile | head -1",
        category="execution/dot",
        skip_stdout_check=True,
    ),
]

# === Arguments Handling ===
EXEC_ARGS_TESTS = [
    TestCase(
        name="multiple arguments",
        command="echo a b c d e",
        category="execution/arguments",
    ),
    TestCase(
        name="quoted arguments",
        command='echo "hello world" foo',
        category="execution/arguments",
    ),
    TestCase(
        name="empty string argument",
        command='echo "" hello',
        category="execution/arguments",
    ),
    TestCase(
        name="single quotes arguments",
        command="echo 'hello world' foo",
        category="execution/arguments",
    ),
    TestCase(
        name="mixed quote arguments",
        command="echo \"hello\" 'world' foo",
        category="execution/arguments",
    ),
    TestCase(
        name="argument with special chars quoted",
        command='echo "a|b" "c>d"',
        category="execution/arguments",
    ),
    TestCase(
        name="many arguments",
        command="echo " + " ".join(f"arg{i}" for i in range(20)),
        category="execution/arguments",
    ),
]

# === Environment Passing ===
EXEC_ENV_TESTS = [
    TestCase(
        name="child sees PATH",
        command="env | grep -c PATH",
        category="execution/environment",
    ),
    TestCase(
        name="child sees HOME",
        command="env | grep -c HOME",
        category="execution/environment",
    ),
    TestCase(
        name="child sees USER",
        command="env | grep -c USER",
        category="execution/environment",
    ),
    TestCase(
        name="env passed to command",
        command="/usr/bin/env | grep PATH",
        category="execution/environment",
    ),
]

# === Exit Codes ===
EXEC_EXIT_TESTS = [
    TestCase(
        name="exit code 0 from true",
        command="true",
        category="execution/exit_codes",
        expected_exit=0,
    ),
    TestCase(
        name="exit code 1 from false",
        command="false",
        category="execution/exit_codes",
        expected_exit=1,
    ),
    TestCase(
        name="exit code from grep no match",
        command="echo hello | grep xyz",
        category="execution/exit_codes",
        expected_exit=1,
    ),
    TestCase(
        name="exit code from grep match",
        command="echo hello | grep hello",
        category="execution/exit_codes",
        expected_exit=0,
    ),
    TestCase(
        name="exit code from test fail",
        command="test 1 -eq 2",
        category="execution/exit_codes",
        expected_exit=1,
    ),
    TestCase(
        name="exit code from test success",
        command="test 1 -eq 1",
        category="execution/exit_codes",
        expected_exit=0,
    ),
]

# === Logical Operators (Bonus) ===
EXEC_LOGICAL_TESTS = [
    # Basic && (AND)
    TestCase(
        name="and both succeed",
        command="true && echo success",
        category="execution/logical",
        bonus=True,
    ),
    TestCase(
        name="and first fails",
        command="false && echo success",
        category="execution/logical",
        bonus=True,
    ),
    TestCase(
        name="and chain all succeed",
        command="true && true && echo success",
        category="execution/logical",
        bonus=True,
    ),
    TestCase(
        name="and chain one fails",
        command="true && false && echo success",
        category="execution/logical",
        bonus=True,
        expected_exit=1,
    ),
    # Basic || (OR)
    TestCase(
        name="or first succeeds",
        command="true || echo fallback",
        category="execution/logical",
        bonus=True,
    ),
    TestCase(
        name="or first fails",
        command="false || echo fallback",
        category="execution/logical",
        bonus=True,
    ),
    TestCase(
        name="or chain first succeeds",
        command="true || false || echo fallback",
        category="execution/logical",
        bonus=True,
    ),
    TestCase(
        name="or chain all fail",
        command="false || false || echo fallback",
        category="execution/logical",
        bonus=True,
    ),
    # Mixed && and ||
    TestCase(
        name="and then or",
        command="false && echo no || echo fallback",
        category="execution/logical",
        bonus=True,
    ),
    TestCase(
        name="or then and",
        command="false || true && echo success",
        category="execution/logical",
        bonus=True,
    ),
    # Exit status propagation
    TestCase(
        name="and preserves exit status",
        command="false && true",
        category="execution/logical",
        bonus=True,
        expected_exit=1,
    ),
    TestCase(
        name="or preserves exit status",
        command="true || false",
        category="execution/logical",
        bonus=True,
        expected_exit=0,
    ),
]

# === Subshell Execution (Bonus) ===
EXEC_SUBSHELL_TESTS = [
    TestCase(
        name="subshell basic",
        command="(echo hello)",
        category="execution/subshell",
        bonus=True,
    ),
    TestCase(
        name="subshell exit status",
        command="(false)",
        category="execution/subshell",
        bonus=True,
        expected_exit=1,
    ),
    TestCase(
        name="subshell with and",
        command="(true && echo success)",
        category="execution/subshell",
        bonus=True,
    ),
    TestCase(
        name="subshell with or",
        command="(false || echo fallback)",
        category="execution/subshell",
        bonus=True,
    ),
    TestCase(
        name="subshell nested",
        command="( (echo hello) )",
        category="execution/subshell",
        bonus=True,
    ),
    TestCase(
        name="subshell does not affect parent",
        commands=["(cd /tmp)", "pwd"],
        category="execution/subshell",
        bonus=True,
    ),
    TestCase(
        name="subshell with logical after",
        command="(false) || echo recovered",
        category="execution/subshell",
        bonus=True,
    ),
    TestCase(
        name="subshell grouping priority",
        command="(true || false) && echo success",
        category="execution/subshell",
        bonus=True,
    ),
]


def get_all_execution_tests() -> list[TestCase]:
    """Return all execution tests."""
    return (
        EXEC_BASIC_TESTS
        + EXEC_ABSOLUTE_TESTS
        + EXEC_RELATIVE_TESTS
        + EXEC_NOT_FOUND_TESTS
        + EXEC_PERMISSION_TESTS
        + EXEC_PATH_TESTS
        + EXEC_PATH_EDGE_TESTS
        + EXEC_DOT_TESTS
        + EXEC_ARGS_TESTS
        + EXEC_ENV_TESTS
        + EXEC_EXIT_TESTS
        + EXEC_LOGICAL_TESTS
        + EXEC_SUBSHELL_TESTS
    )

