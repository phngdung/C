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
void timduong(){
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
}


int main(int argc, char *argv[]){
  if(strcmp(argv[1],"-h")==0) {printf("C Advanced, HK20152\n"); return 0;}
  int choose, check=0;
for(;;){
  printf("\n1. Doc \n");
  printf("2. In ra.\n");
  printf("3. Dua ra danh sach.\n");
  printf("4. .\n");
  printf("5. Tim duong di ngan nhat.\n");
  printf("6. Thoat.\n");
  printf(" Nhap lua chon: ");
  scanf("%d",&choose);
  switch(choose) {
  case 1:
  docfile(argv[1]);
  check=1;
  break; 
  case 2:
  if(check!=1){ printf("Chua doc ban do. Moi chon 1\n"); break;}
  break;
  case 3:
  if(check!=1){ printf("Chua doc ban do. Moi chon 1\n"); break;}
  break;
  case 4:
  if(check!=1){ printf("Chua doc ban do. Moi chon 1\n"); break;}
  break;
  case 5:
  if(check!=1){ printf("Chua doc ban do. Moi chon 1\n"); break;}
  timduong();
  break;
  case 6:
   printf( "Ban da chon 6.Thoat \n");break;
  default: printf("So ban chon khong co trong menu. Moi chon lai: ");
  }
  if (choose==6) break;
  }


}
