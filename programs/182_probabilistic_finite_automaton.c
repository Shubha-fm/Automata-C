/* Program 182: Probabilistic finite automaton with acceptance threshold 0.5. C11. */
#include <stdio.h>
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    double p1=0.0;
    for(const char *s=argv[1];*s;s++){
        if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary alphabet only\n");return 2;}
        if(*s=='1')p1=(1.0-p1)*0.8+p1*0.9;
        else p1=(1.0-p1)*0.1+p1*0.4;
    }
    printf("P_ACCEPT=%.6f DECISION=%s\n",p1,p1>=0.5?"ACCEPT":"REJECT");
    return 0;
}
