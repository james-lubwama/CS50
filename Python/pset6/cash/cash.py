# Calculate the minimum number of coins that could be given in change
# using only 25, 10, 5 and 1 cent coins

# Import CS50 library
from cs50 import get_float

# Initialise coin variables
quarters = 0
dimes = 0
nickels = 0
cents = 0

# Get amount owed from user - must be non-negative number
owed_float = 0
while owed_float <= 0:
    owed_float = get_float("How much cash is owed: ")

# Recast owed_float as an integer
owed = int(owed_float * 100)

# Loop 4 times, once for each coin type, and update variables
while owed - 25 >= 0:
    quarters += 1
    owed -= 25

while owed - 10 >= 0:
    dimes += 1
    owed -= 10

while owed - 5 >= 0:
    nickels += 1
    owed -= 5

while owed != 0:
    cents += 1
    owed -= 1

# Calculate total number of coins
total_coins = quarters + dimes + nickels + cents

# Print final answer
print(total_coins)
