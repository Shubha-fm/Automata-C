/* Program 74: Minimize a sample DFA with partition refinement. Built-in illustrative automaton. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){int t[4][2]={{1,2},{1,3},{1,2},{1,3}},final[4]={0,1,0,1},cls[4]={0,1,0,1},tmp[4];for(int iter=0;iter<4;iter++){int groups=0;for(int i=0;i<4;i++){int j;for(j=0;j<i;j++)if(final[i]==final[j]&&cls[t[i][0]]==cls[t[j][0]]&&cls[t[i][1]]==cls[t[j][1]])break;tmp[i]=(j<i)?tmp[j]:groups++;}int changed=0;for(int i=0;i<4;i++){if(tmp[i]!=cls[i])changed=1;cls[i]=tmp[i];}if(!changed)break;}int groups=0;for(int i=0;i<4;i++)if(cls[i]>=groups)groups=cls[i]+1;printf("Minimized states: %d\n",groups);for(int i=0;i<4;i++)printf("q%d -> group %d\n",i,cls[i]);return 0;}
