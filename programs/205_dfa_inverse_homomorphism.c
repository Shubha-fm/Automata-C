/* Program 205: Recognize the inverse image of ends-in-01 under a binary substitution. ISO C11. */
#include <stdio.h>
/* Homomorphism: a -> 01, b -> 10. Run the binary DFA without expansion. */
static const int delta[3][2]={{1,0},{1,2},{1,0}};
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s AB_WORD\n",argv[0]);return 2;}
    int state=0;
    for(const char*s=argv[1];*s;s++){
        if(*s!='a'&&*s!='b'){fprintf(stderr,"Alphabet must be {a,b}\n");return 2;}
        int first=(*s=='a')?0:1;
        state=delta[state][first];
        state=delta[state][1-first];
    }
    puts(state==2?"ACCEPT":"REJECT");
    return 0;
}
