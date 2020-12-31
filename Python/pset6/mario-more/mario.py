from cs50 import get_int

# Initialise size of pyramid to 0
size = 0

# User must input integer between 1 and 8 inclusive
while size < 1 or size > 8:
    size = get_int("Height: ")

# Loop through, printing hash symbols
for i in range(1, size + 1):
    print(" " * (size - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)
