#include <stdbool.h>
#include <stdio.h>


int main(void)
{

FILE *fp = fopen("dictionaries/small", "r");
 char buffer[45];
 
 if (fp == NULL)
 {
     printf("incorrect directory");
     return 0;
 }
 
 while (fscanf(fp, "%s", buffer) != EOF)
 {
     printf("%s", buffer);
 }

return 0;

}