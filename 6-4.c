#include <stdio.h>

int main() {
    double requests;
    double cost1 = 0.0;
    double cost2 = 0.0;
    double cost3 = 0.0;
    double total = 0.0;

    printf("Введите количество API-запросов: ");
    scanf("%lf", &requests);

    if (requests < 0) {
        printf("Количество запросов не может быть отрицательным!\n");
        return 1;
    }

    if (requests <= 2000) {
        cost1 = requests * 0.02;
        total = cost1;
    }
    else if (requests <= 12000) {
        cost1 = 2000 * 0.02;
        cost2 = (requests - 2000) * 0.015;
        total = cost1 + cost2;
    }
    else {
        cost1 = 2000 * 0.02;
        cost2 = (12000 - 2000) * 0.015;
        cost3 = (requests - 12000) * 0.01;
        total = cost1 + cost2 + cost3;
    }

    printf("\nИсходное количество запросов: %.2f\n", requests);
    printf("----------------------------------------\n");
    printf("Разбивка по тарифным ступеням:\n");
    
    printf("  До 2000 запросов (0.02):     %.2f\n", cost1);
    
    if (requests > 2000) {
        printf("  От 2000 до 12000 (0.015):   %.2f\n", cost2);
    }
    
    if (requests > 12000) {
        printf("  Свыше 12000 (0.01):         %.2f\n", cost3);
    }
    
    printf("----------------------------------------\n");
    printf("Итоговая сумма:                %.2f\n", total);

    return 0;
}
