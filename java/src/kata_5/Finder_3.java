package kata_5;
import org.junit.jupiter.api.Test;


import java.util.*;


import static org.junit.Assert.assertEquals;

public class Finder_3 {
    static int pathFinder(String maze) {
        int N = (int) Math.sqrt(maze.length());
        int[][] grid = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = maze.charAt(i * N + j) - '0';
            }
        }

        Queue<int[]> queue = new LinkedList<>();
        queue.add(new int[]{0, 0});

        int[][] dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int steps = 0;
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] coord = queue.poll();
                int x = coord[0];
                int y = coord[1];
                if (x == N - 1 && y == N - 1) {
                    return steps;
                }
                for (int[] dir : dirs) {
                    int newX = x + dir[0];
                    int newY = y + dir[1];
                    if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                        queue.add(new int[]{newX, newY});
                    }
                }
            }
            steps++;
        }
        return -1;
    }

    @Test
    public void sampleTests() {

        String a = "000\n"+
                   "000\n"+
                   "000",

                b = "010\n"+
                    "010\n"+
                    "010",

                c = "010\n"+
                    "101\n"+
                    "010",

                d = "0707\n"+
                    "7070\n"+
                    "0707\n"+
                    "7070",

                e = "700000\n"+
                    "077770\n"+
                    "077770\n"+
                    "077770\n"+
                    "077770\n"+
                    "000007",

                f = "777000\n"+
                    "007000\n"+
                    "007000\n"+
                    "007000\n"+
                    "007000\n"+
                    "007777",

                g = "000000\n"+
                    "000000\n"+
                    "000000\n"+
                    "000010\n"+
                    "000109\n"+
                    "001010";

        assertEquals(0,  Finder_3.pathFinder(a));
        assertEquals(2,  Finder_3.pathFinder(b));
        assertEquals(4,  Finder_3.pathFinder(c));
        assertEquals(42, Finder_3.pathFinder(d));
        assertEquals(14, Finder_3.pathFinder(e));
        assertEquals(0,  Finder_3.pathFinder(f));
        assertEquals(4,  Finder_3.pathFinder(g));
    }
}
