/* 167: Compute DFA final states for right quotient by suffix 01. ISO C11. */
#include <stdio.h>
static const int delta[4][2]={{0,1},{2,1},{0,3},{3,3}};
static int run(int q,const char*s){
    for(;*s;s++){if(*s!='0'&&*s!='1')return -1;q=delta[q][*s-'0'];}
    return q;
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s PREFIX\n",argv[0]);return 2;}
    int newfinal[4]={0};
    for(int q=0;q<4;q++)newfinal[q]=(run(q,"01")==3);
    printf("RIGHT_QUOTIENT_FINAL_STATES=");
    for(int q=0;q<4;q++)if(newfinal[q])printf("q%d ",q);
    putchar('\n');
    int q=run(0,argv[1]);
    if(q<0){fprintf(stderr,"Only binary words supported\n");return 2;}
    puts(newfinal[q]?"ACCEPT":"REJECT");
    return 0;
}
