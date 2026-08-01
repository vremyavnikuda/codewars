#include <stdlib.h>
long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    int _=numsSize,*c=(int*)calloc((_<<1)+2,sizeof(int)),s=_+1,*e=nums+_,i,t;
    long long r=0;
    for(i=s;i<=(_<<1)+1;i+=i&-i)++c[i];
    for(;nums<e;r+=t){
        for(s+=*nums++==target?1:-1,t=0,i=s-1;i;i&=i-1)t+=c[i];
        for(i=s;i<=(_<<1)+1;i+=i&-i)++c[i];
    }
    free(c);
    return r;
}
