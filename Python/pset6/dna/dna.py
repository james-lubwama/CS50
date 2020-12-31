# Program takes a sequence of DNA, searches for and counts STR repetitions, then cross-references the
# results with a table in a CSV file to identify who the DNA sequence belongs to.

import csv
from sys import argv, exit

def main():
    # User must provide at least one command line argument, otherwise terminate program
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Open DNA database and store as a list in dna_file variable
    file_one = open(f"{argv[1]}", 'r')
    str_list = list(csv.reader(file_one))

    # Create a list of all the STRs we need to search for
    str_search = str_list[0]
    del str_search[0]

    # Grab DNA sequence from CSV file and calculate its length
    sequence_file = open(f"{argv[2]}", "r").read()
    sequence = sequence_file.split()[0]
    sequence_length = len(sequence)

    # Will loop through the DNA sequence once for each STR. Returned each time from the function will be the
    # highest number of repeats for that particular STR.
    repeats = []
    for i in range(len(str_search)):
        repeats.append(check_repeats(str_search[i], sequence_length, sequence))

    # Create a list of lists - each list will represent a row of the csv file
    with open(f"{argv[1]}", "r") as file:
        read_data = csv.reader(file)
        list_of_rows = list(read_data)

    # Calculate number of rows in table
    row_no = len(list_of_rows)

    # Initialise match variable
    match = 0

    # For each row of the CSV file, loop through the repeats list to see if there are any matches.
    for x in range(1, row_no, 1):
        counter = 0
        for y in range(0, len(str_search), 1):
            if repeats[y] == int(list_of_rows[x][y + 1]):
                counter += 1
        if counter == len(str_search):
            match = x
            print(list_of_rows[x][0])
            break

    # Print "No match" if there are no exact matches in the data file.
    if match == 0:
        print("No match")

    # Close file(s)
    file_one.close()

# Function to record STR appearances in sequence
def check_repeats(the_str, sequence_length, sequence):

    # Calculate number of characters in the STR, ie 4 in AATG
    str_chars = len(the_str)

    # Empty list into which the locations of the STRs in the sequence will be recorded
    str_starts = []

    # Loop through the sequence, recording the location of the first STR character (i.e. A in AATG)
    # and storing that location in the str_starts list
    for i in range(sequence_length - str_chars):
        if the_str in sequence[i:i + str_chars]:
            str_starts.append(i)

    # If there was only one instance of the STR in the sequence, simply return 1
    if len(str_starts) == 1:
        return 1

    # Set counter variables
    current_count = 1
    highest_count = 0

    # Loop through the str_starts list, looking for repeating STRs. When found, begin counting, and update
    # the highest_count variable. When a new repeating sequence is found, overwrite the previous highest_count
    # value if it is higher. Always reset current_count when repetition is stopped/not found.
    for j in range(len(str_starts) - 1):
        if str_starts[j] + str_chars == str_starts[j + 1]:
            current_count += 1
            if current_count > highest_count:
                highest_count = current_count
        elif current_count > highest_count:
            highest_count = current_count
            current_count = 1
        else:
            current_count = 1

    # If there was more than one instance of the STR in the sequence, look if the repetition occurred at the
    # end of the sequence. If so add one to the value returned by the function.
    if len(str_starts) > 1:
        if str_starts[-1] == sequence[-str_chars]:
            highest_count += 1

    return highest_count


if __name__ == "__main__":
    main()