#include "stdio.h"

void printNumber(int number)
{
    printf("number = %d \n",number);
}

int main(void)
{
    int number = 10;
    printNumber(number);
    return 0;
}
