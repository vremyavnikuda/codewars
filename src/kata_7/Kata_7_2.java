package kata_7;
/*Дана строка, необходимо проверить является ли она четной или не четной
* если строка имеет четную длину -> вернуть в результат 2 буквы которые находятся посередине строки
* если строка имеет не четную длину -> вернуть в результат 1 букву которая находится посередине строки */

import org.junit.jupiter.api.Test;

import static org.junit.Assert.assertEquals;

public class Kata_7_2 {
    public static String getMiddle(String word){
        //присваиваем переменной middleIndex (середину строки)
        int middleIndex=word.length()/2;
        //обрабатываем исключения
        //если длина строки не четная
        if (word.length()%2!=0){
            //возвращаем букву, которая находится посередине
            return word.substring(middleIndex,middleIndex+1);
        }
        else {
            //в других случаях возвращаем пару букв которые находятся посередине
            return word.substring(middleIndex-1,middleIndex+1);
        }
    }
}

//тесты
class Kata_7_2Tests {
    @Test
    public void evenTests() {
        assertEquals("es", Kata_7_2.getMiddle("test"));
        assertEquals("dd", Kata_7_2.getMiddle("middle"));
    }

    @Test
    public void oddTests() {
        assertEquals("t", Kata_7_2.getMiddle("testing"));
        assertEquals("A", Kata_7_2.getMiddle("A"));
    }
}
