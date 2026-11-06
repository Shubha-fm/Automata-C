/* Program 212: Count distinct NFA-accepted binary words without double-counting paths. ISO C11. */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
static unsigned step(unsigned mask,int bit){
    unsigned next=0;
    if(mask&1u){next|=1u;if(bit==0)next|=2u;}
    if((mask&2u)&&bit==1)next|=4u;
    if(mask&4u)next|=4u;
    return next;
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s LENGTH_0_TO_40\n",argv[0]);return 2;}
    errno=0;char*end=NULL;
    long length=strtol(argv[1],&end,10);
    if(errno==ERANGE||end==argv[1]||*end||length<0||length>40){
        fprintf(stderr,"Length must be 0..40\n");return 2;
    }
    uint64_t dp[8]={0};dp[1]=1;
    for(long i=0;i<length;i++){
        uint64_t next[8]={0};
        for(unsigned mask=0;mask<8;mask++)
            for(int bit=0;bit<2;bit++)
                next[step(mask,bit)]+=dp[mask];
        for(int j=0;j<8;j++)dp[j]=next[j];
    }
    uint64_t accepted=0;
    for(int mask=0;mask<8;mask++)if(mask&4)accepted+=dp[mask];
    printf("DISTINCT_ACCEPTED=%llu\n",(unsigned long long)accepted);
    return 0;
}
