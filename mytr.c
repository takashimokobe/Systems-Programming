#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "mytr.h"

/* Name: Takahiro Shimokobe
 * Section: 3
 * Professor: Dr. Taylor
 * 
 * Description: Implement a version of the Unix tr program.
 */

/* mytr should translate or delete characters from its input. The program should work as a filter,
   reading the input stream, and writing to the output stream. */

void translate(char *set1, char *set2);
void delete(char *set1);
void checkSize(char *set1, char *set2);
void check_escape(char *set1);

int main(int argc, char *argv[])
{
   if(argc!=3){
      fprintf(stderr, "mytr: improper number of arguments\nUsage: %s <SET1> <SET2>\n", argv[0]);
      return -1;
   }
   else{
      if(argv[1][0] == '-'){
         if(strcmp(argv[1], "-d")==0){
            delete(argv[2]);
            return 0;
         }
         else{
            fprintf(stderr, "mytr: Make sure -d switch is being used.\n");
            return -1;
         }
      }
      else{
         checkSize(argv[1], argv[2]);
         check_escape(argv[1]);
         translate(argv[1], argv[2]);
         return 0;
      }
   }
   return 0;
}

void translate(char set1[], char set2[])
{
   int i, j;
   char c;

   char arr[256];

   for(i=0;i<256;i++)
      arr[i] = i;
      
   for(j = 0; set1[j] != '\0'; j++){   /* If there is something in set1. */
      if(set2[j] != set1[j]){          /* If the char in set 2 is not equal to the char in set1 */
         arr[(int)set1[j]] = set2[j];  /* Replace the position of set2 with the ASCII of set1. */
      }
   }
   while((c = getchar())!=EOF)
   {
      putchar(arr[(int)c]);
   }
}

void delete(char set1[]){
   int i, j;
   char c;

   char arr[256];

   for(i = 0; i < 256; i++)
      arr[i] = i;

   for(j = 0; set1[j] != '\0'; j++){   /* If there is something in set2. */
      arr[(int)set1[j]] = '\0';           /* Replace the position of set1 with the ASCII of null */
   }

   while((c = getchar()) != EOF){
      if(arr[(int)c]!='\0'){              /*If not a null character*/
         putchar(arr[(int)c]);            /*It's okay to print out*/
      }
   }
}

void checkSize(char set1[], char set2[])
{
   int newsize, oldsize, i;

   if(strlen(set1) > strlen(set2)){
      newsize = strlen(set1);
      oldsize = strlen(set2);
      for(i = oldsize; i < newsize; i++){
         set2[i] = set2[oldsize - 1];
      }
   }
   else{
      newsize = strlen(set1);
      for(i =0; i < newsize; i++){
         set1[i] = set1[i];
         set2[i] = set2[i];
      }
   }
}

void check_escape(char set[]) /* Doesn't Work, fix later? */
{
   int i;
   while(set[i]!='\0'){
      if(set[i] == '\\'){
         switch(set[i+1]){
            case '\\':
               set[i+1] = '\\';
               break;
            case 'n':
               set[i+1] = '\n';
               break;
            case 't':
               set[i+1] = '\t';
               break;
            default:
               break;
         }
      }
      i++;;
   }
}
