#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"c-vector/cvector.h"
#include"DebugPrintf/debug_printf.h"
#define MAX 1000
  igraph_t g;
  igraph_vector_t v,w;
  JRB tsp=NULL,tkh=NULL;
  FILE* inp;
  int m,n,ind;
  char s[MAX];
  int V[MAX][MAX];
int docfile(char* filename1, char* filename2){
    tsp=make_jrb();
    tkh=make_jrb();
    igraph_vector_init(&v,0);
    igraph_vector_init(&w,0);
    int a,a1;
inp=fopen(filename1,"r");
fscanf(inp,"%d",&m);
for(int i=0;i<m;++i){
    ind=0;
    memset(s,0,MAX);
    fscanf(inp,"%s%d",s,&ind);
    jrb_insert_int(tsp,ind,(Jval){.s=strdup(s)});
}
fclose(inp);
inp=fopen(filename2,"r");
fscanf(inp,"%d",&n);
for(int i=1;i<=n;++i){
memset(s,0,MAX);
ind=0;
fscanf(inp,"%s%d",s,&ind);
jrb_insert_int(tkh,ind,(Jval){.s=strdup(s)});
for(int j=1;j<=m;++j){
    fscanf(inp,"%d%d",&a,&a1);
    V[i][a]=a1;
}
}
int k;
fscanf(inp,"%d",&k);
for(int i=0;i<k;++i){
    a=a1=ind=0;
    fscanf(inp,"%d%d%d",&a,&a1,&ind);
    igraph_vector_push_back(&v,a);
    igraph_vector_push_back(&v,a1);
    igraph_vector_push_back(&w,ind);
}
fclose(inp);
igraph_create(&g,&v,0,0);
}
int insp(){
   for(JRB ptr = jrb_first(tsp); ptr != jrb_nil(tsp); ptr = jrb_next(ptr)){
    printf("%s %d\n", ptr->val.s,ptr->key);
   }
}
int kt(int a, int b){
    if(a>b){int k=a; a=b;b=k;}
if(jrb_find_int(tkh,a)==NULL|| jrb_find_int(tkh,b)==NULL) {printf("-1\n");return;}
else
{   int n1,n2;
    for(int i=0; i<igraph_vector_size(&v);i+=2){
        n1=(int)VECTOR(v)[i];
        n2=(int)VECTOR(v)[i+1];
        if(n1>n2){int k=n1; n1=n2;n2=k;}
        if(n1==a&&n2==b){
        printf("%d km\n",(int)VECTOR(w)[i/2]);
        return;
        }
    }
    printf("-1");
}
}
int kiemke(){
for(int i=1;i<=n;i++){
    printf("%s\n",jrb_find_int(tkh,i)->val.s);
    for(int j=1;j<=m;++j){
        printf(" %d\n",V[i][j]);
    }
}
}
int kiemke1(int k, int k1){
    int* vt=NULL;
    int n1,n2;
      for(int i=0; i<igraph_vector_size(&v);i+=2){
        n1=(int)VECTOR(v)[i];
        n2=(int)VECTOR(v)[i+1];
        if(n1==3) cvector_push_back(vt,n2);
        if(n2==3) cvector_push_back(vt,n1);
      }
       printf("%s\n",jrb_find_int(tkh,k)->val.s);
        printf("%s %d\n",jrb_find_int(tsp,k1)->val.s, V[k][k1]);
      printf("Cac kho ke la:\n");
    for(int i=0;i<cvector_size(vt);++i){
        printf("%s\n",jrb_find_int(tkh,vt[i])->val.s);
        printf("%s %d\n",jrb_find_int(tsp,k1)->val.s, V[vt[i]][k1]);
    }

}
int muahang(int k1, int k2, int k3, int k4){
if(V[k3][k1]>=k2){ printf("Dat hang thanh cong. Thoi gian dat hang la 30 phut\n");return;}
if(V[k3][k1]+V[k4][k1]>= k2){
    printf("Dat hang thanh cong\n");
    igraph_vector_t d,e;
    igraph_vector_init(&d,0);
    igraph_vector_init(&e,0);
    igraph_get_shortest_path_dijkstra(&g,&d,&e,k3,k4,&w,IGRAPH_ALL);
    int t=0;
    for(int i=0; i<igraph_vector_size(&e);++i){
        t+=(int)VECTOR(w)[(int)VECTOR(e)[i]];
    }
    printf("%d\n", t);
    printf("Thoi gian dat hang la: %g phut\n", (float)t/30*60+30);
    return;
}
printf("Dat hang khong thanh cong\n");
}
  int main(int argc, char *argv[]){
    printf("%d\n",atoi(argv[4]));
    docfile("/home/phuongdung/C/b/sanpham.txt","/home/phuongdung/C/b/khohang.txt");
    insp();
    kt(1,3);
    kiemke();
    kiemke1(3,1);
    muahang(1,10,3,2);
  }