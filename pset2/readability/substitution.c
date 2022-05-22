#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    
    // key is now variable that holds inputed encryption key
    string key = argv[1];
    //
    
    // Checks that input key is valid
    if (argc != 2)
    {
        printf("Use one key for the alphabet\n");
        return 1;
    }
    else if ((strlen(argv[1])) != 26)
    {
        printf("Make sure encryption key is 26 letters long\n");
        return 1;
    }
    //
    
    
    // Nested loop that checks every letter of key to make sure every letter is unique
    int checkkey;
    int checkkey2;
    for (int k = 0; k < 25; k++)
    {
        checkkey = key[k];
        for (int l = 0; l < k; l++)
        {
            checkkey2 = key[l];
            if (checkkey == checkkey2)
            {
                printf("Make sure no duplicate alphabet letters are used\n");
                return 1;
            }
        }
    }
    
    // Loop that makes sure key has valid characters
    for (int p = 0, n = (strlen(key)); p < n; p++)
    {
        checkkey = key[p];
        if (checkkey < 65 || checkkey > 122)
        {
            printf("Use valid characters\n");
            return 1;
        }
        else if (checkkey > 90 && checkkey < 97)
        {
            printf("Use valid characters\n");
            return 1;
        }
    }

    // Fills out nkey array with ascii codes of key
    int nkey[26];
    for (int o = 0, n = strlen(key); o < n; o++)
    {
        nkey[o] = key[o];
    }
    //

    // loop that generates two alphabets based off key
    char l_alph[27];
    char u_alph[27];
    for (int j = 0; j < 27; j++)
    {
      if ((isupper(key[j])) != 0)
      {
          l_alph[j] = nkey[j] + 32;
          u_alph[j] = nkey[j];
      }
      else if ((islower(key[j])) != 0)
        {
            l_alph[j] = nkey[j];
            u_alph[j] = nkey[j] - 32;
        }
    }
    //
    
    
    l_alph[26] = '\0';
    u_alph[26] = '\0';
    
    
    string l_a = l_alph;
    string u_a = u_alph;
        
    string word = get_string("plain text: ");
    printf("ciphertext: ");
    int ind;
 
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i]) != 0)
        {
            ind = word[i] - 65;
            printf("%c", u_a[ind]);
        }
        else if (islower(word[i]) != 0)
        {
            ind = word[i] - 97;
            printf("%c", l_a[ind]);
        }
        else
        {
            printf("%c", word[i]);
        }
    }
    
    printf("\n");
    
}