int totalWaviness(int num1, int num2)
{
    int O = 0, x = num1;
    for (; x <= num2; ++x)
    {
        int y = x, a = -1, b = -1, c, n = 0, w = 0;
        if (y > 99)
            do
            {
                c = y % 10;
                y /= 10;
                ++n > 2 && (b - a) * (b - c) > 0 ? ++w : 0;
                a = b;
                b = c;
            } while (y);
        O += w;
    }
    return O;
}