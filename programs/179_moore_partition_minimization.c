/* Partition refinement for a fixed Moore machine with outputs on states. */
#include <stdio.h>
#define N 5
static const int trans[N][2]={{2,3},{2,3},{2,4},{3,4},{4,4}};
static const int output[N]={0,0,1,1,0};
int main(void){
 int cls[N],next[N],groups;
 for(int i=0;i<N;i++)cls[i]=output[i];
 for(int iteration=0;iteration<N;iteration++){
   groups=0;
   for(int i=0;i<N;i++){
     int j=0;for(;j<i;j++)if(output[i]==output[j]&&
      cls[trans[i][0]]==cls[trans[j][0]]&&
      cls[trans[i][1]]==cls[trans[j][1]])break;
     next[i]=j<i?next[j]:groups++;
   }
   int changed=0;for(int i=0;i<N;i++)if(next[i]!=cls[i])changed=1;
   for(int i=0;i<N;i++)cls[i]=next[i];
   if(!changed)break;
 }
 groups=0;for(int i=0;i<N;i++)if(groups<=cls[i])groups=cls[i]+1;
 printf("MOORE_MINIMIZED_STATES=%d\n",groups);
 for(int i=0;i<N;i++)printf("q%d -> class%d\n",i,cls[i]);
 return 0;
}
