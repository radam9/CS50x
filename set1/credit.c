#include <cs50.h>
#include <stdio.h>
#include <math.h>

short value(long n, short p);

int main(void)
{
    // get user input
    long c;
    do
    {
        c = get_long("Enter card number: ");
    }
    while (c < 0);
    // initiate containers
    short even = 0;
    short odd = 0;
    // calculate length of card number
    long tc = c;
    short len = 0;
    while (tc != 0)
    {
        if (len % 2 == 0)
        {
            even += tc % 10;
        }
        else
        {
            short temp = (tc % 10) * 2;
            odd += (temp % 10) + (temp / 10);
        }
        tc /= 10;
        len++;
    }
    if (value((odd + even), 1) == 0)
    {
        // check for visa
        if ((len == 13 && value(c, 13) == 4) || (len == 16 && value(c, 16) == 4))
        {
            printf("Card type is: VISA\n");
        }
        //check for amex
        else if (len == 15 && value(c, 15) == 3 && ((value(c, 14) == 4) || (value(c, 14) == 7)))
        {
            printf("Card type is: AMEX\n");
        }
        // check for mc
        else if (len == 16 && value(c, 16) == 5 && (value(c, 15) > 0 && value(c, 15) < 6))
        {
            printf("Card type is: MASTERCARD\n");
        }
        else
        {
            //print invalid
            printf("INVALID\n");
        }
    }
    else
    {
        //print invalid
        printf("INVALID\n");
    }
}
// function to get the value of the digit at position "p" given number "n"
short value(long n, short p)
{
    long a = pow(10, p);
    long r = n % a;
    r /= pow(10, p - 1);
    return r;
}
