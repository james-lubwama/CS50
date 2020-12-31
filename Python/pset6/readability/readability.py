# Import get_string function from CS50 library
from cs50 import get_string

# Get input from user
text = get_string("Text: ")

# Initialise word_count, taking into account last word won't be followed by a space
if len(text) > 0:
    word_count = 1
else:
    word_count = 0

# Initialise other variables
sentence_end = [".", "!", "?"]
sentence_count = 0
total_chars = 0

# Loop through string
for i in range(len(text)):
    if text[i].isalpha():
        total_chars += 1
    if text[i] in sentence_end:
        sentence_count += 1
    if text[i] == " ":
        word_count += 1

# Calculate average number of letters per 100 words in the text
letters = (total_chars / word_count) * 100

# Calculate average number of sentences per 100 words in the text
sentence = (sentence_count / word_count) * 100

# Implement Coleman-Liau index
grade = 0.0588 * letters - 0.296 * sentence - 15.8

# Print final answer
if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {round(grade)}")