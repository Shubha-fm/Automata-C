/* Program 63: DFA complement: strings avoiding 00. Binary alphabet. */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static int accept(const char *s){int q=0;for(;*s;s++){if(q==0)q=(*s=='0'?1:0);else if(q==1)q=(*s=='0'?2:0);}return q!=2;}
int main(int argc,char **argv){char buf[4096];const char *s;if(argc>2){fprintf(stderr,"Usage: %s [binary-string]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{printf("Enter binary string: ");if(!fgets(buf,sizeof(buf),stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}for(const char *p=s;*p;p++)if(*p!='0'&&*p!='1'){fprintf(stderr,"Only 0 and 1 allowed\n");return 2;}puts(accept(s)?"ACCEPT":"REJECT");return 0;}
