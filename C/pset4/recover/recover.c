#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Create a new type to store a byte of data
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure only 1 command line argument is passed
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open jpeg file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Error\n");
        return 2;
    }

    // Initialise variables
    int jpegs_found = 0;
    FILE *img = NULL;
    char *filename = malloc(3 * sizeof(char));
    bool end = false;

    // Create array to store block of 512 bytes
    BYTE *buffer = malloc(512 * sizeof(BYTE));

    // Begin loop
    while (true)
    {
        // Determine block length and store as integer
        int block_length = fread(buffer, 1, 512, file);
        if (block_length < 512)
        {
            end = true;
        }

        // Check whether block is start of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Add to jpeg count
            jpegs_found++;

            // Close previous jpeg file if appropriate
            if (jpegs_found > 1)
            {
                fclose(img);
            }

            // Update filename
            sprintf(filename, "%03i.jpg", jpegs_found - 1);

            // Make new jpeg file
            img = fopen(filename, "w");

            // Write to file
            fwrite(buffer, 1, 512, img);

        }
        else if (jpegs_found > 0)
        {
            // Continue writing to currently open jpeg file
            fwrite(buffer, 1, block_length, img);
        }

        // Close final image when end of file is reached
        if (end == true)
        {
            fclose(img);
            break;
        }
    }

    // Free allocated memory
    free(filename);
    free(buffer);

    // Close file and wrap up
    fclose(file);
    return 0;
}