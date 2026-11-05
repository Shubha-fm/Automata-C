/* Program 206: Derivative-state recognition of the fixed regular expression 0*1. ISO C11. */
#include <stdio.h>
/* States represent 0*1, epsilon, and the empty language. */
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    int derivative=0;
    for(const char*s=argv[1];*s;s++){
        if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary alphabet only\n");return 2;}
        if(derivative==0)derivative=(*s=='0')?0:1;
        else derivative=2;
    }
    const char*states[]={"ZERO_STAR_ONE","EPSILON","EMPTY"};
    printf("DERIVATIVE=%s %s\n",states[derivative],derivative==1?"ACCEPT":"REJECT");
    return 0;
}
