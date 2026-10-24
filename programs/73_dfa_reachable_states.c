/* Program 73: Find reachable DFA states with BFS. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){int t[5][2]={{1,2},{1,3},{2,3},{3,3},{4,4}},seen[5]={1},q[5]={0},h=0,n=1;while(h<n){int s=q[h++];for(int b=0;b<2;b++){int v=t[s][b];if(!seen[v]){seen[v]=1;q[n++]=v;}}}printf("Reachable:");for(int i=0;i<5;i++)if(seen[i])printf(" %d",i);puts("");return 0;}
