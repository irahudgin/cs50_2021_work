#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Gets credit card number
    long cc;
    do
    {
        cc = get_long("Number: ");
    }
    while (cc < 0);
    
    
    // Checks credit card length if valid for AMEX, MASTERCARD, VISA
    int length = 0;
    long cc1 = cc;
    while (cc1 > 0)
    {
        cc1 = cc1 / 10;
        length++;
    }
    
    // Checks length to verify card validity
    if (length != 13 && length !=15 && length !=16)
    {
        printf("INVALID\n");
        return 0;
    }
    
    // loop variables for luhn algorithm
    long x = cc;
    
    int sum1 = 0;
    int sum2 = 0;
    
    int n = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    int n5 = 0;
    int n6 = 0;
    
    // Breaks down cc number and inputs into variables to use for luhns algorithm
    while (x > 0)
    {
        n = x % 10;
        sum1 = sum1 + n;
        x = x / 10;
        
        
        
        n2 = x % 10;
        
        if (n2 > 4)
        {
            n3 = n2 * 2;
            n4 = n3 % 100 / 10;
            n5 = n3 % 10;
            n6 = n4 + n5;
        }
        else
        {
            n3 = n2 * 2;
            n6 = n3;
        }
        
        sum2 = sum2 + n6;
        x = x / 10;
    }
     
    // luhns algorithm sum   
    int sum3 = sum2 + sum1;
    
    // checks validity from luhns algorithm
    int check1 = sum3 % 10;
    if (check1 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    
    // get first digit
    long check2 = cc;
    for (int i = 1; i < length; i++)
    {
        check2 = check2 / 10;
    }
    
    // get second digit
     long check3 = cc;
    for (int i = 2; i < length; i++)
    {
        check3 = check3 / 10;
    }e
    
    check3 = check3 % 10;
    
    // series of statements to print which card it is
    if (check2 == 4)
    {
        printf("VISA\n");
        return 0;
    }
    else if ((check3 == 4 || check3 == 7) && check2 == 3)
    {
        printf("AMEX\n");
        return 0;
    }
    else if ((check3 > 0 && check3 < 6) && check2 == 5)
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }

    }
    