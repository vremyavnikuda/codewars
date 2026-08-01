#define O 0x7FFFFFFF
#define M(a, b) ((b) ^ (((a) ^ (b)) & -((a) < (b))))
#define X(a, b) ((a) ^ (((a) ^ (b)) & -((a) < (b))))

int earliestFinishTime(int *landStartTime, int landStartTimeSize, int *landDuration, int landDurationSize, int *waterStartTime, int waterStartTimeSize, int *waterDuration, int waterDurationSize)
{
    int a = O, b = O, c = O, d = O, i = 0;
    while (i < landStartTimeSize)
    {
        a = M(a, landStartTime[i] + landDuration[i]);
        i++;
    }
    i = 0;
    while (i < waterStartTimeSize)
    {
        c = M(c, waterStartTime[i] + waterDuration[i]);
        i++;
    }
    i = 0;
    while (i < waterStartTimeSize)
    {
        b = M(b, X(a, waterStartTime[i]) + waterDuration[i]);
        i++;
    }
    i = 0;
    while (i < landStartTimeSize)
    {
        d = M(d, X(c, landStartTime[i]) + landDuration[i]);
        i++;
    }
    return M(b, d);
}
