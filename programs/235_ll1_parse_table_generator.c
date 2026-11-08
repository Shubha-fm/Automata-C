/* Program 235: Compute LL(1) predictive table from a fixed grammar using FIRST and FOLLOW. ISO C11. */
#include <stdio.h>
#include <string.h>
#define N 3
#define R 4
/* E -> TR, R -> +TR | epsilon, T -> i */
static const char names[N]={'E','R','T'};
static const int lhs[R]={0,1,1,2};
static const char*rhs[R]={"TR","+TR","","i"};
static unsigned first[N],follow[N];
static int nullable[N],table[N][3];
static int nonterminal(char c){
    for(int i=0;i<N;i++)if(names[i]==c)return i;
    return -1;
}
static int term_index(char c){
    return c=='i'?0:c=='+'?1:c=='$'?2:-1;
}
static unsigned sequence_first(const char*s,int*all_nullable){
    unsigned mask=0;*all_nullable=1;
    for(;*s;s++){
        int nt=nonterminal(*s);
        if(nt<0){int t=term_index(*s);if(t>=0)mask|=1u<<t;
            *all_nullable=0;break;}
        mask|=first[nt];
        if(!nullable[nt]){*all_nullable=0;break;}
    }
    return mask;
}
int main(void){
    int changed;
    do{
        changed=0;
        for(int r=0;r<R;r++){
            int empty=0;
            unsigned bits=sequence_first(rhs[r],&empty);
            unsigned next=first[lhs[r]]|bits;
            if(next!=first[lhs[r]]){first[lhs[r]]=next;changed=1;}
            if(empty&&!nullable[lhs[r]]){nullable[lhs[r]]=1;changed=1;}
        }
    }while(changed);
    follow[0]=1u<<2;
    do{
        changed=0;
        for(int r=0;r<R;r++){
            const char*s=rhs[r];
            for(int i=0;s[i];i++){
                int nt=nonterminal(s[i]);
                if(nt<0)continue;
                int empty=0;
                unsigned bits=sequence_first(s+i+1,&empty);
                if(empty)bits|=follow[lhs[r]];
                unsigned next=follow[nt]|bits;
                if(next!=follow[nt]){follow[nt]=next;changed=1;}
            }
        }
    }while(changed);
    for(int i=0;i<N;i++)for(int j=0;j<3;j++)table[i][j]=-1;
    int conflicts=0,entries=0;
    for(int r=0;r<R;r++){
        int empty=0;
        unsigned predicts=sequence_first(rhs[r],&empty);
        if(empty)predicts|=follow[lhs[r]];
        for(int t=0;t<3;t++)if(predicts&(1u<<t)){
            if(table[lhs[r]][t]>=0&&table[lhs[r]][t]!=r)conflicts++;
            else if(table[lhs[r]][t]<0){table[lhs[r]][t]=r;entries++;}
        }
    }
    const char terminals[]={'i','+','$'};
    for(int nt=0;nt<N;nt++)for(int t=0;t<3;t++){
        int r=table[nt][t];
        if(r>=0)printf("%c,%c=%s\n",names[nt],terminals[t],
                       *rhs[r]?rhs[r]:"epsilon");
    }
    printf("ENTRIES=%d CONFLICTS=%d\n",entries,conflicts);
    return conflicts?1:0;
}
