/* NFA simulator using 16-bit state sets from an input file. */
#include <stdio.h>
#include <stdint.h>
#define MAX 16
int main(int argc,char **argv){
 if(argc!=3){fprintf(stderr,"Usage: %s NFA_FILE BINARY_WORD\n",argv[0]);return 2;}
 FILE*f=fopen(argv[1],"r");if(!f){perror("open");return 2;}
 int n,start;unsigned final,mask[MAX][2],bound=0;int ok=1;
 if(fscanf(f,"%d%d%u",&n,&start,&final)!=3||n<1||n>MAX||start<0||start>=n)ok=0;
 if(ok){bound=1u<<n;if(final>=bound)ok=0;}
 if(ok)for(int i=0;i<n;i++)for(int b=0;b<2;b++)if(fscanf(f,"%u",&mask[i][b])!=1||mask[i][b]>=bound)ok=0;
 fclose(f);if(!ok){fprintf(stderr,"Invalid NFA file\n");return 2;}
 unsigned active=1u<<start;
 for(const char*s=argv[2];*s;s++){
   if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary input only\n");return 2;}
   unsigned next=0;for(int i=0;i<n;i++)if(active&(1u<<i))next|=mask[i][*s-'0'];
   active=next;
 }
 puts((active&final)?"ACCEPT":"REJECT");return 0;
}
