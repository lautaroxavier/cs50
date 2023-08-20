#include <cs50.h>
#include <stdio.h>

bool checkLuhnsAlgorithm(long number);
bool checkVISA(long number);
bool checkAMEX(long number);
bool checkMASTERCARD(long number);
long sumDigits(long number);

int main(void)
{
    long total = 0;
    long number = get_long("Number: ");
    if (!checkLuhnsAlgorithm(number))
    {
        printf("INVALID\n");
        return 0;
    }
    if (checkVISA(number))
    {
        printf("VISA\n");
        return 0;
    }
    if (checkMASTERCARD(number))
    {
        printf("MASTERCARD\n");
        return 0;
    }
    if (checkAMEX(number))
    {
        printf("AMEX\n");
        return 0;
    }
    printf("INVALID\n");
    return 0;
}

bool checkMASTERCARD(long number)
{
    int digits = 2;
    while (number > 100)
    {
        number /= 10;
        digits++;
    }
    if (digits == 16 && (number >= 51 && number <= 55))
    {
        return true;
    }
    return false;
}

bool checkAMEX(long number)
{
    int digits = 2;
    while (number > 100)
    {
        number /= 10;
        digits++;
    }
    if (digits == 15 && (number == 34 || number == 37))
    {
        return true;
    }
    return false;
}

bool checkVISA(long number)
{
    int digits = 1;
    while (number > 10)
    {
        number /= 10;
        digits++;
    }
    if ((digits == 13 || digits == 16) && number == 4)
    {
        return true;
    }
    return false;
}

bool checkLuhnsAlgorithm(long number)
{
    long total = 0;
    // multiply every other digit by 2 and sum
    long aux = number / 10;
    while (aux > 0)
    {
        total += sumDigits((aux % 10) * 2);
        aux /= 100;
    }
    // sum the rest of the digits
    aux = number;
    while (aux > 0)
    {
        total += aux % 10;
        aux /= 100;
    }
    // check if last digit is zero
    if (total % 10 == 0)
    {
        return true;
    }
    return false;
}

long sumDigits(long number)
{
    long res = 0;
    while (number > 0)
    {
        res += number % 10;
        number /= 10;
    }
    return res;
}