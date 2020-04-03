#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get the user's name
    string name = get_string("What is your name?\n");
    // Greet the user
    printf("hello, %s\n", name);
}
