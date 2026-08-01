int maxRotateFunction(int *nums, int numsSize)
{
    int *_ = nums, *__ = nums + numsSize, ___ = numsSize;
    long long ____ = 0, _____ = 0, ______;
    if (___ < 1)
        return 0;
    for (; _ < __; ++_)
        ____ += *_,
        _____ += (long long)(_ - nums) * *_ ;
    ______ = _____;
    for (_ = __; --_ > nums;)
        _____ += ____ - (long long)___ * *_,
        ______ = ______ < _____ ? _____ : ______;
    return (int)______;
}
