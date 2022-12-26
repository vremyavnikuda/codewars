/*
Следующее большее число с теми же цифрами
*/
package kata_6;
import java.util.Arrays;

public class nextBigger {
    public static long nextBiggerNumber(long n) {
        // Преобразуем целое число в массив цифр
        int[] digits = String.valueOf(n).chars().map(Character::getNumericValue).toArray();

        // Ищем точку перестановки
        int swapPoint = -1;
        for (int i = digits.length - 1; i > 0; i--) {
            if (digits[i] > digits[i - 1]) {
                swapPoint = i - 1;
                break;
            }
        }

        // Если точка перестановки не найдена, вернуть -1
        if (swapPoint == -1) {
            return -1;
        }

        // Ищем наименьшую цифру, которая больше цифры на точке перестановки
        int minLarger = Integer.MAX_VALUE;
        int minLargerIndex = 0;
        for (int i = swapPoint + 1; i < digits.length; i++) {
            if (digits[i] > digits[swapPoint] && digits[i] < minLarger) {
                minLarger = digits[i];
                minLargerIndex = i;
            }
        }
        // Обмениваем цифры на точке перестановки и наименьшей большей цифре
        int temp = digits[swapPoint];
        digits[swapPoint] = digits[minLargerIndex];
        digits[minLargerIndex] = temp;

        // Сортируем число справа от точки перестановки
        Arrays.sort(digits, swapPoint + 1, digits.length);

        // Преобразуем массив цифр обратно в целое число и возвращаем результат
        long result = 0;
        for (int digit : digits) {
            result = result * 10 + digit;
        }
        return result;
    }
}
