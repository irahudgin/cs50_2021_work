#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);
    
    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < 9);
    
    // TODO: Calculate number of years until we reach threshold
    
    int llama_babies = start/3;
    int dead_llamas = start/4;
    int total_llamas = start;
    int years = 0;
    
    while (total_llamas < end)
    {
        llama_babies = total_llamas/3;
        dead_llamas = total_llamas/4;
        total_llamas = total_llamas + llama_babies - dead_llamas; 
        years++;
    }
    // TODO: Print number of years
     printf("years: %i\n", years);
}