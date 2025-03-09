package kata_8.XO;
/*
Проверить содержит ли строка одинаковое кол-во символов "x" и "o"
Метод должен возвращать логическое значение и не учитывать регистр. Строка может содержать любые символы
*/
public class XO {
    public static boolean getXO(String str){
        //приводим строку к нижнему регистру
        str=str.toLowerCase();
        //задаем счетчики букв str
        int count_getX=0,count_getO=0;
        //проходим циклом с проверкой наличия нужных символов в строке
        for (int i=0;i<str.length();i++){
            //задаем переменную char и присваиваем ей буквы из строки str
            char c=str.charAt(i);
            //проверяем на соответствие
            //если char c=='x'
            if (c=='x'){
                //увеличиваем счетчик count_getX+1
                count_getX++;
            //если char c=='o'
            } else if (c=='o') {
                //увеличиваем счетчик count_getO+1
                count_getO++;
            }
        }
        //сравниваем счетчики count_getX==count_getO ? true:false
        return count_getX==count_getO;
    }
}
