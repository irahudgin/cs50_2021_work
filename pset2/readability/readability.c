#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //First remove everything that isnt a part of the alphabet from the string
    //Count the words that are divided by spaces
    //Remove spaces and count letters
    
    string text = get_string("text: ");
    int length = strlen(text);
    
    float sent = 0, words = 1, letters = 0, letter = 0;
    
    for (int i = 0; i < length; i++)
    {
        letter = text[i];
        if (letter == 46 || letter == 63 || letter == 33)
        {
            sent++;
        }
        else if ((91 > letter && letter > 64) || (123 > letter && letter > 96))
        {
            letters++;
        }
        else if (letter == 32)
        {
            words++;
        }

    }
    
    float L = (letters / words) * 100;
    float S = (sent / words) * 100;

    // Index 1 is used in case of a rounding error for anything below 1
    float index1 = 0.0588 * L - 0.296 * S - 15.8;
    int index = (0.0588 * L - 0.296 * S - 15.8) + 0.5;
    
    //Conditions for printing output
    if (index > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else if (index1 < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else
    {
        printf("Grade %i\n", index);
        return 0;
    }
   
        
}