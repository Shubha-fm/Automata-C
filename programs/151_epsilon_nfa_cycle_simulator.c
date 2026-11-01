/* Program 151: Epsilon-NFA simulation with a cyclic epsilon closure. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* States: 0 eps->1, 1 eps->0; 1 loops and can begin 01; 3 accepts. */
static unsigned closure(unsigned mask) {
    unsigned old;
    do {
        old=mask;
        if(mask & 1u) mask |= 2u;
        if(mask & 2u) mask |= 1u;
    } while(mask!=old);
    return mask;
}
static int accepts(const char *s) {
    unsigned states=closure(1u);
    for (;*s;s++) {
        if(*s!='0' && *s!='1') return 0;
        unsigned next=0;
        if(states & 2u) { next|=2u; if(*s=='0')next|=4u; }
        if((states & 4u) && *s=='1') next|=8u;
        if(states & 8u) next|=8u;
        states=closure(next);
    }
    return (states & 8u)!=0;
}
int main(int argc,char **argv) {
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    puts(accepts(argv[1]) ? "ACCEPT":"REJECT");
    return 0;
}
