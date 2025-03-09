/*
Numbers ending with zeros are boring.

They might be fun in your world, but not here.

Get rid of them. Only the ending ones.

1450 -> 145
960000 -> 96
1050 -> 105
-1050 -> -105
Zero alone is fine, don't worry about it. Poor guy anyway
*/
package kata_7;
public class NoBoring {
    public static int noBoringZero(int n){
        //счетчик
        int count=0;
        //создаем цикл в котором проверяем есть ли в int 0
        while(n%10==0){
            //добавляем исключение когда входные данные ==0
            if (n==0){
                //прерываем выполнение цикла
                //возвращаем значение
                break;
            }
            //если есть ,то убираем его
            n=n/10;
            //к счетчику прибавляем значение
            count++;
        }
        //возвращаем результат
        return n;
    }
}
