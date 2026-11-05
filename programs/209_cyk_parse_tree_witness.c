/* Program 209: Construct an explicit CYK parse tree for a fixed CNF grammar. ISO C11. */
#include <stdio.h>
#include <string.h>
#define MAXLEN 64
enum {S,A,B,C};
typedef struct {int left,right;char symbol;} Rule;
static const Rule rules[5]={{A,B,'S'},{B,C,'S'},{B,A,'A'},{C,C,'B'},{A,B,'C'}};
static unsigned char chart[MAXLEN][MAXLEN+1][4];
static signed char split_at[MAXLEN][MAXLEN+1][4];
static signed char rule_at[MAXLEN][MAXLEN+1][4];
static const char names[4]={'S','A','B','C'};
static const char*input;
static void print_tree(int start,int length,int nonterminal){
    printf("%c(",names[nonterminal]);
    if(length==1)putchar(input[start]);
    else{
        int rule=rule_at[start][length][nonterminal];
        int split=split_at[start][length][nonterminal];
        print_tree(start,split,rules[rule].left);
        putchar(',');
        print_tree(start+split,length-split,rules[rule].right);
    }
    putchar(')');
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s A_B_WORD\n",argv[0]);return 2;}
    input=argv[1];size_t n=strlen(input);
    if(n>MAXLEN){fprintf(stderr,"Maximum length 64\n");return 2;}
    for(size_t i=0;i<n;i++){
        if(input[i]=='a'){chart[i][1][A]=1;chart[i][1][C]=1;}
        else if(input[i]=='b')chart[i][1][B]=1;
        else{fprintf(stderr,"Alphabet is {a,b}\n");return 2;}
    }
    for(int length=2;length<=(int)n;length++)
        for(int start=0;start+length<=(int)n;start++)
            for(int split=1;split<length;split++)
                for(int k=0;k<5;k++){
                    int lhs=rules[k].symbol=='S'?S:rules[k].symbol=='A'?A:
                        rules[k].symbol=='B'?B:C;
                    if(chart[start][length][lhs])continue;
                    if(chart[start][split][rules[k].left]&&
                       chart[start+split][length-split][rules[k].right]){
                        chart[start][length][lhs]=1;
                        split_at[start][length][lhs]=(signed char)split;
                        rule_at[start][length][lhs]=(signed char)k;
                    }
                }
    if(n==0||!chart[0][n][S]){puts("REJECT");return 0;}
    printf("TREE=");print_tree(0,(int)n,S);putchar('\n');return 0;
}
