package kata_7;
public class FindOutlier {
    static int find(int[] integers) {
        // Сначала определим, какой тип чисел (четный или нечетный) преобладает в массиве
        int evenCount = 0;
        int oddCount = 0;
        for (int num : integers) {
            if (num % 2 == 0) {
                evenCount++;
            } else {
                oddCount++;
            }
        }
        // Теперь просто найдем и вернем "выброс" N
        for (int num : integers) {
            if (evenCount > oddCount && num % 2 != 0) {
                return num;
            } else if (oddCount > evenCount && num % 2 == 0) {
                return num;
            }
        }
        // Если мы дошли сюда, значит в массиве нет "выброса" N
        return -1;
    }
}
/*
В этой функции мы сначала подсчитываем, сколько четных и сколько нечетных чисел в массиве.
Затем используем эту информацию, чтобы найти и вернуть "выброс" N.
Если мы не нашли "выброс" N, значит он не присутствует в массиве, и функция вернет -1.
*/