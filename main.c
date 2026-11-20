#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

static void show(const char *type, long value, size_t size)
{
    _Static_assert(LONG_MAX >= UINT_MAX, "long must hold every unsigned int");
    unsigned long bits = (unsigned long)value;
    printf("%-14s %12ld | %zu байт | ", type, value, size);
    for (int bit = (int)size * CHAR_BIT - 1; bit >= 0; --bit) {
        putchar(((bits >> bit) & 1u) ? '1' : '0');
        if (bit % CHAR_BIT == 0) {
            putchar(bit == 0 ? '\n' : ' ');
        }
    }
}

static int input_and_formats(void)
{
    char c;
    int code, i;
    float f;
    double d;

    puts("Задание 1. Ввод и форматированный вывод");
    puts("Введите число для char:");
    if (scanf("%d", &code) != 1 || code < CHAR_MIN || code > CHAR_MAX) {
        return 0;
    }
    c = (char)code;
    printf("Введено char: %d\n", c);

    puts("Введите int:");
    if (scanf("%d", &i) != 1) {
        return 0;
    }
    printf("Введено int: %d\n", i);

    puts("Введите float (дробная часть через точку):");
    if (scanf("%f", &f) != 1 || !isfinite(f)) {
        return 0;
    }
    printf("Введено float: %f\n", f);

    puts("Введите double (дробная часть через точку):");
    if (scanf("%lf", &d) != 1 || !isfinite(d)) {
        return 0;
    }
    printf("Введено double: %f\n", d);

    printf("\nС шириной поля: char |%6d| int |%12d| float |%12.3f| double |%18.6f|\n",
           c, i, f, d);
    unsigned int uc = (unsigned char)c;
    unsigned int ui = (unsigned int)i;
    puts("\nСимвол, десятичное, восьмеричное, шестнадцатеричное:");
    printf("char: %c, %d, %o, %x\n", (int)uc, c, uc, uc);
    printf("int:  %c, %d, %o, %x\n", (unsigned char)i, i, ui, ui);
    printf("float: %e\ndouble: %e\n", f, d);
    printf("Размеры в байтах: char %zu, int %zu, float %zu, double %zu\n",
           sizeof c, sizeof i, sizeof f, sizeof d);
    return 1;
}

static void limits(void)
{
    puts("\nЗадание 2. Границы типов");
    printf("char: CHAR_MIN=%d, CHAR_MAX=%d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char: 0 ... %u (UCHAR_MAX)\n", (unsigned int)UCHAR_MAX);
    printf("int: INT_MIN=%d, INT_MAX=%d\n", INT_MIN, INT_MAX);
    printf("unsigned int: 0 ... %u (UINT_MAX)\n", UINT_MAX);
    printf("float: от %.8e до %.8e, FLT_MIN=%.8e\n", -FLT_MAX, FLT_MAX, FLT_MIN);
    printf("double: от %.16e до %.16e, DBL_MIN=%.16e\n", -DBL_MAX, DBL_MAX, DBL_MIN);
}

static void chains(const char *title, char c, unsigned char uc,
                   int int_start, unsigned int uint_start)
{
    short int s;
    int i;
    unsigned short int us;
    unsigned int ui;

    printf("\n%s\n", title);
    puts("char -> short int -> int");
    s = c;
    i = s;
    show("char", c, sizeof c);
    show("short int", s, sizeof s);
    show("int", i, sizeof i);

    puts("unsigned char -> unsigned short int -> unsigned int");
    us = uc;
    ui = us;
    show("unsigned char", uc, sizeof uc);
    show("unsigned short", us, sizeof us);
    show("unsigned int", ui, sizeof ui);

    puts("int -> short int -> char");
    i = int_start;
    s = i;
    c = s;
    show("int", i, sizeof i);
    show("short int", s, sizeof s);
    show("char", c, sizeof c);

    puts("unsigned int -> unsigned short int -> unsigned char");
    ui = uint_start;
    us = ui;
    uc = us;
    show("unsigned int", ui, sizeof ui);
    show("unsigned short", us, sizeof us);
    show("unsigned char", uc, sizeof uc);
}

static void overflow(void)
{
    int s = INT_MAX;
    unsigned int u = UINT_MAX;

    puts("\nЗадание 4. Выход за границы диапазона");
    printf("int максимум: %d", s);
    ++s;
    printf(" -> %d\n", s);
    printf("unsigned int максимум: %u", u);
    ++u;
    printf(" -> %u\n", u);

    s = INT_MIN;
    u = 0;
    printf("int минимум: %d", s);
    --s;
    printf(" -> %d\n", s);
    printf("unsigned int минимум: %u", u);
    --u;
    printf(" -> %u\n", u);
}

int main(void)
{
    if (!input_and_formats()) {
        fputs("Некорректный ввод.\n", stderr);
        return 1;
    }
    limits();
    puts("\nЗадание 3. Преобразования типов");
    chains("Этап 1. Максимумы", CHAR_MAX, UCHAR_MAX, INT_MAX, UINT_MAX);
    chains("Этап 2. Минимумы", CHAR_MIN, 0, INT_MIN, 0);
    chains("Этап 3.1. Положительные", 65, 200, 483, 70000u);
    chains("Этап 3.2. Отрицательные", -65, 255, -483, 100000u);
    overflow();
    return 0;
}
