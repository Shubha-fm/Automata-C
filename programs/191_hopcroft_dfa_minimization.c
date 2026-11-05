/* Program 191: Hopcroft partition refinement of a six-state DFA. ISO C11. */
#include <stdio.h>
#define N 6
static int delta[N][2],final[N],block[N],pending[N];
int main(void){
    /* Two disjoint copies of the mod-3 DFA. Equivalent states merge. */
    for(int s=0;s<N;s++){
        int r=s%3,offset=s>=3?3:0;
        delta[s][0]=offset+(2*r)%3;
        delta[s][1]=offset+(2*r+1)%3;
        final[s]=(r==0);
        block[s]=final[s]?1:0;
    }
    int classes=2;pending[0]=pending[1]=1;
    for(;;){
        int splitter=-1;
        for(int c=0;c<classes;c++)if(pending[c]){splitter=c;break;}
        if(splitter<0)break;
        pending[splitter]=0;
        for(int symbol=0;symbol<2;symbol++){
            int pred[N];
            for(int s=0;s<N;s++)pred[s]=(block[delta[s][symbol]]==splitter);
            int old_classes=classes;
            for(int c=0;c<old_classes;c++){
                int yes=0,no=0;
                for(int s=0;s<N;s++)if(block[s]==c){
                    if(pred[s])yes++;else no++;
                }
                if(!yes||!no)continue;
                int fresh=classes++;
                for(int s=0;s<N;s++)
                    if(block[s]==c&&pred[s])block[s]=fresh;
                if(pending[c])pending[fresh]=1;
                else if(yes<=no)pending[fresh]=1;
                else pending[c]=1;
            }
        }
    }
    printf("MIN_STATES=%d\n",classes);
    for(int s=0;s<N;s++)printf("q%d=class%d\n",s,block[s]);
    return classes==3?0:1;
}
