#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pixel = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = pixel;
            image[i][j].rgbtGreen = pixel;
            image[i][j].rgbtRed = pixel;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int center = width / 2;
    int end = width - 1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < center; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][end - j];
            image[i][end - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float red = 0, blue = 0, green = 0;
            float i = 0;
            for (int a = h - 1; a <= h + 1; a++)
            {
                for (int b = w - 1; b <= w + 1; b++)
                {
                    if (a >= 0 && a < height && b >= 0 && b < width)
                    {
                        red += image[a][b].rgbtRed;
                        green += image[a][b].rgbtGreen;
                        blue += image[a][b].rgbtBlue;
                        i++;
                    }
                }
            }
            temp[h][w].rgbtRed = round(red / i);
            temp[h][w].rgbtGreen = round(green / i);
            temp[h][w].rgbtBlue = round(blue / i);
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = temp[h][w];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE temp[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int rgx = 0, ggx = 0, bgx = 0;
            int rgy = 0, ggy = 0, bgy = 0;
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    int ha = h + a - 1, wb = w + b - 1;
                    if (ha >= 0 && ha < height && wb >= 0 && wb < width)
                    {
                        rgx += image[ha][wb].rgbtRed * gx[a][b];
                        ggx += image[ha][wb].rgbtGreen * gx[a][b];
                        bgx += image[ha][wb].rgbtBlue * gx[a][b];
                        rgy += image[ha][wb].rgbtRed * gy[a][b];
                        ggy += image[ha][wb].rgbtGreen * gy[a][b];
                        bgy += image[ha][wb].rgbtBlue * gy[a][b];
                    }
                }
            }
            int t[3];
            t[0] = round(pow(pow(rgx, 2) + pow(rgy, 2), 0.5));
            t[1] = round(pow(pow(ggx, 2) + pow(ggy, 2), 0.5));
            t[2] = round(pow(pow(bgx, 2) + pow(bgy, 2), 0.5));
            for (int i = 0; i < 3; i++)
            {
                if (t[i] > 255)
                {
                    t[i] = 255;
                }
            }
            temp[h][w].rgbtRed = t[0];
            temp[h][w].rgbtGreen = t[1];
            temp[h][w].rgbtBlue = t[2];
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = temp[h][w];
        }
    }
}
