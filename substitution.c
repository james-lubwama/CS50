#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[])
{
    // Start of validation.
    // Check if no key was entered, or more than 1 key
    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }

    // Check if the key contains only 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }

    // Check that only alphabetic characters are included in the key
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]))
        {
        }
        else
        {
            printf("Error\n");
            return 1;
        }
    }

    // Check that no letter is repeated more than once
    double checksum  = 0;
    for (int z = 65; z < 91; z++)
    {
        checksum += pow(z, 2);
    }
    checksum = sqrt(checksum);

    double validation = 0;
    for (int a = 0; a < 26; a++)
    {
        validation += pow(toupper(argv[1][a]), 2);
    }
    validation = sqrt(validation);

    // Check 2 values match
    if (checksum != validation)
    {
        printf("Error\n");
        return 1;
    }
    // End of validation

    // Get plaintext
    string plaintext = get_string("plaintext: ");
    int plaintext_length = strlen(plaintext);

    // Calculate and print ciphertext
    printf("ciphertext: ");
    for (int k = 0; k < plaintext_length; k++)
    {
        if (plaintext[k] >= 97 && plaintext[k] <= 122) // if lowercase
        {
            int lower_position = plaintext[k] - 97;
            printf("%c", tolower(argv[1][lower_position]));
        }
        else if (plaintext[k] >= 65 && plaintext[k] <= 90) // uppercase
        {
            int upper_position = plaintext[k] - 65;
            printf("%c", toupper(argv[1][upper_position]));
        }
        else
        {
            printf("%c", plaintext[k]);
        }
    }
    printf("\n");
    return 0;
}


