/* Program 296: Restrict DFA language to words avoiding a fixed binary substring. ISO C11. */
#include "../include/dfa_io.h"
#define MAX_PATTERN 30
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s MODEL.dfa NONEMPTY_BINARY_PATTERN\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 const char*pat=argv[2];size_t m=strlen(pat);
 if(m<1||m>MAX_PATTERN){fprintf(stderr,"Pattern length must be 1..30\n");return 2;}
 for(size_t i=0;i<m;i++)if(pat[i]!='0'&&pat[i]!='1'){
  fprintf(stderr,"Binary pattern required\n");return 2;
 }
 if(d.n*((int)m+1)>DFA_MAX){fprintf(stderr,"Pattern product exceeds 32 states\n");return 2;}
 int prefix[MAX_PATTERN]={0};
 for(int i=1;i<(int)m;i++){
  int k=prefix[i-1];
  while(k>0&&pat[k]!=pat[i])k=prefix[k-1];
  if(pat[k]==pat[i])k++;
  prefix[i]=k;
 }
 DFA out={0};out.n=d.n*((int)m+1);out.start=d.start*((int)m+1);
 for(int q=0;q<d.n;q++)for(int k=0;k<=(int)m;k++){
  int index=q*((int)m+1)+k;
  out.final[index]=(k<(int)m)&&d.final[q];
  for(int bit=0;bit<2;bit++){
   int next=k;
   if(next<(int)m){
    char c=(char)('0'+bit);
    while(next>0&&pat[next]!=c)next=prefix[next-1];
    if(pat[next]==c)next++;
   }
   out.go[index][bit]=d.go[q][bit]*((int)m+1)+next;
  }
 }
 dfa_write(&out);return 0;
}
