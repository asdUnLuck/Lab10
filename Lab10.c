#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

double x, f1, f2, res;
int choice, N, i;
double eps, s_std, s_n, s_eps;

double fa(double x);
double fb(double x);
double product(double a, double b);
double diff_squares(double a, double b);
double double_sum(double a, double b);

double sin_n(double x, int N);
double sin_eps(double x, double eps);

double arcsin_n(double x, int N);
double arcsin_eps(double x, double eps);

int main(void) {
    setlocale(0, ".UTF8");

    printf("=== Задание 1 ===\n");
    printf("F1(x) = x^2 - 3x + 9, если x <= 3; 1 / (x^3 + 3), если x > 3\n");
    printf("F2(x) = x * e^(sin(x^2))\n\n");

    printf("Введите значение x: ");
    scanf("%lf", &x);

    f1 = fa(x);
    f2 = fb(x);

    printf("\nРезультаты вычислений:\n");
    printf("fa(x) = %lf, fb(x) = %lf\n", f1, f2);
    printf("произведение = %lf\n", product(f1, f2));
    printf("разность квадратов = %lf\n", diff_squares(f1, f2));
    printf("удвоенная сумма = %lf\n\n", double_sum(f1, f2));

    do {
        printf("--- Меню ---\n");
        printf("1 - Вычислить F1(x)\n");
        printf("2 - Вычислить F2(x)\n");
        printf("3 - Произведение F1(x) * F2(x)\n");
        printf("4 - Разность квадратов F1(x)^2 - F2(x)^2\n");
        printf("5 - Удвоенная сумма 2 * (F1(x) + F2(x))\n");
        printf("0 - Выход из меню\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5) {
            printf("Введите x: ");
            scanf("%lf", &x);
            f1 = fa(x);
            f2 = fb(x);
        }

        switch (choice) {
        case 1:
            res = f1;
            printf("F1(%.4lf) = %lf\n\n", x, res);
            break;
        case 2:
            res = f2;
            printf("F2(%.4lf) = %lf\n\n", x, res);
            break;
        case 3:
            res = product(f1, f2);
            printf("Произведение = %lf\n\n", res);
            break;
        case 4:
            res = diff_squares(f1, f2);
            printf("Разность квадратов = %lf\n\n", res);
            break;
        case 5:
            res = double_sum(f1, f2);
            printf("Удвоенная сумма = %lf\n\n", res);
            break;
        case 0:
            printf("Выход из меню...\n\n");
            break;
        default:
            printf("Неизвестный пункт меню. Попробуйте снова.\n\n");
            break;
        }
    } while (choice != 0);

    printf("=== Задание 2. Вычисление sin(x) ===\n");
    printf("Введите x (в радианах): ");
    scanf("%lf", &x);

    printf("Введите число членов ряда N: ");
    scanf("%d", &N);

    printf("Введите точность eps (например, 0.0001): ");
    scanf("%lf", &eps);

    if (N < 1 || eps <= 0) {
        printf("Ошибка: N должно быть >= 1, eps > 0\n");
    }
    else {
       
        s_std = sin(x);

        s_n = sin_n(x, N);

        s_eps = sin_eps(x, eps);

        printf("\n--- Результаты для sin(%lf) ---\n", x);
        printf("1) Стандартная sin(x) = %.10lf\n", s_std);
        printf("2) Ряд по N = %d      = %.10lf, отклонение = %+.4e\n", N, s_n, s_n - s_std);
        printf("3) Ряд по eps = %g    = %.10lf, отклонение = %+.4e\n\n", eps, s_eps, s_eps - s_std);
    }

    printf("\n=== Задание 2 (Вариант 6). Вычисление arcsin(x) ===\n");
    printf("Введите x (|x| < 1): ");
    scanf("%lf", &x);
    if (fabs(x) >= 1.0) {
        printf("Ошибка: для arcsin(x) модуль x должен быть меньше 1\n");
    } else {
        printf("Введите N: "); scanf("%d", &N);
        printf("Введите eps: "); scanf("%lf", &eps);
        s_std = asin(x);
        s_n = arcsin_n(x, N);
        s_eps = arcsin_eps(x, eps);
        printf("1) Стандартная asin(x) = %.10lf\n", s_std);
        printf("2) Ряд по N = %d      = %.10lf, отклонение = %+.4e\n", N, s_n, s_n - s_std);
        printf("3) Ряд по eps = %g    = %.10lf, отклонение = %+.4e\n", eps, s_eps, s_eps - s_std);
    }
    

    return 0;
}

double fa(double x) {
    double y;
    if (x <= 3.0) {
        y = x * x - 3.0 * x + 9.0;
    }
    else {
        y = 1.0 / (x * x * x + 3.0);
    }
    return y;
}

double fb(double x) {
    double y;
    y = x * exp(sin(x * x));
    return y;
}

double product(double a, double b) {
    return a * b;
}

double diff_squares(double a, double b) {
    return (a * a) - (b * b);
}

double double_sum(double a, double b) {
    return 2.0 * (a + b);
}

double sin_n(double x, int N) {
    double sum = 0.0;
    double term = x;
    int k;
    for (k = 1; k <= N; k++) {
        sum += term;
        term *= -x * x / ((2.0 * k) * (2.0 * k + 1.0));
    }
    return sum;
}

double sin_eps(double x, double eps) {
    double sum = 0.0;
    double term = x;
    int k = 1;
    while (fabs(term) >= eps) {
        sum += term;
        term *= -x * x / ((2.0 * k) * (2.0 * k + 1.0));
        k++;
    }
    return sum;
}

double arcsin_n(double x, int N) {
    double sum = x;
    double term = x;
    int n;
    for (n = 1; n <= N; n++) {
        term *= (x * x * (2.0 * n - 1.0) * (2.0 * n - 1.0)) / ((2.0 * n) * (2.0 * n + 1.0));
        sum += term;
    }
    return sum;
}

double arcsin_eps(double x, double eps) {
    double sum = x;
    double term = x;
    int n = 1;
    while (fabs(term) >= eps) {
        term *= (x * x * (2.0 * n - 1.0) * (2.0 * n - 1.0)) / ((2.0 * n) * (2.0 * n + 1.0));
        sum += term;
        n++;
    }
    return sum;
}