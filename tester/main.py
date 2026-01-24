#!/usr/bin/env python3
"""Minishell tester - main entry point."""

import argparse
import sys
from pathlib import Path

from config import Config, ValgrindConfig, Colors
from runner import TestRunner, TestPrinter, TestLogger

# Import test categories
from tests.syntax import (
    get_all_syntax_tests,
    get_mandatory_syntax_tests,
    UNCLOSED_QUOTE_TESTS,
    PIPE_SYNTAX_TESTS,
    REDIR_SYNTAX_TESTS,
    PAREN_SYNTAX_TESTS,
    LOGICAL_SYNTAX_TESTS,
)
from tests.parsing import (
    get_all_parsing_tests,
    QUOTE_TESTS,
    EXPANSION_TESTS,
    TOKENIZATION_TESTS,
    EDGE_CASE_TESTS,
)
from tests.builtins import (
    get_all_builtin_tests,
    ECHO_TESTS,
    PWD_TESTS,
    CD_TESTS,
    EXPORT_TESTS,
    UNSET_TESTS,
    ENV_TESTS,
    EXIT_TESTS,
)
from tests.pipes import (
    get_all_pipe_tests,
    PIPE_BASIC_TESTS,
    PIPE_MULTIPLE_TESTS,
    PIPE_EXIT_TESTS,
    PIPE_BUILTIN_TESTS,
    PIPE_EDGE_TESTS,
    PIPE_SUBSHELL_TESTS,
)
from tests.execution import (
    get_all_execution_tests,
    EXEC_BASIC_TESTS,
    EXEC_ABSOLUTE_TESTS,
    EXEC_RELATIVE_TESTS,
    EXEC_NOT_FOUND_TESTS,
    EXEC_PERMISSION_TESTS,
    EXEC_PATH_TESTS,
    EXEC_PATH_EDGE_TESTS,
    EXEC_DOT_TESTS,
    EXEC_ARGS_TESTS,
    EXEC_ENV_TESTS,
    EXEC_EXIT_TESTS,
)
from tests.redirections import (
    get_all_redirection_tests,
    REDIR_OUT_TESTS,
    REDIR_APPEND_TESTS,
    REDIR_IN_TESTS,
    REDIR_COMBINED_TESTS,
    REDIR_PIPE_TESTS,
    REDIR_ERROR_TESTS,
    REDIR_MULTIPLE_TESTS,
)


def parse_args() -> argparse.Namespace:
    """Parse command line arguments."""
    parser = argparse.ArgumentParser(
        description="Minishell tester - compare your shell against bash",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s                      Run all mandatory tests
  %(prog)s -s                   Run syntax error tests only
  %(prog)s -p                   Run parsing tests only
  %(prog)s -b                   Run builtin tests
  %(prog)s -i                   Run pipe tests
  %(prog)s -x                   Run execution tests
  %(prog)s -r                   Run redirection tests
  %(prog)s -c syntax/quotes     Run specific subcategory
  %(prog)s --bonus              Include bonus tests (&&, ||, (), *)
  %(prog)s -l                   Enable memory leak checks with valgrind (slow)
  %(prog)s -v                   Verbose output
  %(prog)s --list               List all available categories
        """
    )
    
    parser.add_argument(
        "-m", "--minishell",
        type=Path,
        default=Path("./minishell"),
        help="Path to minishell binary (default: ./minishell)"
    )
    
    # Category shorthand flags
    parser.add_argument(
        "-s", "--syntax",
        action="store_true",
        help="Run syntax error tests"
    )
    parser.add_argument(
        "-p", "--parsing",
        action="store_true",
        help="Run parsing tests (quotes, expansion)"
    )
    parser.add_argument(
        "-b", "--builtins",
        action="store_true",
        help="Run builtin tests"
    )
    parser.add_argument(
        "-i", "--pipes",
        action="store_true",
        help="Run pipe tests"
    )
    parser.add_argument(
        "-x", "--execution",
        action="store_true",
        help="Run execution tests"
    )
    parser.add_argument(
        "-r", "--redirections",
        action="store_true",
        help="Run redirection tests"
    )
    
    parser.add_argument(
        "-c", "--category",
        action="append",
        dest="categories",
        help="Run specific test category/subcategory (can be used multiple times)"
    )
    
    parser.add_argument(
        "--bonus",
        action="store_true",
        help="Include bonus tests (&&, ||, wildcards, etc.)"
    )
    
    parser.add_argument(
        "-a", "--all",
        action="store_true",
        help="Run all test categories"
    )
    
    parser.add_argument(
        "-t", "--timeout",
        type=float,
        default=0.5,
        help="Timeout per test in seconds (default: 0.5)"
    )
    
    parser.add_argument(
        "-l", "--leaks",
        action="store_true",
        help="Enable valgrind memory leak checks"
    )
    
    parser.add_argument(
        "--no-fds",
        action="store_true",
        help="Skip file descriptor checking (when using -l/--leaks)"
    )
    
    parser.add_argument(
        "-v", "--verbose",
        action="store_true",
        help="Verbose output"
    )
    
    parser.add_argument(
        "-o", "--log",
        type=Path,
        default=Path("minishell_test.log"),
        help="Log file for failed tests (default: minishell_test.log)"
    )
    
    parser.add_argument(
        "--list",
        action="store_true",
        help="List all available test categories"
    )
    
    return parser.parse_args()


def list_categories():
    """Print available test categories."""
    categories = {
        "syntax": "All syntax error tests (exit code 2)",
        "syntax/quotes": "Unclosed quote errors",
        "syntax/pipe": "Pipe syntax errors",
        "syntax/redirect": "Redirection syntax errors",
        "syntax/parentheses": "Parentheses errors (bonus)",
        "syntax/logical": "&&/|| errors (bonus)",
        "parsing": "All parsing tests (quotes + expansion)",
        "parsing/quotes": "Quote handling",
        "parsing/expansion": "Variable expansion ($VAR, $?, etc.)",
        "parsing/tokenization": "Whitespace and tokenization",
        "parsing/edge_cases": "Edge cases and weird inputs",
        "builtins": "All builtin tests",
        "builtins/echo": "echo command",
        "builtins/pwd": "pwd command",
        "builtins/cd": "cd command",
        "builtins/export": "export command",
        "builtins/unset": "unset command",
        "builtins/env": "env command",
        "builtins/exit": "exit command",
        "pipes": "All pipe tests",
        "pipes/basic": "Basic pipe functionality",
        "pipes/multiple": "Multiple pipes in chain",
        "pipes/exit_status": "Exit status from last command",
        "pipes/builtins": "Pipes with builtin commands",
        "pipes/edge_cases": "Pipe edge cases",
        "pipes/subshell": "Pipes with subshells (bonus)",
        "execution": "All execution tests",
        "execution/basic": "Basic command execution",
        "execution/absolute": "Absolute path execution",
        "execution/relative": "Relative path execution",
        "execution/not_found": "Command not found (exit 127)",
        "execution/permissions": "Permission denied (exit 126)",
        "execution/path": "PATH resolution",
        "execution/path_edge": "PATH edge cases (unset/empty)",
        "execution/dot": "Dot file/directory handling",
        "execution/arguments": "Argument handling",
        "execution/environment": "Environment passing",
        "execution/exit_codes": "Exit code handling",
        "redirections": "All redirection tests",
        "redirections/output": "Output redirection (>)",
        "redirections/append": "Append redirection (>>)",
        "redirections/input": "Input redirection (<)",
        "redirections/combined": "Combined redirections",
        "redirections/pipes": "Redirections with pipes",
        "redirections/errors": "Redirection errors",
        "redirections/multiple": "Multiple redirections",
    }
    
    print(f"\n{Colors.BOLD_GREEN}Available test categories:{Colors.RESET}\n")
    
    current_section = ""
    for cat, desc in categories.items():
        section = cat.split("/")[0]
        if section != current_section:
            if current_section:
                print()
            current_section = section
        
        indent = "  " if "/" in cat else ""
        print(f"{indent}{Colors.CYAN}{cat:30}{Colors.RESET} {desc}")
    print()


def get_tests_for_categories(categories: list[str], include_bonus: bool):
    """Get all tests matching the specified categories."""
    tests = []
    
    # Map category names to test lists
    category_map = {
        # Syntax errors
        "syntax": get_mandatory_syntax_tests if not include_bonus else get_all_syntax_tests,
        "syntax/quotes": lambda: UNCLOSED_QUOTE_TESTS,
        "syntax/pipe": lambda: PIPE_SYNTAX_TESTS,
        "syntax/redirect": lambda: REDIR_SYNTAX_TESTS,
        "syntax/parentheses": lambda: PAREN_SYNTAX_TESTS,
        "syntax/logical": lambda: LOGICAL_SYNTAX_TESTS,
        # Parsing
        "parsing": get_all_parsing_tests,
        "parsing/quotes": lambda: QUOTE_TESTS,
        "parsing/expansion": lambda: EXPANSION_TESTS,
        "parsing/tokenization": lambda: TOKENIZATION_TESTS,
        "parsing/edge_cases": lambda: EDGE_CASE_TESTS,
        # Builtins
        "builtins": get_all_builtin_tests,
        "builtins/echo": lambda: ECHO_TESTS,
        "builtins/pwd": lambda: PWD_TESTS,
        "builtins/cd": lambda: CD_TESTS,
        "builtins/export": lambda: EXPORT_TESTS,
        "builtins/unset": lambda: UNSET_TESTS,
        "builtins/env": lambda: ENV_TESTS,
        "builtins/exit": lambda: EXIT_TESTS,
        # Pipes
        "pipes": get_all_pipe_tests,
        "pipes/basic": lambda: PIPE_BASIC_TESTS,
        "pipes/multiple": lambda: PIPE_MULTIPLE_TESTS,
        "pipes/exit_status": lambda: PIPE_EXIT_TESTS,
        "pipes/builtins": lambda: PIPE_BUILTIN_TESTS,
        "pipes/edge_cases": lambda: PIPE_EDGE_TESTS,
        "pipes/subshell": lambda: PIPE_SUBSHELL_TESTS,
        # Execution
        "execution": get_all_execution_tests,
        "execution/basic": lambda: EXEC_BASIC_TESTS,
        "execution/absolute": lambda: EXEC_ABSOLUTE_TESTS,
        "execution/relative": lambda: EXEC_RELATIVE_TESTS,
        "execution/not_found": lambda: EXEC_NOT_FOUND_TESTS,
        "execution/permissions": lambda: EXEC_PERMISSION_TESTS,
        "execution/path": lambda: EXEC_PATH_TESTS,
        "execution/path_edge": lambda: EXEC_PATH_EDGE_TESTS,
        "execution/dot": lambda: EXEC_DOT_TESTS,
        "execution/arguments": lambda: EXEC_ARGS_TESTS,
        "execution/environment": lambda: EXEC_ENV_TESTS,
        "execution/exit_codes": lambda: EXEC_EXIT_TESTS,
        # Redirections
        "redirections": get_all_redirection_tests,
        "redirections/output": lambda: REDIR_OUT_TESTS,
        "redirections/append": lambda: REDIR_APPEND_TESTS,
        "redirections/input": lambda: REDIR_IN_TESTS,
        "redirections/combined": lambda: REDIR_COMBINED_TESTS,
        "redirections/pipes": lambda: REDIR_PIPE_TESTS,
        "redirections/errors": lambda: REDIR_ERROR_TESTS,
        "redirections/multiple": lambda: REDIR_MULTIPLE_TESTS,
    }
    
    if not categories:
        # Default: all mandatory tests
        categories = ["syntax", "parsing", "builtins"]
    
    for cat in categories:
        if cat in category_map:
            cat_tests = category_map[cat]()
            tests.extend(cat_tests)
        else:
            print(f"{Colors.warn(f'Unknown category: {cat}')}")
    
    # Filter bonus tests if not enabled
    if not include_bonus:
        tests = [t for t in tests if not t.bonus]
    
    # Remove duplicates while preserving order
    seen = set()
    unique_tests = []
    for t in tests:
        # Use command or commands for dedup key
        if t.commands:
            key = (t.name, tuple(t.commands))
        else:
            key = (t.name, t.command)
        if key not in seen:
            seen.add(key)
            unique_tests.append(t)
    
    return unique_tests


def check_requirements(config: Config) -> bool:
    """Check that required tools are available."""
    issues = []
    
    # Check minishell exists
    if not config.minishell_path.exists():
        issues.append(f"Minishell not found at {config.minishell_path}")
    elif not config.minishell_path.is_file():
        issues.append(f"{config.minishell_path} is not a file")
    
    # Check bash
    if not config.bash_cmd:
        issues.append("bash not found in PATH")
    
    # Warn about optional tools
    if config.valgrind.enabled and not config.valgrind.available:
        print(f"{Colors.warn('WARNING:')} valgrind not available, skipping memory checks")
        config.valgrind.enabled = False
    
    if issues:
        for issue in issues:
            print(f"{Colors.ko('ERROR:')} {issue}")
        return False
    
    return True


def main():
    args = parse_args()
    
    # Handle --list
    if args.list:
        list_categories()
        return 0
    
    # Build configuration
    valgrind_config = ValgrindConfig(
        enabled=args.leaks,
        check_leaks=True,
        check_fds=not args.no_fds,
    )
    
    # Build categories list from flags
    categories = args.categories or []
    
    # Add categories from shorthand flags
    if args.syntax:
        categories.append("syntax")
    if args.parsing:
        categories.append("parsing")
    if args.builtins:
        categories.append("builtins")
    if args.pipes:
        categories.append("pipes")
    if args.execution:
        categories.append("execution")
    if args.redirections:
        categories.append("redirections")
    
    # If --all, run everything available
    if args.all:
        categories = [
            "syntax", "parsing", "builtins",
            "pipes", "execution", "redirections"
        ]
    
    config = Config(
        minishell_path=args.minishell,
        timeout=args.timeout,
        valgrind=valgrind_config,
        categories=categories,
        bonus_enabled=args.bonus,
        verbose=args.verbose,
        log_file=args.log,
    )
    
    # Check requirements
    if not check_requirements(config):
        return 1
    
    # Get tests
    tests = get_tests_for_categories(categories, args.bonus)
    
    if not tests:
        print(f"{Colors.warn('No tests to run!')}")
        print("Use --list to see available categories")
        return 1
    
    # Initialize runner, printer, logger
    runner = TestRunner(config)
    printer = TestPrinter(config)
    logger = TestLogger(config)
    
    try:
        # Group tests by top-level category for display
        by_category = {}
        for test in tests:
            cat = test.category.split("/")[0]
            if cat not in by_category:
                by_category[cat] = []
            by_category[cat].append(test)
        
        # Run tests in logical order
        category_order = [
            "syntax", "parsing", "builtins",
            "pipes", "execution", "redirections"
        ]
        sorted_categories = sorted(
            by_category.keys(),
            key=lambda x: category_order.index(x) if x in category_order else 999
        )
        
        for category in sorted_categories:
            cat_tests = by_category[category]
            printer.print_header(category.upper())
            
            for test in cat_tests:
                result = runner.run_test(test)
                printer.print_result(result, runner.test_num)
                logger.log_result(result)
        
        # Print summary
        summary = runner.get_summary()
        printer.print_summary(summary, runner.test_num)
        
        return 0 if summary["failed"] == 0 else 1
        
    finally:
        runner.cleanup()


if __name__ == "__main__":
    sys.exit(main())