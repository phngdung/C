#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "libfdr/jrb.h"
#include "c-vector/cvector.h"
#include "igraph/igraph.h"

JRB tree1=NULL,tree2=NULL;
igraph_vector_t v,ve,eg;
igraph_vector_t weight;
igraph_t g;
int n,m;
int *V[100001];
int *V1[100001];
float rank[100001];
float rankupdate[100001];
char *url[100001];
int mk[100001];
void readfile(char *filename ,char *filename1){
    memset(V,0,100001*4);
    memset(V1,0,100001*4);
    for(int i=0;i<100001;++i)rank[i]=1;
    
    igraph_vector_init(&v,0);
    igraph_vector_init(&ve,0);
    igraph_vector_init(&eg,0);
    igraph_vector_init(&weight,0);


   FILE *fp;
   fp=fopen(filename,"rt");
   if(fp==NULL)printf("sai\n");
   tree1=make_jrb();
   tree2=make_jrb();
   
   char s[10000],s1[1000];
   int idex;
   fscanf(fp,"%d",&n);
   for(int i=1;i<=n;++i){
   	idex=0;
   	memset(s,0,10000);
   	fscanf(fp,"%s %d",s,&idex);
    url[i]=strdup(s);
    mk[i]=idex;
    jrb_insert_int(tree1,i,(Jval){.i=idex});
    jrb_insert_int(tree2,idex,(Jval){.i=i});
    printf("%d %d\n",i,idex);
   }
   fclose(fp);
   
   fp=fopen(filename1,"rt");
   if(fp==NULL)printf("sai\n");

   fscanf(fp,"%d",&m);
   fgets(s,10,fp);
   for(int i=0;i<m;++i){
    memset(s,0,10000);
    memset(s1,0,1000);
    fgets(s,10000,fp);
    int k=0;
    sscanf(s,"%s",s1);
    k+=strlen(s1)+1;
    int node=jrb_find_int(tree2,atoi(s1))->val.i;
    while(k<strlen(s)){
    	memset(s1,0,1000);
        sscanf(s+k,"%s",s1);
        int node1=jrb_find_int(tree2,atoi(s1))->val.i;
        k+=strlen(s1)+1;
        cvector_push_back(V[node],node1);
        cvector_push_back(V1[node1],node);
        igraph_vector_push_back(&v,node);
        igraph_vector_push_back(&v,node1);
        igraph_vector_push_back(&weight,1);
    }
   }
   igraph_create(&g,&v,0,1);
   fclose(fp);   
}
void fc_1(){
	printf("%d\n",n);
	for(int i=1;i<=n;++i)
		printf("%s %d\n",url[i],mk[i]);
}
void fc_2(){
	 int *vmin=NULL,*vmax=NULL;
     int max=0,min=10000000;
     for(int i=1;i<=n;++i){
     if(cvector_size(V1[i])>max)max=cvector_size(V1[i]);
     if(cvector_size(V1[i])<min)min=cvector_size(V1[i]);
     }
     for(int i=1;i<=n;++i){
     	if(cvector_size(V1[i])==max)cvector_push_back(vmax,jrb_find_int(tree1,i)->val.i);
     	if(cvector_size(V1[i])==min)cvector_push_back(vmin,jrb_find_int(tree1,i)->val.i);
     }
     
     printf("cac dinh bac vao lon nhat :");
     for(int i=0;i<cvector_size(vmax);++i)printf("%d ",vmax[i]);
     printf("\n");
     printf("cac dinh bac vao nho nhat :");
     for(int i=0;i<cvector_size(vmin);++i)printf("%d ",vmin[i]);
     printf("\n");
}

int rank_max(){
	float max=0;
	printf("rank max: \n");
	for(int i=1;i<=n;++i)if(max<rank[i])max=rank[i];
    for(int i=1;i<=n;++i)if(max==rank[i])printf("%s %f\n",url[i],rank[i]);
}

int webto(){
	int dem=0;
    printf("so luong web khong co trang khac toi: ");
	for(int i=1;i<=n;++i)if(cvector_size(V1[i])==0)dem++;
		printf("%d\n",dem);
}

int webfrom(){
	int dem=0;
	printf("so luong web khong toi trang nao: ");
	for(int i=1;i<=n;++i)if(cvector_size(V[i])==0)dem++;
    printf("%d\n",dem);
}
int rank_top3(){
	printf("web top 3 :\n");
	if(n<=3){
		for(int i=1;i<=n;++i)printf("%s %f\n",url[i],rank[i]);
		return 0;
	}
    float r[n+1];
    memcpy(r,rank,(n+1)*4);
    for (int i = 1; i <=n-1; ++i)
    {
      	for(int j=j+1;j<=n;++j)if(r[i]<r[j]){
      		float k=r[i];
      		r[i]=r[j];
      		r[j]=r[i];
      	}
    }

    for(int i=1;i<=n;++i)if(rank[i]==r[1]||rank[i]==r[2]||rank[i]==r[3])printf("%s %f\n",url[i],rank[i]);
}
int rank_page(){
	for(int i=1;i<=n;++i){
		rankupdate[i]=0;
		for(int j=0;j<cvector_size(V1[i]);++j){			
		rankupdate[i]+=rank[V1[i][j]]/cvector_size(V[V1[i][j]]);
		}
	}
	for(int i=1;i<=n;++i)rank[i]=rankupdate[i];
    float max=0;   
}
int rank_up(int m){
	for(int i=0;i<m;++i)rank_page();
}

int fc_F(int n1 ,int n2){
	igraph_get_shortest_path_dijkstra(&g,&ve,&eg,n1,n2,&weight,IGRAPH_OUT);
	for(int i=0;i<igraph_vector_size(&ve);++i)printf("%d ",jrb_find_int( tree1,(int)VECTOR(ve)[i])->val.i);
		printf("\n");
	
}
int main(){
	readfile("webpages.txt","pageConnections.txt");
    fc_1();
    fc_2();
    rank_page();
    rank_max();
    rank_up(50);
    rank_top3();	
    webto();
    webfrom();	

    fc_F(jrb_find_int(tree2,1012)->val.i,jrb_find_int(tree2,1010)->val.i);    
}
