/* Program 76: Construct complement accepting states. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){int accepting[4]={0,1,0,1};puts("Complement final states:");for(int i=0;i<4;i++)if(!accepting[i])printf("q%d\n",i);return 0;}
