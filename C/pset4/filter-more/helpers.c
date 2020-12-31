#include "helpers.h"
#include "math.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0, x = width; i < x; i++)
    {
        for (int j = 0, y = height; j < y; j++)
        {
            float flt_average = (image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.0;
            int average = round(flt_average);
            image[j][i].rgbtBlue = average;
            image[j][i].rgbtGreen = average;
            image[j][i].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            // Use the temp variable to temporarily store the pixel being moved
            temp = image[y][x];
            image[y][x] = image[y][(width - 1) - x];
            image[y][(width - 1) - x] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image
    RGBTRIPLE copy[height][width];

    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            copy[i][j] = image[i][j];
        }
    }


    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            // Initialise variables
            int blue = 0;
            int green = 0;
            int red = 0;
            int count = 0;

            for (int a = y - 1; a <= y + 1; a++)
            {

                for (int b = x - 1; b <= x + 1; b++)
                {

                    if (a >= 0 && b >= 0 && a < height && b < width)
                    {
                        blue += copy[a][b].rgbtBlue;
                        green += copy[a][b].rgbtGreen;
                        red += copy[a][b].rgbtRed;
                        count++;
                    }
                }
            }

            // Assign final values
            image[y][x].rgbtBlue = round(blue / (float)count);
            image[y][x].rgbtGreen = round(green / (float)count);
            image[y][x].rgbtRed = round(red / (float)count);

        }
    }

    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image
    RGBTRIPLE copy[height][width];

    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Initialise Gx and Gy values
            int gxblue = 0;
            int gxgreen = 0;
            int gxred = 0;

            int gyblue = 0;
            int gygreen = 0;
            int gyred = 0;

            for (int a = y - 1; a <= y + 1; a++)
            {

                for (int b = x - 1; b <= x + 1; b++)
                {

                    if (a >= 0 && b >= 0 && a < height && b < width)
                    {
                        // Calculate Gx values
                        if (b < x && (a < y || a > y))
                        {
                            gxblue += -1 * copy[a][b].rgbtBlue;
                            gxgreen += -1 * copy[a][b].rgbtGreen;
                            gxred += -1 * copy[a][b].rgbtRed;
                        }
                        else if (b > x && (a < y || a > y))
                        {
                            gxblue += copy[a][b].rgbtBlue;
                            gxgreen += copy[a][b].rgbtGreen;
                            gxred += copy[a][b].rgbtRed;
                        }
                        else if (b < x && a == y)
                        {
                            gxblue += -2 * copy[a][b].rgbtBlue;
                            gxgreen += -2 * copy[a][b].rgbtGreen;
                            gxred += -2 * copy[a][b].rgbtRed;
                        }
                        else if (b > x && a == y)
                        {
                            gxblue += 2 * copy[a][b].rgbtBlue;
                            gxgreen += 2 * copy[a][b].rgbtGreen;
                            gxred += 2 * copy[a][b].rgbtRed;
                        }

                        // Calculate Gy values
                        if (a < y && (b < x || b > x))
                        {
                            gyblue += -1 * copy[a][b].rgbtBlue;
                            gygreen += -1 * copy[a][b].rgbtGreen;
                            gyred += -1 * copy[a][b].rgbtRed;
                        }
                        else if (a > y && (b < x || b > x))
                        {
                            gyblue += copy[a][b].rgbtBlue;
                            gygreen += copy[a][b].rgbtGreen;
                            gyred += copy[a][b].rgbtRed;
                        }
                        else if (a < y && b == x)
                        {
                            gyblue += -2 * copy[a][b].rgbtBlue;
                            gygreen += -2 * copy[a][b].rgbtGreen;
                            gyred += -2 * copy[a][b].rgbtRed;
                        }
                        else if (a > y && b == x)
                        {
                            gyblue += 2 * copy[a][b].rgbtBlue;
                            gygreen += 2 * copy[a][b].rgbtGreen;
                            gyred += 2 * copy[a][b].rgbtRed;
                        }
                    }
                }
            }

            // Apply the Sobel filter algorithm to provide final values
            int blue = round(sqrt(pow(gxblue, 2) + pow(gyblue, 2)));
            int green = round(sqrt(pow(gxgreen, 2) + pow(gygreen, 2)));
            int red = round(sqrt(pow(gxred, 2) + pow(gyred, 2)));

            // Cap values at 255
            if (blue > 255)
            {
                blue = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (red > 255)
            {
                red = 255;
            }

            // Apply values to original image
            image[y][x].rgbtBlue = blue;
            image[y][x].rgbtGreen = green;
            image[y][x].rgbtRed = red;

        }
    }
    return;
}
