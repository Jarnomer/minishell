"""Tests module for minishell tester."""

from tests.syntax import get_all_syntax_tests, get_mandatory_syntax_tests
from tests.parsing import get_all_parsing_tests
from tests.builtins import get_all_builtin_tests
from tests.pipes import get_all_pipe_tests
from tests.execution import get_all_execution_tests
from tests.redirections import get_all_redirection_tests, get_heredoc_tests

__all__ = [
    "get_all_syntax_tests",
    "get_mandatory_syntax_tests",
    "get_all_parsing_tests",
    "get_all_builtin_tests",
    "get_all_pipe_tests",
    "get_all_execution_tests",
    "get_all_redirection_tests",
    "get_heredoc_tests",
]