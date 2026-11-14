/* Program 300: Compute distinguishable residual-language classes of reachable DFA states. ISO C11. */
#include "../include/dfa_io.h"
static int different[DFA_MAX][DFA_MAX];
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int seen[DFA_MAX]={0},queue[DFA_MAX],h=0,t=1;
 queue[0]=d.start;seen[d.start]=1;
 while(h<t){
  int q=queue[h++];
  for(int bit=0;bit<2;bit++){
   int z=d.go[q][bit];if(!seen[z]){seen[z]=1;queue[t++]=z;}
  }
 }
 for(int q=0;q<d.n;q++)for(int r=0;r<d.n;r++)
  different[q][r]=d.final[q]!=d.final[r];
 int changed;
 do{
  changed=0;
  for(int q=0;q<d.n;q++)for(int r=0;r<d.n;r++){
   if(different[q][r])continue;
   for(int bit=0;bit<2;bit++){
    if(different[d.go[q][bit]][d.go[r][bit]]){
     different[q][r]=1;changed=1;break;
    }
   }
  }
 }while(changed);
 int classes[DFA_MAX],representatives[DFA_MAX],count=0;
 for(int q=0;q<d.n;q++)classes[q]=-1;
 for(int i=0;i<t;i++){
  int q=queue[i],class_id=-1;
  for(int k=0;k<count;k++){
   if(!different[q][representatives[k]]){class_id=k;break;}
  }
  if(class_id<0){class_id=count;representatives[count++]=q;}
  classes[q]=class_id;
 }
 printf("REACHABLE=%d RESIDUAL_CLASSES=%d MINIMAL=%s\n",
  t,count,t==count?"YES":"NO");
 for(int i=0;i<t;i++){
  int q=queue[i];printf("q%d=class%d\n",q,classes[q]);
 }
 return 0;
}
