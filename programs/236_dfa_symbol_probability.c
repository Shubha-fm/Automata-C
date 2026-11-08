/* Program 236: Compute DFA state probabilities under biased independent binary input. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
int main(int argc,char**argv){
    if(argc!=3){fprintf(stderr,"Usage: %s STEPS_0_TO_100000 PROBABILITY_ONE\n",argv[0]);return 2;}
    errno=0;char*end=NULL;
    long n=strtol(argv[1],&end,10);
    if(errno==ERANGE||end==argv[1]||*end||n<0||n>100000){
        fprintf(stderr,"Invalid number of steps\n");return 2;
    }
    errno=0;
    double p=strtod(argv[2],&end);
    if(errno==ERANGE||end==argv[2]||*end||!isfinite(p)||p<0||p>1){
        fprintf(stderr,"Probability must be within [0,1]\n");return 2;
    }
    double even=1.0,odd=0.0;
    for(long step=0;step<n;step++){
        double next_even=even*(1-p)+odd*p;
        double next_odd=odd*(1-p)+even*p;
        even=next_even;odd=next_odd;
    }
    printf("P_EVEN=%.6f P_ODD=%.6f\n",even,odd);
    return 0;
}
