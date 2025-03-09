package kata_8;

/*Реализовать функцию, которая преобразует данное логическое значение в его строковое представление.*/

import org.junit.jupiter.api.Test;

import static org.junit.Assert.assertEquals;

public class BooleanToString {
    public static String convert(boolean b){
        //возвращаем примитивное значение объекта String(строкового преставления аргумента)
        return String.valueOf(b);
    }
}

class BoolToStrTest{
    @Test
    void testTrue(){
        assertEquals("true", BooleanToString.convert(true));
    }

    @Test void testFalse(){
        assertEquals("false", BooleanToString.convert(false));
    }
}