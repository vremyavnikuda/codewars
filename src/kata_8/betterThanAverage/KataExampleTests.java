package kata_8.betterThanAverage;

import org.testng.annotations.Test;

import static org.junit.Assert.assertEquals;

//Test
public class KataExampleTests {
    @Test
    public void tests() {
        assertEquals(true, betterThanAverage.BetterThanAverage(new int[]{2, 3}, 5));
        assertEquals(true, betterThanAverage.BetterThanAverage(new int[]{100, 40, 34, 57, 29, 72, 57, 88}, 75));
        assertEquals(true, betterThanAverage.BetterThanAverage(new int[]{12, 23, 34, 45, 56, 67, 78, 89, 90}, 69));
        assertEquals(false, betterThanAverage.BetterThanAverage(new int[]{100, 90}, 11));
    }
}
