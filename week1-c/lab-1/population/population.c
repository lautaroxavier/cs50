#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    int end;
    int deaths;
    int births;
    int years = 0;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);
    // TODO: Prompt for end size
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);
    // TODO: Calculate number of years until we reach threshold
    while (start < end)
    {
        deaths = start / 4;
        births = start / 3;
        start += births - deaths;
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}