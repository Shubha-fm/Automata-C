/* Program 88: Simulate an NFA on 0101 using bit sets. Standalone educational example. */
#include <stdio.h>
int main(void){unsigned t[3][2]={{3,1},{0,4},{0,4}},mask=1;char*s="0101";for(char*p=s;*p;p++){unsigned next=0;for(int q=0;q<3;q++)if(mask&(1u<<q))next|=t[q][*p-'0'];mask=next;printf("after %c: %u\n",*p,mask);}puts((mask&4)?"ACCEPT":"REJECT");return 0;}
