/* Program 297: Give a shortest safety counterexample and a valid infinite lasso. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int queue[DFA_MAX],seen[DFA_MAX]={0},parent[DFA_MAX],edge[DFA_MAX];
 for(int q=0;q<d.n;q++){parent[q]=-1;edge[q]=-1;}
 queue[0]=d.start;seen[d.start]=1;int h=0,t=1,goal=-1;
 while(h<t){
  int q=queue[h++];
  if(!d.final[q]){goal=q;break;}
  for(int b=0;b<2;b++){
   int next=d.go[q][b];
   if(!seen[next]){
    seen[next]=1;parent[next]=q;edge[next]=b;queue[t++]=next;
   }
  }
 }
 if(goal<0){puts("SAFETY_PASS");return 0;}
 char word[DFA_MAX+1];int n=0;
 for(int q=goal;parent[q]>=0;q=parent[q])word[n++]=(char)('0'+edge[q]);
 printf("SAFETY_FAIL WITNESS=");
 if(!n)printf("<epsilon>");
 while(n){putchar(word[--n]);}
 int first[DFA_MAX],states[DFA_MAX+1];
 for(int q=0;q<d.n;q++)first[q]=-1;
 int q=goal,length=0;
 while(first[q]<0){
  first[q]=length;states[length++]=q;q=d.go[q][0];
 }
 int prefix=first[q],period=length-prefix;
 printf(" TAIL_ZEROS=%d LOOP_ZEROS=%d\n",prefix,period);
 return 0;
}
