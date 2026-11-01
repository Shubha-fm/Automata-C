/* Program 157: Count accepting runs of a nondeterministic automaton. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* Each occurrence of 01 creates one accepting run; final state loops. */
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    const char*s=argv[1];
    if(strlen(s)>32){fprintf(stderr,"Maximum 32 input digits\n");return 2;}
    unsigned long long q0=1,q1=0,q2=0;
    for(;*s;s++){
        if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary only\n");return 2;}
        unsigned long long a=0,b=0,c=0;
        if(*s=='0'){a=q0;b=q0;c=q2;}
        else {a=q0;c=q1+q2;}
        q0=a;q1=b;q2=c;
    }
    printf("ACCEPTING_PATHS=%llu\n",q2);
    return 0;
}
