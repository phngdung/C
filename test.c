#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"c-vector/cvector.h"
// #include"DebugPrintf/debug_printf.h"
#define MAX 1000
  igraph_t g,p;
  igraph_vector_t v,w,b,e;
  FILE* inp;
  int n,m, id;
  JRB id_name,id_stt,stt_id;
  int max=0,min=0;
  int mt[MAX][MAX], A[MAX]; //mt[i][j]=1 tuc la dinh j tro toi i
void print_vector(igraph_vector_t *v) {
    long int i;
    for (i = 0; i < igraph_vector_size(v); i++) {
       printf("%ld\t",(long int) VECTOR(*v)[i]);
    }
}
int maxvector(igraph_vector_t a, int n)
{
     max = (int)VECTOR(a)[0];
     min = (int)VECTOR(a)[0];
    for (int i = 1; i < n; i++)
        {if (max < (int)VECTOR(a)[i])
            max = (int)VECTOR(a)[i];
        if (min > (int)VECTOR(a)[i]&& jrb_find_int(id_name,i)!=NULL)
            min = (int)VECTOR(a)[i];}
}
int docfile(char* filename1, char* filename2){
    char s[MAX],s1[MAX];
    id_name=make_jrb();
    id_stt=make_jrb();
    stt_id=make_jrb();
inp=fopen(filename1,"r");
fscanf(inp,"%d",&n);
for(int i=0;i<n;i++){
    fscanf(inp,"%s%d",s,&id);
    jrb_insert_int(id_name,id,(Jval){.s=strdup(s)});
    jrb_insert_int(id_stt,id,(Jval){.i=i});
    jrb_insert_int(stt_id,i,(Jval){.i=id});
}
fclose(inp);
printf("So luong webpage: %d\n",n);
// for(JRB ptr=jrb_first(id_name);ptr!=jrb_nil(id_name);ptr=jrb_next(ptr)){
//   printf("%s %d\n",ptr->val.s,ptr->key.i);
// }
for(JRB ptr=jrb_first(id_stt);ptr!=jrb_nil(id_stt);ptr=jrb_next(ptr)){
  printf("%d %d\n",ptr->val.i,ptr->key.i);
}
inp=fopen(filename2,"r");
fscanf(inp,"%d",&m);
   for(int i=0;i<=m;++i){
    fgets(s,MAX,inp);
    int k=0;
    sscanf(s,"%s",s1);
    id=atoi(s1);
    k+=strlen(s1)+1;
    while(k<strlen(s)){
        sscanf(s+k,"%s",s1);
        k+=strlen(s1)+1;
        igraph_vector_push_back(&v,id);
        igraph_vector_push_back(&v,atoi(s1));
        igraph_vector_push_back(&w,1);
        // int j=jrb_find_int(id_stt, atoi(s1))->val.i;
        printf("%d",jrb_find_int(id_stt, id)->val.i);
              // printf("%d %d",j,j1);
       //mt[1][id]=1;
    }
   }
fclose(inp);
igraph_create(&g,&v,0,1);
  igraph_vector_init(&e,0);
  igraph_degree(&g, &e, igraph_vss_all(), IGRAPH_IN, IGRAPH_NO_LOOPS);
   maxvector(e,(int)(igraph_vector_size(&e)));
   printf("\nWeb co nhieu lien ket toi nhat: ");
   for(int i=0;i<igraph_vector_size(&e);++i){
    if((int)VECTOR(e)[i]==max) printf(" %s ",jrb_find_int(id_name,i)->val.s);}
    printf("\nWeb co it lien ket toi nhat: ");
     for(int i=0;i<igraph_vector_size(&e);++i){
    if((int)VECTOR(e)[i]==min&& jrb_find_int(id_name,i)!=NULL) printf(" %s \n",jrb_find_int(id_name,i)->val.s);}
}
void find(int id1, int id2){
  igraph_vector_t d,e;
  igraph_vector_init(&d,0);
  igraph_vector_init(&e,0);
  igraph_get_shortest_path_dijkstra(&g,&d,&e,id1,id2,&w,IGRAPH_OUT);
  if(igraph_vector_size(&d)<=1) {printf("-1"); return;}
  int t=0;
  for(int i=0; i<igraph_vector_size(&e);++i){
    t+=1;
  }
  printf("Khoang cach nho nhat tu webpage co %d den webpage co %d la : %d\n", id1,id2, t);
}
int pr_set(){
  for( int i=0; i<n;++i) A[i]=1;
}

int pr_1(){
  int bac;
  int B[n-1];
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      if(mt[i][j]==1) {
        bac= (int)VECTOR(e)[i];
        B[i]+=(A[j]/(bac));
        }
    }
  }
  for(int i=0;i<n;++i){ printf("%d\t", B[i]);}
}





  int main(int argc, char *argv[]){
  FILE* inp;
  int choose,a=0,b=0, check=0;
  igraph_vector_init(&v,0);
  igraph_vector_init(&w,0);
for(;;){
  printf("\n1.Doc file\n");
  printf("2.PageRank sau lan lap dau.\n");
  printf("3.PageRank sau m lan lap.\n");
  printf("4.In ra so luong theo yeu cau.\n");
  printf("5.Tim khoang cach ngan nhat giua 2 webpage.\n");
  printf("6. Thoat.\n");
  printf(" Nhap lua chon: ");
  scanf("%d",&choose);
  switch(choose) {
      case 1: 
    docfile("/home/phuongdung/C/b/webpages.txt","/home/phuongdung/C/b/pageConnections.txt" );
    check=1;
      break;
      case 2:
      pr_set();
      pr_1();
      break;
  case 5:
  printf("Moi nhap vao id 2 webpage.\n ");
    scanf("%d",&a);
    if(a<0) {printf("-1\n"); break;}
    scanf("%d",&b);
    if(b<0) {printf("-1\n"); break;}
    if(jrb_find_int(id_name,a)==NULL||jrb_find_int(id_name,b)==NULL||a==b||check==0) 
      {printf("-1\n"); break;}
      else find(a,b);
      
    break;
    case 6: printf( "Ban da chon 6.Thoat \n");break;
     default: printf("So ban chon khong co trong menu. Moi chon lai: ");
     }
  if (choose==6) break;
}
  }

//   In ra so luong webpage va url kem id tuong ung
//    In ra web co nhieu lien ket toi nhat va it lien ket toi nhat
//     PageRank 1 lan lap
//      PageRank m lan lap