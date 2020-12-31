import csv
from cs50 import SQL
from sys import argv, exit

# Verify the correct number of command line arguments were provided
if len(argv) != 2:
    print("Error")
    exit(1)

# Open database
db = SQL("sqlite:///students.db")

# Run through the CSV file row by row, extracting data ready for insertion into SQL database
with open(f"{argv[1]}", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        # Split name
        row["name"] = row["name"].split()

        # Assign result of split name into appropriate variables
        first = row["name"][0]
        middle = row["name"][1] if len(row["name"]) == 3 else None
        last = row["name"][-1]
        house = row["house"]
        birth = row["birth"]

        # Write/insert student data into the SQL database
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);", first, middle, last, house, birth)