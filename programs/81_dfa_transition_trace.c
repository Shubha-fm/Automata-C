/* Program 81: Trace transitions for input 1010. Standalone educational example. */
#include <stdio.h>
int main(void){int t[2][2]={{0,1},{0,1}},q=0;char *s="1010";printf("start=%d",q);for(char*p=s;*p;p++){q=t[q][*p-'0'];printf(" -> %d",q);}printf("\nfinal=%d\n",q);return 0;}
