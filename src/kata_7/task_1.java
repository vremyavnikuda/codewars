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
        int a= sc.nextInt();
        int b= sc.nextInt();
        int count=0;
        int q=a;
        while (q<=b){
            q++;
            count++;
        }
        int []between=new int[count];
        for (int i=0;i< between.length;i++){
            between[i]+=a++;
        }
        for (int i=0;i< between.length;i++) {
            System.out.print(between[i] + " ");
        }
    }
}
