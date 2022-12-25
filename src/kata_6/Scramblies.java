/*
Завершите функцию scramble(str1, str2) java, которая возвращает true, если часть str1 символов может быть
переставлена для соответствия str2, в противном случае возвращает false.

Примечания:

Будут использоваться только строчные буквы (a-z). Знаки препинания или цифры не будут включены.

Необходимо учитывать производительность.

Примеры
scramble('rkqodlw', 'world') ==> True
scramble('cedewaraaossoqqyt', 'codewars') ==> True
scramble('katas', 'steak') ==> False
*/
package kata_6;
public class Scramblies {
    public static boolean scramble(String str1, String str2) {
        //Создаем массив счетчиков для букв строки str1
        int[]letters1=new int[26];
        //создаем массив счетчиков для букв строки str2
        int []letters2=new int[26];

        //заполняем массив счетчиков для каждой буквы
        for (int i=0;i<str1.length();i++){
            letters1[str1.charAt(i)-'a']++;
        }
        for (int i=0;i<str2.length();i++){
            letters2[str2.charAt(i)-'a']++;
        }

        //сравниваем массивы счетчиков
        for (int i=0;i<26;i++){
            if (letters1[i]<letters2[i]){
                return false;
            }
        }
        return true;
    }
}
