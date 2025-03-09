package kata_8.Opposite;

import org.testng.annotations.Test;

import static org.junit.Assert.assertEquals;

public class OppositeExampleTests {
    @Test
    public void tests() {
        assertEquals(-1, Opposite.opposite(1));
    }
}
