/* Program 75: Check sample DFA equivalence by product-state BFS. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){int a[2][2]={{1,0},{0,1}},b[4][2]={{1,2},{0,3},{3,0},{2,1}},fa[2]={1,0},fb[4]={1,0,0,1},seen[8]={1},q[8]={0},h=0,n=1;while(h<n){int p=q[h++],x=p/4,y=p%4;if(fa[x]!=fb[y]){puts("NOT EQUIVALENT");return 0;}for(int bit=0;bit<2;bit++){int np=a[x][bit]*4+b[y][bit];if(!seen[np]){seen[np]=1;q[n++]=np;}}}puts("EQUIVALENT");return 0;}
