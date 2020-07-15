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
  JRB id_name=NULL,name_id=NULL;
  FILE* inp;
  int m,n;
  int docfile(char* filename){
     id_name=make_jrb();
     name_id=make_jrb();
      char s[MAX];
      int id,id1;
      igraph_vector_init(&v,0);
      igraph_vector_init(&w,0);
      inp=fopen(filename,"r");
      if(inp==NULL) printf("Loi mo file\n");
      fscanf(inp,"%d%d", &n,&m);
      for(int i=0;i<n;++i){
          memset(s,0,MAX);
          fscanf(inp,"%s %d\n",s,&id);    
        jrb_insert_int(id_name,id,(Jval){.s=strdup(s)});
        jrb_insert_str(name_id,strdup(s),(Jval){.i=id});
      }
        for(int i=0;i<m;++i){
            fscanf(inp,"%d %d",&id,&id1);
            igraph_vector_push_back(&v,id);
            igraph_vector_push_back(&v,id1);
            igraph_vector_push_back(&w,1);
        }
        fclose(inp);
     igraph_create(&g,&v,0,1);
  }
int i2n(char* filename, int id){
    docfile(filename);
    printf("%s\n",jrb_find_int(id_name,id)->val.s);
}
int n2i(char* filename, char* name){
    docfile(filename);
   if(jrb_find_str(name_id,name)!=NULL) printf("%d\n",jrb_find_str(name_id,name)->val.i);    
   else printf("Khong co an pham %s\n", name);
}
int cc(char* filename, int x, int y){
    int a=0;
    docfile(filename);
for(int i=0;i<igraph_vector_size(&v);i+=2){
   if((int)VECTOR(v)[i]==x) {a=(int)VECTOR(v)[i+1]; 
    for(int j=0;j<igraph_vector_size(&v);j+=2){
    if((int)VECTOR(v)[j+1]==a&&(int)VECTOR(v)[j]==y) printf("%s\n",jrb_find_int(id_name,a)->val.s);
            }
        }
        }
}
int cr(char* filename, int x, int y){
    int a=0;
    docfile(filename);
for(int i=0;i<igraph_vector_size(&v);i+=2){
   if((int)VECTOR(v)[i+1]==x) {
    a=(int)VECTOR(v)[i]; 
    for(int j=0;j<igraph_vector_size(&v);j+=2){
    if((int)VECTOR(v)[j]==a&&(int)VECTOR(v)[j+1]==y) printf("%s\n",jrb_find_int(id_name,a)->val.s);
            }
        }
        }
}

void bbr(char* filename, int a){
 docfile(filename);
int bac=0;
for(JRB ptr=jrb_first(id_name);ptr!=jrb_nil(id_name);ptr=jrb_next(ptr)){
    bac=0;
for(int i=0;i<igraph_vector_size(&v);i+=2){
    if((int)VECTOR(v)[i] == ptr->key.i) bac++;
    if(bac>a) {printf("%s\n",ptr->val.s); break;}
     }
    }  
}
int odg(char* filename, int a){ // tinh ban bac ra
docfile(filename); 
 igraph_vector_t e;
  igraph_vector_init(&e,0);
igraph_degree(&g, &e, igraph_vss_all(), IGRAPH_OUT, IGRAPH_LOOPS);
    for(int i=0; i<igraph_vector_size(&e);++i){
     if(VECTOR(e)[i]>a) printf("%s\n",jrb_find_int(id_name,i)->val.s);
   }
   //bbr(filename,a);

}
int rel(char* filename, int a){
    igraph_vector_t d,e;
    igraph_vector_init(&d,0);
    igraph_vector_init(&e,0);       
docfile(filename);
for(JRB ptr=jrb_first(id_name);ptr!=jrb_nil(id_name);ptr=jrb_next(ptr)){
        igraph_get_shortest_path_dijkstra(&g,&d,&e,a,ptr->key.i,&w,IGRAPH_OUT);
        int t=0;
        for (int i = 0; i < igraph_vector_size(&e); i++) 
                t+=(int)VECTOR(w)[(int)VECTOR(e)[i]];
        if(t<3&&t>0) printf("%s\n",ptr->val.s);
    }
}
  int main(int argc, char *argv[]){
    if(strcmp(argv[1],"help")==0) printf("Supported command: help,i2n,n2i,cc,cr,odg,rel\n");
   if(strcmp(argv[1],"about")==0) printf("C advanced 20142 final exam\n");    
   if(strcmp(argv[1],"i2n")==0) i2n(argv[2],atoi(argv[3]));
   if(strcmp(argv[1],"n2i")==0) n2i(argv[2],argv[3]);
    if(strcmp(argv[1],"cc")==0) cc(argv[2],atoi(argv[3]),atoi(argv[4]));
    if(strcmp(argv[1],"cr")==0) cr(argv[2],atoi(argv[3]),atoi(argv[4]));
    if(strcmp(argv[1],"odg")==0) odg(argv[2],atoi(argv[3]));
    if(strcmp(argv[1],"rel")==0) rel(argv[2],atoi(argv[3]));
  }