#include <stdbool.h>

bool isGood(int* nums,int numsSize){int n=numsSize-1,i=0,x,c=0,u=0;if(n<1)return 0;for(;i<numsSize;++i)if(((x=nums[i])<0&&(x=-x)),x^n){if((unsigned)(x-1)>=(unsigned)(n-1)||nums[x-1]<0)return 0;nums[x-1]=-nums[x-1],++u;}else++c;return !((c^2)|(u^(n-1)));}
