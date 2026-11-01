/* 168: Reverse all transitions of a DFA to recognize its reverse language. ISO C11. */
#include <stdio.h>
static const int delta[3][2]={{1,0},{1,2},{1,0}};
static int accepts(const char*s){
    unsigned mask=1u<<2;
    for(;*s;s++){
        if(*s!='0'&&*s!='1')return 0;
        int bit=*s-'0';unsigned next=0;
        for(int src=0;src<3;src++)if(mask&(1u<<delta[src][bit]))
            next|=1u<<src;
        mask=next;
    }
    return (mask&1u)!=0;
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    puts(accepts(argv[1])?"ACCEPT":"REJECT");return 0;
}
