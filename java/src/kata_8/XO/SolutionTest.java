package kata_8.XO;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class SolutionTest {
    @Test
    public void testSomething1() {
        assertEquals(true, XO.getXO("xxxooo"));
    }

    @Test
    public void testSomething2() {
        assertEquals(true, XO.getXO("xxxXooOo"));
    }

    @Test
    public void testSomething3() {
        assertEquals(false, XO.getXO("xxx23424esdsfvxXXOOooo"));
    }

    @Test
    public void testSomething4() {
        assertEquals(false, XO.getXO("xXxxoewrcoOoo"));
    }

    @Test
    public void testSomething5() {
        assertEquals(false, XO.getXO("XxxxooO"));
    }

    @Test
    public void testSomething6() {
        assertEquals(true, XO.getXO("zssddd"));
    }

    @Test
    public void testSomething7() {
        assertEquals(false, XO.getXO("Xxxxertr34"));
    }
}
