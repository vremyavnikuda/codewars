package kata_7;
/*
Учитывая строку слов, необходимо вернуть длину самого короткого слова
строка никогда не будет пустой и не нужно учитывать разные типы данных(считать просто строки)
*/
import org.junit.jupiter.api.Test;

import static org.junit.Assert.assertEquals;

public class Kata_7_3 {
    public static int findShort(String s){
        //задаем минимально возможную длину слова
        int minLength=Integer.MAX_VALUE;
        // разделяем строки слов и преобразовываем в массив слов
        // используя в качестве разделителя (пробел)
        String []words=s.split(" ");
        for (String word:words){
            //получаем длину текущего слова
            int lenght=word.length();
            //Сравниваем длину текущего слова с минимальной длиной
            if (lenght<minLength){
                //если длина текущего слова меньше минимальной ,то задаем ее как новую минимальную
                minLength=lenght;
            }
        }
        //возвращаем минимальную длину слова
        return minLength;
    }
}
//тесты
class Kata_7_3Test {
    @Test
    public void findShort() throws Exception {
        assertEquals(3, Kata_7_3.findShort("bitcoin take over the world maybe who knows perhaps"));
        assertEquals(3, Kata_7_3.findShort("turns out random test cases are easier than writing out basic ones"));
        assertEquals(2, Kata_7_3.findShort("Let's travel abroad shall we"));
    }

}