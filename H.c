
#include <stdio.h>

int main() {
    int cpu_state[8] = {0};
    int memory[256] = {0};

    FILE *file;
    int value;
    int count = 1;
    int command;
    int address;
    int error;

    // Начальные значения процессора
    cpu_state[0] = 1;
    cpu_state[1] = 0;
    cpu_state[2] = 0;
    cpu_state[3] = 250;
    cpu_state[4] = 0;
    cpu_state[5] = 0;
    cpu_state[6] = 0;
    cpu_state[7] = 0;

    // Вектор прерываний
    memory[0] = cpu_state[3];

    // Обработчик ошибок
    memory[250] = 0;

    // Открытие файла
    file = fopen("program.txt", "r");

    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    // Чтение программы из файла
    while (fscanf(file, "%d", &value) == 1) {

        if (count >= 250) {
            printf("Программа слишком большая!\n");
            fclose(file);
            return 1;
        }

        memory[count] = value;
        count++;
    }

    // Проверка EOF
    if (feof(file)) {
        printf("Достигнут конец файла EOF\n");
    }
    else {
        printf("Ошибка чтения файла!\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    if (count == 1) {
        printf("Файл пуст!\n");
        return 1;
    }

    printf("\nНачало выполнения программы\n\n");

    // Выполнение команд процессора
    while (cpu_state[4] == 0) {

        error = 0;
        address = -1;

        // Проверка счетчика команд
        if (cpu_state[0] < 1 || cpu_state[0] > 250) {
            error = 2;
        }

        if (error != 0) {
            cpu_state[5] = error;
            printf("Ошибка адреса команды!\n");
            cpu_state[0] = memory[0];
        }
        else {

            // Получение команды
            command = memory[cpu_state[0]];
            cpu_state[2] = command;

            printf("PC = %d | Команда = %d",
                   cpu_state[0], command);

            // Выбор команды
            switch (command) {

                case 0:
                    cpu_state[4] = 1;

                    printf(" | Остановка процессора");
                    printf(" | ACC = %d\n", cpu_state[1]);
                    break;

                case 1:
                case 2:
                case 3:

                    // Проверка наличия адреса операнда
                    if (cpu_state[0] >= 249) {
                        error = 3;
                        break;
                    }

                    // Получение адреса операнда
                    address = memory[cpu_state[0] + 1];

                    printf(" | Адрес = %d", address);

                    // Проверка адреса памяти
                    if (address < 1 || address >= 250) {
                        error = 3;
                        break;
                    }

                    // Проверка деления на ноль
                    if (command == 3 && memory[address] == 0) {
                        error = 1;
                        break;
                    }

                    // Выполнение команды
                    switch (command) {

                        case 1:
                            cpu_state[1] = memory[address];
                            break;

                        case 2:
                            cpu_state[1] =
                                cpu_state[1] * memory[address];
                            break;

                        case 3:
                            cpu_state[1] =
                                cpu_state[1] / memory[address];
                            break;
                    }

                    // Переход к следующей команде
                    cpu_state[0] += 2;

                    printf(" | Значение = %d", memory[address]);
                    printf(" | ACC = %d\n", cpu_state[1]);
                    break;

                default:
                    error = 4;
                    break;
            }

            // Обработка ошибок
            if (error != 0) {

                cpu_state[5] = error;

                if (error == 1) {
                    printf(" | Ошибка: деление на ноль!");
                }
                else if (error == 3) {
                    printf(" | Ошибка: неверный адрес!");
                }
                else {
                    printf(" | Неизвестная команда или адрес!");
                }

                printf(" | ACC = %d\n", cpu_state[1]);

                // Переход к обработчику ошибок
                cpu_state[0] = memory[0];
            }
        }
    }

    printf("\nВыполнение завершено.\n");
    printf("Итоговый аккумулятор: %d\n", cpu_state[1]);
    printf("Код ошибки: %d\n", cpu_state[5]);

    return 0;
}
