/* Program 299: Find a reachable accepting-state cycle witnessing Büchi nonemptiness. ISO C11. */
#include "../include/dfa_io.h"
static DFA d;
static int get_cycle(int start,char out[DFA_MAX+1]){
 int queue[DFA_MAX],seen[DFA_MAX]={0},parent[DFA_MAX],edge[DFA_MAX];
 for(int q=0;q<d.n;q++){parent[q]=-1;edge[q]=-1;}
 queue[0]=start;seen[start]=1;int h=0,t=1;
 while(h<t){
  int q=queue[h++];
  for(int bit=0;bit<2;bit++){
   int next=d.go[q][bit];
   if(next==start){
    char reverse[DFA_MAX+1];int length=0;
    reverse[length++]=(char)('0'+bit);
    for(int p=q;parent[p]>=0;p=parent[p])
     reverse[length++]=(char)('0'+edge[p]);
    for(int i=0;i<length;i++)out[i]=reverse[length-i-1];
    out[length]='\0';return length;
   }
   if(!seen[next]){
    seen[next]=1;parent[next]=q;edge[next]=bit;queue[t++]=next;
   }
  }
 }
 return -1;
}
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int seen[DFA_MAX]={0},parent[DFA_MAX],edge[DFA_MAX],queue[DFA_MAX],dist[DFA_MAX]={0};
 for(int q=0;q<d.n;q++){parent[q]=-1;edge[q]=-1;}
 queue[0]=d.start;seen[d.start]=1;int h=0,t=1;
 while(h<t){
  int q=queue[h++];
  for(int bit=0;bit<2;bit++){
   int next=d.go[q][bit];
   if(!seen[next]){
    seen[next]=1;parent[next]=q;edge[next]=bit;
    dist[next]=dist[q]+1;queue[t++]=next;
   }
  }
 }
 int goal=-1,best=1000000;char loop[DFA_MAX+1],candidate[DFA_MAX+1];
 for(int i=0;i<t;i++){
  int q=queue[i];if(!d.final[q])continue;
  int size=get_cycle(q,candidate);
  if(size>0 && dist[q]+size<best){
   goal=q;best=dist[q]+size;strcpy(loop,candidate);
  }
 }
 if(goal<0){puts("BUCHI_EMPTY");return 0;}
 char reverse[DFA_MAX+1];int n=0;
 for(int q=goal;parent[q]>=0;q=parent[q])
  reverse[n++]=(char)('0'+edge[q]);
 printf("BUCHI_NONEMPTY PREFIX=");
 if(!n)printf("<epsilon>");
 while(n){putchar(reverse[--n]);}
 printf(" LOOP=%s TOTAL_LENGTH=%d\n",loop,best);
 return 0;
}
