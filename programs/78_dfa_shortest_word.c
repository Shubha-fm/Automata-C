/* Program 78: Find shortest accepted word using BFS. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){int t[4][2]={{1,0},{1,2},{3,0},{3,3}},final[4]={0,0,0,1},seen[4]={1},q[4]={0},prev[4]={-1},sym[4]={0},h=0,n=1,target=-1;while(h<n){int s=q[h++];if(final[s]){target=s;break;}for(int b=0;b<2;b++){int v=t[s][b];if(!seen[v]){seen[v]=1;q[n++]=v;prev[v]=s;sym[v]=b;}}}if(target<0){puts("Language empty");return 0;}char word[5];int size=0;for(int s=target;prev[s]>=0;s=prev[s])word[size++]=(char)('0'+sym[s]);printf("Shortest accepted word: ");while(size)putchar(word[--size]);putchar('\n');return 0;}
