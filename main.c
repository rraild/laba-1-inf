#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

static void print_bits(const void *address, size_t size)
{
    const unsigned char *bytes = address;
    const unsigned int marker = 1;
    const int little_endian = *(const unsigned char *)&marker;

    for (size_t i = 0; i < size; ++i) {
        size_t index = little_endian ? size - 1 - i : i;
        for (int bit = CHAR_BIT - 1; bit >= 0; --bit) {
            putchar(((bytes[index] >> bit) & 1u) ? '1' : '0');
        }
        if (i + 1 < size) {
            putchar(' ');
        }
    }
}

static void print_signed(const char *type, long long value,
                         const void *address, size_t size)
{
    printf("%-19s = %12lld | %zu байт | ", type, value, size);
    print_bits(address, size);
    putchar('\n');
}

static void print_unsigned(const char *type, unsigned long long value,
                           const void *address, size_t size)
{
    printf("%-19s = %12llu | %zu байт | ", type, value, size);
    print_bits(address, size);
    putchar('\n');
}

static int task1(void)
{
    char c;
    int i;
    float f;
    double d;
    int char_code;

    puts("ЗАДАНИЕ 1. Ввод и форматированный вывод");
    printf("Введите числовое значение char [%d, %d]: ", CHAR_MIN, CHAR_MAX);
    fflush(stdout);
    if (scanf("%d", &char_code) != 1 ||
        char_code < CHAR_MIN || char_code > CHAR_MAX) {
        fputs("Некорректное значение char.\n", stderr);
        return 0;
    }
    c = (char)char_code;
    printf("Введено char: %d\n", (int)c);

    printf("Введите int [%d, %d]: ", INT_MIN, INT_MAX);
    fflush(stdout);
    if (scanf("%d", &i) != 1) {
        fputs("Некорректное значение int.\n", stderr);
        return 0;
    }
    printf("Введено int: %d\n", i);

    printf("Введите float (дробная часть через точку): ");
    fflush(stdout);
    if (scanf("%f", &f) != 1 || !isfinite(f)) {
        fputs("Некорректное значение float.\n", stderr);
        return 0;
    }
    printf("Введено float: %f\n", (double)f);

    printf("Введите double (дробная часть через точку): ");
    fflush(stdout);
    if (scanf("%lf", &d) != 1 || !isfinite(d)) {
        fputs("Некорректное значение double.\n", stderr);
        return 0;
    }
    printf("Введено double: %f\n", d);

    printf("\nВывод с заданной шириной полей:\nchar: |%6d|\nint: |%14d|\n"
           "float: |%14.3f|\ndouble: |%20.6f|\n",
           (int)c, i, (double)f, d);

    puts("\nСимвол, десятичная, восьмеричная и шестнадцатеричная запись:");
    printf("char: символ='%c', десятичное=%d, восьмеричное=%o, шестнадцатеричное=%x\n",
           (int)(unsigned char)c, (int)c,
           (unsigned int)(unsigned char)c, (unsigned int)(unsigned char)c);
    printf("int:  символ='%c', десятичное=%d, восьмеричное=%o, шестнадцатеричное=%x\n",
           (int)(unsigned char)i, i, (unsigned int)i, (unsigned int)i);
    printf("float: %e\ndouble: %e\n", (double)f, d);
    printf("\nsizeof(char)=%zu, sizeof(int)=%zu, "
           "sizeof(float)=%zu, sizeof(double)=%zu, CHAR_BIT=%d\n",
           sizeof c, sizeof i, sizeof f, sizeof d, CHAR_BIT);
    return 1;
}

static void task2(void)
{
    puts("\nЗАДАНИЕ 2. Границы типов");
    printf("CHAR_MIN=%d, CHAR_MAX=%d\n", CHAR_MIN, CHAR_MAX);
    printf("SCHAR_MIN=%d, SCHAR_MAX=%d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: минимум=0, UCHAR_MAX=%u\n", (unsigned int)UCHAR_MAX);
    printf("SHRT_MIN=%d, SHRT_MAX=%d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: минимум=0, USHRT_MAX=%u\n", (unsigned int)USHRT_MAX);
    printf("INT_MIN=%d, INT_MAX=%d\n", INT_MIN, INT_MAX);
    printf("unsigned int: минимум=0, UINT_MAX=%u\n", UINT_MAX);
    printf("float: минимум=%.*e, максимум=%.*e\n",
           FLT_DECIMAL_DIG - 1, -(double)FLT_MAX,
           FLT_DECIMAL_DIG - 1, (double)FLT_MAX);
    printf("FLT_MIN=%.*e, FLT_TRUE_MIN=%.*e\n",
           FLT_DECIMAL_DIG - 1, (double)FLT_MIN,
           FLT_DECIMAL_DIG - 1, (double)FLT_TRUE_MIN);
    printf("double: минимум=%.*e, максимум=%.*e\n",
           DBL_DECIMAL_DIG - 1, -DBL_MAX, DBL_DECIMAL_DIG - 1, DBL_MAX);
    printf("DBL_MIN=%.*e, DBL_TRUE_MIN=%.*e\n",
           DBL_DECIMAL_DIG - 1, DBL_MIN, DBL_DECIMAL_DIG - 1, DBL_TRUE_MIN);
}

static void conversion_chains(const char *title, char char_start,
                              unsigned char uchar_start, int int_start,
                              unsigned int uint_start)
{
    char c;
    short int s;
    int i;
    unsigned char uc;
    unsigned short int us;
    unsigned int ui;

    printf("\n%s\n", title);
    puts("char -> short int -> int");
    c = char_start;
    s = c;
    i = s;
    print_signed("char", c, &c, sizeof c);
    print_signed("short int", s, &s, sizeof s);
    print_signed("int", i, &i, sizeof i);

    puts("unsigned char -> unsigned short int -> unsigned int");
    uc = uchar_start;
    us = uc;
    ui = us;
    print_unsigned("unsigned char", uc, &uc, sizeof uc);
    print_unsigned("unsigned short int", us, &us, sizeof us);
    print_unsigned("unsigned int", ui, &ui, sizeof ui);

    puts("int -> short int -> char");
    i = int_start;
    s = i;
    c = s;
    print_signed("int", i, &i, sizeof i);
    print_signed("short int", s, &s, sizeof s);
    print_signed("char", c, &c, sizeof c);

    puts("unsigned int -> unsigned short int -> unsigned char");
    ui = uint_start;
    us = ui;
    uc = us;
    print_unsigned("unsigned int", ui, &ui, sizeof ui);
    print_unsigned("unsigned short int", us, &us, sizeof us);
    print_unsigned("unsigned char", uc, &uc, sizeof uc);
}

static void task3(void)
{
    puts("\nЗАДАНИЕ 3. Преобразования при присваивании и двоичное доказательство");
    puts("Биты показаны от старшего байта к младшему.");
    conversion_chains("Этап 1: максимальные значения",
                      CHAR_MAX, UCHAR_MAX, INT_MAX, UINT_MAX);
    conversion_chains("Этап 2: минимальные значения",
                      CHAR_MIN, 0, INT_MIN, 0);
    conversion_chains("Этап 3.1: положительные значения, int = 483",
                      65, 200, 483, 70000u);
    conversion_chains("Этап 3.2: отрицательные значения, int = -483",
                      (CHAR_MIN < 0 ? -65 : 65), 255, -483, 100000u);
    conversion_chains("Этап 3.3: потеря старших битов, int = 70000",
                      100, 128, 70000, 305419896u);
}

static void task4(void)
{
    signed int s;
    unsigned int u;

    puts("\nЗАДАНИЕ 4. Арифметика на границах диапазона");
    puts("Для знаковой арифметики в этом опыте требуется GCC/Clang -fwrapv.");
    s = INT_MAX;
    printf("signed int максимум: %d", s);
    s++;
    printf(" -> максимум+1: %d\n", s);

    u = UINT_MAX;
    printf("unsigned int максимум: %u", u);
    u++;
    printf(" -> максимум+1: %u\n", u);

    s = INT_MIN;
    printf("signed int минимум: %d", s);
    s--;
    printf(" -> минимум-1: %d\n", s);

    u = 0;
    printf("unsigned int минимум: %u", u);
    u--;
    printf(" -> минимум-1: %u\n", u);
}

int main(void)
{
    if (!task1()) {
        return 1;
    }
    task2();
    task3();
    task4();
    return 0;
}
