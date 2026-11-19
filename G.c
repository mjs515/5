
#include <stdio.h>

int main() {
    int cpu_state[8] = {0};
    int memory[256] = {0};

    FILE *file;
    int value;
    int count = 1;

    // Настройка процессора
    cpu_state[0] = 1;    // Счетчик команд (PC)
    cpu_state[1] = 0;    // Аккумулятор (ACC)
    cpu_state[2] = 0;    // Регистр команд (IR)
    cpu_state[3] = 250;  // Адрес обработчика ошибок
    cpu_state[4] = 0;    // Флаг остановки
    cpu_state[5] = 0;    // Код ошибки
    cpu_state[6] = 0;    // Резерв
    cpu_state[7] = 0;    // Резерв

    // Вектор прерываний
    memory[0] = cpu_state[3];

    // Обработчик ошибок: команда СТОП
    memory[250] = 0;

    // Открываем файл с программой
    file = fopen("program.txt", "r");

    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    // Загружаем числа в память
    while (fscanf(file, "%d", &value) == 1) {
        if (count >= 250) {
            printf("Программа слишком большая!\n");
            fclose(file);
            return 1;
        }

        memory[count] = value;
        count++;
    }

    fclose(file);

    if (count == 1) {
        printf("Файл пуст!\n");
        return 1;
    }

    printf("Начало выполнения программы\n\n");

    // Выполнение команд процессора
    while (cpu_state[4] == 0) {

        int command;
        int address = -1;
        int error = 0;

        // Проверяем счетчик команд
        if (cpu_state[0] < 1 || cpu_state[0] >= 250) {

            if (cpu_state[5] == 0) {
                error = 2;
            }
        }

        // Если произошла ошибка, переходим к обработчику
        if (error != 0) {
            cpu_state[5] = error;
            printf("Ошибка: неверный адрес команды!\n");

            cpu_state[0] = memory[0];
            continue;
        }

        // Получаем команду из памяти
        command = memory[cpu_state[0]];
        cpu_state[2] = command;

        printf("PC = %d | Команда = %d",
               cpu_state[0], command);

        // Команда СТОП
        if (command == 0) {

            cpu_state[4] = 1;

            printf(" | Остановка процессора");
            printf(" | ACC = %d\n", cpu_state[1]);

        }

        // Команды 1, 2 и 3
        else if (command == 1 ||
                 command == 2 ||
                 command == 3) {

            // Получаем адрес операнда
            address = memory[cpu_state[0] + 1];

            printf(" | Адрес = %d", address);

            // Проверяем адрес памяти
            if (address < 1 || address >= 250) {
                error = 3;
            }

            // Команда деления
            else if (command == 3 && memory[address] == 0) {
                error = 1;
            }

            // Выполняем команду
            if (error == 0) {

                if (command == 1) {
                    cpu_state[1] = memory[address];
                }

                else if (command == 2) {
                    cpu_state[1] =
                        cpu_state[1] * memory[address];
                }

                else if (command == 3) {
                    cpu_state[1] =
                        cpu_state[1] / memory[address];
                }

                // Переходим к следующей команде
                cpu_state[0] += 2;

                printf(" | Значение = %d", memory[address]);
                printf(" | ACC = %d\n", cpu_state[1]);
            }

            else {
                cpu_state[5] = error;

                if (error == 1) {
                    printf(" | Ошибка: деление на ноль!");
                }
                else {
                    printf(" | Ошибка: неверный адрес!");
                }

                printf(" | ACC = %d\n", cpu_state[1]);

                // Переход к обработчику ошибок
                cpu_state[0] = memory[0];
            }
        }

        // Неизвестная команда
        else {

            cpu_state[5] = 4;

            printf(" | Ошибка: неизвестная команда");
            printf(" | ACC = %d\n", cpu_state[1]);

            cpu_state[0] = memory[0];
        }
    }

    printf("\nВыполнение завершено.\n");
    printf("Итоговый аккумулятор: %d\n", cpu_state[1]);
    printf("Код ошибки: %d\n", cpu_state[5]);

    return 0;
}
