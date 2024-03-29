package kata_7;

public class Solution_zero {
    public static int zeros(int n) {
        // Проверяем, что n не меньше нуля
        if (n < 0) {
            return -1;
        }
        // Считаем количество нулей
        int count = 0;
        for (int i = 5; n / i > 0; i *= 5) {
            count += n / i;
        }
        return count;
    }
}
/*
Эта функция работает так: она сначала проверяет, что n не меньше нуля.
Затем она считает количество нулей, деля число n на 5 и постоянно увеличивая его в 5 раз,
пока результат деления больше нуля. Поскольку факториал числа n содержит столько же нулей,
сколько чисел, кратных 5, в числах от 1 до n, то мы можем вычислить количество нулей, деля
число n на 5 и постоянно увеличивая его в 5 раз.
*/
