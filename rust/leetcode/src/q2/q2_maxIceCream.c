int maxIceCream(int *costs, int costsSize, int coins)
{
    int g, i, j, t;
    for (g = 1; g < costsSize; g = 3 * g + 1)
        ;
    while (g /= 3)
        for (i = g; i < costsSize; i++)
        {
            t = costs[i];
            for (j = i; j >= g && costs[j - g] > t; costs[j] = costs[j - g], j -= g)
                ;
            costs[j] = t;
        }
    for (i = 0; i < costsSize && coins >= costs[i]; coins -= costs[i++])
        ;
    return i;
}