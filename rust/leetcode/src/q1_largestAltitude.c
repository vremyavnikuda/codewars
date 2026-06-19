int largestAltitude(int *gain, int gainSize)
{
    int a = 0, h = 0, *e = gain + gainSize;
    while (gain < e)
        h += *gain++, a ^= (h ^ a) & -(h > a);
    return a;
}
