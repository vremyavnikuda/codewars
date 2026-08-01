#include <stdbool.h>
#include <string.h>

bool rotateString(char* s, char* goal){size_t _0=0,_1=0,_2;for(;s[_0]&&goal[_1];++_0,++_1);if(s[_0]|goal[_1])return 0;for(_2=0;_2<_0;++_2)if(s[_2]==*goal&&!memcmp(s+_2,goal,_0-_2)&&!memcmp(s,goal+_0-_2,_2))return 1;return !_0;}
