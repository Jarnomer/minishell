#!/usr/bin/env python3
"""Minishell tester - main entry point."""

import argparse
import sys
from pathlib import Path

from config import Config, ValgrindConfig, Colors
from runner import TestRunner, TestPrinter, TestLogger

# Import test categories
from tests.parsing import (
    get_all_parsing_tests,
    QUOTE_TESTS,
    EXPANSION_TESTS,
    TOKENIZATION_TESTS,
    OPERATOR_TESTS,
    EDGE_CASE_TESTS,
    UNCLOSED_QUOTE_TESTS,
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


def parse_args() -> argparse.Namespace:
    """Parse command line arguments."""
    parser = argparse.ArgumentParser(
        description="Minishell tester - compare your shell against bash",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s                      Run all mandatory tests
  %(prog)s -p                   Run parsing tests only
  %(prog)s -p -b                Run parsing and builtin tests
  %(prog)s -c parsing/quotes    Run specific subcategory
  %(prog)s --bonus              Include bonus tests
  %(prog)s -l                   Enable memory leak checks with valgrind
  %(prog)s -v                   Verbose output
  %(prog)s --help               Show this help message
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
        "-p", "--parsing",
        action="store_true",
        help="Run parsing tests"
    )
    parser.add_argument(
        "-b", "--builtins",
        action="store_true",
        help="Run builtin tests"
    )
    parser.add_argument(
        "-e", "--execution",
        action="store_true",
        help="Run execution tests"
    )
    parser.add_argument(
        "-r", "--redirections",
        action="store_true",
        help="Run redirection tests"
    )
    parser.add_argument(
        "-s", "--signals",
        action="store_true",
        help="Run signal tests"
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
    
    return parser.parse_args()


def list_categories():
    """Print available test categories."""
    categories = {
        "parsing": "All parsing tests",
        "parsing/quotes": "Quote handling",
        "parsing/expansion": "Variable expansion ($VAR, $?, etc.)",
        "parsing/tokenization": "Whitespace and tokenization",
        "parsing/operators": "Pipes and redirections",
        "parsing/syntax_errors": "Syntax error handling",
        "parsing/edge_cases": "Edge cases and weird inputs",
        "builtins": "All builtin tests",
        "builtins/echo": "echo command",
        "builtins/pwd": "pwd command",
        "builtins/cd": "cd command",
        "builtins/export": "export command",
        "builtins/unset": "unset command",
        "builtins/env": "env command",
        "builtins/exit": "exit command",
        # Future categories
        "execution": "Command execution (coming soon)",
        "redirections": "Redirections (coming soon)",
        "signals": "Signal handling (coming soon)",
        "bonus": "Bonus features (coming soon)",
    }
    
    print(f"\n{Colors.BOLD_GREEN}Available test categories:{Colors.RESET}\n")
    for cat, desc in categories.items():
        print(f"  {Colors.CYAN}{cat:25}{Colors.RESET} {desc}")
    print()


def get_tests_for_categories(categories: list[str], include_bonus: bool):
    """Get all tests matching the specified categories."""
    tests = []
    
    # Map category names to test lists
    category_map = {
        # Parsing
        "parsing": get_all_parsing_tests,
        "parsing/quotes": lambda: QUOTE_TESTS,
        "parsing/expansion": lambda: EXPANSION_TESTS,
        "parsing/tokenization": lambda: TOKENIZATION_TESTS,
        "parsing/operators": lambda: OPERATOR_TESTS,
        "parsing/syntax_errors": lambda: UNCLOSED_QUOTE_TESTS,
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
    }
    
    if not categories:
        # Default: all mandatory tests
        categories = ["parsing", "builtins"]
    
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
    
    # Build configuration
    valgrind_config = ValgrindConfig(
        enabled=args.leaks,  # Only enable if -l/--leaks flag is passed
        check_leaks=True,
        check_fds=not args.no_fds,
    )
    
    # Build categories list from flags
    categories = args.categories or []
    
    # Add categories from shorthand flags
    if args.parsing:
        categories.append("parsing")
    if args.builtins:
        categories.append("builtins")
    if args.execution:
        categories.append("execution")
    if args.redirections:
        categories.append("redirections")
    if args.signals:
        categories.append("signals")
    
    # If --all or no categories specified, run all available
    if args.all or not categories:
        categories = ["parsing", "builtins"]  # Add more as implemented
    
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
        return 1
    
    # Initialize runner, printer, logger
    runner = TestRunner(config)
    printer = TestPrinter(config)
    logger = TestLogger(config)
    
    try:
        # Group tests by category
        by_category = {}
        for test in tests:
            cat = test.category.split("/")[0]
            if cat not in by_category:
                by_category[cat] = []
            by_category[cat].append(test)
        
        # Run tests
        for category, cat_tests in by_category.items():
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