/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define MAX_SIZE 100001
#define OFFSET 1000000
#define RANGE 2000001

static int* result_pairs[MAX_SIZE];
static int result_storage[MAX_SIZE][2];
static int column_sizes[MAX_SIZE];
static unsigned char present[RANGE];

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    int min_val = arr[0];
    int max_val = arr[0];
    int start, end, min_diff, prev, pair_count;
    int i;

    for (i = 0; i < arrSize; i++) {
        present[arr[i] + OFFSET] = 1;
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    start = min_val + OFFSET;
    end = max_val + OFFSET;

    min_diff = RANGE;
    prev = -1;
    for (i = start; i <= end; i++) {
        if (present[i]) {
            if (prev >= 0) {
                int diff = i - prev;
                if (diff < min_diff) min_diff = diff;
            }
            prev = i;
        }
    }

    pair_count = 0;
    prev = -1;
    for (i = start; i <= end; i++) {
        if (present[i]) {
            if (prev >= 0 && i - prev == min_diff) {
                result_storage[pair_count][0] = prev - OFFSET;
                result_storage[pair_count][1] = i - OFFSET;
                result_pairs[pair_count] = result_storage[pair_count];
                column_sizes[pair_count] = 2;
                pair_count++;
            }
            prev = i;
            present[i] = 0;
        }
    }

    *returnSize = pair_count;
    *returnColumnSizes = column_sizes;
    return result_pairs;
}
