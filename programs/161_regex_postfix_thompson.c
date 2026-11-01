/* 161: Compile postfix regex to a Thompson ε-NFA and simulate it. ISO C11. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define MAX 62
typedef struct {int start,end;} Fragment;
static unsigned char edges[MAX][MAX];
static int count=0;
static int state(void){return count<MAX?count++:-1;}
static void edge(int a,int b,unsigned char kind){edges[a][b]|=kind;}
static uint64_t closure(uint64_t mask){
    uint64_t old;
    do{
        old=mask;
        for(int i=0;i<count;i++)if(mask&(UINT64_C(1)<<i))
            for(int j=0;j<count;j++)if(edges[i][j]&1u)mask|=UINT64_C(1)<<j;
    }while(old!=mask);
    return mask;
}
static int compile(const char *expr,Fragment *out){
    Fragment stack[MAX];int top=0;
    if(!*expr)return 0;
    for(const char *p=expr;*p;p++){
        if(*p=='0'||*p=='1'){
            int a=state(),b=state();
            if(a<0||b<0)return 0;
            edge(a,b,*p=='0'?2u:4u);
            stack[top++]=(Fragment){a,b};
        }else if(*p=='.'||*p=='|'){
            if(top<2)return 0;
            Fragment right=stack[--top],left=stack[--top];
            if(*p=='.'){edge(left.end,right.start,1u);
                stack[top++]=(Fragment){left.start,right.end};
            }else{
                int a=state(),b=state();if(a<0||b<0)return 0;
                edge(a,left.start,1u);edge(a,right.start,1u);
                edge(left.end,b,1u);edge(right.end,b,1u);
                stack[top++]=(Fragment){a,b};
            }
        }else if(*p=='*'){
            if(top<1)return 0;
            Fragment x=stack[--top];
            int a=state(),b=state();if(a<0||b<0)return 0;
            edge(a,x.start,1u);edge(a,b,1u);
            edge(x.end,x.start,1u);edge(x.end,b,1u);
            stack[top++]=(Fragment){a,b};
        }else return 0;
    }
    if(top!=1)return 0;
    *out=stack[0];return 1;
}
int main(int argc,char **argv){
    if(argc!=3){fprintf(stderr,"Usage: %s POSTFIX_REGEX BINARY_WORD\n",argv[0]);return 2;}
    Fragment f;
    if(strlen(argv[1])>28||!compile(argv[1],&f)){
        fprintf(stderr,"Invalid or oversized postfix regex\n");return 2;
    }
    uint64_t mask=closure(UINT64_C(1)<<f.start);
    for(const char *p=argv[2];*p;p++){
        if(*p!='0'&&*p!='1'){fprintf(stderr,"Binary input only\n");return 2;}
        uint64_t next=0;
        unsigned char kind=*p=='0'?2u:4u;
        for(int i=0;i<count;i++)if(mask&(UINT64_C(1)<<i))
            for(int j=0;j<count;j++)if(edges[i][j]&kind)next|=UINT64_C(1)<<j;
        mask=closure(next);
    }
    puts((mask&(UINT64_C(1)<<f.end))?"ACCEPT":"REJECT");
    return 0;
}
