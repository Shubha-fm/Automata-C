/* Load and simulate a DFA encoded as an integer transition table. */
#include <stdio.h>
#include <string.h>
#define MAX 32
int main(int argc,char **argv){
 if(argc!=3){fprintf(stderr,"Usage: %s DFA_FILE BINARY_WORD\n",argv[0]);return 2;}
 FILE*f=fopen(argv[1],"r");if(!f){perror("open");return 2;}
 int n,start,k,final[MAX]={0},tr[MAX][2],ok=1;
 if(fscanf(f,"%d%d%d",&n,&start,&k)!=3||n<1||n>MAX||start<0||start>=n||k<0||k>n)ok=0;
 if(ok)for(int i=0;i<k;i++){int v;if(fscanf(f,"%d",&v)!=1||v<0||v>=n){ok=0;break;}final[v]=1;}
 if(ok)for(int i=0;i<n;i++)for(int b=0;b<2;b++)if(fscanf(f,"%d",&tr[i][b])!=1||tr[i][b]<0||tr[i][b]>=n)ok=0;
 fclose(f);if(!ok){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int state=start;for(const char*s=argv[2];*s;s++){
   if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary input only\n");return 2;}
   state=tr[state][*s-'0'];
 }
 puts(final[state]?"ACCEPT":"REJECT");return 0;
}
