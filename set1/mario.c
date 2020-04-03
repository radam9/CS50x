#include <cs50.h>
#include <stdio.h>

void hash(int n);

int main(void)
{
    // declare height variable
    int h;
    // get height from user
    do
    {
        h = get_int("Enter the Height: ");
    }
    while (h < 1 || h > 8);
    // print obstacle 
    for (int j = 1; j <= h; j++)
    {
        // Print the spaces "8 - j" times
        for (int k = 0; k < h - j; k++)
        {
            printf(" ");
        }
        hash(j);
        printf("  ");
        hash(j);
        printf("\n");
    }
}

// Print hashes "n" times
void hash(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}
