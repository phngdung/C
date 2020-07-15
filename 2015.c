#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <jrb.h>
#include <igraph.h>
#include <cvector.h>
  igraph_t g;
  igraph_vector_t v,weight;
  JRB id_ip, ip_id;
void case3(int a, int b){
  int eid;
  igraph_get_eid(&g,&eid,a,b,0,NULL);
  if(eid==-1) printf("-1"); else printf("%d\n",(int)VECTOR( weight)[eid]);
}
void case4( int a, int b){
  igraph_vector_t v,e;
     igraph_vector_init(&v,0); //vector cac dinh di qua
        igraph_vector_init(&e,0);// vector cac canh di qua
  igraph_get_shortest_path_dijkstra(&g,&v,&e,a,b,&weight,IGRAPH_ALL);
  int t=0;
  for(int i=0;i<igraph_vector_size(&e);++i){
    t+= (int)VECTOR( weight)[(int)VECTOR(e)[i]];
  }
  printf("%d\n",t);
  for(int i=0; i<igraph_vector_size(&v);++i){
    printf("%s\n",jrb_find_int(id_ip,(int)VECTOR(v)[i])->val.s);
  }

}
void case5(int a){
  int dem=0;
  for(int i=0;i<igraph_vector_size(&v);i++)
  if((int)VECTOR(v)[i]==a){
    dem++;
  }
  printf("%d\n",dem);
   for(int i=0;i<igraph_vector_size(&v);i++){
    if((int)VECTOR(v)[i]==a){
    if(i%2==0){
      printf("%d %s %d\n",(int)VECTOR(v)[i+1], jrb_find_int(id_ip,(int)VECTOR(v)[i+1])->val.s,(int)VECTOR(weight)[(int)(i/2)]) ;
    }
    else
    {
    printf("%d %s %d\n",(int)VECTOR(v)[i-1], jrb_find_int(id_ip,(int)VECTOR(v)[i-1])->val.s,(int)VECTOR(weight)[(int)(i/2)]) ;
    }
    
    }
   }
}
void case6(int* b, int size){
  int eid;
  int * v=NULL;
for(int i=0;i<size;i++){
  for(int j=i+1;j<size;j++){
    if(igraph_get_eid(&g,&eid,b[i],b[j],0,IGRAPH_ALL)!=-1) {cvector_push_back(v,b[i]);cvector_push_back(v,b[j]);cvector_push_back(v,(int)VECTOR( weight)[eid]);}
  }
}

printf("%d\n",cvector_size(v)/3);
for(int i=0;i<cvector_size(v);i=i+3){
  printf("%d %d %d\n", v[i],v[i+1],v[i+2]);
}
}

int main(int argc, char *argv[]){
    FILE* inp;
    int n,m,w,id,id1,id2,i;
    char ip[100];
    id_ip=make_jrb();
    ip_id=make_jrb();
  
    igraph_vector_init(&v,0);
    igraph_vector_init(&weight,0);
    inp=fopen("/home/phuongdung/nhap/damdung/bt/demo.txt","r");
    fscanf(inp,"%d",&n);
    for ( i = 0; i < n; i++)
    {
        fscanf(inp,"%d %s",&id, ip);
        jrb_insert_int(id_ip,id, (Jval){.s=strdup(ip)});
        jrb_insert_str(ip_id,ip,(Jval){.d=id});
    }
     fscanf(inp,"%d",&m);
    for ( i = 0; i < m; i++){
        fscanf(inp,"%d %d %d",&id1,&id2,&w);
      igraph_vector_push_back(&v,id1);
      igraph_vector_push_back(&v,id2);
      igraph_vector_push_back(&weight,w);
    }
    igraph_create(&g,&v,0,0);
//case3(1,3);
//case4(2,3);
case5(1);
int b[argc-3];
for(int i=0;i<argc-3;i++){
  b[i]=(int)atof(argv[i+3]);
}
//case6(b, argc-3);
}
