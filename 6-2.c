#include <stdio.h>
#include <wchar.h>
#include <locale.h>
int main(void) {
    setlocale(LC_ALL, "");
    wint_t ch, prev;
    int count = 0;
    int first = 1;
    printf("Введите текст (для окончания введите #):\n");
    while ((ch = getwchar()) != WEOF && ch != L'#') {
        if (!first && ch == prev) {
            count++;
        }
        prev = ch;
        first = 0;
   }
   printf("Количество одинаковых соседних пар: %d\n", count);
   return 0;
}
