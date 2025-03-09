/*
What is between?
Complete the function that takes two integers (a, b, where a < b) and return an array of all
integers between the input parameters, including them.

For example:

a = 1
b = 4
--> [1, 2, 3, 4]
*/
package kata_7;
import java.util.Scanner;
public class task_1 {
    public static void main (String []args){
        Scanner sc=new Scanner(System.in);
        //получаем данные которые войдут в условие заполнения массива
        //а==первое число
        int a= sc.nextInt();
        //b==второе число
        int b= sc.nextInt();
        //так как нам не известна длинна массива
        //создаем счетчик длинны
        int count=0;
        //задаем временную переменную в которую сложим значение переменной a
        int q=a;
        //задаем цикл (при помощи которого будем искать длину массава)
        while (q<=b){
            q++;
            count++;
        }
        //инициализируем массив
        int []between=new int[count];
        //создаем условие заполнения массива данными
        for (int i=0;i< between.length;i++){
            between[i]+=a++;
        }
        //создаем условие вывода массива данных
        for (int i=0;i< between.length;i++) {
            //через пробел
            System.out.print(between[i] + " ");
        }
    }
}
