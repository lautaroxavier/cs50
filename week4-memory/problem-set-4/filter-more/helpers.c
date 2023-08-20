#include "helpers.h"
#include <math.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

RGBTRIPLE blur_pixel(int height, int width, int i, int j, RGBTRIPLE img[height][width]);
RGBTRIPLE sobel_pixel(int height, int width, int r, int c, RGBTRIPLE img[height][width]);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // iterate over all the elements excluding edges
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l] = sobel_pixel(height, width, k, l, copy);
        }
    }
    return;
}

RGBTRIPLE sobel_pixel(int height, int width, int r, int c, RGBTRIPLE img[height][width])
{
    RGBTRIPLE res;
    int matrixGx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int matrixGy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int limSup = MAX(r - 1, 0);
    int limInf = MIN(r + 1, height - 1);
    int limIzq = MAX(c - 1, 0);
    int limDer = MIN(c + 1, width - 1);

    float valueRedGx = 0;
    float valueRedGy = 0;
    float valueGreenGx = 0;
    float valueGreenGy = 0;
    float valueBlueGx = 0;
    float valueBlueGy = 0;

    int valueGx, valueGy;
    RGBTRIPLE pixel;
    for (int i = limSup; i <= limInf; i++)
    {
        for (int j = limIzq; j <= limDer; j++)
        {
            pixel = img[i][j];
            valueGx = matrixGx[1 + i - r][1 + j - c];
            valueGy = matrixGy[1 + i - r][1 + j - c];
            valueRedGx += pixel.rgbtRed * valueGx;
            valueRedGy += pixel.rgbtRed * valueGy;
            valueGreenGx += pixel.rgbtGreen * valueGx;
            valueGreenGy += pixel.rgbtGreen * valueGy;
            valueBlueGx += pixel.rgbtBlue * valueGx;
            valueBlueGy += pixel.rgbtBlue * valueGy;
        }
    }

    res.rgbtRed = MIN(255, round(sqrt(pow(valueRedGx, 2) + pow(valueRedGy, 2))));
    res.rgbtGreen = MIN(255, round(sqrt(pow(valueGreenGx, 2) + pow(valueGreenGy, 2))));
    res.rgbtBlue = MIN(255, round(sqrt(pow(valueBlueGx, 2) + pow(valueBlueGy, 2))));

    return res;
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
