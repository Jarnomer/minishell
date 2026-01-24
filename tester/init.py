"""Tests module for minishell tester."""

from tests.syntax import get_all_syntax_tests, get_mandatory_syntax_tests
from tests.parsing import get_all_parsing_tests
from tests.builtins import get_all_builtin_tests

__all__ = [
    'get_all_syntax_tests',
    'get_mandatory_syntax_tests',
    'get_all_parsing_tests',
    'get_all_builtin_tests',
]