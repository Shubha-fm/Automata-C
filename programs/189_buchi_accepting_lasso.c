/* Program 189: Find a reachable Büchi accepting cycle and show a lasso witness. C11. */
#include <stdio.h>
static const int delta[4][2]={{1,2},{1,3},{2,3},{3,3}};
static const int accepting[4]={0,1,0,0};
static void print_path(const int parent[],int end){
    int sequence[8],n=0;
    for(int q=end;q>=0;q=parent[q])sequence[n++]=q;
    while(n){printf("q%d",sequence[--n]);if(n)printf("->");}
}
int main(void){
    int reach[4]={1},queue[4]={0},parent[4]={-1,-1,-1,-1};
    int head=0,tail=1;
    while(head<tail){
        int q=queue[head++];
        for(int b=0;b<2;b++){
            int z=delta[q][b];
            if(!reach[z]){reach[z]=1;parent[z]=q;queue[tail++]=z;}
        }
    }
    for(int root=0;root<4;root++)if(reach[root]&&accepting[root]){
        int seen[4]={0},q[4]={0},pred[4]={-1,-1,-1,-1};
        int h=0,t=1,end=-1;seen[root]=1;q[0]=root;
        while(h<t&&end<0){
            int state=q[h++];
            for(int b=0;b<2;b++){
                int z=delta[state][b];
                if(z==root){end=state;break;}
                if(!seen[z]){seen[z]=1;pred[z]=state;q[t++]=z;}
            }
        }
        if(end>=0){
            printf("PREFIX=");print_path(parent,root);putchar('\n');
            int reverse[4],n=0;
            for(int z=end;z!=root;z=pred[z])reverse[n++]=z;
            printf("CYCLE=q%d",root);
            while(n)printf("->q%d",reverse[--n]);
            printf("->q%d\n",root);
            puts("BUCHI_NONEMPTY=YES");return 0;
        }
    }
    puts("BUCHI_NONEMPTY=NO");return 0;
}
