/* Program 199: CYK membership for a nontrivial fixed Chomsky-normal-form grammar. ISO C11. */
#include <stdio.h>
#include <string.h>
/* S -> AB | BC; A -> BA | a; B -> CC | b; C -> AB | a
   Bit flags: S=1,A=2,B=4,C=8. */
static unsigned combine(unsigned left,unsigned right){
    unsigned mask=0;
    if((left&2u)&&(right&4u))mask|=1u|8u;
    if((left&4u)&&(right&8u))mask|=1u;
    if((left&4u)&&(right&2u))mask|=2u;
    if((left&8u)&&(right&8u))mask|=4u;
    return mask;
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s A_B_WORD\n",argv[0]);return 2;}
    const char*s=argv[1];size_t n=strlen(s);
    if(n==0){puts("REJECT");return 0;}
    if(n>64){fprintf(stderr,"Maximum 64 symbols\n");return 2;}
    static unsigned chart[64][65]; /* chart[start][length] */
    for(size_t i=0;i<n;i++){
        if(s[i]=='a')chart[i][1]=2u|8u;
        else if(s[i]=='b')chart[i][1]=4u;
        else{fprintf(stderr,"Alphabet is {a,b}\n");return 2;}
    }
    for(size_t len=2;len<=n;len++)
        for(size_t start=0;start+len<=n;start++)
            for(size_t split=1;split<len;split++)
                chart[start][len]|=combine(chart[start][split],
                                           chart[start+split][len-split]);
    puts((chart[0][n]&1u)?"ACCEPT":"REJECT");
    return 0;
}
