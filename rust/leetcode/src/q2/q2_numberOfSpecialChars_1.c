int numberOfSpecialChars(char *w)
{
    int l[26] = {0}, f[26] = {0}, i = 0, a = 0;
    for (; w[i]; ++i)
    {
        int c = w[i], x = (c & 31) - 1;
        c & 32 ? (l[x] = i + 1) : (!f[x] && (f[x] = i + 1));
    }
    for (i = 0; i < 26; ++i)
        a += l[i] && l[i] < f[i];
    return a;
}
