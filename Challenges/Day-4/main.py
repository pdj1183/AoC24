import sys


def count_xmas(grid):
    """Count all occurrences of 'XMAS' in the grid in all 8 directions."""
    if not grid or not grid[0]:
        return 0

    rows = len(grid)
    cols = len(grid[0])

    # All 8 directions: (row_delta, col_delta)
    directions = [
        (-1, 0),  # up
        (1, 0),  # down
        (0, -1),  # left
        (0, 1),  # right
        (-1, -1),  # up-left
        (-1, 1),  # up-right
        (1, -1),  # down-left
        (1, 1),  # down-right
    ]

    def search_direction(r, c, dr, dc):
        """Search for 'XMAS' starting at (r,c) in direction (dr,dc)."""
        # Boundary check: can the word fit in this direction?
        end_r = r + 3 * dr
        end_c = c + 3 * dc

        if end_r < 0 or end_r >= rows or end_c < 0 or end_c >= cols:
            return False

        # Check each letter with early exit on mismatch
        word = "XMAS"
        for i in range(4):
            if grid[r + i * dr][c + i * dc] != word[i]:
                return False

        return True

    count = 0

    # Iterate through every position in the grid
    for r in range(rows):
        for c in range(cols):
            # Optimization: only start search if we find an 'X'
            if grid[r][c] == "X":
                # Try all 8 directions
                for dr, dc in directions:
                    if search_direction(r, c, dr, dc):
                        count += 1

    return count


def count_x_mas(grid):
    """Count all X-MAS patterns (two MAS in X shape) in the grid."""
    if not grid or not grid[0]:
        return 0

    rows = len(grid)
    cols = len(grid[0])
    count = 0

    # A must be at least 1 away from any edge
    for r in range(1, rows - 1):
        for c in range(1, cols - 1):
            # Only check if center is 'A'
            if grid[r][c] == "A":
                # Check diagonal 1: top-left to bottom-right
                diag1 = {grid[r - 1][c - 1], grid[r + 1][c + 1]}

                # Check diagonal 2: top-right to bottom-left
                diag2 = {grid[r - 1][c + 1], grid[r + 1][c - 1]}

                # Both diagonals must have one M and one S
                if diag1 == diag2 == {"M", "S"}:
                    count += 1

    return count


def main():
    # Parse command line arguments
    part = 1
    if len(sys.argv) > 1:
        try:
            part = int(sys.argv[1])
            if part not in [1, 2]:
                print("Usage: python main.py [1|2]")
                print("  1: Count XMAS occurrences (default)")
                print("  2: Count X-MAS patterns")
                sys.exit(1)
        except ValueError:
            print("Usage: python main.py [1|2]")
            sys.exit(1)

    # Read input file
    with open("input.txt", "r") as f:
        lines = f.read().strip().split("\n")

    # Convert to 2D grid
    grid = [list(line) for line in lines]

    if part == 1:
        # Part 1: Count all occurrences of XMAS
        result = count_xmas(grid)
        print(f"Part 1: XMAS appears {result} times")
    else:
        # Part 2: Count all X-MAS patterns
        result = count_x_mas(grid)
        print(f"Part 2: X-MAS appears {result} times")


if __name__ == "__main__":
    main()
