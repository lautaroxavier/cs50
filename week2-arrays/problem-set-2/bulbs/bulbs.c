#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void bulbify(int n);

int main(void)
{
    string msg = get_string("Message: ");
    while (*msg)
    {
        bulbify(*msg);
        printf("\n");
        msg++;
    }
}

void bulbify(int n)
{
    int byte[BITS_IN_BYTE];
    int *pByte = byte + BITS_IN_BYTE - 1;
    for (int i = 0; i < BITS_IN_BYTE; i++, n /= 2, pByte--)
    {
        *pByte = n % 2;
    }
    pByte = byte;
    for (int j = 0; j < BITS_IN_BYTE; j++, pByte++)
    {
        print_bulb(*pByte);
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
