/* Program 89: Generate Moore machine outputs for 10110. Standalone educational example. */
#include <stdio.h>
int main(void){int t[2][2]={{0,1},{0,1}},output[2]={0,1},q=0;char*s="10110";printf("output: %d",output[q]);for(char*p=s;*p;p++){q=t[q][*p-'0'];printf(" %d",output[q]);}puts("");return 0;}
