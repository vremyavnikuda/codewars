int numberOfSpecialChars(char *w)
{
    unsigned l = 0, u = 0, c;
    for (; c = *w++; c & 32 ? l |= 1 << (c & 31) : (u |= 1 << (c & 31)))
        ;
    c = l & u;
    c -= c >> 1 & 0x55555555;
    c = (c & 0x33333333) + (c >> 2 & 0x33333333);
    c = c + (c >> 4) & 0x0f0f0f0f;
    c += c >> 8;
    c += c >> 16;
    return c & 63;
}
