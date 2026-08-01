#include <stdbool.h>

bool hasValidPath(int** grid, int gridSize, int* gridColSize) {
    int m=gridSize,n,a,b,c,d,e,f,g,h;
    if(!m||!(n=*gridColSize))return 0;
    if(m==1&&n==1)return 1;
    for(a=0x65A9C30>>(**grid<<2)&15,b=4;b--;)if(a>>b&1){
        c=d=0;e=b;f=m*n;
        while(f--){
            c+=(e==3)-(e==2);d+=(e==1)-(e==0);
            if((unsigned)c>=(unsigned)m||(unsigned)d>=(unsigned)n)break;
            g=0x65A9C30>>(grid[c][d]<<2)&15;h=e^1;
            if(!(g>>h&1))break;
            if(c==m-1&&d==n-1)return 1;
            g^=1<<h;
            e=(g>1)+(g>3)+(g>7);
            if(!c&&!d)break;
        }
    }
    return 0;
}
