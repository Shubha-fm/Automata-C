/* Program 90: Generate Mealy machine outputs for 10110. Standalone educational example. */
#include <stdio.h>
int main(void){int t[2][2]={{0,1},{0,1}},out[2][2]={{0,1},{1,0}},q=0;char*s="10110";printf("output:");for(char*p=s;*p;p++){int b=*p-'0';printf(" %d",out[q][b]);q=t[q][b];}puts("");return 0;}
