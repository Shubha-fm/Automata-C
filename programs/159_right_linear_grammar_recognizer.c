/* Program 159: Right-linear grammar recognition via an equivalent NFA. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* Grammar: S -> 0S | 1A; A -> 0A | 1.
   The resulting regular language is 0*10*1. */
static int accepts(const char *s){
    unsigned mask=1u;
    for(;*s;s++){
        if(*s!='0'&&*s!='1')return 0;
        unsigned next=0;
        if(mask&1u){if(*s=='0')next|=1u;else next|=2u;}
        if(mask&2u){if(*s=='0')next|=2u;else next|=4u;}
        mask=next;
    }
    return !!(mask&4u);
}
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    puts(accepts(argv[1])?"ACCEPT":"REJECT");
    return 0;
}
