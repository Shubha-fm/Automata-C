/* Program 187: Dynamically construct a trie DFA for six compiler keywords. C11. */
#include <stdio.h>
#define MAXNODES 64
typedef struct{int next[26];int final;}Node;
static Node trie[MAXNODES];
static int count=1;
static void initialize(void){
    for(int i=0;i<MAXNODES;i++)
        for(int j=0;j<26;j++)trie[i].next[j]=-1;
}
static int insert(const char*word){
    int q=0;
    for(;*word;word++){
        int d=*word-'a';if(d<0||d>=26)return 0;
        if(trie[q].next[d]<0){
            if(count>=MAXNODES)return 0;
            trie[q].next[d]=count++;
        }
        q=trie[q].next[d];
    }
    trie[q].final=1;return 1;
}
static int accepts(const char*word){
    int q=0;
    for(;*word;word++){
        int d=*word-'a';
        if(d<0||d>=26||trie[q].next[d]<0)return 0;
        q=trie[q].next[d];
    }
    return trie[q].final;
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s KEYWORD\n",argv[0]);return 2;}
    initialize();
    const char *words[]={"if","for","while","return","int","else"};
    for(int i=0;i<6;i++)if(!insert(words[i]))return 1;
    puts(accepts(argv[1])?"ACCEPT":"REJECT");
    return 0;
}
