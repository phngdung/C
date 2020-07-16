#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"c-vector/cvector.h"
#include"DebugPrintf/debug_printf.h"
#define MAX 20000
FILE *inp;
  igraph_t g,p;
  igraph_vector_t v,w;
  JRB id_name;
  int n,m;// so ip, so lk
 void print_vector(igraph_vector_t *v) {
     int i;
    for (i = 0; i < igraph_vector_size(v); i++) {
        printf("%d\t ", (int) VECTOR(*v)[i]);
    }
    printf("\n");
    }
int docfile(char* filename){
 id_name=make_jrb();
      char s[MAX];
      int a,b,w1;
      igraph_vector_init(&v,0);
      igraph_vector_init(&w,0);
      inp=fopen(filename,"r");
      if(inp==NULL) printf("Loi mo file\n");
      fscanf(inp,"%d", &n);
      for(int i=0;i<n;++i){
          memset(s,0,MAX);
          fscanf(inp,"%d %s\n",&a,s);    
        jrb_insert_int(id_name,a,(Jval){.s=strdup(s)});
      }
        fscanf(inp,"%d", &m);
        for(int i=0;i<n;++i){
            fscanf(inp,"%d%d%d",&a,&b,&w1);
            igraph_vector_push_back(&v,a);
            igraph_vector_push_back(&v,b);
            igraph_vector_push_back(&w,w1);
        }
        igraph_create(&g,&v,0,0);


fclose(inp);
}
int fc_v(char* filename){
    docfile(filename);
    for(JRB ptr=jrb_first(id_name);ptr!=jrb_nil(id_name);ptr=jrb_next(ptr)){
    {
       printf("%d %s\n",ptr->key.i,ptr->val.s);
    }
}
}
int fc_w(char * filename,int a, int b){
docfile(filename);
for(int i=0; i<igraph_vector_size(&v);i+=2){
    if(((int)VECTOR(v)[i]==a&&(int)VECTOR(v)[i+1]==b)||(int)VECTOR(v)[i]==b&&(int)VECTOR(v)[i+1]==a)
    {   printf("%d\n",(int)VECTOR(w)[i/2]);
        return 0;   }
   }
   printf("-1\n");
}
int fc_p(char * filename,int a, int b){
docfile(filename);
    igraph_vector_t d,e;
    igraph_vector_init(&d,0);
    igraph_vector_init(&e,0);
     igraph_get_shortest_path_dijkstra(&g,&d,&e,a,b,&w,IGRAPH_ALL);
    int t=0;
    for (int i = 0; i < igraph_vector_size(&e); i++) 
                t+=(int)VECTOR(w)[(int)VECTOR(e)[i]];
    printf("%d\n",t);
   for(int i=0; i<igraph_vector_size(&d);++i){
    printf("%s\n",jrb_find_int(id_name, (int)VECTOR(d)[i])->val.s);
  }
}
int fc_n(char * filename,int a){
docfile(filename);
int dem=0;
for (int i = 0; i < igraph_vector_size(&v); i++) {
if((int)VECTOR(v)[i]==a) dem++;
}
printf("%d\n",dem);
for (int i = 0; i < igraph_vector_size(&v); i+=2) {
if((int)VECTOR(v)[i]==a) printf("%d %s\n", (int)VECTOR(v)[i+1],jrb_find_int(id_name, (int)VECTOR(v)[i+1])->val.s);
else if((int)VECTOR(v)[i+1]==a) printf("%d %s\n", (int)VECTOR(v)[i],jrb_find_int(id_name, (int)VECTOR(v)[i])->val.s);
}

}
int fc_s(char* argv[] ) {
    igraph_vector_t v1;
    igraph_vector_t ws;
    igraph_vector_init(&v1,0);
    igraph_vector_init(&ws,0);
    int a=0, check1=0,check2=0;
docfile(argv[2]);
if(argv[3]==NULL) return 0;
for(int i=0; i<igraph_vector_size(&v);i+=2){
    check1=check2=0;
    for(int j=3; argv[j]!=NULL;++j){
     a=atoi(argv[j]);
    if((int)VECTOR(v)[i]==a){check1=1;
    printf("%d\n",a);
     break;}
    }
      for(int j=3; argv[j]!=NULL;++j){
     a=atoi(argv[j]);
    if((int)VECTOR(v)[i+1]==a) {check2=1;printf("%d\n",a); break;}
    }
    if(check1==1&&check2==1){
    igraph_vector_push_back(&v1,(int)VECTOR(v)[i]);
       igraph_vector_push_back(&v1,(int)VECTOR(v)[i+1]);
    igraph_vector_push_back(&ws,(int)VECTOR(w)[i/2]);
    }

}
int dem=0;
for(int j=3; argv[j]!=NULL;++j){ dem++;}
    printf("%d\n",dem);
for(int j=3; argv[j]!=NULL;++j){
    int a=atoi(argv[j]);
  //  printf("%d %s\n",a,jrb_find_int(id_name,a)->val.s);
}
 printf("%d\n",igraph_vector_size(&ws));
for(int i=0; i<igraph_vector_size(&ws);++i){
   // printf("%d %d %d\n",(int)VECTOR(v1)[2*i],(int)VECTOR(v1)[2*i+1],(int)VECTOR(w)[i]);
    }
}




int main(int argc, char *argv[]){
    if(strcmp(argv[1],"-h")==0) printf("C Advanced, HK20152\n");
    if(strcmp(argv[1],"-v")==0) fc_v(argv[2]);   
    if(strcmp(argv[1],"-w")==0) fc_w(argv[2],atoi(argv[3]),atoi(argv[4]));     
    if(strcmp(argv[1],"-p")==0) fc_p(argv[2],atoi(argv[3]),atoi(argv[4]));     
    if(strcmp(argv[1],"-n")==0) fc_n(argv[2],atoi(argv[3]));
    if(strcmp(argv[1],"-s")==0) fc_s(argv);     
  }