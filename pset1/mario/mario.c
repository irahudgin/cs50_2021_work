#include <stdio.h>
#include <cs50.h>

void block(int n);
void spaces(int n);


int main(void)
{
    // Asks user for positive integer between 1 and 8
    int levels;
    do
    {
        levels = get_int("Height: ");
    }
    while (levels < 1 || levels > 8);
    
    // Creates pyramid with levels indicated by user
    int spacemove = 1;
    for (int i = 0; i < levels; i++)
    {
        spaces(levels - spacemove);
        spacemove++;
        block(i + 1);
        spaces(2);
        block(i + 1);
        printf("\n");
    }
}

// Function that prints blocks
void block(int n)
{
    for (int j = 0; j < n; j++)
    {
        printf("#");
    }
}

// Function that prints spaces
void spaces(int n)
{
    for (int u = 0; u < n; u++)
    {
        printf(" ");
    }
}