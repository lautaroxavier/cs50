#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt user for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    // print pyramid
    for (int i = 0; i < height; i++)
    {
        // print left triangle
        int j;
        for (j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        while (j < height)
        {
            printf("#");
            j++;
        }
        printf("  ");
        // print right triangle
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}