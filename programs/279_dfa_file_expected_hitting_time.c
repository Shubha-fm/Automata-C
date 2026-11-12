/* Program 279: Compute expected steps to first accepting state for fair random inputs. ISO C11. */
#include "../include/dfa_io.h"
#define EPS 1e-11
static double magnitude(double x){return x<0?-x:x;}
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int reach[DFA_MAX]={0},productive[DFA_MAX]={0},queue[DFA_MAX],h=0,t=1;
 queue[0]=d.start;reach[d.start]=1;
 while(h<t){
  int q=queue[h++];for(int b=0;b<2;b++){
   int z=d.go[q][b];if(!reach[z]){reach[z]=1;queue[t++]=z;}
  }
 }
 for(int q=0;q<d.n;q++)productive[q]=d.final[q];
 int changed;
 do{changed=0;for(int q=0;q<d.n;q++)for(int b=0;b<2;b++){
  if(productive[d.go[q][b]]&&!productive[q]){productive[q]=1;changed=1;}
 }}while(changed);
 for(int q=0;q<d.n;q++)if(reach[q]&&!productive[q]){
  puts("EXPECTED_STEPS=INFINITE");return 0;
 }
 double a[DFA_MAX][DFA_MAX+1]={{0}};
 for(int q=0;q<d.n;q++){
  a[q][q]=1;
  if(reach[q]&&!d.final[q]){
   a[q][d.go[q][0]]-=0.5;a[q][d.go[q][1]]-=0.5;
   a[q][d.n]=1;
  }
 }
 for(int c=0;c<d.n;c++){
  int pivot=c;
  for(int r=c+1;r<d.n;r++)
   if(magnitude(a[r][c])>magnitude(a[pivot][c]))pivot=r;
  if(magnitude(a[pivot][c])<EPS){
   puts("EXPECTED_STEPS=INFINITE");return 0;
  }
  if(pivot!=c)for(int k=c;k<=d.n;k++){
   double v=a[c][k];a[c][k]=a[pivot][k];a[pivot][k]=v;
  }
  double divisor=a[c][c];
  for(int k=c;k<=d.n;k++)a[c][k]/=divisor;
  for(int r=0;r<d.n;r++)if(r!=c){
   double factor=a[r][c];
   for(int k=c;k<=d.n;k++)a[r][k]-=factor*a[c][k];
  }
 }
 printf("EXPECTED_STEPS=%.6f\n",a[d.start][d.n]);return 0;
}
