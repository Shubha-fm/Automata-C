/* Program 193: On-the-fly exact equivalence of an NFA and a DFA, with witness. ISO C11. */
#include <stdio.h>
static unsigned nfa_step(unsigned mask,int bit){
    unsigned out=0;
    if(mask&1u){out|=1u;if(bit==0)out|=2u;}
    if((mask&2u)&&bit==1)out|=4u;
    if(mask&4u)out|=4u;
    return out;
}
static const int dfa[3][2]={{1,0},{1,2},{2,2}};
int main(int argc,char**argv){
    if(argc>2||(argc==2&&
       !(argv[1][0]=='m'&&argv[1][1]=='u'&&argv[1][2]=='t'&&
       argv[1][3]=='a'&&argv[1][4]=='n'&&argv[1][5]=='t'&&
       argv[1][6]=='\0'))){
        fprintf(stderr,"Usage: %s [mutant]\n",argv[0]);return 2;
    }
    int mutant=(argc==2),queue[24]={3},seen[24]={0},parent[24],edge[24];
    for(int i=0;i<24;i++){parent[i]=-1;edge[i]=-1;}
    int head=0,tail=1,goal=-1;
    seen[3]=1;  /* mask 1, DFA state 0 */
    while(head<tail){
        int p=queue[head++],mask=p/3,state=p%3;
        int accept_nfa=!!(mask&4),accept_dfa=(state==2||(mutant&&state==1));
        if(accept_nfa!=accept_dfa){goal=p;break;}
        for(int b=0;b<2;b++){
            int next=3*(int)nfa_step((unsigned)mask,b)+dfa[state][b];
            if(!seen[next]){
                seen[next]=1;parent[next]=p;edge[next]=b;queue[tail++]=next;
            }
        }
    }
    if(goal<0){puts("EQUIVALENT");return 0;}
    char word[25];int len=0;
    for(int p=goal;parent[p]>=0;p=parent[p])word[len++]=(char)('0'+edge[p]);
    printf("COUNTEREXAMPLE=");
    if(!len)printf("<epsilon>");
    while(len)putchar(word[--len]);
    putchar('\n');
    return 0;
}
