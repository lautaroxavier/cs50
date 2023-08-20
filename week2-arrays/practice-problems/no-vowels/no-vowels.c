// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

string replace(string word);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("This function takes exactly one argument.\n");
        return 1;
    }
    printf("%s\n", replace(*(++argv)));
}

string replace(string word)
{
    char *pWord = word;
    while(*pWord)
    {
        switch (tolower(*pWord))
        {
            case 'a':
                *pWord = '6';
                break;
            case 'e':
                *pWord = '3';
                break;
            case 'i':
                *pWord = '1';
                break;
            case 'o':
                *pWord = '0';
                break;
        }
        pWord++;
    }
    return word;
}