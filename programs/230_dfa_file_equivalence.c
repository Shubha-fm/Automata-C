/* Program 230: File-based DFA equivalence checking with shortest counterexample. C11. */
#include <stdio.h>
#define MAXN 32
#define PAIRS (MAXN*MAXN)
typedef struct {
    int n,start,accept[MAXN],delta[MAXN][2];
} DFA;
static int load(const char*path,DFA*dfa){
    FILE*f=fopen(path,"r");
    if(!f){perror("DFA file");return 0;}
    int ok=fscanf(f,"%d%d",&dfa->n,&dfa->start)==2;
    if(!ok||dfa->n<1||dfa->n>MAXN||
        dfa->start<0||dfa->start>=dfa->n){fclose(f);return 0;}
    for(int i=0;i<dfa->n;i++){
        if(fscanf(f,"%d",&dfa->accept[i])!=1||
            (dfa->accept[i]!=0&&dfa->accept[i]!=1)){fclose(f);return 0;}
    }
    for(int i=0;i<dfa->n;i++)for(int bit=0;bit<2;bit++)
        if(fscanf(f,"%d",&dfa->delta[i][bit])!=1||
           dfa->delta[i][bit]<0||dfa->delta[i][bit]>=dfa->n){
            fclose(f);return 0;
        }
    char extra;
    if(fscanf(f," %c",&extra)==1){fclose(f);return 0;}
    fclose(f);return 1;
}
int main(int argc,char**argv){
    if(argc!=3){fprintf(stderr,"Usage: %s FIRST_DFA SECOND_DFA\n",argv[0]);return 2;}
    DFA a,b;
    if(!load(argv[1],&a)||!load(argv[2],&b)){
        fprintf(stderr,"Invalid DFA input files\n");return 2;
    }
    int total=a.n*b.n;
    int seen[PAIRS]={0},parent[PAIRS],letter[PAIRS],queue[PAIRS];
    for(int i=0;i<total;i++){parent[i]=-1;letter[i]=-1;}
    int start=a.start*b.n+b.start,h=0,t=1,goal=-1;
    seen[start]=1;queue[0]=start;
    while(h<t){
        int p=queue[h++],qa=p/b.n,qb=p%b.n;
        if(a.accept[qa]!=b.accept[qb]){goal=p;break;}
        for(int bit=0;bit<2;bit++){
            int next=a.delta[qa][bit]*b.n+b.delta[qb][bit];
            if(!seen[next]){
                seen[next]=1;parent[next]=p;letter[next]=bit;
                queue[t++]=next;
            }
        }
    }
    if(goal<0){puts("EQUIVALENT");return 0;}
    char word[PAIRS+1];int n=0;
    for(int p=goal;parent[p]>=0;p=parent[p])
        word[n++]=(char)('0'+letter[p]);
    printf("NOT_EQUIVALENT WITNESS=");
    if(!n)printf("<epsilon>");
    while(n)putchar(word[--n]);
    putchar('\n');return 0;
}

