/* Program 79: Enumerate accepted binary strings of length three. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){int t[3][2]={{1,0},{1,2},{1,0}},final[3]={0,0,1};for(int x=0;x<8;x++){int state=0;char s[4];for(int j=0;j<3;j++){int b=(x>>(2-j))&1;s[j]=(char)('0'+b);state=t[state][b];}s[3]=0;if(final[state])puts(s);}return 0;}
