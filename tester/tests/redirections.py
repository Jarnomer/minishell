"""Redirection tests for minishell."""

from config import TestCase

REDIR_OUT_TESTS = [
    TestCase(
        name="redirect out basic",
        commands=["echo hello > outfile", "cat outfile"],
        category="redirections/output",
    ),
    TestCase(
        name="redirect out creates file",
        commands=["echo test > newfile", "ls newfile"],
        category="redirections/output",
    ),
    TestCase(
        name="redirect out overwrites",
        commands=[
            "echo first > overfile",
            "echo second > overfile",
            "cat overfile",
        ],
        category="redirections/output",
    ),
    TestCase(
        name="redirect out no spaces",
        commands=["echo hello>nospace", "cat nospace"],
        category="redirections/output",
    ),
    TestCase(
        name="redirect out with pipe after",
        commands=["echo hello > pipeout", "cat pipeout | cat"],
        category="redirections/output",
    ),
    TestCase(
        name="redirect out empty file",
        commands=["> emptyfile", "cat emptyfile"],
        category="redirections/output",
    ),
    TestCase(
        name="redirect out multiple words",
        commands=["echo hello world foo > multiword", "cat multiword"],
        category="redirections/output",
    ),
    TestCase(
        name="redirect out quoted filename",
        commands=['echo test > "quotedfile"', "cat quotedfile"],
        category="redirections/output",
    ),
    TestCase(
        name="redirect out single quoted filename",
        commands=["echo test > 'singlequoted'", "cat singlequoted"],
        category="redirections/output",
    ),
    TestCase(
        name="redirect out with variable in content",
        commands=["echo $USER > varfile", "cat varfile"],
        category="redirections/output",
        skip_stdout_check=True,
    ),
    TestCase(
        name="redirect out builtin pwd",
        commands=["pwd > pwdfile", "cat pwdfile"],
        category="redirections/output",
        skip_stdout_check=True,
    ),
]

REDIR_APPEND_TESTS = [
    TestCase(
        name="append basic",
        commands=[
            "echo first > appfile",
            "echo second >> appfile",
            "cat appfile",
        ],
        category="redirections/append",
    ),
    TestCase(
        name="append creates file",
        commands=["echo test >> appendnew", "cat appendnew"],
        category="redirections/append",
    ),
    TestCase(
        name="append multiple",
        commands=[
            "echo a >> appmulti",
            "echo b >> appmulti",
            "echo c >> appmulti",
            "cat appmulti",
        ],
        category="redirections/append",
    ),
    TestCase(
        name="append no spaces",
        commands=["echo hello>>appnospace", "cat appnospace"],
        category="redirections/append",
    ),
    TestCase(
        name="append after overwrite",
        commands=[
            "echo first > appover",
            "echo second >> appover",
            "echo third > appover",
            "cat appover",
        ],
        category="redirections/append",
    ),
]

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
    TestCase(
        name="redirect in single quotes",
        command="cat < '/etc/hostname'",
        category="redirections/input",
    ),
    TestCase(
        name="redirect in with head",
        command="head -1 < /etc/passwd",
        category="redirections/input",
    ),
    TestCase(
        name="redirect in from created file",
        commands=["echo testcontent > intest", "cat < intest"],
        category="redirections/input",
    ),
    TestCase(
        name="redirect in with grep",
        command="grep root < /etc/passwd | head -1",
        category="redirections/input",
    ),
]

REDIR_COMBINED_TESTS = [
    TestCase(
        name="redirect in and out",
        commands=["cat < /etc/hostname > copyfile", "cat copyfile"],
        category="redirections/combined",
    ),
    TestCase(
        name="input redirect before command",
        command="< /etc/hostname cat",
        category="redirections/combined",
    ),
    TestCase(
        name="output redirect before command",
        commands=["> outbefore echo hello", "cat outbefore"],
        category="redirections/combined",
    ),
    TestCase(
        name="redirect in middle of args",
        commands=["echo hello > midfile world", "cat midfile"],
        category="redirections/combined",
    ),
    TestCase(
        name="redirect out before args",
        commands=["> outbeforeargs echo hello world", "cat outbeforeargs"],
        category="redirections/combined",
    ),
    TestCase(
        name="in and out reversed order",
        commands=["> revfile < /etc/hostname cat", "cat revfile"],
        category="redirections/combined",
    ),
    TestCase(
        name="redirect between args",
        commands=["echo one > betweenfile two", "cat betweenfile"],
        category="redirections/combined",
    ),
    TestCase(
        name="multiple redirects different positions",
        commands=["< /etc/hostname > posfile cat", "cat posfile"],
        category="redirections/combined",
    ),
]

REDIR_PIPE_TESTS = [
    TestCase(
        name="pipe then redirect out",
        commands=["echo hello | cat > pipeoutfile", "cat pipeoutfile"],
        category="redirections/pipes",
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
    TestCase(
        name="redirect in piped multiple",
        command="cat < /etc/hostname | cat | cat",
        category="redirections/pipes",
    ),
    TestCase(
        name="pipe chain with final redirect",
        commands=["echo hello | cat | cat > chainfile", "cat chainfile"],
        category="redirections/pipes",
    ),
    TestCase(
        name="redirect in first pipe out last",
        commands=[
            "echo line1 > pipeinout",
            "cat < pipeinout | cat > pipeinout2",
            "cat pipeinout2",
        ],
        category="redirections/pipes",
    ),
    TestCase(
        name="pipe with append",
        commands=[
            "echo first > appendpipe",
            "echo second | cat >> appendpipe",
            "cat appendpipe",
        ],
        category="redirections/pipes",
    ),
    TestCase(
        name="redirect in middle of pipeline",
        commands=["echo hello | cat > midpipe | cat", "cat midpipe"],
        category="redirections/pipes",
    ),
]

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
    TestCase(
        name="redirect out nested nonexistent",
        command="echo test > /nonexistent/path/file",
        category="redirections/errors",
        expect_error=True,
    ),
    TestCase(
        name="append to directory",
        command="echo test >> /tmp",
        category="redirections/errors",
        expect_error=True,
    ),
    TestCase(
        name="append no permission",
        command="echo test >> /etc/shadow",
        category="redirections/errors",
        expect_error=True,
    ),
    TestCase(
        name="redirect error stops command",
        commands=["echo visible", "echo test > /etc/noperm", "echo $?"],
        category="redirections/errors",
        expect_error=True,
    ),
]

REDIR_MULTIPLE_TESTS = [
    TestCase(
        name="multiple output redirects",
        commands=["echo test > multiout1 > multiout2", "cat multiout2"],
        category="redirections/multiple",
    ),
    TestCase(
        name="multiple input redirects",
        command="cat < /etc/hostname < /etc/hosts | head -1",
        category="redirections/multiple",
    ),
    TestCase(
        name="three output redirects",
        commands=[
            "echo test > tri1 > tri2 > tri3",
            "cat tri3",
        ],
        category="redirections/multiple",
    ),
    TestCase(
        name="out then append same file",
        commands=[
            "echo first > outapp",
            "echo second >> outapp",
            "cat outapp",
        ],
        category="redirections/multiple",
    ),
]

HEREDOC_BASIC_TESTS = [
    TestCase(
        name="heredoc basic",
        commands=["cat << EOF", "hello", "world", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc single line",
        commands=["cat << END", "single line", "END"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc empty",
        commands=["cat << EOF", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc multiple lines",
        commands=["cat << STOP", "line one", "line two", "line three", "STOP"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc with numbers delimiter",
        commands=["cat << 123", "content", "123"],
        category="redirections/heredoc",
    ),
]

HEREDOC_EXPAND_TESTS = [
    TestCase(
        name="heredoc expands variable",
        commands=["cat << EOF", "$USER", "EOF"],
        category="redirections/heredoc",
        skip_stdout_check=True,  # USER varies
    ),
    TestCase(
        name="heredoc expands exit status",
        commands=["cat << EOF", "$?", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc expands in text",
        commands=["cat << EOF", "hello $USER world", "EOF"],
        category="redirections/heredoc",
        skip_stdout_check=True,
    ),
    TestCase(
        name="heredoc unset var empty",
        commands=["cat << EOF", "$UNSET_VAR_12345", "EOF"],
        category="redirections/heredoc",
    ),
]

HEREDOC_QUOTED_TESTS = [
    TestCase(
        name="heredoc quoted delimiter single",
        commands=["cat << 'EOF'", "$USER", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc quoted delimiter double",
        commands=['cat << "EOF"', "$USER", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc quoted no expand exit status",
        commands=["cat << 'END'", "$?", "END"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc quoted preserves dollar",
        commands=["cat << 'STOP'", "$HOME $PATH $?", "STOP"],
        category="redirections/heredoc",
    ),
]

HEREDOC_PIPE_TESTS = [
    TestCase(
        name="heredoc piped to cat",
        commands=["cat << EOF | cat", "hello", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc piped to wc",
        commands=["cat << EOF | wc -l", "line1", "line2", "line3", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc piped to grep",
        commands=["cat << EOF | grep hello", "hello world", "foo bar", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc double pipe",
        commands=["cat << EOF | cat | cat", "test", "EOF"],
        category="redirections/heredoc",
    ),
]

HEREDOC_EDGE_TESTS = [
    TestCase(
        name="heredoc with spaces in content",
        commands=["cat << EOF", "   spaces   ", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc delimiter in content",
        commands=["cat << EOF", "not EOF yet", "still not", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc special chars in content",
        commands=["cat << EOF", "| > < & * ?", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc empty lines",
        commands=["cat << EOF", "", "middle", "", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc long delimiter",
        commands=["cat << VERYLONGDELIMITER", "content", "VERYLONGDELIMITER"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc with quotes in content",
        commands=["cat << EOF", "say \"hello\" and 'bye'", "EOF"],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc backslash in content",
        commands=["cat << EOF", "path\\to\\file", "EOF"],
        category="redirections/heredoc",
    ),
]

HEREDOC_MULTIPLE_TESTS = [
    TestCase(
        name="two heredocs sequential",
        commands=[
            "cat << EOF",
            "first",
            "EOF",
            "cat << END",
            "second",
            "END",
        ],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc then echo",
        commands=[
            "cat << EOF",
            "heredoc content",
            "EOF",
            "echo after heredoc",
        ],
        category="redirections/heredoc",
    ),
    TestCase(
        name="echo then heredoc",
        commands=[
            "echo before heredoc",
            "cat << EOF",
            "heredoc content",
            "EOF",
        ],
        category="redirections/heredoc",
    ),
]

HEREDOC_REDIR_TESTS = [
    TestCase(
        name="heredoc output to file",
        commands=[
            "cat << EOF > hdocfile",
            "hello heredoc",
            "EOF",
            "cat hdocfile",
        ],
        category="redirections/heredoc",
    ),
    TestCase(
        name="heredoc append to file",
        commands=[
            "echo first > hdocapp",
            "cat << EOF >> hdocapp",
            "second",
            "EOF",
            "cat hdocapp",
        ],
        category="redirections/heredoc",
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
        + HEREDOC_BASIC_TESTS
        + HEREDOC_EXPAND_TESTS
        + HEREDOC_QUOTED_TESTS
        + HEREDOC_PIPE_TESTS
        + HEREDOC_EDGE_TESTS
        + HEREDOC_MULTIPLE_TESTS
        + HEREDOC_REDIR_TESTS
    )


def get_heredoc_tests() -> list[TestCase]:
    """Return only heredoc tests."""
    return (
        HEREDOC_BASIC_TESTS
        + HEREDOC_EXPAND_TESTS
        + HEREDOC_QUOTED_TESTS
        + HEREDOC_PIPE_TESTS
        + HEREDOC_EDGE_TESTS
        + HEREDOC_MULTIPLE_TESTS
        + HEREDOC_REDIR_TESTS
    )