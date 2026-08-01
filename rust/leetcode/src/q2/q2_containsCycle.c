#include <stdbool.h>
#include <stdlib.h>

bool containsCycle(char **grid, int gridSize, int *gridColSize)
{
    int a,b,c,d,e,f,g,h,*q,p,r,s,t,u,n,m=gridSize,D[5]={-1,0,1,0,-1};
    if(!m)return 0;
    n=gridColSize[0];
    if(!n)return 0;
    q=malloc((size_t)m*n*sizeof*q);
    if(!q)return 0;
    for(a=0;a<m;++a)for(b=0;b<n;++b)if(grid[a][b]>96){
        c=grid[a][b];p=r=0;grid[a][b]^=32;q[r++]=((a*n+b)<<3)|4;
        while(p<r){
            e=q[p++];f=e>>3;g=f/n;h=f-g*n;
            for(d=0;d<4;++d)if((e&7)!=d){
                s=g+D[d];t=h+D[d+1];
                if((unsigned)s<(unsigned)m&&(unsigned)t<(unsigned)n){
                    u=grid[s][t];
                    if(u==c)grid[s][t]^=32,q[r++]=((s*n+t)<<3)|((d+2)&3);
                    else if(u==(c^32)){free(q);return 1;}
                }
            }
        }
    }
    free(q);
    return 0;
}
