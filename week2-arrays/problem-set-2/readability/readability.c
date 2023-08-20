#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

string count_everything(string text, int *letters, int *words, int *sentences);

int main(void)
{
    string text = get_string("Text: ");
    int letters = 0;
    int words = 0;
    int sentences = 0;
    count_everything(text, &letters, &words, &sentences);
    float L = (float) letters / words * 100.0;
    float S = (float) sentences / words * 100.0;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (grade >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    printf("Grade %i\n", grade);
}

string count_everything(string text, int *letters, int *words, int *sentences)
{
    string res = text;
    while (*text)
    {
        if (isalpha(*text))
        {
            (*letters)++;
        }
        if (*text == ' ')
        {
            (*words)++;
        }
        if (*text == '?' || *text == '!' || *text == '.')
        {
            (*sentences)++;
        }
        text++;
    }
    (*words)++;
    return res;
}