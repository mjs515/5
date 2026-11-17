#include<stdio.h>
int main(void) {
    int n;
    int count3 = 0, count5 = 0;
    int sum3 = 0, sum5 = 0;
    printf("Введите числа(0 для завершения):\n");
    while (1) {
        scanf("%d", &n);
        if (n == 0) {
            break;
        }
        if (n % 3 ==0) {
            count3++;
            sum3 +=n;
        }
        else if (n % 5 == 0) {
                 count5++;
                 sum5 += n;
        }
    }
    printf("\nЧисла, кратные 3:\n");
    printf("Количество: %d\n", count3);
    if (count3 > 0) {
        printf("Среднее арифмитическое: %.2f\n",
                (double)sum3 / count3);
    }
    else {
        printf("Нет таких чисел\n");
    }

    printf("\nЧисла, кратные 5:\n");
    printf("Количество: %d\n", count5);
    if (count5 > 0) {
        printf("Среднее арифмитическое: %.2f\n",
                (double)sum5 / count5);
   }
   else {
       printf("Нет таких чисел\n");
   }
   return 0;
}
