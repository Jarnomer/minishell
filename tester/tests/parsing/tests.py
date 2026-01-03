"""Parsing tests for minishell - quotes, tokenization, expansion."""

from config import TestCase

# === Quote Handling ===
QUOTE_TESTS = [
    # Basic quotes
    TestCase(
        name="single quotes basic",
        command="echo 'hello world'",
        category="parsing/quotes"
    ),
    TestCase(
        name="double quotes basic", 
        command='echo "hello world"',
        category="parsing/quotes"
    ),
    TestCase(
        name="empty single quotes",
        command="echo ''",
        category="parsing/quotes"
    ),
    TestCase(
        name="empty double quotes",
        command='echo ""',
        category="parsing/quotes"
    ),
    TestCase(
        name="adjacent quotes",
        command="echo 'hel''lo'",
        category="parsing/quotes"
    ),
    TestCase(
        name="mixed adjacent quotes",
        command='echo "hel"\'lo\'',
        category="parsing/quotes"
    ),
    TestCase(
        name="single quote in double",
        command='echo "it\'s working"',
        category="parsing/quotes"
    ),
    TestCase(
        name="double quote in single",
        command="echo 'say \"hello\"'",
        category="parsing/quotes"
    ),
    TestCase(
        name="quotes preserve spaces",
        command='echo "   spaces   "',
        category="parsing/quotes"
    ),
    TestCase(
        name="quotes preserve whitespace",
        command='echo "  a  b  c  "',
        category="parsing/quotes"
    ),
    TestCase(
        name="multiple quoted args",
        command='echo "one" "two" "three"',
        category="parsing/quotes"
    ),
    TestCase(
        name="quote then unquoted",
        command='echo "hello"world',
        category="parsing/quotes"
    ),
    TestCase(
        name="unquoted then quote",
        command='echo hello"world"',
        category="parsing/quotes"
    ),
    TestCase(
        name="complex mixed quotes",
        command='echo "a"\'b\'"c"\'d\'',
        category="parsing/quotes"
    ),
]

# === Unclosed Quotes (Syntax Errors) ===
UNCLOSED_QUOTE_TESTS = [
    TestCase(
        name="unclosed single quote",
        command="echo 'hello",
        category="parsing/syntax_errors",
        expect_error=True
    ),
    TestCase(
        name="unclosed double quote",
        command='echo "hello',
        category="parsing/syntax_errors",
        expect_error=True
    ),
    TestCase(
        name="unclosed quote in middle",
        command="echo hello 'world",
        category="parsing/syntax_errors",
        expect_error=True
    ),
    TestCase(
        name="unclosed nested quote attempt",
        command='echo "hello \'world"\'',
        category="parsing/syntax_errors",
        expect_error=True
    ),
]

# === Variable Expansion ===
EXPANSION_TESTS = [
    # Basic expansion
    TestCase(
        name="expand PATH",
        command="echo $PATH",
        category="parsing/expansion"
    ),
    TestCase(
        name="expand HOME",
        command="echo $HOME",
        category="parsing/expansion"
    ),
    TestCase(
        name="expand USER",
        command="echo $USER",
        category="parsing/expansion"
    ),
    TestCase(
        name="expand unset var",
        command="echo $UNSET_VAR_12345",
        category="parsing/expansion"
    ),
    TestCase(
        name="expand exit status",
        command="echo $?",
        category="parsing/expansion"
    ),
    TestCase(
        name="expand exit status after true",
        command="true; echo $?",
        category="parsing/expansion",
        bonus=True  # Requires semicolon
    ),
    TestCase(
        name="expand exit status after false",
        command="false; echo $?",
        category="parsing/expansion",
        bonus=True
    ),
    # Expansion in quotes
    TestCase(
        name="expand in double quotes",
        command='echo "$USER"',
        category="parsing/expansion"
    ),
    TestCase(
        name="no expand in single quotes",
        command="echo '$USER'",
        category="parsing/expansion"
    ),
    TestCase(
        name="expand with text before",
        command='echo "hello$USER"',
        category="parsing/expansion"
    ),
    TestCase(
        name="expand with text after",
        command='echo "$USER world"',
        category="parsing/expansion"
    ),
    TestCase(
        name="expand multiple vars",
        command='echo "$USER $HOME"',
        category="parsing/expansion"
    ),
    # Edge cases
    TestCase(
        name="dollar at end",
        command="echo hello$",
        category="parsing/expansion"
    ),
    TestCase(
        name="dollar space",
        command="echo $ hello",
        category="parsing/expansion"
    ),
    TestCase(
        name="double dollar",
        command="echo $$",
        category="parsing/expansion",
        skip_stdout_check=True  # PID varies
    ),
    TestCase(
        name="dollar question dollar",
        command="echo $?$?",
        category="parsing/expansion"
    ),
    TestCase(
        name="var with underscore",
        command="echo $_",
        category="parsing/expansion",
        skip_stdout_check=True  # Implementation specific
    ),
    TestCase(
        name="dollar followed by number",
        command="echo $4",
        category="parsing/expansion"
    ),
    TestCase(
        name="dollar followed by number and text",
        command="echo $42",
        category="parsing/expansion"
    ),
    TestCase(
        name="dollar in middle of word",
        command="echo hello$USER world",
        category="parsing/expansion"
    ),
    TestCase(
        name="empty quotes around var",
        command='echo ""$USER""',
        category="parsing/expansion"
    ),
    TestCase(
        name="quoted dollar sign",
        command="echo '$'",
        category="parsing/expansion"
    ),
]

# === Tokenization ===
TOKENIZATION_TESTS = [
    # Whitespace handling
    TestCase(
        name="multiple spaces",
        command="echo    hello    world",
        category="parsing/tokenization"
    ),
    TestCase(
        name="leading whitespace",
        command="   echo hello",
        category="parsing/tokenization"
    ),
    TestCase(
        name="trailing whitespace",
        command="echo hello   ",
        category="parsing/tokenization"
    ),
    TestCase(
        name="only whitespace",
        command="   ",
        category="parsing/tokenization"
    ),
    TestCase(
        name="empty command",
        command="",
        category="parsing/tokenization"
    ),
]

# === Operator Parsing ===
OPERATOR_TESTS = [
    # Pipes
    TestCase(
        name="simple pipe",
        command="echo hello | cat",
        category="parsing/operators"
    ),
    TestCase(
        name="pipe no spaces",
        command="echo hello|cat",
        category="parsing/operators"
    ),
    TestCase(
        name="pipe only left space",
        command="echo hello |cat",
        category="parsing/operators"
    ),
    TestCase(
        name="pipe only right space",
        command="echo hello| cat",
        category="parsing/operators"
    ),
    TestCase(
        name="multiple pipes",
        command="echo hello | cat | cat | cat",
        category="parsing/operators"
    ),
    # Redirections - output
    TestCase(
        name="redirect out",
        command="echo hello > /tmp/test_out",
        category="parsing/operators"
    ),
    TestCase(
        name="redirect out no space",
        command="echo hello>/tmp/test_out",
        category="parsing/operators"
    ),
    TestCase(
        name="redirect append",
        command="echo hello >> /tmp/test_out",
        category="parsing/operators"
    ),
    TestCase(
        name="multiple redirect out",
        command="echo hello > /tmp/test1 > /tmp/test2",
        category="parsing/operators"
    ),
    # Redirections - input
    TestCase(
        name="redirect in",
        command="cat < /etc/hostname",
        category="parsing/operators"
    ),
    TestCase(
        name="redirect in quoted filename",
        command='cat < "/etc/hostname"',
        category="parsing/operators"
    ),
    # Redirections - mixed
    TestCase(
        name="redirect in and out",
        command="cat < /etc/hostname > /tmp/test_out",
        category="parsing/operators"
    ),
    TestCase(
        name="redirect before command",
        command="> /tmp/test_out echo hello",
        category="parsing/operators"
    ),
    TestCase(
        name="redirect in before command",
        command="< /etc/hostname cat",
        category="parsing/operators"
    ),
    TestCase(
        name="redirect between args",
        command="echo hello > /tmp/test_out world",
        category="parsing/operators"
    ),
    # Syntax errors
    TestCase(
        name="pipe at start",
        command="| echo hello",
        category="parsing/syntax_errors",
        expect_error=True
    ),
    TestCase(
        name="pipe at end",
        command="echo hello |",
        category="parsing/syntax_errors",
        expect_error=True
    ),
    TestCase(
        name="double pipe",
        command="echo hello || cat",
        category="parsing/syntax_errors",
        expect_error=True,
        bonus=False  # Unless bonus implements ||
    ),
    TestCase(
        name="redirect without file",
        command="echo hello >",
        category="parsing/syntax_errors",
        expect_error=True
    ),
    TestCase(
        name="double redirect",
        command="echo hello > > file",
        category="parsing/syntax_errors",
        expect_error=True
    ),
    TestCase(
        name="redirect to pipe",
        command="echo hello > |",
        category="parsing/syntax_errors",
        expect_error=True
    ),
]

# === Edge Cases and Weird Inputs ===
EDGE_CASE_TESTS = [
    TestCase(
        name="semicolon in quotes",
        command='echo "hello;world"',
        category="parsing/edge_cases"
    ),
    TestCase(
        name="pipe in quotes",
        command='echo "hello|world"',
        category="parsing/edge_cases"
    ),
    TestCase(
        name="redirect in quotes",
        command='echo "hello>world"',
        category="parsing/edge_cases"
    ),
    TestCase(
        name="very long argument",
        command="echo " + "a" * 1000,
        category="parsing/edge_cases"
    ),
    TestCase(
        name="many arguments",
        command="echo " + " ".join(f"arg{i}" for i in range(100)),
        category="parsing/edge_cases"
    ),
    TestCase(
        name="command is just quotes",
        command='""',
        category="parsing/edge_cases",
        expect_error=True
    ),
    TestCase(
        name="argument looks like option",
        command="echo -n hello",
        category="parsing/edge_cases"
    ),
]


def get_all_parsing_tests() -> list[TestCase]:
    """Return all parsing tests."""
    return (
        QUOTE_TESTS +
        UNCLOSED_QUOTE_TESTS +
        EXPANSION_TESTS +
        TOKENIZATION_TESTS +
        OPERATOR_TESTS +
        EDGE_CASE_TESTS
    )


def get_parsing_tests_by_subcategory(subcategory: str) -> list[TestCase]:
    """Get parsing tests filtered by subcategory."""
    all_tests = get_all_parsing_tests()
    return [t for t in all_tests if subcategory in t.category]