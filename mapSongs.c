#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <math.h>

int **songIds;
char ***songNames;

void initializeSongMapping(char ***names);
char * searchForChar(char ** arr, int n, char *value);

int main(int argc, char * argv[])
{
    char names[4][40];
    strcpy(names[0],"blue");
    strcpy(names[1],"chinatown");
    strcpy(names[2],"happy");
    strcpy(names[3],"win");
    initializeSongMapping(&names);
    searchForChar(names,4,"blue");
    
}

void initializeSongMapping(char ***names, int n)
{
    songNames = names;
    int l = n;
    int i;
    songIds = malloc(l*sizeof(int));
    for(i=0;i<l;i++)
        songIds[i] = 0;
}

char * searchForChar(char ** arr, int n, char *value)
{
   int first = 0;
   int last = n - 1;
   int middle = (first+last)/2;
   
   while( first <= last )
   {
      if ( strcmp(arr[middle],value)<0 )
         first = middle + 1;    
      else if ( strcmp(arr[middle],value)==0 ) 
      {
         printf("%d found at location %d.\n", value, middle+1);
         return arr[middle];
      }
      else
         last = middle - 1;
 
      middle = (first + last)/2;
   }
    if ( first > last )
    {
        printf("Not found! %s is not present in the list.\n", value);
        return NULL;
    }
}
