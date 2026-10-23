/* Program 62: Epsilon-NFA simulation: ends in 10. Binary alphabet. */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static unsigned closure(unsigned m){if(m&1)m|=2;return m;} static int accept(const char *s){unsigned m=closure(1);for(;*s;s++){unsigned n=0;if(m&2)n|=2;if(*s=='1'&&(m&2))n|=4;if(*s=='0'&&(m&4))n|=8;m=closure(n);}return !!(m&8);}
int main(int argc,char **argv){char buf[4096];const char *s;if(argc>2){fprintf(stderr,"Usage: %s [binary-string]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{printf("Enter binary string: ");if(!fgets(buf,sizeof(buf),stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}for(const char *p=s;*p;p++)if(*p!='0'&&*p!='1'){fprintf(stderr,"Only 0 and 1 allowed\n");return 2;}puts(accept(s)?"ACCEPT":"REJECT");return 0;}
