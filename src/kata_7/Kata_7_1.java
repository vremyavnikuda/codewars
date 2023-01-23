package kata_7;

import org.junit.jupiter.api.Test;

import static org.junit.Assert.assertEquals;

public class Kata_7_1 {
    /*
    public static boolean solution(String str,String ending){
        //Метод endsWith() проверяет ,заканчивается ли эта строка указанным окончанием
        return str.endsWith(ending);
    }
    */
    //Длинный вариант решения

    public static boolean solution(String str,String ending){

        //приводим обе строки к массиву символов
        char[] array_1=str.toCharArray(),array_2=ending.toCharArray();
        /*Проверяем если массив символов array_2 "строка"(на которую должен оканчиваться) массив символов array_1
        длиннее, то вернуть false*/
        if (array_2.length>array_1.length)
            return false;
        for (int i=0;i<(array_2.length);i++)
            //через цикл for проверяем каждый индекс array_1 != ли индексам array_2
            if (array_1[(array_1.length-1)-i]!=array_2[(array_2.length-1)-i])
                //false
                return false;
        //в любых других случаях
        //true
        return true;
    }

}

class SolutionTest {
    @Test
    public void staticTests() {
        check("samurai", "ai", true);
        check("sumo", "omo", false);
        check("ninja", "ja", true);
        check("sensei", "i", true);
        check("samurai", "ra", false);
        check("abc", "abcd", false);
        check("abc", "abc", true);
        check("abcabc", "bc", true);
        check("ails", "fails", false);
        check("fails", "ails", true);
        check("this", "fails", false);
        check("this", "", true);
        check(":-)", ":-(", false);
        check("!@#$%^&*() :-)", ":-)", true);
        check("abc\n", "abc", false);
    }

    private static void check(String str, String ending, boolean expected) {
        boolean result = Kata_7_1.solution(str, ending);
        assertEquals("Expected solution(\"" + str + "\", \"" + ending + "\") to return " + expected, expected, result);
    }
}
