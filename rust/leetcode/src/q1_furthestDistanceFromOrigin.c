int furthestDistanceFromOrigin(char *moves)
{
    int l=0,I=0,O;for(;(O=*moves++);l+=O==95,I+=(O==82)-(O==76));return l+(I<0?-I:I);
}
