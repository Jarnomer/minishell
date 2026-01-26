"""Build utilities for minishell tester."""

import subprocess
from pathlib import Path
from typing import Optional, Tuple

from config import Colors


def has_makefile_rule(makefile_dir: Path, rule: str) -> bool:
    """Check if a Makefile has a specific rule."""
    makefile = makefile_dir / "Makefile"
    if not makefile.exists():
        return False
    try:
        result = subprocess.run(
            ["make", "-n", rule],
            cwd=makefile_dir,
            capture_output=True,
            timeout=5,
        )
        return result.returncode == 0
    except (subprocess.TimeoutExpired, Exception):
        return False


def detect_bonus(project_dir: Path) -> bool:
    """Detect if project has bonus rule in Makefile."""
    return has_makefile_rule(project_dir, "bonus")


def build_project(project_dir: Path, force_bonus: bool = False) -> Tuple[bool, bool]:
    """Build the project using make.
    
    Args:
        project_dir: Path to project directory containing Makefile
        force_bonus: If True, only try bonus rule
        
    Returns:
        Tuple of (success, used_bonus)
    """
    makefile = project_dir / "Makefile"
    if not makefile.exists():
        print(f"{Colors.ko('ERROR:')} No Makefile found in {project_dir}")
        return False, False

    has_bonus = detect_bonus(project_dir)
    target = "bonus" if (has_bonus or force_bonus) else "all"
    
    print(f"{Colors.info('Building:')} make {target}")
    
    try:
        result = subprocess.run(
            ["make", target],
            cwd=project_dir,
            capture_output=True,
            timeout=60,
        )
        
        if result.returncode != 0:
            print(f"{Colors.ko('Build failed:')}")
            if result.stderr:
                print(result.stderr.decode("utf-8", errors="replace"))
            if result.stdout:
                print(result.stdout.decode("utf-8", errors="replace"))
            return False, target == "bonus"
            
        print(f"{Colors.ok('Build successful')}")
        return True, target == "bonus"
        
    except subprocess.TimeoutExpired:
        print(f"{Colors.ko('ERROR:')} Build timed out")
        return False, target == "bonus"
    except Exception as e:
        print(f"{Colors.ko('ERROR:')} Build failed: {e}")
        return False, target == "bonus"


def clean_project(project_dir: Path) -> bool:
    """Run make fclean on the project."""
    makefile = project_dir / "Makefile"
    if not makefile.exists():
        return False
        
    try:
        result = subprocess.run(
            ["make", "fclean"],
            cwd=project_dir,
            capture_output=True,
            timeout=30,
        )
        return result.returncode == 0
    except Exception:
        return False