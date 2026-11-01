/* Program 156: Dynamic programming counts accepted words of a given length. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* The two-state DFA accepts binary strings containing an even number of 1s. */
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s LENGTH_0_TO_32\n",argv[0]);return 2;}
    char *end=NULL;
    long len=strtol(argv[1],&end,10);
    if(!argv[1][0] || *end || len<0 || len>32){
        fprintf(stderr,"Length must be 0..32\n");return 2;
    }
    unsigned long long dp[2]={1,0};
    const int tr[2][2]={{0,1},{1,0}};
    for(long step=0;step<len;step++){
        unsigned long long next[2]={0,0};
        for(int q=0;q<2;q++)
            for(int bit=0;bit<2;bit++)next[tr[q][bit]]+=dp[q];
        for(int q=0;q<2;q++)dp[q]=next[q];
    }
    printf("ACCEPTED=%llu\n",dp[0]);
    return 0;
}
