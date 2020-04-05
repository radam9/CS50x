#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{
    string key;
    if (argc == 1 || argc > 2)
    {
        //check that only 1 argument was given
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc == 2)
    {
        //convert key to lower
        for (int i = 0; argv[1][i]; i++)
        {
            argv[1][i] = tolower(argv[1][i]);
        }
        key = argv[1];
        int len = strlen(key);
        if (len != 26)
        {
            // check length of key
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        for (int i = 0; i < len; i++)
        {
            // check that all key characters are alphabetic
            if (isalpha(key[i]) == 0)
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
            // check for duplicates
            for (int m = 0; m < len - 1; m++)
            {
                for (int n = m + 1; n < len; n++)
                {
                    if (key[m] == key[n])
                    {
                        printf("Key must not contain repeated characters.\n");
                        return 1;
                    }
                }
            }
        }
    }
    // get user plaintext
    string text = get_string("plaintext: ");
    // convert plaintext to ciphertext
    printf("ciphertext: ");
    // looping though each character in the text.
    for (int i = 0; i < strlen(text); i++)
    {
        // checking with lower and upper case letters.
        for (int j = 0; j < 26; j++)
        {
            if (text[i] == 'a' + j)
            {
                printf("%c", key[j]);
            }
            else if (text[i] == 'A' + j)
            {
                printf("%c", key[j] - 32);
            }
        }
        if (isalpha(text[i]) == 0)
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}
