/*
Last digit of a large number
*/

package kata_6;
import java.math.BigInteger;
public class Kata {
    public static int lastDigit(BigInteger n1, BigInteger n2) {
        if (n2.equals(BigInteger.ZERO)) {
            return 1;
        }

        int lastDigitOfN1 = n1.mod(BigInteger.TEN).intValue();
        if (lastDigitOfN1 == 0 || lastDigitOfN1 == 1 || lastDigitOfN1 == 5 || lastDigitOfN1 == 6) {
            return lastDigitOfN1;
        }

        int lastDigitOfN2 = n2.mod(BigInteger.valueOf(4)).intValue();
        if (lastDigitOfN2 == 0) {
            lastDigitOfN2 = 4;
        }

        int result = (int) Math.pow(lastDigitOfN1, lastDigitOfN2);
        return result % 10;
    }
}


