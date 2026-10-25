/* Program 85: Compute epsilon-closure of a chosen state set. Standalone educational example. */
#include <stdio.h>
int main(void){unsigned eps[5]={2,4,0,16,0},mask=(1u<<0)|(1u<<3),old;do{old=mask;for(int i=0;i<5;i++)if(mask&(1u<<i))mask|=eps[i];}while(old!=mask);printf("closure:");for(int i=0;i<5;i++)if(mask&(1u<<i))printf(" q%d",i);puts("");return 0;}
