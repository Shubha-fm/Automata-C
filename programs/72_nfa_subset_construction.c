/* Program 72: Convert sample NFA to DFA by subset construction. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){unsigned nfa[3][2]={{3,1},{0,4},{0,4}},seen[8]={1},queue[8]={1},h=0,t=1;while(h<t){unsigned mask=queue[h++];printf("{");for(int i=0;i<3;i++)if(mask&(1u<<i))printf("%d",i);printf("}");for(int b=0;b<2;b++){unsigned next=0;for(int i=0;i<3;i++)if(mask&(1u<<i))next|=nfa[i][b];printf(" %c=%u",'0'+b,next);if(!seen[next]){seen[next]=1;queue[t++]=next;}}puts("");}return 0;}
