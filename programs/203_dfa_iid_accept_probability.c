/* Program 203: Compute DFA acceptance probability for uniformly random binary words. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
static const int delta[3][2]={{1,0},{1,2},{1,0}};
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s LENGTH_0_TO_100000\n",argv[0]);return 2;}
    errno=0;char*end=NULL;
    long n=strtol(argv[1],&end,10);
    if(errno==ERANGE||end==argv[1]||*end||n<0||n>100000){
        fprintf(stderr,"Invalid length\n");return 2;
    }
    double p[3]={1.0,0,0};
    for(long k=0;k<n;k++){
        double next[3]={0,0,0};
        for(int q=0;q<3;q++)for(int bit=0;bit<2;bit++)
            next[delta[q][bit]]+=p[q]*0.5;
        for(int q=0;q<3;q++)p[q]=next[q];
    }
    printf("P_ACCEPT=%.6f\n",p[2]);
    return 0;
}
