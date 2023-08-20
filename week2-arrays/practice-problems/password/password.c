// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool lowercase = false;
    bool uppercase = false;
    bool number = false;
    bool symbol = false;
    while (*password)
    {
        if (islower(*password))
        {
            lowercase = true;
        }
        else if (isupper(*password))
        {
            uppercase = true;
        }
        else if (isdigit(*password))
        {
            number = true;
        }
        else if (ispunct(*password))
        {
            symbol = true;
        }
        password++;
    }
    return uppercase && lowercase && number && symbol;
}