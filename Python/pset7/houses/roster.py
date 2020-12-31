from cs50 import SQL
from sys import argv, exit

# Verify the correct number of command line arguments were provided
if len(argv) != 2:
    print("Error")
    exit(1)

# Record the house inputted by the user as a command line argument
cla_house = argv[1]

# Open database
db = SQL("sqlite:///students.db")

# Select data from database
house_list = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", cla_house)

# Loop through rows/lists, printing each time
for row in house_list:
    row["middle"] = 0 if row["middle"] == "NULL" else row["middle"]
    if row["middle"]:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['last']}, born {row['birth']}")