/* Program 292: Find the shortest suffix making a supplied DFA prefix accepted. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s MODEL.dfa BINARY_PREFIX\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 size_t n=strlen(argv[2]);
 if(n>4096){fprintf(stderr,"Maximum prefix length is 4096\n");return 2;}
 int start=d.start;
 for(size_t i=0;i<n;i++){
  int b=argv[2][i]-'0';
  if(b!=0&&b!=1){fprintf(stderr,"Binary prefix required\n");return 2;}
  start=d.go[start][b];
 }
 int queue[DFA_MAX],parent[DFA_MAX],edge[DFA_MAX],seen[DFA_MAX]={0};
 for(int q=0;q<d.n;q++){parent[q]=-1;edge[q]=-1;}
 queue[0]=start;seen[start]=1;int head=0,tail=1,goal=-1;
 while(head<tail){
  int q=queue[head++];
  if(d.final[q]){goal=q;break;}
  for(int b=0;b<2;b++){
   int z=d.go[q][b];if(!seen[z]){
    seen[z]=1;parent[z]=q;edge[z]=b;queue[tail++]=z;
   }
  }
 }
 if(goal<0){puts("NO_ACCEPTED_EXTENSION");return 0;}
 char reverse[DFA_MAX+1];int k=0;
 for(int q=goal;parent[q]>=0;q=parent[q])
  reverse[k++]=(char)('0'+edge[q]);
 printf("SUFFIX=");
 if(!k)printf("<epsilon>");
 for(int i=k-1;i>=0;i--)putchar(reverse[i]);
 printf(" LENGTH=%d\n",k);return 0;
}
