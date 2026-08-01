int minimumEffort(int **tasks, int tasksSize, int *tasksColSize)
{
    for (int i = tasksSize >> 1; i--;)
    {
        int r = i;
        for (;;)
        {
            int c = r + r + 1;
            if (c >= tasksSize)
                break;
            c + 1 < tasksSize &&tasks[c + 1][0] - tasks[c + 1][1] > tasks[c][0] - tasks[c][1] && ++c;
            if (tasks[r][0] - tasks[r][1] >= tasks[c][0] - tasks[c][1])
                break;
            int *x = tasks[r];
            tasks[r] = tasks[c];
            tasks[c] = x;
            r = c;
        }
    }
    for (int i = tasksSize; --i;)
    {
        int *x = tasks[0];
        tasks[0] = tasks[i];
        tasks[i] = x;
        int r = 0;
        for (;;)
        {
            int c = r + r + 1;
            if (c >= i)
                break;
            c + 1 < i &&tasks[c + 1][0] - tasks[c + 1][1] > tasks[c][0] - tasks[c][1] && ++c;
            if (tasks[r][0] - tasks[r][1] >= tasks[c][0] - tasks[c][1])
                break;
            int *x = tasks[r];
            tasks[r] = tasks[c];
            tasks[c] = x;
            r = c;
        }
    }
    int r = 0, c = 0, i = 0;
    for (; i < tasksSize; ++i)
    {
        int *a = tasks[i];
        c < *++a && (r += *a - c, c = *a);
        c -= a[-1];
    }
    return r;
}
