/* Program 82: Check emptiness using reachable accepting states. Standalone educational example. */
#include <stdio.h>
int main(void){int t[3][2]={{1,0},{1,1},{2,2}},f[3]={0,0,1},seen[3]={1},queue[3]={0},h=0,n=1,found=0;while(h<n){int q=queue[h++];if(f[q])found=1;for(int b=0;b<2;b++){int z=t[q][b];if(!seen[z])seen[z]=1,queue[n++]=z;}}puts(found?"NONEMPTY":"EMPTY");return 0;}
