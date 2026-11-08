/* Program 239: Enumerate distinct NFA-accepted binary words of a specified length. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
static unsigned step(unsigned mask,int bit){
    unsigned out=0;
    if(mask&1u){out|=1u;if(bit==0)out|=2u;}
    if((mask&2u)&&bit==1)out|=4u;
    if(mask&4u)out|=4u;
    return out;
}
static char word[14];
static int total=0;
static void enumerate(int length,int position,unsigned subset){
    if(position==length){
        if(subset&4u){word[length]='\0';printf("WORD=%s\n",word);total++;}
        return;
    }
    for(int bit=0;bit<2;bit++){
        word[position]=(char)('0'+bit);
        enumerate(length,position+1,step(subset,bit));
    }
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s LENGTH_0_TO_12\n",argv[0]);return 2;}
    errno=0;char*end=NULL;long n=strtol(argv[1],&end,10);
    if(errno==ERANGE||end==argv[1]||*end||n<0||n>12){
        fprintf(stderr,"Length must be 0..12\n");return 2;
    }
    enumerate((int)n,0,1u);
    printf("TOTAL=%d\n",total);
    return 0;
}
