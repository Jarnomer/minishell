"""Parsing tests for minishell - quotes, tokenization, expansion.

Test Categories:
- QUOTE_TESTS: Basic quote handling + mixing quotes + special chars in quotes + whitespace + weird combinations
- EXPANSION_TESTS: Variable expansion + expansion with quotes
- TOKENIZATION_TESTS: Whitespace handling
- OPERATOR_TESTS: Pipes and redirections
- EDGE_CASE_TESTS: Edge cases and weird inputs
- UNCLOSED_QUOTE_TESTS: Syntax errors
"""

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

# === Quote Mixing Within Words ===
QUOTE_MIXING_TESTS = [
    TestCase(
        name="single quote inside double quotes",
        command='echo "wor\'ld"',
        category="parsing/quotes"
    ),
    TestCase(
        name="double quote inside single quotes",
        command="echo 'wor\"ld'",
        category="parsing/quotes"
    ),
    TestCase(
        name="multiple single quotes in double",
        command='echo "it\'s a \'test\'"',
        category="parsing/quotes"
    ),
    TestCase(
        name="alternating quotes same word",
        command='echo "hel"\'lo\'',
        category="parsing/quotes"
    ),
    TestCase(
        name="three-way quote mix",
        command='echo "a"\'b\'"c"',
        category="parsing/quotes"
    ),
    TestCase(
        name="quoted then unquoted in word",
        command='echo "hello"world',
        category="parsing/quotes"
    ),
    TestCase(
        name="unquoted then quoted in word",
        command='echo hello"world"',
        category="parsing/quotes"
    ),
    TestCase(
        name="single-double-single pattern",
        command="echo 'a\"b'",
        category="parsing/quotes"
    ),
    TestCase(
        name="double-single-double pattern",
        command='echo "a\'b"',
        category="parsing/quotes"
    ),
    TestCase(
        name="empty quotes mixed with text",
        command='echo ""hello""world""',
        category="parsing/quotes"
    ),
    TestCase(
        name="alternating empty and filled",
        command='echo ""a""b""',
        category="parsing/quotes"
    ),
    TestCase(
        name="complex email-like pattern",
        command='echo "$USER"@"$HOME"',
        category="parsing/quotes",
        skip_stdout_check=True  # Output varies by user
    ),
]

# === Special Characters in Quotes ===
SPECIAL_CHARS_IN_QUOTES_TESTS = [
    TestCase(
        name="dollar sign in single quotes",
        command="echo '$USER'",
        category="parsing/quotes"
    ),
    TestCase(
        name="dollar sign in double quotes",
        command='echo "$USER"',
        category="parsing/quotes"
    ),
    TestCase(
        name="literal dollar in single quotes",
        command="echo '$'",
        category="parsing/quotes"
    ),
    TestCase(
        name="asterisk in single quotes",
        command="echo '*'",
        category="parsing/quotes"
    ),
    TestCase(
        name="asterisk in double quotes",
        command='echo "*"',
        category="parsing/quotes"
    ),
    TestCase(
        name="question mark in quotes",
        command="echo '?'",
        category="parsing/quotes"
    ),
    TestCase(
        name="pipe symbol in quotes",
        command="echo 'hello | world'",
        category="parsing/quotes"
    ),
    TestCase(
        name="redirect in quotes",
        command='echo "a > b"',
        category="parsing/quotes"
    ),
    TestCase(
        name="ampersand in quotes",
        command="echo 'a && b'",
        category="parsing/quotes"
    ),
    TestCase(
        name="semicolon in single quotes",
        command="echo 'a;b;c'",
        category="parsing/quotes"
    ),
    TestCase(
        name="parentheses in quotes",
        command='echo "(hello)"',
        category="parsing/quotes"
    ),
    TestCase(
        name="brackets in quotes",
        command="echo '[test]'",
        category="parsing/quotes"
    ),
    TestCase(
        name="backslash in single quotes",
        command="echo 'hello\\world'",
        category="parsing/quotes"
    ),
    TestCase(
        name="multiple special chars quoted",
        command='echo "| > < & * ?"',
        category="parsing/quotes"
    ),
]

# === Whitespace in Quotes ===
WHITESPACE_IN_QUOTES_TESTS = [
    TestCase(
        name="multiple spaces preserved",
        command='echo "a    b    c"',
        category="parsing/quotes"
    ),
    TestCase(
        name="leading spaces in quotes",
        command='echo "   hello"',
        category="parsing/quotes"
    ),
    TestCase(
        name="trailing spaces in quotes",
        command='echo "hello   "',
        category="parsing/quotes"
    ),
    TestCase(
        name="only spaces in quotes",
        command='echo "     "',
        category="parsing/quotes"
    ),
]

# === Weird Quote Combinations ===
WEIRD_QUOTE_TESTS = [
    TestCase(
        name="many empty quotes",
        command='echo "" "" "" ""',
        category="parsing/quotes"
    ),
    TestCase(
        name="alternating quote types empty",
        command='echo ""\'\'""\'\'',
        category="parsing/quotes"
    ),
    TestCase(
        name="six consecutive quotes",
        command='echo """"""',
        category="parsing/quotes"
    ),
    TestCase(
        name="quote soup",
        command='echo "a"\'\'"b"\'c\'""',
        category="parsing/quotes"
    ),
    TestCase(
        name="single char in each quote type",
        command='echo "a"\'b\'"c"\'d\'',
        category="parsing/quotes"
    ),
]

# === Variable Expansion with Quotes ===
EXPANSION_WITH_QUOTES_TESTS = [
    TestCase(
        name="var with surrounding text in quotes",
        command='echo "user:$USER:end"',
        category="parsing/expansion"
    ),
    TestCase(
        name="var in single quotes not expanded",
        command="echo 'user:$USER:end'",
        category="parsing/expansion"
    ),
    TestCase(
        name="mix quoted and unquoted var",
        command='echo $USER"@example.com"',
        category="parsing/expansion"
    ),
    TestCase(
        name="var between quotes",
        command='echo "user:"$USER":end"',
        category="parsing/expansion"
    ),
    TestCase(
        name="dollar question in quotes",
        command='echo "exit: $?"',
        category="parsing/expansion"
    ),
    TestCase(
        name="dollar question in single quotes",
        command="echo 'exit: $?'",
        category="parsing/expansion"
    ),
    TestCase(
        name="empty var in quotes",
        command='echo "value:$UNSET_VAR:end"',
        category="parsing/expansion"
    ),
    TestCase(
        name="multiple vars in quotes",
        command='echo "$USER $HOME $PATH" | wc -w',
        category="parsing/expansion"
    ),
    TestCase(
        name="var with quote immediately after",
        command='echo $USER"s home"',
        category="parsing/expansion"
    ),
]

# Add them all to QUOTE_TESTS
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
] + QUOTE_MIXING_TESTS + SPECIAL_CHARS_IN_QUOTES_TESTS + WHITESPACE_IN_QUOTES_TESTS + WEIRD_QUOTE_TESTS

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
] + EXPANSION_WITH_QUOTES_TESTS

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
        name="command is just quotes",
        command='""',
        category="parsing/edge_cases",
        expect_error=True
    ),
    TestCase(
        name="empty string argument to echo",
        command='echo "" hello',
        category="parsing/edge_cases"
    ),
    TestCase(
        name="multiple empty string arguments",
        command='echo "" "" hello ""',
        category="parsing/edge_cases"
    ),
    TestCase(
        name="unset variable disappears",
        command='echo $UNSET_VAR_12345',
        category="parsing/edge_cases"
    ),
    TestCase(
        name="quoted unset variable kept",
        command='echo "$UNSET_VAR_12345"',
        category="parsing/edge_cases"
    ),
    TestCase(
        name="unset variable as command",
        command='$UNSET_VAR_12345',
        category="parsing/edge_cases"
    ),
    TestCase(
        name="argument looks like option",
        command="echo -n hello",
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