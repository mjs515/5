#include <stdio.h>

int main() {
    int choice;
    double value, result;

    while (1) {
        printf("\n===== Конвертер данных =====\n");
        printf("1. Б → КБ\n");
        printf("2. КБ → МБ\n");
        printf("3. МБ → ГБ\n");
        printf("4. бит → байт\n");
        printf("5. Выход\n");
        printf("Выберите пункт: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода! Введите число.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice < 1 || choice > 5) {
            printf("Некорректный номер пункта! Попробуйте снова.\n");
            continue;
        }

        if (choice == 5) {
            printf("Выход из программы.\n");
            break;
        }

        printf("Введите значение: ");
        scanf("%lf", &value);

        switch (choice) {
            case 1:
                result = value / 1024.0;
                printf("%.2f Б = %.4f КБ\n", value, result);
                break;
            case 2:
                result = value / 1024.0;
                printf("%.2f КБ = %.4f МБ\n", value, result);
                break;
            case 3:
                result = value / 1024.0;
                printf("%.2f МБ = %.4f ГБ\n", value, result);
                break;
            case 4:
                result = value / 8.0;
                printf("%.2f бит = %.4f байт\n", value, result);
                break;
        }
    }

    return 0;
}
