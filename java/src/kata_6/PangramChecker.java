package kata_6;

import java.util.HashSet;
import java.util.Set;

public class PangramChecker {
    public static boolean check(String sentence) {
        // Создаем множество символов, соответствующее алфавиту
        Set<Character> alphabet = new HashSet<>();
        for (char c = 'a'; c <= 'z'; c++) {
            alphabet.add(c);
        }

        // Удаляем из множества все символы, которые встречаются в строке
        for (char c : sentence.toLowerCase().toCharArray()) {
            if (alphabet.contains(c)) {
                alphabet.remove(c);
            }
        }

        // Если множество пустое, то строка является панграммой
        return alphabet.isEmpty();
    }
}
