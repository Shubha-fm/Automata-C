/* 162: Convert binary infix regex with implicit concatenation to postfix. ISO C11. */
#include <stdio.h>
#include <string.h>
static int precedence(char c){return c=='|'?1:c=='.'?2:0;}
static int push_operator(char op,char *stack,int *top,char *out,int *used){
    while(*top>0&&stack[*top-1]!='('&&
          precedence(stack[*top-1])>=precedence(op)){
        if(*used>=510)return 0;
        out[(*used)++]=stack[--*top];
    }
    stack[(*top)++]=op;
    return 1;
}
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s INFIX_REGEX\n",argv[0]);return 2;}
    const char*s=argv[1];char stack[512],out[512];
    int top=0,used=0,expect_atom=1;
    if(strlen(s)>240||!*s)goto bad;
    for(const char*p=s;*p;p++){
        char c=*p;
        if(c=='0'||c=='1'||c=='('){
            if(!expect_atom&&!push_operator('.',stack,&top,out,&used))goto bad;
            if(c=='('){stack[top++]='(';expect_atom=1;}
            else{out[used++]=c;expect_atom=0;}
        }else if(c==')'){
            if(expect_atom)goto bad;
            while(top>0&&stack[top-1]!='(')out[used++]=stack[--top];
            if(top==0)goto bad;
            top--;expect_atom=0;
        }else if(c=='*'){
            if(expect_atom)goto bad;
            out[used++]='*';
        }else if(c=='|'){
            if(expect_atom||!push_operator('|',stack,&top,out,&used))goto bad;
            expect_atom=1;
        }else goto bad;
    }
    if(expect_atom)goto bad;
    while(top){
        if(stack[top-1]=='(')goto bad;
        out[used++]=stack[--top];
    }
    out[used]=0;printf("POSTFIX=%s\n",out);return 0;
bad:
    fprintf(stderr,"Invalid infix regex\n");return 2;
}
