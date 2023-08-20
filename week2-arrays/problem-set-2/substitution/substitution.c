#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

bool is_valid_key(string k);
char cipher(char c, string k);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (!is_valid_key(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");
    while (*plaintext)
    {
        printf("%c", cipher(*plaintext, argv[1]));
        plaintext++;
    }
    printf("\n");
}

char cipher(char c, string k)
{
    if (isupper(c))
    {
        return toupper(*(k + c - 'A'));
    }
    else if (islower(c))
    {
        return tolower(*(k + c - 'a'));
    }
    return c;
}

bool is_valid_key(string k)
{
    int len = 0;
    string start = k;
    while (*k)
    {
        if (!isalpha(*k))
        {
            return false;
        }
        for (int i = 0; i < len; i++)
        {
            if (tolower(start[i]) == tolower(*k))
            {
                return false;
            }
        }
        len++;
        k++;
    }
    if (len == 26)
    {
        return true;
    }
    return false;
}