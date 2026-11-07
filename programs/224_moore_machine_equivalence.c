/* Program 224: Check two Moore machines and return a shortest output-mismatch witness. C11. */
#include <stdio.h>
#include <string.h>
static const int transition[2][2]={{0,1},{0,1}};
int main(int argc,char**argv){
    if(argc>2||(argc==2&&strcmp(argv[1],"mutant"))){
        fprintf(stderr,"Usage: %s [mutant]\n",argv[0]);return 2;
    }
    int mutation=argc==2;
    int queue[4]={0},seen[4]={1},parent[4],letter[4],head=0,tail=1,goal=-1;
    for(int i=0;i<4;i++){parent[i]=-1;letter[i]=-1;}
    while(head<tail){
        int p=queue[head++],a=p/2,b=p%2;
        int first_output=a,second_output=(mutation&&b==1)?0:b;
        if(first_output!=second_output){goal=p;break;}
        for(int symbol=0;symbol<2;symbol++){
            int next=2*transition[a][symbol]+transition[b][symbol];
            if(!seen[next]){
                seen[next]=1;parent[next]=p;letter[next]=symbol;queue[tail++]=next;
            }
        }
    }
    if(goal<0){puts("EQUIVALENT");return 0;}
    char word[5];int len=0;
    for(int q=goal;parent[q]>=0;q=parent[q])
        word[len++]=(char)('0'+letter[q]);
    printf("OUTPUT_MISMATCH_WITNESS=");
    if(!len)printf("<epsilon>");
    while(len)putchar(word[--len]);
    putchar('\n');return 0;
}

