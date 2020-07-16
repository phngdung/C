#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"c-vector/cvector.h"
//#include"DebugPrintf/debug_printf.h"
#define MAX 20000
FILE* inp;
  igraph_t g,p;
  igraph_vector_t v,w,q,w1;
  int n,m;
  JRB id_name;
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
}
void fc_v(char* filename){
    docfile(filename);
  int x,y;
  printf(" Nhap vao diem xuat phat: ");
  scanf("%d",&x);
  printf(" Nhap vao diem dich: ");
  scanf("%d",&y);
  igraph_vector_t d,e;
   igraph_vector_init(&d,0); //vector cac dinh di qua
   igraph_vector_init(&e,0);// vector cac canh di qua
  igraph_get_shortest_path_dijkstra(&g,&d,&e,x,y,&w,IGRAPH_ALL);
  int t=0;
  for(int i=0;i<igraph_vector_size(&e);++i){
    t+= (int)VECTOR( w)[(int)VECTOR(e)[i]];
  }
  if(t==0) {printf("Khong co duong di\n");return;}
  printf(" Do dai duong di la : %d\n",t);
  printf(" Thu tu di qua : ");
  for(int i=0; i<igraph_vector_size(&d);++i){
    printf("%d ", (int)VECTOR(d)[i]);
  }
  printf("\n");
}


int main(int argc, char *argv[]){
    if(strcmp(argv[1],"-h")==0) printf("C Advanced, HK20152\n");
    if(strcmp(argv[1],"-v")==0) fc_v(argv[2]);   
    // if(strcmp(argv[1],"-w")==0) fc_w(argv[2],atoi(argv[3]),atoi(argv[4]));     
    // if(strcmp(argv[1],"-p")==0) fc_p(argv[2],atoi(argv[3]),atoi(argv[4]));     
    // if(strcmp(argv[1],"-n")==0) fc_n(argv[2],atoi(argv[3]));
    // if(strcmp(argv[1],"-s")==0) fc_s(argv);     
  }