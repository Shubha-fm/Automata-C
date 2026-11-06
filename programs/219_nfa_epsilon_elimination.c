/* Program 219: Eliminate epsilon transitions and exhaustively cross-check the result. ISO C11. */
#include <stdio.h>
#define N 4
static const unsigned eps[N]={1u<<1,0,1u<<3,0};
static unsigned edges[N][2];
static unsigned eliminated[N][2];
static int accepted[N]={0,0,0,1};
static unsigned closure(unsigned mask){
    unsigned old;
    do{
        old=mask;
        for(int i=0;i<N;i++)if(mask&(1u<<i))mask|=eps[i];
    }while(old!=mask);
    return mask;
}
static unsigned step(unsigned mask,int bit,unsigned table[N][2]){
    unsigned out=0;
    for(int q=0;q<N;q++)if(mask&(1u<<q))out|=table[q][bit];
    return out;
}
static int original(const char*s){
    unsigned mask=closure(1u);
    for(;*s;s++)mask=closure(step(mask,*s-'0',edges));
    return !!(mask&(1u<<3));
}
static int reduced(const char*s,unsigned finalmask){
    unsigned mask=1u;
    for(;*s;s++)mask=step(mask,*s-'0',eliminated);
    return !!(mask&finalmask);
}
int main(void){
    edges[1][0]=1u<<1;edges[1][1]=1u<<2;
    edges[3][0]=edges[3][1]=1u<<3;
    unsigned finalmask=0;
    for(int q=0;q<N;q++){
        unsigned c=closure(1u<<q);
        for(int state=0;state<N;state++)
            if((c&(1u<<state))&&accepted[state])finalmask|=1u<<q;
        for(int bit=0;bit<2;bit++){
            unsigned t=0;
            for(int state=0;state<N;state++)if(c&(1u<<state))
                t|=edges[state][bit];
            eliminated[q][bit]=closure(t);
        }
    }
    int checked=0,mismatches=0;
    for(int length=0;length<=10;length++)for(int x=0;x<(1<<length);x++){
        char word[12];for(int i=0;i<length;i++)
            word[i]=(char)('0'+((x>>(length-i-1))&1));
        word[length]='\0';
        if(original(word)!=reduced(word,finalmask))mismatches++;
        checked++;
    }
    printf("FINAL_MASK=%u CHECKED=%d MISMATCHES=%d\n",
           finalmask,checked,mismatches);
    return mismatches?1:0;
}
