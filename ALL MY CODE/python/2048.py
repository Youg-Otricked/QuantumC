import random
keep = True
def display_grid(grid):
    for row in grid:
        print(" ".join(map(str, row)))
grid = [
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0]]

def add_random_tile(grid):
    keep = True
    filled = sum(1 for row in grid for cell in row if cell != 0)
    if filled > 15:
        return grid
    while keep:
        x = random.randrange(0, 4, 1)
        y = random.randrange(0, 4, 1)
        if grid[x][y] == 0:
            grid[x][y] = random.randrange(2, 5, 2)
            keep = False
            return grid
grid = add_random_tile(grid)
grid = add_random_tile(grid)
display_grid(grid)
