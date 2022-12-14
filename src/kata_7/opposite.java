/*
Very simple, given an integer or a floating-point number, find its opposite.

Examples:

1: -1
14: -14
-34: 34
*/
package kata_7;
import java.util.Scanner;
public class opposite {
    public static int opposite(int number){
        //если число + ,его противоположность -
        if (number>0){
            number-=Math.abs(number*2);
        //если число - ,его противоположность +
        }else if (number<0){
            number+=Math.abs(number*2);
        }
        return number;
    }
}
