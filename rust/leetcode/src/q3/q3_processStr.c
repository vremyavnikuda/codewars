char processStr(char *s, long long k)
{
    long long m = 0;
    char *p = s;
    for (; *p; m = *p ^ 42 ? *p ^ 35 ? *p ^ 37 ? -~m : m : m + m : m > 0 ? ~-m
                                                                         : 0,
               p++)
        ;
    if (k >= m)
        return 46;
    for (; p - s;)
    {
        *--p ^ 42 ? *p ^ 35 ? *p ^ 37 ? --m : (k = m + ~k) : (m >>= 1, k >= m && (k -= m)) : m++;
        if (*p ^ 42 && *p ^ 35 && *p ^ 37 && !(k ^ m))
            return *p;
    }
    return 46;
}