package kata_5;

import org.junit.jupiter.api.Test;

import static org.junit.Assert.assertEquals;

public class Matrix {
    public static int determinant(int[][] matrix) {
        // Обработка случая матрицы 1x1
        if (matrix.length == 1) {
            return matrix[0][0];
        }

        // Обработка случая матрицы 2x2
        if (matrix.length == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }

        // Обработка случая матрицы 3x3 и большего размера
        int det = 0;
        for (int i = 0; i < matrix[0].length; i++) {
            // Вычисление определителя матрицы-минора
            int[][] minor = getMinor(matrix, i);

            // Вычисление текущего элемента определителя
            int currentElement = (int) Math.pow(-1, i) * matrix[0][i] * determinant(minor);

            det += currentElement;
        }
        return det;
    }

    // Вспомогательная функция для получения матрицы-минора
    private static int[][] getMinor(int[][] matrix, int col) {
        int[][] minor = new int[matrix.length - 1][matrix.length - 1];
        for (int i = 1; i < matrix.length; i++) {
            int jMinor = 0;
            for (int j = 0; j < matrix[0].length; j++) {
                if (j == col) {
                    continue;
                }
                minor[i - 1][jMinor] = matrix[i][j];
                jMinor++;
            }
        }
        return minor;
    }


    private static int[][][] matrix = { {{1}},
            {{1, 3}, {2,5}},
            {{2,5,3}, {1,-2,-1}, {1, 3, 4}}};

    private static int[] expected = {1, -1, -20};

    private static String[] msg = {"Determinant of a 1 x 1 matrix yields the value of the one element",
            "Should return 1 * 5 - 3 * 2 == -1 ",
            ""};

    @Test
    public void sampleTests() {
        for (int n = 0 ; n < expected.length ; n++)
            assertEquals(msg[n], expected[n], Matrix.determinant(matrix[n]));
    }
}
