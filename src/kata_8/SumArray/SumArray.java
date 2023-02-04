package kata_8.SumArray;

import org.testng.annotations.Test;

import static org.junit.Assert.assertEquals;

public class SumArray {
    public static double sum (double[]numbers){
        //переменная в которой будем хранить итоговый результат и выводить по окончанию метода
        double count=0;
        //проходимся циклом for-each по массиву(суммируюя его)
        for (double sum:numbers){
            //проверяем массив на наличие элементов в нем
            //если в массиве есть элементы
            if (numbers.length!=0){
                //суммируем их
                count+=sum;
            //если их нет
            }else {
                //присваиваем результирующей переменной нужное значение согласно условию задачи
                count=0;
            }
        }
        //возвращаем результирующую переменную с полученным результатом
        return count;
    }
}
