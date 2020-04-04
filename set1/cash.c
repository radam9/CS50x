#include <cs50.h>
#include <stdio.h>
#include <math.h>

// second solution
int main(void)
{
    // get change owed from user
    int co;
    do
    {
        co = round(get_float("Change owed: ") * 100);
    }
    while (co < 0);

    // initialize coin counter & count coins
    int cc = co / 25;
    cc += (co % 25) / 10;
    cc += ((co % 25) % 10) / 5;
    cc += (((co % 25) % 10) % 5) / 1;

    // print result
    printf("Least number of coins for change are: %i\n", cc);
}

// first solution
int main(void)
{
    // get change owed from user
    float co;
    do
    {
    co = get_float("Change owed: ");
    }
    while(co < 0);
    // rounding up the input to remove errors and convert dollars to cents
    co = round(co * 100);
    // initiate coin counter
    int cc = 0;
    // check for 0.25
    while (co >= 25)
    {
        co -= 25;
        cc++;
    }
    // check for 0.1
    while (co >= 10)
    {
        co -= 10;
        cc++;
    }
    // check for 0.05
    while (co >= 5)
    {
        co -= 5;
        cc++;
    }
    // check for 0.01
    while (co >= 1)
    {
        co -= 1;
        cc++;
    }
    // print result
    printf("Least number of coins for change are: %i\n",cc);
}
