#include <stdint.h>
#include "stdio.h"
#include "stdbool.h"
#include <stdlib.h>

static double print_ref_number()
{
    double number = 3.14;
    printf("number =+ %f\n", number);
}

static void print_ref_number_1()
{
    unsigned short number1 = 1u;
    unsigned short int number2 = 2u;
    short number3 = 3;
    short int number4 = -4;
    signed short number5 = 5;
    signed short int number6 = -6;

    long number7 = -2147483648l;
    long int number8 = -2147483648L;
    signed long number9 = 2147483647l;
    signed long int number10 = 2147483647L;

    unsigned long number11 = 4294967295ul;
    unsigned long int number12 = 4294967295UL;

    long long number13 = -9223372036854775807ll;
    long long int number14 = 9223372036854775807ll;
    signed long long number15 = -9223372036854775807LL;
    signed long long int number16 = 9223372036854775807LL;

    unsigned long long number17 = 18446744073709551615ull;
    unsigned long long int number18 = 18446744073709551615ULL;

    printf("number1 = %hu\n", number1);
    printf("number2 = %hu\n", number2);
    printf("number3 = %d\n", number3);
    printf("number4 = %d\n", number4);
    printf("number5 = %d\n", number5);
    printf("number6 = %d\n", number6);
    printf("number7 = %ld\n", number7);
    printf("number8 = %ld\n", number8);
    printf("number9 = %ld\n", number9);
    printf("number10 = %ld\n", number10);
    printf("number11 = %lu\n", number11);
    printf("number12 = %lu\n", number12);
    printf("number13 = %lld\n", number13);
    printf("number14 = %lld\n", number14);
    printf("number15 = %lld\n", number15);
    printf("number16 = %lld\n", number16);
    printf("number17 = %llu\n", number17);
    printf("number18 = %llu\n", number18);
}

static void print_ref_number_2()
{
    char letter = 65;
    printf("letter = %c\n", letter);
}

// псевдонимы
static void printlntypedef()
{
    typedef unsigned char vremyavnikuda;

    vremyavnikuda bype = 22;
    printf("bype = %d\n", bype);
}

// static void print_my_type_def_variable()
// {
//	 typedef int vremyavnikuda;
//	 printf("sizeof(vremyavnikuda)= %d\n", sizeof(vremyavnikuda));

//	 printf("sizeof(func prinlntypedef)= %d\n", sizeof(printlntypedef));
// }

// по пробуем определить результат выраежения
static void get_size_sum()
{
    int a, b;
    a = 10;
    b = 20;
    size_t sum = sizeof(a + b);
    printf("sizeof(sum = a+b) = %d\n", sum);
}

void task_1()
{
    char a = 'F';
    int number = 10;
    float number_float = 3.14;
    double double_number = 3.14159;
    printf("%d\n", a);
    printf("%d\n", number);
    printf("%f\n", number_float);
    printf("%f\n", double_number);
}

bool return_boot_function()
{
    int a = 10;
    int b = 10;

    bool c = a == b;
    return c;
}

int return_function_bit()
{
    int a = 2 << 2;
    printf("a = %d\n", a);
    return a;
    int b = 16 >> 3;
    printf("b = %d\n", b);
    return b;
}

unsigned int swap_bits()
{
    unsigned int num = 13;
    unsigned int bit1 = (num >> 1) & 1;
    unsigned int bit2 = (num >> 2) & 1;
    num ^= (1 << 1);
    num ^= (1 << 2);
    return num;
}

void print_str()
{
    char str[] = "Hellow vremyavnikuda";
    printf("%s\n", str);
}

/**
 * @brief Prints value of a variable declared with auto keyword.
 *
 * @details Declares integer variable with auto keyword and prints its value.
 */
int ref_auto()
{
    auto int a = 10;
    printf("a = %d\n", a);
}

bool lovefunc(int flower1, int flower2)
{
    return (flower1 + flower2) % 2 == 1;
}

void invert(int* values, size_t values_size)
{
    for (size_t i = 0; i < values_size; i++)
    {
        values[i] = -values[i];
    }
}

bool hero(uint32_t bullets, uint32_t dragons)
{
    return bullets >= dragons * 2;
}

unsigned short* reverse_seq(unsigned short num)
{
    unsigned short* sequence = malloc(num * sizeof(unsigned short));
    if (sequence == NULL) return NULL;

    for (unsigned short i = 0; i < num; i++)
    {
        sequence[i] = num - i;
    }
    return sequence;
}

int posledovatelnost_hisel(int number)
{
    do
    {
        printf("%d", number);
        number++;
    }
    while (number <= 5);
    return 0;
}

int posledovatelnost_cifr()
{
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", i);
    }
    return 0;
}

int main(void)
{
    posledovatelnost_cifr();
    //posledovatelnost_hisel(1);
    // printf("%d ", reverse_seq(5));
    // printf("%d\n", lovefunc(1, 4));
    // print_str();
    // ref_auto();
    // return_function_bit();
    // swap_bits();
    // printf("%s\n", return_boot_function() ? "true" : "false");
    // print_ref_number_1();
    // print_ref_number();
    // print_ref_number_2();
    // printlntypedef();
    // // создати свой тип данных и передаем,что бы по смотреть какой у него размер
    // // print_my_type_def_variable();
    // // определяем размер результата выражения
    // get_size_sum();
    // task_1();
    // return 0;
}
