/* Aho-Corasick automaton for three binary patterns. */
#include <stdio.h>
#include <string.h>
#define MAX 32
static const char *pat[]={"001","010","111"};
typedef struct{int next[2],fail;unsigned out;}Node;
static Node nodes[MAX];static int count=1;
int main(int argc,char **argv){
 if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
 for(int p=0;p<3;p++){
   int q=0;for(const char*s=pat[p];*s;s++){
     int b=*s-'0';if(!nodes[q].next[b]){
       if(count>=MAX)return 2;
       nodes[q].next[b]=count++;
     }q=nodes[q].next[b];
   }nodes[q].out|=1u<<p;
 }
 int queue[MAX]={0},h=0,t=0;
 for(int b=0;b<2;b++)if(nodes[0].next[b])queue[t++]=nodes[0].next[b];
 while(h<t){int q=queue[h++];
   for(int b=0;b<2;b++){
     int z=nodes[q].next[b];
     if(z){nodes[z].fail=nodes[nodes[q].fail].next[b];
       nodes[z].out|=nodes[nodes[z].fail].out;queue[t++]=z;}
     else nodes[q].next[b]=nodes[nodes[q].fail].next[b];
   }
 }
 int q=0,hits=0;
 for(size_t i=0;argv[1][i];i++){
   char c=argv[1][i];if(c!='0'&&c!='1'){
      fprintf(stderr,"Binary input only\n");return 2;}
   q=nodes[q].next[c-'0'];
   for(int p=0;p<3;p++)if(nodes[q].out&(1u<<p)){
      printf("%s@%zu\n",pat[p],i+1-strlen(pat[p]));hits++;
   }
 }
 printf("HITS=%d\n",hits);return 0;
}
