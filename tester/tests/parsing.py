"""Parsing tests for minishell - quotes and variable expansion only.

These tests focus on tokenization, quote handling, and variable expansion.
They require only: lexer + parser + expander + ability to run echo.

Syntax error tests are in syntax.py (separate category).
Pipe and redirection tests are in their own categories.
"""

from config import TestCase

# === Basic Quote Handling ===
QUOTE_BASIC_TESTS = [
    TestCase(
        name="single quotes basic",
        command="echo 'hello world'",
        category="parsing/quotes",
    ),
    TestCase(
        name="double quotes basic",
        command='echo "hello world"',
        category="parsing/quotes",
    ),
    TestCase(name="empty single quotes", command="echo ''", category="parsing/quotes"),
    TestCase(name="empty double quotes", command='echo ""', category="parsing/quotes"),
    TestCase(
        name="adjacent single quotes",
        command="echo 'hel''lo'",
        category="parsing/quotes",
    ),
    TestCase(
        name="adjacent double quotes",
        command='echo "hel""lo"',
        category="parsing/quotes",
    ),
    TestCase(
        name="mixed adjacent quotes",
        command="echo \"hel\"'lo'",
        category="parsing/quotes",
    ),
    TestCase(
        name="single quote in double",
        command='echo "it\'s working"',
        category="parsing/quotes",
    ),
    TestCase(
        name="double quote in single",
        command="echo 'say \"hello\"'",
        category="parsing/quotes",
    ),
]

# === Quote Whitespace Preservation ===
QUOTE_WHITESPACE_TESTS = [
    TestCase(
        name="quotes preserve spaces",
        command='echo "   spaces   "',
        category="parsing/quotes",
    ),
    TestCase(
        name="multiple spaces in quotes",
        command='echo "a    b    c"',
        category="parsing/quotes",
    ),
    TestCase(
        name="leading spaces in quotes",
        command='echo "   hello"',
        category="parsing/quotes",
    ),
    TestCase(
        name="trailing spaces in quotes",
        command='echo "hello   "',
        category="parsing/quotes",
    ),
    TestCase(
        name="only spaces in quotes", command='echo "     "', category="parsing/quotes"
    ),
]

# === Quote Mixing Within Words ===
QUOTE_MIXING_TESTS = [
    TestCase(
        name="single quote inside double",
        command='echo "wor\'ld"',
        category="parsing/quotes",
    ),
    TestCase(
        name="double quote inside single",
        command="echo 'wor\"ld'",
        category="parsing/quotes",
    ),
    TestCase(
        name="alternating quotes same word",
        command='echo "a"\'b\'"c"',
        category="parsing/quotes",
    ),
    TestCase(
        name="quoted then unquoted",
        command='echo "hello"world',
        category="parsing/quotes",
    ),
    TestCase(
        name="unquoted then quoted",
        command='echo hello"world"',
        category="parsing/quotes",
    ),
    TestCase(
        name="empty quotes mixed with text",
        command='echo ""hello""world""',
        category="parsing/quotes",
    ),
    TestCase(
        name="complex mixed quotes",
        command="echo \"a\"'b'\"c\"'d'",
        category="parsing/quotes",
    ),
]

# === Special Characters in Quotes ===
QUOTE_SPECIAL_CHARS_TESTS = [
    TestCase(
        name="pipe symbol in quotes",
        command="echo 'hello | world'",
        category="parsing/quotes",
    ),
    TestCase(
        name="redirect in quotes", command='echo "a > b"', category="parsing/quotes"
    ),
    TestCase(
        name="ampersand in quotes", command="echo 'a && b'", category="parsing/quotes"
    ),
    TestCase(
        name="semicolon in quotes", command="echo 'a;b;c'", category="parsing/quotes"
    ),
    TestCase(
        name="parentheses in quotes",
        command='echo "(hello)"',
        category="parsing/quotes",
    ),
    TestCase(
        name="brackets in quotes", command="echo '[test]'", category="parsing/quotes"
    ),
    TestCase(
        name="backslash in single quotes",
        command="echo 'hello\\world'",
        category="parsing/quotes",
    ),
    TestCase(name="asterisk in quotes", command="echo '*'", category="parsing/quotes"),
    TestCase(
        name="question mark in quotes", command="echo '?'", category="parsing/quotes"
    ),
    TestCase(
        name="multiple special chars",
        command='echo "| > < & * ?"',
        category="parsing/quotes",
    ),
    TestCase(
        name="dollar sign in single quotes",
        command="echo '$HOME $USER'",
        category="parsing/quotes",
    ),
]

# === Weird Quote Combinations ===
QUOTE_WEIRD_TESTS = [
    TestCase(
        name="many empty quotes", command='echo "" "" "" ""', category="parsing/quotes"
    ),
    TestCase(
        name="alternating empty quotes",
        command="echo \"\"''\"\"''",
        category="parsing/quotes",
    ),
    TestCase(
        name="six consecutive quotes", command='echo """"""', category="parsing/quotes"
    ),
    TestCase(
        name="multiple quoted args",
        command='echo "one" "two" "three"',
        category="parsing/quotes",
    ),
]

# Combine all quote tests
QUOTE_TESTS = (
    QUOTE_BASIC_TESTS
    + QUOTE_WHITESPACE_TESTS
    + QUOTE_MIXING_TESTS
    + QUOTE_SPECIAL_CHARS_TESTS
    + QUOTE_WEIRD_TESTS
)

# === Basic Variable Expansion ===
EXPANSION_BASIC_TESTS = [
    TestCase(name="expand USER", command="echo $USER", category="parsing/expansion"),
    TestCase(name="expand HOME", command="echo $HOME", category="parsing/expansion"),
    TestCase(
        name="expand PATH",
        command="echo $PATH | wc -c",
        category="parsing/expansion",
        skip_stdout_check=True,  # Length varies
    ),
    TestCase(
        name="expand unset var",
        command="echo $UNSET_VAR_12345",
        category="parsing/expansion",
    ),
    TestCase(
        name="expand exit status", command="echo $?", category="parsing/expansion"
    ),
]

# === Expansion in Quotes ===
EXPANSION_QUOTES_TESTS = [
    TestCase(
        name="expand in double quotes",
        command='echo "$USER"',
        category="parsing/expansion",
    ),
    TestCase(
        name="no expand in single quotes",
        command="echo '$USER'",
        category="parsing/expansion",
    ),
    TestCase(
        name="expand with text before",
        command='echo "hello$USER"',
        category="parsing/expansion",
    ),
    TestCase(
        name="expand with text after",
        command='echo "$USER world"',
        category="parsing/expansion",
    ),
    TestCase(
        name="expand multiple vars",
        command='echo "$USER $HOME"',
        category="parsing/expansion",
    ),
    TestCase(
        name="var with surrounding text",
        command='echo "user:$USER:end"',
        category="parsing/expansion",
    ),
    TestCase(
        name="var in single quotes literal",
        command="echo 'user:$USER:end'",
        category="parsing/expansion",
    ),
    TestCase(
        name="empty var in quotes",
        command='echo "value:$UNSET_VAR_12345:end"',
        category="parsing/expansion",
    ),
]

# === Expansion Edge Cases ===
EXPANSION_EDGE_TESTS = [
    TestCase(name="dollar at end", command="echo hello$", category="parsing/expansion"),
    TestCase(
        name="dollar at end in quotes", command='echo "$"', category="parsing/expansion"
    ),
    TestCase(name="dollar space", command="echo $ hello", category="parsing/expansion"),
    TestCase(
        name="double dollar",
        command="echo $$",
        category="parsing/expansion",
        skip_stdout_check=True,  # PID varies
    ),
    TestCase(
        name="double dollar in quotes",
        command='echo "$$"',
        category="parsing/expansion",
        skip_stdout_check=True,
    ),
    TestCase(
        name="dollar question dollar", command="echo $?$?", category="parsing/expansion"
    ),
    TestCase(
        name="dollar followed by number",
        command="echo $1",
        category="parsing/expansion",
    ),
    TestCase(
        name="dollar followed by number and text",
        command="echo $1abc",
        category="parsing/expansion",
    ),
    TestCase(
        name="dollar in middle of word",
        command="echo hello$USER world",
        category="parsing/expansion",
    ),
    TestCase(
        name="quoted dollar sign", command="echo '$'", category="parsing/expansion"
    ),
    TestCase(
        name="mixed quoted unquoted exit status",
        command="echo '$?'$?",
        category="parsing/expansion",
    ),
    TestCase(
        name="var with quote after",
        command='echo $USER"s home"',
        category="parsing/expansion",
    ),
    TestCase(
        name="empty quotes around var",
        command='echo ""$USER""',
        category="parsing/expansion",
    ),
    TestCase(
        name="consecutive vars no space",
        command="echo $USER$HOME",
        category="parsing/expansion",
    ),
    TestCase(
        name="var between text no spaces",
        command="echo prefix$USER suffix",
        category="parsing/expansion",
    ),
]

# Combine all expansion tests
EXPANSION_TESTS = EXPANSION_BASIC_TESTS + EXPANSION_QUOTES_TESTS + EXPANSION_EDGE_TESTS

# === Tokenization / Whitespace ===
TOKENIZATION_TESTS = [
    TestCase(
        name="multiple spaces between args",
        command="echo    hello    world",
        category="parsing/tokenization",
    ),
    TestCase(
        name="leading whitespace",
        command="   echo hello",
        category="parsing/tokenization",
    ),
    TestCase(
        name="trailing whitespace",
        command="echo hello   ",
        category="parsing/tokenization",
    ),
    TestCase(name="only whitespace", command="   ", category="parsing/tokenization"),
    TestCase(name="empty command", command="", category="parsing/tokenization"),
]

# === Edge Cases ===
EDGE_CASE_TESTS = [
    TestCase(
        name="empty string argument",
        command='echo "" hello',
        category="parsing/edge_cases",
    ),
    TestCase(
        name="multiple empty strings",
        command='echo "" "" hello ""',
        category="parsing/edge_cases",
    ),
    TestCase(
        name="unset var disappears",
        command="echo a$UNSET_VAR_12345 b",
        category="parsing/edge_cases",
    ),
    TestCase(
        name="quoted unset var kept",
        command='echo "$UNSET_VAR_12345"',
        category="parsing/edge_cases",
    ),
    TestCase(
        name="very long argument",
        command="echo " + "a" * 1000,
        category="parsing/edge_cases",
    ),
    TestCase(
        name="many arguments",
        command="echo " + " ".join(f"arg{i}" for i in range(100)),
        category="parsing/edge_cases",
    ),
    TestCase(
        name="command is empty quotes",
        command='""',
        category="parsing/edge_cases",
        expect_error=True,
    ),
]


def get_all_parsing_tests() -> list[TestCase]:
    """Return all parsing tests (quotes, expansion, tokenization)."""
    return QUOTE_TESTS + EXPANSION_TESTS + TOKENIZATION_TESTS + EDGE_CASE_TESTS

