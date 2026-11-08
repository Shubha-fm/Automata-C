/* Program 232: Compare two NFAs on every binary word up to a chosen length. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
static unsigned step_a(unsigned mask,int bit){
    unsigned out=0;
    if(mask&1u){out|=1u;if(bit==0)out|=2u;}
    if((mask&2u)&&bit==1)out|=4u;
    if(mask&4u)out|=4u;
    return out;
}
static unsigned step_b(unsigned mask,int bit,int mutant){
    unsigned out=0;
    if(mask&1u){out|=1u;if(bit==0)out|=2u|8u;}
    if(!mutant&&bit==1&&(mask&(2u|8u)))out|=4u;
    if(mask&4u)out|=4u;
    return out;
}
int main(int argc,char**argv){
    if(argc<2||argc>3||(argc==3&&strcmp(argv[2],"mutant"))){
        fprintf(stderr,"Usage: %s MAX_LENGTH_0_TO_15 [mutant]\n",argv[0]);return 2;
    }
    errno=0;char*end=NULL;
    long limit=strtol(argv[1],&end,10);
    if(errno==ERANGE||end==argv[1]||*end||limit<0||limit>15){
        fprintf(stderr,"Length must be 0..15\n");return 2;
    }
    int mutant=argc==3,checked=0;
    for(int length=0;length<=limit;length++)
        for(int number=0;number<(1<<length);number++){
            unsigned a=1u,b=1u;
            char word[17];
            for(int pos=0;pos<length;pos++){
                int bit=(number>>(length-pos-1))&1;
                word[pos]=(char)('0'+bit);
                a=step_a(a,bit);
                b=step_b(b,bit,mutant);
            }
            word[length]='\0';checked++;
            if(!!(a&4u)!=!!(b&4u)){
                printf("MISMATCH=%s CHECKED=%d\n",*word?word:"<epsilon>",checked);
                return 0;
            }
        }
    printf("EQUIVALENT_UP_TO=%ld CHECKED=%d\n",limit,checked);
    return 0;
}
