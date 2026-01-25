"""Redirection tests for minishell."""

from config import TestCase

# === Output Redirection (>) ===
REDIR_OUT_TESTS = [
    TestCase(
        name="redirect out basic",
        command="echo hello > /tmp/ms_test_out && cat /tmp/ms_test_out",
        category="redirections/output",
        bonus=True,
    ),
    TestCase(
        name="redirect out creates file",
        command="echo test > /tmp/ms_newfile && ls /tmp/ms_newfile",
        category="redirections/output",
        bonus=True,
    ),
    TestCase(
        name="redirect out overwrites",
        command="echo first > /tmp/ms_over && echo second > /tmp/ms_over && cat /tmp/ms_over",
        category="redirections/output",
        bonus=True,
    ),
    TestCase(
        name="redirect out no spaces",
        command="echo hello>/tmp/ms_nospace && cat /tmp/ms_nospace",
        category="redirections/output",
        bonus=True,
    ),
    TestCase(
        name="redirect out with pipe after",
        command="echo hello > /tmp/ms_pipeout && cat /tmp/ms_pipeout | cat",
        category="redirections/output",
        bonus=True,
    ),
]

# === Append Redirection (>>) ===
REDIR_APPEND_TESTS = [
    TestCase(
        name="append basic",
        command="echo first > /tmp/ms_app && echo second >> /tmp/ms_app && cat /tmp/ms_app",
        category="redirections/append",
        bonus=True,
    ),
    TestCase(
        name="append creates file",
        command="echo test >> /tmp/ms_appnew && cat /tmp/ms_appnew",
        category="redirections/append",
        bonus=True,
    ),
    TestCase(
        name="append multiple",
        command="echo a >> /tmp/ms_multi && echo b >> /tmp/ms_multi && cat /tmp/ms_multi",
        category="redirections/append",
        bonus=True,
    ),
]

# === Input Redirection (<) ===
REDIR_IN_TESTS = [
    TestCase(
        name="redirect in basic",
        command="cat < /etc/hostname",
        category="redirections/input",
    ),
    TestCase(
        name="redirect in with wc",
        command="wc -l < /etc/passwd",
        category="redirections/input",
        skip_stdout_check=True,
    ),
    TestCase(
        name="redirect in nonexistent",
        command="cat < /nonexistent_file_12345",
        category="redirections/input",
        expect_error=True,
    ),
    TestCase(
        name="redirect in quoted filename",
        command='cat < "/etc/hostname"',
        category="redirections/input",
    ),
    TestCase(
        name="redirect in no space",
        command="cat</etc/hostname",
        category="redirections/input",
    ),
]

# === Combined Redirections ===
REDIR_COMBINED_TESTS = [
    TestCase(
        name="redirect in and out",
        command="cat < /etc/hostname > /tmp/ms_copy && cat /tmp/ms_copy",
        category="redirections/combined",
        bonus=True,
    ),
    TestCase(
        name="input redirect before command",
        command="< /etc/hostname cat",
        category="redirections/combined",
    ),
    TestCase(
        name="output redirect before command",
        command="> /tmp/ms_before echo hello && cat /tmp/ms_before",
        category="redirections/combined",
        bonus=True,
    ),
    TestCase(
        name="redirect in middle of args",
        command="echo hello > /tmp/ms_mid world && cat /tmp/ms_mid",
        category="redirections/combined",
        bonus=True,
    ),
]

# === Redirections with Pipes ===
REDIR_PIPE_TESTS = [
    TestCase(
        name="pipe then redirect out",
        command="echo hello | cat > /tmp/ms_pout && cat /tmp/ms_pout",
        category="redirections/pipes",
        bonus=True,
    ),
    TestCase(
        name="redirect in then pipe",
        command="cat < /etc/hostname | wc -c",
        category="redirections/pipes",
    ),
    TestCase(
        name="redirect in piped to grep",
        command="cat < /etc/hostname | cat",
        category="redirections/pipes",
    ),
]

# === Redirection Errors ===
REDIR_ERROR_TESTS = [
    TestCase(
        name="redirect out to directory",
        command="echo test > /tmp",
        category="redirections/errors",
        expect_error=True,
    ),
    TestCase(
        name="redirect out no permission",
        command="echo test > /etc/test_noperm",
        category="redirections/errors",
        expect_error=True,
    ),
    TestCase(
        name="redirect in directory",
        command="cat < /tmp",
        category="redirections/errors",
        expect_error=True,
    ),
    TestCase(
        name="redirect in no permission",
        command="cat < /etc/shadow",
        category="redirections/errors",
        expect_error=True,
    ),
]

# === Multiple Redirections ===
REDIR_MULTIPLE_TESTS = [
    TestCase(
        name="multiple output redirects",
        command="echo test > /tmp/ms_m1 > /tmp/ms_m2 && cat /tmp/ms_m2",
        category="redirections/multiple",
        bonus=True,
    ),
    TestCase(
        name="multiple input redirects",
        command="cat < /etc/hostname < /etc/hosts | head -1",
        category="redirections/multiple",
    ),
]


def get_all_redirection_tests() -> list[TestCase]:
    """Return all redirection tests."""
    return (
        REDIR_OUT_TESTS
        + REDIR_APPEND_TESTS
        + REDIR_IN_TESTS
        + REDIR_COMBINED_TESTS
        + REDIR_PIPE_TESTS
        + REDIR_ERROR_TESTS
        + REDIR_MULTIPLE_TESTS
    )
