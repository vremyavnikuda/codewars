package kata_5;

import org.junit.jupiter.api.Test;

import java.util.LinkedList;
import java.util.Queue;

import static org.junit.Assert.assertEquals;

public class Finder {
    private static final int[][] DIRS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    public static int pathFinder(String maze) {
        char[][] grid = parseMaze(maze);
        int n = grid.length;

        Queue<int[]> queue = new LinkedList<>();
        queue.add(new int[]{0, 0});

        int[][] steps = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                steps[i][j] = -1;
            }
        }
        steps[0][0] = 0;

        while (!queue.isEmpty()) {
            int[] node = queue.poll();
            int x = node[0];
            int y = node[1];

            for (int[] dir : DIRS) {
                int xx = x + dir[0];
                int yy = y + dir[1];
                if (xx >= 0 && xx < n && yy >= 0 && yy < n && grid[xx][yy] != 'W' && steps[xx][yy] == -1) {
                    queue.add(new int[]{xx, yy});
                    steps[xx][yy] = steps[x][y] + 1;
                }
            }
        }

        return steps[n - 1][n - 1];
    }

    private static char[][] parseMaze(String maze) {
        String[] rows = maze.split("\n");
        int n = rows.length;
        char[][] grid = new char[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                grid[i][j] = rows[i].charAt(j);
            }
        }
        return grid;
    }



    @Test
    public void sampleTests() {

        String a = ".W.\n"+
                ".W.\n"+
                "...",

                b = ".W.\n"+
                        ".W.\n"+
                        "W..",

                c = "......\n"+
                        "......\n"+
                        "......\n"+
                        "......\n"+
                        "......\n"+
                        "......",

                d = "......\n"+
                        "......\n"+
                        "......\n"+
                        "......\n"+
                        ".....W\n"+
                        "....W.";

        assertEquals(a, 4,  Finder.pathFinder(a));
        assertEquals(b, -1, Finder.pathFinder(b));
        assertEquals(c, 10,  Finder.pathFinder(c));
        assertEquals(d, -1, Finder.pathFinder(d));

    }
}
