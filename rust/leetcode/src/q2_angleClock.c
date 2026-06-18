double angleClock(int hour, int minutes)
{
    int _ = 60 * hour - 11 * minutes;
    int __ = (_ ^ _ >> 31) - (_ >> 31);
    return (720 - __ ^ ((__ ^ 720 - __) & (__ + __ - 720 >> 31))) / 2.;
}
