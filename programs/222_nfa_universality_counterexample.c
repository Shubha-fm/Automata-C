/* Program 222: Exact NFA universality test via subset BFS with shortest rejected word. C11. */
#include <stdio.h>
#include <string.h>
static const unsigned transitions[3][2]={{1u,2u},{1u,4u},{4u,4u}};
static unsigned step(unsigned subset,int bit){
    unsigned result=0;
    for(int q=0;q<3;q++)if(subset&(1u<<q))result|=transitions[q][bit];
    return result;
}
int main(int argc,char**argv){
    if(argc>2||(argc==2&&strcmp(argv[1],"universal"))){
        fprintf(stderr,"Usage: %s [universal]\n",argv[0]);return 2;
    }
    unsigned final=(argc==2)?7u:3u;
    int seen[8]={0},queue[8]={1},parent[8],letter[8],h=0,t=1,goal=-1;
    for(int i=0;i<8;i++){parent[i]=-1;letter[i]=-1;}
    seen[1]=1;
    while(h<t){
        int subset=queue[h++];
        if(!((unsigned)subset&final)){goal=subset;break;}
        for(int bit=0;bit<2;bit++){
            int next=(int)step((unsigned)subset,bit);
            if(!seen[next]){
                seen[next]=1;parent[next]=subset;letter[next]=bit;queue[t++]=next;
            }
        }
    }
    if(goal<0){puts("UNIVERSAL");return 0;}
    char word[10];int len=0;
    for(int subset=goal;parent[subset]>=0;subset=parent[subset])
        word[len++]=(char)('0'+letter[subset]);
    printf("NOT_UNIVERSAL WITNESS=");
    if(!len)printf("<epsilon>");
    while(len)putchar(word[--len]);
    putchar('\n');
    return 0;
}

