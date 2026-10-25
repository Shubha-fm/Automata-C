/* Program 83: Check whether every binary string is accepted. Standalone educational example. */
#include <stdio.h>
int main(void){int t[3][2]={{1,2},{1,1},{2,2}},f[3]={1,1,0},seen[3]={1},queue[3]={0},h=0,n=1,all=1;while(h<n){int q=queue[h++];if(!f[q])all=0;for(int b=0;b<2;b++){int z=t[q][b];if(!seen[z])seen[z]=1,queue[n++]=z;}}puts(all?"UNIVERSAL":"NOT UNIVERSAL");return 0;}
