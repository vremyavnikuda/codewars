package offertask;

import java.util.Formatter;

public class TestFormatter {
    public static void main(String[] args) {
        Integer i1=0;
        Integer i2=-1;
        Integer i3=1;
        Formatter f=new Formatter();
        f.format("%1$b ",i1.toString());
        f.format("%1$b ",i2.toString());
        f.format("%1$b ",i3.toString());
        System.out.println(f.toString());
    }
}
