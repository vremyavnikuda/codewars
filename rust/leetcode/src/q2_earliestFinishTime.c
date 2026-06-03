int earliestFinishTime(int *landStartTime, int landStartTimeSize, int *landDuration, int landDurationSize, int *waterStartTime, int waterStartTimeSize, int *waterDuration, int waterDurationSize)
{
    int _ = 0x7FFFFFFF, __ = _, ___ = _, ____ = _, _____ = _, ______ = landStartTimeSize, _______ = waterStartTimeSize;
    while (______--)
        _ = (_____ = *landStartTime++ + *landDuration++) < _ ? _____ : _;
    landStartTime -= landStartTimeSize, landDuration -= landDurationSize;
    while (_______--)
        _____ = _ > *waterStartTime ? _ + *waterDuration : *waterStartTime + *waterDuration, __ = _____ < __ ? _____ : __, waterStartTime++, waterDuration++;
    waterStartTime -= waterStartTimeSize, waterDuration -= waterDurationSize;
    while (waterDurationSize--)
        ___ = (_____ = *waterStartTime++ + *waterDuration++) < ___ ? _____ : ___;
    while (landDurationSize--)
        _____ = ___ > *landStartTime ? ___ + *landDuration : *landStartTime + *landDuration, ____ = _____ < ____ ? _____ : ____, landStartTime++, landDuration++;
    return __ < ____ ? __ : ____;
}