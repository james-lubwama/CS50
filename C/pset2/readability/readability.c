#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int check_ellipses(string);

int main(void)
{
    string text = get_string("Text: ");
    int string_length = strlen(text);
    int letters = 0;
    int spaces = 0;
    int end_punc = 0;
    int misc = 0;
    int ellipses = check_ellipses(text);


    // Loop through the array, counting different character types.
    for (int i = string_length; i >= 0; i--)
    {
        int this_char = text[i];
        if (islower(this_char) || isupper(this_char))
        {
            letters++;
        }
        else if (this_char == 33 || this_char == 46 || this_char == 63)
        {
            end_punc++;
        }
        else if (isspace(this_char))
        {
            spaces++;
        }
        else
        {
            misc++;
        }
    }


    // Calculate the number of words in the text, as well as average word length.
    int words = spaces + 1;
    float avg_word_length = (float) letters / (float) words;
    float sentences = end_punc - (ellipses * 2);


    // Implement the Coleman-Liau formula.
    float l = avg_word_length * 100;
    float s = (sentences / words) * 100; //problem?
    float raw_formula = (0.0588 * l) - (0.296 * s) - 15.8;
    int round_formula = round(raw_formula);


    // Print result
    if (round_formula >= 1 && round_formula <= 16)
    {
        printf("Grade %i\n", round_formula);
    }
    else if (round_formula < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}


// Function to count the number of ellipses contained within the string.
int check_ellipses(string x)
{
    int y = strlen(x);
    int ellipses_counter = 0;
    for (int i = 0; i <= (y - 2); i++)
    {
        if (x[i] + x[i + 1] + x[i + 2] == 138)
        {
            ellipses_counter++;
        }
        else
        {
            ellipses_counter += 0; // need this??
        }
    }
    return ellipses_counter;
}