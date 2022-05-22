#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// node structure 
typedef struct node
{
    struct node *next[2];
    char alleles[2];
}
node;


node *mylist(int generation);

int main(void)
{
    // trying to return pointer to first link in node
    node *p = mylist(3);
    
}

node *mylist(int generation)
{
    node *n = malloc(sizeof(node));
    
    // This should be the last link in the node where the number is set to 1 and the link is NULL
    if (generation == 0)
    {
        n->number[0] = 1;
        n->number[1] = 1;
        n->next[0] = NULL;
        n->next[1] = NULL;

        return n;
    }
    else
    {
        // all other links will have random numbers
        n->number[0] = rand();
        n->number[1] = rand();
        n->next[0] = mylist(generation - 1);
        n->next[1] = mylist(generation - 1);
        return n;
    }
}