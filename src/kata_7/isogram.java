/*
Изограмма - это слово, в котором нет повторяющихся букв, последовательных или непоследовательных.
Реализуйте функцию, которая определяет, является ли строка, содержащая только буквы, изограммой.
Предположим, что пустая строка является изограммой. Игнорируйте регистр букв.

Пример: (Ввод -> Вывод)

"Dermatoglyphics" -> true "aba" -> false "moOse" -> false (игнорировать регистр букв)

isIsogram "Dermatoglyphics" = true
isIsogram "moose" = false
isIsogram "aba" = false
*/
package kata_7;
import java.util.HashSet;
import java.util.Set;

public class isogram {
    public static boolean isIsogram(String str) {
        // Если строка пустая, возвращаем true
        if (str.isEmpty()) {
            return true;
        }
        // Преобразуем строку в нижний регистр
        str = str.toLowerCase();
        // Создаем множество, чтобы проверить, встречалась ли каждая буква ранее
        Set<Character> set = new HashSet<>();
        // Перебираем все символы в строке
        for (char c : str.toCharArray()) {
            // Если этот символ уже встречался ранее, возвращаем false
            if (set.contains(c)) {
                return false;
            }
            // Иначе, добавляем символ в множество
            set.add(c);
        }
        // Если мы дошли до этой точки, это значит, что строка является изограммой
        return true;
    }
}
