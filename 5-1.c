#include<stdio.h>
int main(void) {
    double A = -2.0;
    double B = 2.0;
    double H = 1.0;
    double X, Y;
    int i = 1;
    printf("итерация\tX\t\tY\n");
    for (X = A; X <= B; X +=H) {
        Y = X * X + 2 * X + 1;
        printf("%d\t\t%.4f\t\t%.4f\n", i, X, Y);
        i++;
    }
    return 0;
}
