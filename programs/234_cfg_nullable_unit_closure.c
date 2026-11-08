/* Program 234: Compute nullable nonterminals and unit-production closure of a CFG. ISO C11. */
#include <stdio.h>
#define N 3
static const char names[N]={'S','A','B'};
static int unit[N][N]={{0,1,0},{0,0,1},{0,1,0}};
static int nullable[N]={0,1,0};
int main(void){
    for(int i=0;i<N;i++)unit[i][i]=1;
    for(int mid=0;mid<N;mid++)for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)if(unit[i][mid]&&unit[mid][j])unit[i][j]=1;
    int changed;
    do{
        changed=0;
        for(int i=0;i<N;i++)for(int j=0;j<N;j++)
            if(unit[i][j]&&nullable[j]&&!nullable[i]){
                nullable[i]=1;changed=1;
            }
    }while(changed);
    /* S -> b; B -> a. Unit closure copies terminal rules to ancestors. */
    const int terminal[N][2]={{0,1},{0,0},{1,0}};
    for(int i=0;i<N;i++){
        printf("%c NULLABLE=%s UNIT=",names[i],nullable[i]?"YES":"NO");
        for(int j=0;j<N;j++)if(unit[i][j])putchar(names[j]);
        printf(" TERMINALS=");
        for(int k=0;k<2;k++){
            int enabled=0;
            for(int j=0;j<N;j++)if(unit[i][j]&&terminal[j][k])enabled=1;
            if(enabled)putchar('a'+k);
        }
        putchar('\n');
    }
    return 0;
}
