/* Program 225: Iteratively compute FIRST, nullable, and FOLLOW sets for a fixed CFG. C11. */
#include <stdio.h>
#include <string.h>
enum{S,A,B,NT};
typedef struct{int lhs;const char*body;} Production;
static const Production rules[]={
    {S,"AB"},{A,"aA"},{A,""},{B,"bB"},{B,"c"}
};
static unsigned first[NT],follow[NT];
static int nullable[NT];
static int nt_index(char symbol){return symbol=='S'?S:symbol=='A'?A:B;}
static unsigned term(char symbol){return 1u<<(symbol-'a');}
static void print_set(unsigned mask,int has_epsilon){
    putchar('{');
    int first_item=1;
    for(int i=0;i<4;i++){
        if(mask&(1u<<i)){
            if(!first_item)putchar(',');
            putchar(i==3?'$':(char)('a'+i));first_item=0;
        }
    }
    if(has_epsilon){
        if(!first_item)putchar(',');
        printf("eps");
    }
    putchar('}');
}
int main(void){
    int changed;
    do{
        changed=0;
        for(size_t r=0;r<sizeof(rules)/sizeof(rules[0]);r++){
            int lhs=rules[r].lhs,all_nullable=1;
            unsigned initial=first[lhs];
            for(const char*p=rules[r].body;*p;p++){
                if(*p>='a'&&*p<='c'){
                    first[lhs]|=term(*p);all_nullable=0;break;
                }
                int q=nt_index(*p);
                first[lhs]|=first[q];
                if(!nullable[q]){all_nullable=0;break;}
            }
            if(initial!=first[lhs])changed=1;
            if(all_nullable&&!nullable[lhs]){nullable[lhs]=1;changed=1;}
        }
    }while(changed);
    follow[S]=1u<<3;/* end-of-input $ */
    do{
        changed=0;
        for(size_t r=0;r<sizeof(rules)/sizeof(rules[0]);r++){
            const char *body=rules[r].body;
            for(size_t i=0;body[i];i++){
                if(body[i]<'A'||body[i]>'Z')continue;
                int q=nt_index(body[i]),all_nullable=1;
                unsigned add=0;
                for(size_t j=i+1;body[j];j++){
                    if(body[j]>='a'&&body[j]<='c'){
                        add|=term(body[j]);all_nullable=0;break;
                    }
                    int v=nt_index(body[j]);
                    add|=first[v];
                    if(!nullable[v]){all_nullable=0;break;}
                }
                if(all_nullable)add|=follow[rules[r].lhs];
                unsigned next=follow[q]|add;
                if(next!=follow[q]){follow[q]=next;changed=1;}
            }
        }
    }while(changed);
    const char *names[]={"S","A","B"};
    for(int q=0;q<NT;q++){
        printf("%s FIRST=",names[q]);print_set(first[q],nullable[q]);
        printf(" FOLLOW=");print_set(follow[q],0);putchar('\n');
    }
    return 0;
}

