//
// Created by vremyavnikuda on 9/24/24.
//
#include <complex>
bool is_cube(int volume, int side)
{
    if (volume <= 0 || side <= 0)
    {
        return false;
    }
    else if (std::pow(side, 3) == volume)
    {
        return true;
    }
    else
    {
        return false;
    }
}
