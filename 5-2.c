#include<stdio.h>
#define SIDE 5
int main(void)
{
    int i, j;
    for (i = 0; i < SIDE; i++)
    {
       for (j = 0; j < SIDE; j++) 
       {
          if (i == j || i + j == SIDE -1)
          {
              printf("x ");
          }
          else {
              printf("  "); 
          }
       }
       printf("\n");
    }
    return 0;
}
