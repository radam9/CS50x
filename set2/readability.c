#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // get user input
    string text = get_string("Text: ");
    // initiating counters and switch "a"
    int letters = 0;
    int words = 1;
    int sentences = 0;
    int a = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // check if alphabet, add letter and change switch.
        if (isalpha(text[i]))
        {
            letters++;
            a = 1;
        }
        // check if sentence
        else if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            sentences++;
        }
        // check if whitespace, if switch then add words
        else if (isspace(text[i]) && a == 1)
        {
            words++;
            a = 0;
        }
    }
    float l = (float) letters / words * 100;
    float s = (float) sentences / words * 100;
    int grade = round(0.0588 * l - 0.296 * s - 15.8);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
