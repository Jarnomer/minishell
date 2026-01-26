"""Pipe tests for minishell."""

from config import TestCase

PIPE_BASIC_TESTS = [
    TestCase(
        name="pipe simple",
        command="echo hello | cat",
        category="pipes/basic"
    ),
    TestCase(
        name="pipe with grep",
        command="echo hello world | grep hello",
        category="pipes/basic",
    ),
    TestCase(
        name="pipe with wc",
        command="echo hello | wc -c",
        category="pipes/basic"
    ),
    TestCase(
        name="pipe preserves output",
        command="echo hello | cat | cat",
        category="pipes/basic",
    ),
    TestCase(
        name="pipe no match grep",
        command="echo hello | grep xyz",
        category="pipes/basic",
        expected_exit=1,
    ),
]

PIPE_MULTIPLE_TESTS = [
    TestCase(
        name="pipe three commands",
        command="echo hello world | cat | cat",
        category="pipes/multiple",
    ),
    TestCase(
        name="pipe four commands",
        command="echo hello | cat | cat | cat",
        category="pipes/multiple",
    ),
    TestCase(
        name="pipe five commands",
        command="echo test | cat | cat | cat | cat",
        category="pipes/multiple",
    ),
    TestCase(
        name="pipe long chain",
        command="echo abc | cat | cat | cat | cat | cat | cat",
        category="pipes/multiple",
    ),
]

PIPE_EXIT_TESTS = [
    TestCase(
        name="pipe exit from last true",
        command="false | true",
        category="pipes/exit_status",
        expected_exit=0,
    ),
    TestCase(
        name="pipe exit from last false",
        command="true | false",
        category="pipes/exit_status",
        expected_exit=1,
    ),
    TestCase(
        name="pipe exit from grep fail",
        command="echo hello | grep xyz",
        category="pipes/exit_status",
        expected_exit=1,
    ),
    TestCase(
        name="pipe exit from grep success",
        command="echo hello | grep hello",
        category="pipes/exit_status",
        expected_exit=0,
    ),
    TestCase(
        name="pipe middle fails",
        command="echo test | false | cat",
        category="pipes/exit_status",
        expected_exit=0,
    ),
    TestCase(
        name="pipe all fail except last",
        command="false | false | true",
        category="pipes/exit_status",
        expected_exit=0,
    ),
    TestCase(
        name="pipe command not found",
        command="notexist42 | echo hello",
        category="pipes/exit_status",
        expected_exit=0,
    ),
    TestCase(
        name="pipe to command not found",
        command="echo hello | notexist42",
        category="pipes/exit_status",
        expected_exit=127,
    ),
]

PIPE_BUILTIN_TESTS = [
    TestCase(
        name="pipe echo to cat",
        command="echo hello | cat",
        category="pipes/builtins"
    ),
    TestCase(
        name="pipe echo to wc",
        command="echo hello world | wc -w",
        category="pipes/builtins",
    ),
    TestCase(
        name="pipe pwd to cat",
        command="pwd | cat",
        category="pipes/builtins"
    ),
    TestCase(
        name="pipe env to grep",
        command="env | grep PATH",
        category="pipes/builtins"
    ),
    TestCase(
        name="pipe env to wc",
        command="env | wc -l",
        category="pipes/builtins",
        skip_stdout_check=True,
    ),
    TestCase(
        name="pipe export to grep",
        command="export | grep PATH",
        category="pipes/builtins",
    ),
    TestCase(
        name="pipe echo -n to cat",
        command="echo -n hello | cat",
        category="pipes/builtins",
    ),
]

PIPE_EDGE_TESTS = [
    TestCase(
        name="pipe no spaces",
        command="echo hello|cat",
        category="pipes/edge_cases"
    ),
    TestCase(
        name="pipe only left space",
        command="echo hello |cat",
        category="pipes/edge_cases",
    ),
    TestCase(
        name="pipe only right space",
        command="echo hello| cat",
        category="pipes/edge_cases",
    ),
    TestCase(
        name="pipe with double quotes",
        command='echo "hello world" | cat',
        category="pipes/edge_cases",
    ),
    TestCase(
        name="pipe with single quotes",
        command="echo 'hello world' | cat",
        category="pipes/edge_cases",
    ),
    TestCase(
        name="pipe empty echo",
        command="echo | cat",
        category="pipes/edge_cases"
    ),
    TestCase(
        name="pipe echo -n empty",
        command="echo -n | cat",
        category="pipes/edge_cases"
    ),
    TestCase(
        name="pipe cat /dev/null",
        command="cat /dev/null | cat",
        category="pipes/edge_cases",
    ),
    TestCase(
        name="pipe with variable",
        command="echo $USER | cat",
        category="pipes/edge_cases",
    ),
    TestCase(
        name="pipe with expansion in quotes",
        command="echo '$USER' | cat",
        category="pipes/edge_cases",
    ),
    TestCase(
        name="pipe with expansion in quotes",
        command='echo "$USER" | cat',
        category="pipes/edge_cases",
    ),
    TestCase(
        name="pipe multiple args",
        command="echo one two three | cat",
        category="pipes/edge_cases",
    ),
]

PIPE_SUBSHELL_TESTS = [
    TestCase(
        name="pipe from subshell",
        command="(echo hello) | cat",
        category="pipes/subshell",
        bonus=True,
    ),
    TestCase(
        name="pipe to subshell",
        command="echo hello | (cat)",
        category="pipes/subshell",
        bonus=True,
    ),
    TestCase(
        name="pipe subshell both sides",
        command="(echo hello) | (cat)",
        category="pipes/subshell",
        bonus=True,
    ),
    TestCase(
        name="pipe with and after",
        command="echo hello | cat && echo done",
        category="pipes/subshell",
        bonus=True,
    ),
    TestCase(
        name="pipe with or after",
        command="echo hello | grep xyz || echo fallback",
        category="pipes/subshell",
        bonus=True,
    ),
]


def get_all_pipe_tests() -> list[TestCase]:
    """Return all pipe tests."""
    return (
        PIPE_BASIC_TESTS
        + PIPE_MULTIPLE_TESTS
        + PIPE_EXIT_TESTS
        + PIPE_BUILTIN_TESTS
        + PIPE_EDGE_TESTS
        + PIPE_SUBSHELL_TESTS
    )

