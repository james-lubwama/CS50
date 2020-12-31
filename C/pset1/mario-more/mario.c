#include <cs50.h>
#include <stdio.h>

void print_hash(int counter);

int main(void)
{
    // initialise counter, starting at 1 (as there will always be at least 1 hash)
    int counter = 1;

    // prompt user to enter an integer between 1 and 8
    int layers = 0;
    while (layers < 1 || layers > 8)

        layers = get_int("Please enter a number between 1 and 8: ");

    // run the process a number of times equal to the integer entered by the user,
    // i.e. 6 times
    for (int x = layers; x > 0; x--)
    {
        for (int y = x - 1; y > 0; y--)
        {
            printf(" ");
        }
        print_hash(counter);
        printf("  ");
        print_hash(counter);
        printf("\n");
        counter++;
    }
}



// function to print hashes - number of hashes will be equal to counter count
// i.e. on 5th loop it will display 5 hash characters
void print_hash(int counter)
{
    for (int a = 0; a < counter; a++)
    {
        printf("#");
    }  
}
