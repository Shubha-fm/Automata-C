/* 166: Evaluate a left quotient of the ends-in-01 language. ISO C11. */
#include <stdio.h>
static const int delta[3][2]={{1,0},{1,2},{1,0}};
static int run(int q,const char*s){
    for(;*s;s++){if(*s!='0'&&*s!='1')return -1;q=delta[q][*s-'0'];}
    return q;
}
int main(int argc,char**argv){
    if(argc!=3){fprintf(stderr,"Usage: %s PREFIX SUFFIX\n",argv[0]);return 2;}
    int state=run(0,argv[1]);if(state>=0)state=run(state,argv[2]);
    if(state<0){fprintf(stderr,"Only binary words supported\n");return 2;}
    printf("LEFT_QUOTIENT_START=q%d\n",run(0,argv[1]));
    puts(state==2?"ACCEPT":"REJECT");
    return 0;
}
