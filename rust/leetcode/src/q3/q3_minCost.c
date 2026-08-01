#define MAX_GRID_DIM 81
#define MAX_CELL_VAL 10001
#define INF 0x3f3f3f3f

static int cst[MAX_GRID_DIM][MAX_GRID_DIM];
static int mbv[MAX_CELL_VAL];
static int bbv[MAX_CELL_VAL];

static inline int mn2(int x, int y) { return x < y ? x : y; }

int minCost(int** grid, int gridSize, int* gridColSize, int k) {
    int a = gridSize;
    int b = gridColSize[0];
    int z = 0;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (grid[i][j] > z) z = grid[i][j];
        }
    }
    for (int v = 0; v <= z; v++) mbv[v] = INF;
    cst[a - 1][b - 1] = 0;
    mbv[grid[a - 1][b - 1]] = 0;
    for (int j = b - 2; j >= 0; j--) {
        cst[a - 1][j] = cst[a - 1][j + 1] + grid[a - 1][j + 1];
        int w = grid[a - 1][j];
        mbv[w] = mn2(mbv[w], cst[a - 1][j]);
    }
    for (int i = a - 2; i >= 0; i--) {
        cst[i][b - 1] = cst[i + 1][b - 1] + grid[i + 1][b - 1];
        int w = grid[i][b - 1];
        mbv[w] = mn2(mbv[w], cst[i][b - 1]);
        for (int j = b - 2; j >= 0; j--) {
            int d = cst[i + 1][j] + grid[i + 1][j];
            int r = cst[i][j + 1] + grid[i][j + 1];
            cst[i][j] = mn2(d, r);
            w = grid[i][j];
            mbv[w] = mn2(mbv[w], cst[i][j]);
        }
    }
    for (int t = 0; t < k; t++) {
        bbv[0] = mbv[0];
        for (int v = 1; v <= z; v++) bbv[v] = mn2(bbv[v - 1], mbv[v]);
        for (int j = b - 2; j >= 0; j--) {
            int m = cst[a - 1][j + 1] + grid[a - 1][j + 1];
            int q = bbv[grid[a - 1][j]];
            cst[a - 1][j] = mn2(m, q);
            int w = grid[a - 1][j];
            mbv[w] = mn2(mbv[w], cst[a - 1][j]);
        }
        for (int i = a - 2; i >= 0; i--) {
            int m = cst[i + 1][b - 1] + grid[i + 1][b - 1];
            int q = bbv[grid[i][b - 1]];
            cst[i][b - 1] = mn2(m, q);
            int w = grid[i][b - 1];
            mbv[w] = mn2(mbv[w], cst[i][b - 1]);
            for (int j = b - 2; j >= 0; j--) {
                int d = cst[i + 1][j] + grid[i + 1][j];
                int r = cst[i][j + 1] + grid[i][j + 1];
                q = bbv[grid[i][j]];
                cst[i][j] = mn2(mn2(d, r), q);
                w = grid[i][j];
                mbv[w] = mn2(mbv[w], cst[i][j]);
            }
        }
    }
    return cst[0][0];
}
