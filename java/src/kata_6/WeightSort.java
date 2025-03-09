package kata_6;

import java.util.Arrays;
import java.util.Comparator;

public class WeightSort {
    public static String orderWeight(String strng) {
        String[] arr = strng.split(" ");
        Arrays.sort(arr, new Comparator<String>() {
            @Override
            public int compare(String s1, String s2) {
                int sum1 = sum(s1);
                int sum2 = sum(s2);
                if (sum1 != sum2) {
                    return sum1 - sum2;
                } else {
                    return s1.compareTo(s2);
                }
            }
        });
        String result = String.join(" ", arr);
        return result;
    }

    private static int sum(String s) {
        int sum = 0;
        for (char c : s.toCharArray()) {
            sum += c - '0';
        }
        return sum;
    }
}
