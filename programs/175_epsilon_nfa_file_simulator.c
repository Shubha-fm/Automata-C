/* Configurable epsilon-NFA simulator (up to sixteen states). */
#include <stdio.h>
#define MAX 16
static unsigned closure(unsigned active,int n,const unsigned eps[MAX]){
 unsigned old;do{old=active;for(int i=0;i<n;i++)if(active&(1u<<i))active|=eps[i];}while(old!=active);
 return active;
}
int main(int argc,char **argv){
 if(argc!=3){fprintf(stderr,"Usage: %s ENFA_FILE BINARY_WORD\n",argv[0]);return 2;}
 FILE*f=fopen(argv[1],"r");if(!f){perror("open");return 2;}
 int n,start,ok=1;unsigned final,moves[MAX][2],eps[MAX],bound=0;
 if(fscanf(f,"%d%d%u",&n,&start,&final)!=3||n<1||n>MAX||start<0||start>=n)ok=0;
 if(ok){bound=1u<<n;if(final>=bound)ok=0;}
 if(ok)for(int i=0;i<n;i++){
   if(fscanf(f,"%u%u%u",&moves[i][0],&moves[i][1],&eps[i])!=3||
      moves[i][0]>=bound||moves[i][1]>=bound||eps[i]>=bound){ok=0;break;}
 }
 fclose(f);if(!ok){fprintf(stderr,"Invalid epsilon-NFA file\n");return 2;}
 unsigned active=closure(1u<<start,n,eps);
 for(const char*s=argv[2];*s;s++){
   if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary input only\n");return 2;}
   unsigned next=0;for(int i=0;i<n;i++)if(active&(1u<<i))next|=moves[i][*s-'0'];
   active=closure(next,n,eps);
 }
 puts((active&final)?"ACCEPT":"REJECT");return 0;
}
