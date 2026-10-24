/* Program 77: Construct product automaton for even zeros AND even ones. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){puts("state  on0  on1  final");for(int a=0;a<2;a++)for(int b=0;b<2;b++){int s=2*a+b;printf("%5d %4d %4d %6s\n",s,2*(a^1)+b,2*a+(b^1),s==0?"yes":"no");}return 0;}
