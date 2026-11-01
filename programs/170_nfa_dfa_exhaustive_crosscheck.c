/* 170: Exhaustively compare NFA and DFA recognition through length eight. ISO C11. */
#include <stdio.h>
static int nfa(const char*s){
    unsigned mask=1u;
    for(;*s;s++){
        unsigned next=0;
        if(mask&1u){next|=1u;if(*s=='0')next|=2u;}
        if((mask&2u)&&*s=='1')next|=4u;
        if(mask&4u)next|=4u;
        mask=next;
    }
    return (mask&4u)!=0;
}
static int dfa(const char*s){
    static const int trans[3][2]={{1,0},{1,2},{2,2}};
    int q=0;for(;*s;s++)q=trans[q][*s-'0'];
    return q==2;
}
int main(void){
    int checked=0,mismatch=0;
    for(int length=0;length<=8;length++){
        for(int bits=0;bits<(1<<length);bits++){
            char word[10];int i;
            for(i=0;i<length;i++)word[i]=(char)('0'+((bits>>(length-i-1))&1));
            word[length]=0;
            if(nfa(word)!=dfa(word)){printf("MISMATCH=%s\n",word);mismatch++;}
            checked++;
        }
    }
    printf("CHECKED=%d MISMATCHES=%d\n",checked,mismatch);
    return mismatch?1:0;
}
