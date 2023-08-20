#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

bool isNumber(char *number);

int main(int argc, string argv[])
{
    if (argc != 2 || !isNumber(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int k = atoi(argv[1]);
    string plaintext = get_string("plaintext:  ");
    string start = plaintext;
    while (*plaintext)
    {
        if (isupper(*plaintext))
        {
            *plaintext = 'A' + (((*plaintext - 'A') + k) % 26);
        }
        else if (islower(*plaintext))
        {
            *plaintext = 'a' + (((*plaintext - 'a') + k) % 26);
        }
        plaintext++;
    }
    printf("ciphertext: %s\n", start);
}

bool isNumber(char *number)
{
    while (*number)
    {
        if (!isdigit(*number))
        {
            return false;
        }
        number++;
    }
    return true;
}