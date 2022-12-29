/*
Write a function java which makes a list of strings representing all of the ways you can balance n pairs of
parentheses

Examples

balancedParens(0) returns ArrayList<String> with element:  ""
balancedParens(1) returns ArrayList<String> with element:  "()"
balancedParens(2) returns ArrayList<String> with elements: "()()","(())"
balancedParens(3) returns ArrayList<String> with elements: "()()()","(())()","()(())","(()())","((()))"
*/
package kata_5;

import java.util.ArrayList;
import java.util.List;


public class BalancedParens {
    public static List<String> balancedParens (int n) {
        //Создаем список результатов
        List<String> result=new ArrayList<>();
        //Базовый случай:если n==0,то возвращаем пустую строку
        if (n==0){
            result.add("");
            return result;
        }
        //итерируемся по всем возможным значениям i от 0 до n-1
        for (int i=0;i<n;i++){
            //Для каждого i генерируется все возможные комбинации сбалансированных
            //скобок для i пар скобок
            //и n-i-1 пар скобок
            for (String left:balancedParens(i)){
                for (String right:balancedParens(n-i-1)){
                    //Комбинируем эти комбинации ,заключая комбинации i пар скобок в дополнительные
                    //пары скобок
                    result.add("("+left+")"+right);
                }
            }
        }
        //Возвращаем результирующий список
        return result;
    }
}
