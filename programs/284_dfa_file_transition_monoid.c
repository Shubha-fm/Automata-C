/* Program 284: Enumerate the transition monoid of a file-based DFA. ISO C11. */
#include "../include/dfa_io.h"
#define MAX_MONOID 3125
static int maps[MAX_MONOID][5],seen[MAX_MONOID],queue[MAX_MONOID];
static int encode(const int *map,int n){
 int result=0;for(int i=0;i<n;i++)result=result*n+map[i];return result;
}
static void decode(int code,int n,int *map){
 for(int i=n-1;i>=0;i--){map[i]=code%n;code/=n;}
}
int main(int argc,char **argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(d.n>5){fprintf(stderr,"Monoid calculation limited to 5 states\n");return 2;}
 int map[5],h=0,t=1;
 for(int q=0;q<d.n;q++)map[q]=q;
 int initial=encode(map,d.n);seen[initial]=1;queue[0]=initial;
 while(h<t){
  int code=queue[h++];decode(code,d.n,map);
  for(int bit=0;bit<2;bit++){
   int next[5];
   for(int q=0;q<d.n;q++)next[q]=d.go[map[q]][bit];
   int key=encode(next,d.n);
   if(!seen[key]){
    seen[key]=1;maps[t][0]=key;queue[t++]=key;
   }
  }
 }
 printf("MONOID_SIZE=%d\n",t);
 for(int k=0;k<t;k++){
  decode(queue[k],d.n,map);
  printf("MAP_%d=",k);
  for(int q=0;q<d.n;q++)printf("%s%d",q?",":"",map[q]);
  putchar('\n');
 }
 return 0;
}
