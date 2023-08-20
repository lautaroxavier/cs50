#include "helpers.h"
#include "math.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

RGBTRIPLE blur_pixel(int height, int width, int i, int j, RGBTRIPLE img[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg;
    RGBTRIPLE pixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixel = image[i][j];
            avg = round((pixel.rgbtBlue + pixel.rgbtRed + pixel.rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaBlue, sepiaGreen;
    RGBTRIPLE pixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixel = image[i][j];
            sepiaRed = .393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue;
            sepiaGreen = .349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue;
            sepiaBlue = .272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue;
            image[i][j].rgbtRed = MIN(round(sepiaRed), 255);
            image[i][j].rgbtGreen = MIN(round(sepiaGreen), 255);
            image[i][j].rgbtBlue = MIN(round(sepiaBlue), 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            pixel = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = pixel;
        }
    }
    return;
}

RGBTRIPLE blur_pixel(int height, int width, int i, int j, RGBTRIPLE img[height][width])
{
    int limSup = MAX(i - 1, 0);
    int limInf = MIN(i + 1, height - 1);
    int limIzq = MAX(j - 1, 0);
    int limDer = MIN(j + 1, width - 1);

    float acumRed = 0;
    float acumBlue = 0;
    float acumGreen = 0;
    int items = 0;
    RGBTRIPLE res;
    for (int k = limSup; k <= limInf; k++)
    {
        for (int l = limIzq; l <= limDer; l++, items++)
        {
            acumRed += img[k][l].rgbtRed;
            acumGreen += img[k][l].rgbtGreen;
            acumBlue += img[k][l].rgbtBlue;
        }
    }
    res.rgbtRed = round(acumRed / items);
    res.rgbtBlue = round(acumBlue / items);
    res.rgbtGreen = round(acumGreen / items);
    return res;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // calculate new value for each pixel
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l] = blur_pixel(height, width, k, l, copy);
        }
    }
    return;
}
