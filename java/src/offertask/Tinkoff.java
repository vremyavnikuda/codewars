package offertask;

import java.util.Scanner;

public class Tinkoff {

    public static void main(String[] args) {
        // String bricks = "010"; // Test input
        Scanner sc = new Scanner(System.in);
        String bricks = sc.nextLine(); // Read input string of bricks

        // Create 4 by 4 grid
        int[][] grid = new int[4][4];

        // Initialize position
        int row = 0;
        int col = 0;

        for (int i = 0; i < bricks.length(); i++) {
            int brick = Character.getNumericValue(bricks.charAt(i)); // Convert character to integer

            // Place brick
            boolean placed = false;
            for (int j = row; j < 4; j++) {
                for (int k = col; k < 4; k++) {
                    if (grid[j][k] == 0) {
                        grid[j][k] = 1; // Place brick
                        row = j; // Update row
                        col = k; // Update column
                        placed = true;
                        break;
                    }
                }
                if (placed) {
                    break;
                }
            }

            // Print position of brick
            System.out.println((row + 1) + " " + (col + 1));

            // Update position for next brick
            if (brick == 0) { // Vertical brick
                row += 2;
            } else { // Horizontal brick
                col += 2;
            }
        }
    }
}

