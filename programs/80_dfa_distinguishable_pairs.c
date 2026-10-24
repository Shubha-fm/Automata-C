/* Program 80: Table-filling distinguishability for DFA states. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){int t[4][2]={{1,2},{1,3},{1,2},{1,3}},fin[4]={0,1,0,1},marked[4][4]={{0}};for(int i=0;i<4;i++)for(int j=0;j<i;j++)if(fin[i]!=fin[j])marked[i][j]=1;int change;do{change=0;for(int i=0;i<4;i++)for(int j=0;j<i;j++)if(!marked[i][j])for(int b=0;b<2;b++){int x=t[i][b],y=t[j][b];if(x<y){int z=x;x=y;y=z;}if(marked[x][y]){marked[i][j]=1;change=1;break;}}}while(change);for(int i=0;i<4;i++)for(int j=0;j<i;j++)printf("q%d,q%d: %s\n",i,j,marked[i][j]?"distinguishable":"equivalent");return 0;}
