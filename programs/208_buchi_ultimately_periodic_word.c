/* Program 208: Check Büchi acceptance of an ultimately periodic infinite word u(v)^omega. ISO C11. */
#include <stdio.h>
#include <string.h>
/* State 2 means 01 was observed at the current step, and is Büchi accepting. */
static const int delta[3][2]={{1,0},{1,2},{1,0}};
static int check_binary(const char*s){
    for(;*s;s++)if(*s!='0'&&*s!='1')return 0;
    return 1;
}
int main(int argc,char**argv){
    if(argc!=3){fprintf(stderr,"Usage: %s PREFIX NONEMPTY_LOOP\n",argv[0]);return 2;}
    const char*prefix=argv[1],*loop=argv[2];
    if(!*loop||!check_binary(prefix)||!check_binary(loop)){
        fprintf(stderr,"Binary prefix and nonempty binary loop required\n");return 2;
    }
    int state=0;
    for(const char*s=prefix;*s;s++)state=delta[state][*s-'0'];
    int first_seen[3]={-1,-1,-1},block_accepts[3]={0};
    int blocks=0;
    while(first_seen[state]<0){
        first_seen[state]=blocks;
        int visited=0;
        for(const char*s=loop;*s;s++){
            state=delta[state][*s-'0'];
            if(state==2)visited=1;
        }
        block_accepts[blocks++]=visited;
    }
    int accepted=0;
    for(int i=first_seen[state];i<blocks;i++)if(block_accepts[i])accepted=1;
    printf("BUCHI_ACCEPT=%s\n",accepted?"YES":"NO");
    return 0;
}
