package kata_5;
import org.junit.jupiter.api.Test;

import java.math.BigInteger;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

import static org.junit.Assert.assertEquals;

public class Equation {
    private static final Pattern TERM = Pattern.compile("(.*?)x(\\^\\d+)?");

    public static BigInteger differentiate(String equation, long x) {
        BigInteger xb = BigInteger.valueOf(x);
        BigInteger result = BigInteger.ZERO;
        Matcher m = TERM.matcher(equation);
        while (m.find()) {
            long k = 1;
            String ks = m.group(1);
            if (!ks.isEmpty() && !ks.equals("+"))
                k = ks.equals("-") ? -1 : Long.parseLong(ks);
            int p = 1;
            String ps = m.group(2);
            if (ps != null)
                p = Integer.parseInt(ps.substring(1));
            result = result.add(BigInteger.valueOf(k).multiply(BigInteger.valueOf(p)).multiply(xb.pow(p - 1)));
        }
        return result;
    }


    @Test
    public void sampleTests() {
        assertEquals(new BigInteger("12"),  Equation.differentiate("12x+2", 3));
        assertEquals(new BigInteger("5"),   Equation.differentiate("x^2-x", 3));
        assertEquals(new BigInteger("-20"), Equation.differentiate("-5x^2+10x+4", 3));
    }
}
