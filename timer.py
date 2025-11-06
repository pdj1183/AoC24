import sys
import time
import subprocess
from pathlib import Path

if len(sys.argv) < 2:
    print("Usage: python timer.py <path-to-day-folder>")
    sys.exit(1)

day_path = Path(sys.argv[1]).resolve()
main_file = day_path / "main.py"

if not main_file.exists():
    print(f"Error: {main_file} not found")
    sys.exit(1)

start_time = time.time()
result = subprocess.run([sys.executable, str(main_file)], cwd=str(day_path))
end_time = time.time()

elapsed = end_time - start_time
print(f"\nExecution time: {elapsed:.4f} seconds")

sys.exit(result.returncode)
