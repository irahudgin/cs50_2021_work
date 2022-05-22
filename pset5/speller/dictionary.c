// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>



// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hash table

int wordcounter;
const unsigned int N = 18000;
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash word to get hash index
    // Access linked list at that hash index
    
    node *cursor = table[hash(word)];
    // Use strcasecmp(case insensitive) while traversing the linked list to find the word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    
        cursor = cursor->next;
    }
    
    return false;
    // If word is found, return true because the word is in the dictionary
    // If not found return false
    
    // Traversing a linked list : Start with a cursor with pointer equal to start of first item, keep progressing cursor with
    // cursor = cursor->next until NULL, checking for the word along the way
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // http://www.cse.yorku.ca/%7Eoz/hash.html - djb2 hash function copied from here
    unsigned int hash = 5381;
        int c;

        while ((c = tolower(*word++)))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Opens file
    FILE* dict = fopen(dictionary, "r");
    // Checks to see if file directory exists
    if (dict == NULL)
    {
    return false;
    }

    // generate initial null hash table, and size

    for (int i = 0; i < N; i++)
    {
        table[i] = calloc(1, sizeof(node));
        table[i]->next = NULL;
    }

    
    // Return file stream to beginning to start loading into hash table
    fseek(dict, 0, SEEK_SET);

    // Puts word from dictionary into string "word1" using fscanf
    char word1[LENGTH + 1];
    wordcounter = 0;
    while (fscanf(dict, "%s", word1) != EOF)
    {
        
        // Hash function will return int index for first letter of word
        if (table[hash(word1)]->next == NULL) // if it is the first in the initial array
        {
            node *n = malloc(sizeof(node));
            strcpy(n->word, word1);
            // n->word = word1;
            table[hash(word1)]->next = n;
            n->next = NULL;
        }
        else // when theres a collision
        {
            node *n = malloc(sizeof(node));
            strcpy(n->word, word1);
            // n->word = word1;
            n->next = table[hash(word1)]->next;
            table[hash(word1)]->next = n;
        }
        wordcounter++;
    }
    
    // prints hashtable for debugging
    // for (int i = 0; i < N; i++)
    // {
    //     printf("table[%i] -- ", i);
    
    //     node *temp=table[i];
    
    //     while(temp!=NULL)
    //     {
    //          printf("%s -- ", temp->word);
    //          temp = temp->next;
    //     }
    //     printf("\n");
    // }
    fclose(dict);


    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wordcounter > 0)
    {
        return wordcounter;
    }
    else
    {
    return 0;
    }
    
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    
    node *tmp;
    node *cursor;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    
    }

return true;
}
