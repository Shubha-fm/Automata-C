/* Program 196: Find the shortest word with multiple accepting NFA runs. ISO C11. */
#include <stdio.h>
/* 0 has two transitions on 0 to distinct accepting states 1 and 2. */
static int count_paths(const char *s){
    int q[3]={1,0,0};
    for(;*s;s++){
        int next[3]={0,0,0};
        if(*s=='0'){next[1]=q[0];next[2]=q[0];}
        for(int i=0;i<3;i++)q[i]=next[i];
    }
    return q[1]+q[2];
}
int main(void){
    for(int length=0;length<=6;length++){
        for(int bits=0;bits<(1<<length);bits++){
            char s[8];
            for(int i=0;i<length;i++)
                s[i]=(char)('0'+((bits>>(length-i-1))&1));
            s[length]='\0';
            int paths=count_paths(s);
            if(paths>1){
                printf("AMBIGUOUS_WORD=%s PATHS=%d\n",s,paths);
                return 0;
            }
        }
    }
    puts("NO_AMBIGUITY_UP_TO_LENGTH_6");return 0;
}
