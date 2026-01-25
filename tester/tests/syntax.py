"""Syntax error tests for minishell.

These tests verify that minishell properly detects and reports syntax errors.
All syntax errors should:
- Print an error message to stderr
- Return exit code 2

Run these tests early - they only require tokenization/parsing, not execution.
"""

from config import TestCase

# === Unclosed Quote Errors ===
UNCLOSED_QUOTE_TESTS = [
    TestCase(
        name="unclosed single quote",
        command="echo 'hello",
        category="syntax/quotes",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="unclosed double quote",
        command='echo "hello',
        category="syntax/quotes",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="unclosed quote at end",
        command="echo hello'",
        category="syntax/quotes",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="unclosed quote in middle",
        command="echo hello 'world",
        category="syntax/quotes",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="unclosed double quote in middle",
        command='echo "hello world',
        category="syntax/quotes",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="multiple unclosed quotes",
        command="echo 'hello \"world",
        category="syntax/quotes",
        expect_error=True,
        expected_exit=2,
    ),
]

# === Pipe Syntax Errors ===
PIPE_SYNTAX_TESTS = [
    TestCase(
        name="pipe at start",
        command="| echo hello",
        category="syntax/pipe",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="pipe at end",
        command="echo hello |",
        category="syntax/pipe",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="double pipe",
        command="echo hello | | cat",
        category="syntax/pipe",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="pipe only",
        command="|",
        category="syntax/pipe",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="triple pipe",
        command="echo | | | cat",
        category="syntax/pipe",
        expect_error=True,
        expected_exit=2,
    ),
]

# === Redirection Syntax Errors ===
REDIR_SYNTAX_TESTS = [
    TestCase(
        name="redirect out no target",
        command="echo hello >",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="redirect in no target",
        command="cat <",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="append no target",
        command="echo hello >>",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="heredoc no delimiter",
        command="cat <<",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="double redirect out",
        command="echo hello > > file",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="double redirect in",
        command="cat < < file",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="redirect to pipe",
        command="echo hello > |",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="redirect from pipe",
        command="cat < |",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="redirect to redirect",
        command="echo > < file",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="heredoc no delimiter spaces",
        command="cat << ",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="append to pipe",
        command="echo hello >> |",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
    TestCase(
        name="heredoc to pipe",
        command="cat << |",
        category="syntax/redirect",
        expect_error=True,
        expected_exit=2,
    ),
]

# === Parentheses Syntax Errors (Bonus) ===
PAREN_SYNTAX_TESTS = [
    TestCase(
        name="unmatched open paren",
        command="(echo hello",
        category="syntax/parentheses",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
    TestCase(
        name="unmatched close paren",
        command="echo hello)",
        category="syntax/parentheses",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
    TestCase(
        name="empty parentheses",
        command="()",
        category="syntax/parentheses",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
    TestCase(
        name="nested unmatched",
        command="((echo hello)",
        category="syntax/parentheses",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
    TestCase(
        name="paren with only pipe",
        command="(|)",
        category="syntax/parentheses",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
]

# === Logical Operator Syntax Errors (Bonus) ===
LOGICAL_SYNTAX_TESTS = [
    TestCase(
        name="and at start",
        command="&& echo hello",
        category="syntax/logical",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
    TestCase(
        name="and at end",
        command="echo hello &&",
        category="syntax/logical",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
    TestCase(
        name="or at start",
        command="|| echo hello",
        category="syntax/logical",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
    TestCase(
        name="or at end",
        command="echo hello ||",
        category="syntax/logical",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
    TestCase(
        name="double and",
        command="echo a && && echo b",
        category="syntax/logical",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
    TestCase(
        name="and or adjacent",
        command="echo a && || echo b",
        category="syntax/logical",
        expect_error=True,
        expected_exit=2,
        bonus=True,
    ),
]


MISC_SYNTAX_TESTS = []


def get_all_syntax_tests() -> list[TestCase]:
    """Return all syntax error tests."""
    return (
        UNCLOSED_QUOTE_TESTS
        + PIPE_SYNTAX_TESTS
        + REDIR_SYNTAX_TESTS
        + PAREN_SYNTAX_TESTS
        + LOGICAL_SYNTAX_TESTS
        + MISC_SYNTAX_TESTS
    )


def get_mandatory_syntax_tests() -> list[TestCase]:
    """Return only mandatory syntax error tests (no bonus)."""
    all_tests = get_all_syntax_tests()
    return [t for t in all_tests if not t.bonus]

