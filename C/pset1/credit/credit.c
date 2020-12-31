#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Prototype functions
int get_card_length(long);
int digit_process(int); 

int main(void)
{
    // Declare var to store card number and initialise another var to store number of digits in card number.
    long card_number; 
    int card_length = 0; // 
    card_number = get_long("Number: ");
    card_length = get_card_length(card_number); 
    int start_card_length = card_length;


    // Identify cards by opening 1-2 digits on card.
    int first_two = card_number / pow(10, (card_length - 2)); // get first 2 digits of card number
    int first_one = card_number / pow(10, (card_length - 1)); // get first digit of card number

    int card_start;
    if (first_two == 34 || first_two == 37)
    {
        // American Express
        card_start = 1; 
    }
    else if (first_two == 51 || first_two == 52 || first_two == 53 ||
            first_two == 54 || first_two == 55)
    {
        // MasterCard
        card_start = 2; 
    }
    else if (first_one == 4)
    {
        // Visa
        card_start = 3; 
    }
    else
    {
        card_start = 0;
    }


    // Initialise vars containing sum of digits multiplied by 2 and sum of digits not multiplied by 2.
    int checksum_out = 0;
    int checksum_in = 0; 

    // Digit counter, where 1 represents the rightmost card digit.
    int which_digit = 1;
    while (card_length > 0)
    {
        if (which_digit % 2 != 0)
        {
            checksum_out += (card_number % 10);
            card_length--; 
            card_number /= 10;
            which_digit++;
        }
        else 
        {
            int a = digit_process(card_number % 10);
            checksum_in += a;
            card_length--; 
            card_number /= 10;
            which_digit++;
        }
    }


    // Check whether card adheres to Luhn's algorithm. 1 means valid, 0 means invalid.
    int valid_status;
    int checksum_total = checksum_out + checksum_in;
    if ((checksum_total % 10) == 0)
    {
        valid_status = 1;
    }
    else
    {
        valid_status = 0;
    }

    // Final checks, considering Luhn's algorithm, card length and start digits.
    if (valid_status == 1)
    {
        if (card_start == 1 && start_card_length == 15)
        {
            printf("AMEX\n");
        }
        else if (card_start == 2 && start_card_length == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (card_start == 3 && start_card_length == 13)
        {
            printf("VISA\n");
        }
        else if (card_start == 3 && start_card_length == 16)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");  
        }
    } 
    else
    {
        printf("INVALID\n");  
    }
} 


// Helper function, which takes the digits which need to be multiplied by 2.
// The function assesses whether the result is > 10.
// It is the sum of the digits that is returned, if/when appropriate. 
int digit_process(int b)
{ 
    int x = b * 2; 
    if (x > 9)
    {
        int z = x / 10; 
        int y = x % 10; 
        int sum = y + z;
        return sum;
    }
    else
    {
        return x;
    }
}


// Second helper function, which returns the number of digits contained in the card number passed to it.
int get_card_length(long card_number)
{
    int counter = 0;
    long z = card_number;
    while (z >= 1)
    {
        z /= 10;
        counter++;
    }
    return counter;
}
