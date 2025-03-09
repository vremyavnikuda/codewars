import java.util.ResourceBundle;
public class offer_task {
    private static ResourceBundle rs;
    private static Process log;
    public static void main (String[]args){
        enum Tree {
            FIRS(500),
            SPRUCE(600),
            PINE(700);

            private int mass = 1000;
            private boolean isAmazing = false;

            Tree(int mass) {
                this.mass = mass;
                this.isAmazing = !isAmazing;
            }

            public boolean isAmazing() {
                return isAmazing;
            }

            public int getMass() {
                return mass;
            }
        }
        System.out.println(Tree.SPRUCE.getMass());
        System.out.println(Tree.SPRUCE.isAmazing());
    }
}
