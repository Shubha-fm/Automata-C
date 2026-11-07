/* Program 226: Stack-based LL(1) parser for S -> a S b | epsilon. C11. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s AB_WORD\n",argv[0]);return 2;}
    const char*s=argv[1];size_t n=strlen(s);
    if(n>1000){fprintf(stderr,"Maximum input length is 1000\n");return 2;}
    for(size_t i=0;i<n;i++)if(s[i]!='a'&&s[i]!='b'){
        fprintf(stderr,"Alphabet must be {a,b}\n");return 2;
    }
    char stack[3010];int top=0,expansions=0;
    stack[top++]='$';stack[top++]='S';
    size_t position=0;
    while(top>0){
        char current=stack[--top];
        char lookahead=position<n?s[position]:'$';
        if(current=='S'){
            expansions++;
            if(lookahead=='a'){
                stack[top++]='b';stack[top++]='S';stack[top++]='a';
            }else if(lookahead!='b'&&lookahead!='$'){
                puts("REJECT");return 0;
            }
        }else if(current==lookahead){
            if(current!='$')position++;
        }else{
            puts("REJECT");return 0;
        }
    }
    if(position!=n){puts("REJECT");return 0;}
    printf("ACCEPT EXPANSIONS=%d\n",expansions);return 0;
}

