int maxNumberOfBalloons(char *text)
{
    int _[0x1A] = {0};
    while (*text)
        ++_[*text++ - 0x61];
    _[0xE] >>= 1;
    _[0xB] >>= 1;
    int __ = _[1];
    __ = _[0] < __ ? _[0] : __;
    __ = _[0xB] < __ ? _[0xB] : __;
    __ = _[0xE] < __ ? _[0xE] : __;
    __ = _[0xD] < __ ? _[0xD] : __;
    return __;
}
