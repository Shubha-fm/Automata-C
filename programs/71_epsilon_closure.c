/* Program 71: Compute epsilon closure of NFA state sets. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){unsigned edge[4]={2,4,8,0};for(unsigned i=0;i<4;i++){unsigned m=1u<<i,old;do{old=m;for(unsigned j=0;j<4;j++)if(m&(1u<<j))m|=edge[j];}while(m!=old);printf("q%u: ",i);for(unsigned j=0;j<4;j++)if(m&(1u<<j))printf("q%u ",j);puts("");}return 0;}
