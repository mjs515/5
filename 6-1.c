#include <stdio.h>
#include <ctype.h>
int main(void) {
    int c;
    int prev = 0;
    int count = 0;
    printf("Введите текст, для завершения введите #:)\n");
    while ((c = getchar()) !='#') {
        if (isalpha(c)) {
            if (prev == 'e' && c =='i') {
                count++;
            }
        }
        prev = c;
   }
   printf("Количество вхождений последовательности \"ei\": %d\n", count);
   return 0;
}
