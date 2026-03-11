int bitwiseComplement(int n){unsigned _=(unsigned)(n|!n);_|=_>>1,_|=_>>2,_|=_>>4,_|=_>>8,_|=_>>16;return (int)(_^(unsigned)n);} 
