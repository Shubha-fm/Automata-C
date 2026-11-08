/* Program 237: Explore bounded pushdown configurations for the language a^n b^n. ISO C11. */
#include <stdio.h>
#include <string.h>
#define LIMIT 24
typedef struct{int position,phase,height;}Config;
static Config queue[(LIMIT+1)*2*(LIMIT+1)];
static int visited[LIMIT+1][2][LIMIT+1];
static void add(int pos,int phase,int height,int *tail){
    if(visited[pos][phase][height])return;
    visited[pos][phase][height]=1;
    queue[(*tail)++]=(Config){pos,phase,height};
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s AB_WORD\n",argv[0]);return 2;}
    const char*s=argv[1];size_t n=strlen(s);
    if(n>LIMIT){fprintf(stderr,"Maximum length is 24\n");return 2;}
    for(size_t i=0;i<n;i++)if(s[i]!='a'&&s[i]!='b'){
        fprintf(stderr,"Alphabet must be {a,b}\n");return 2;
    }
    int head=0,tail=0;
    add(0,0,0,&tail);
    while(head<tail){
        Config c=queue[head++];
        if(c.position==(int)n&&c.phase==1&&c.height==0){
            printf("ACCEPT EXPLORED=%d\n",head);return 0;
        }
        if(c.phase==0){
            /* A nondeterministic epsilon transition switches to reading b. */
            add(c.position,1,c.height,&tail);
            if(c.position<(int)n&&s[c.position]=='a'&&c.height<LIMIT)
                add(c.position+1,0,c.height+1,&tail);
        }else if(c.position<(int)n&&s[c.position]=='b'&&c.height>0){
            add(c.position+1,1,c.height-1,&tail);
        }
    }
    printf("REJECT EXPLORED=%d\n",head);return 0;
}
