/* Buchi nonemptiness: reachable accepting state on a reachable cycle. */
#include <stdio.h>
#define MAX 6
static int nonempty(int n,const int graph[MAX][MAX],const int final[MAX]){
 int reach[MAX][MAX]={0};
 for(int i=0;i<n;i++)for(int j=0;j<n;j++)reach[i][j]=graph[i][j];
 for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)
    if(reach[i][k]&&reach[k][j])reach[i][j]=1;
 for(int i=0;i<n;i++)if(final[i]&&reach[i][i]&&(i==0||reach[0][i]))return i;
 return -1;
}
int main(void){
 static const int g1[MAX][MAX]={
 {0,1,0,0,0,0},{0,0,1,0,0,0},{0,0,0,1,0,0},
 {0,0,0,0,1,0},{0,0,0,1,0,0},{0,0,0,0,0,0}};
 static const int f1[MAX]={0,0,0,1,0,0};
 static const int g2[MAX][MAX]={
 {0,1,0,0,0,0},{0,0,1,0,0,0},{0,0,0,1,0,0},
 {0,0,0,0,1,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
 static const int f2[MAX]={0,0,0,1,0,0};
 int a=nonempty(6,g1,f1),b=nonempty(6,g2,f2);
 if(a<0)puts("CYCLIC_EXAMPLE=EMPTY");else printf("CYCLIC_EXAMPLE=NONEMPTY state=q%d\n",a);
 if(b<0)puts("ACYCLIC_EXAMPLE=EMPTY");else printf("ACYCLIC_EXAMPLE=NONEMPTY state=q%d\n",b);
 return 0;
}
