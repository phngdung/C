#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "libfdr/jrb.h"
#include "c-vector/cvector.h"
#include "igraph/igraph.h"

#define sizemax 100001

JRB tree1=NULL,tree2=NULL;

igraph_vector_t v,ve,eg;
igraph_vector_t weight;
igraph_t g;
int n,m;
char *name[sizemax];
int id[sizemax];
int *V0[sizemax];
int *V10[sizemax];
int *V11[sizemax];
FILE *fp;

void cvector_show(int* vt){
	for(int i=0;i<cvector_size(vt);++i){
		int k=vt[i];
		printf("%d ",id[k]);
	}
	printf("\n");
}
void igraph_vector_show(igraph_vector_t vt){
    for(int i=0;i<igraph_vector_size(&vt);++i){
    	int k=id[(int)VECTOR(vt)[i]];
    	printf("%d ",k);
    }    
    printf("\n");
}

void jrb_show(JRB tree){
	for(JRB str=jrb_first(tree);str!=jrb_nil(tree);str=jrb_next(str));
}
void show_dsk(int **vt){
    for(int i=1;i<=n;++i){
    	printf("%d :",id[i]);
    	cvector_show(vt[i]);
    }
}

int push_back(int id1,int id2,int w){
	    int a=jrb_find_int(tree1,id1)->val.i;
        int b=jrb_find_int(tree1,id2)->val.i;
        //du lieu canh do thi
        igraph_vector_push_back(&v,a);
        igraph_vector_push_back(&v,b);
        igraph_vector_push_back(&weight,w);
        //ko co huong
        cvector_push_back(V0[a],b);
        cvector_push_back(V0[b],a);
        //co huong
        cvector_push_back(V10[a],b);//thuan
        cvector_push_back(V11[b],a);//nghich
}


void variable_init(){
	igraph_vector_init(&v,0);
	igraph_vector_init(&ve,0);
	igraph_vector_init(&eg,0);
	igraph_vector_init(&weight,0);
	memset(V0,0,4*sizemax);
	memset(V10,0,4*sizemax);
	memset(V11,0,4*sizemax);
	memset(name,0,4*sizemax);
	memset(id,0,4*sizemax);
	fp=NULL;
	n=0;
	m=0;
	tree1=make_jrb();
	tree2=make_jrb();
}


int readfile(char* filename){
    
     variable_init();

	fp=fopen(filename,"rt");
	if(fp==NULL){
		printf("find not found\n");
        return 0;
	}

	fscanf(fp,"%d%d",&n,&m);
    printf("m=%d n=%d\n",n,m);

    //read name and id ->key
	do{
		char s[1000];
		int key=0;
		for(int i=1;i<=n;++i){
			memset(s,0,1000);
			key=0;
			fscanf(fp,"%s%d",s,&key);
			printf("%s %d\n",s,key);
            id[i]=key;
            name[i]=strdup(s);

            jrb_insert_int(tree1,key,(Jval){.i=i});
            jrb_insert_str(tree2,name[i],(Jval){.i=i});

		}

	}while(0);
    //doc danh sach canh
   /* do{
    	int id1,id2,w=1;
    	for(int i=1;i<=m;++i){
        id1=0;
        id2=0;
        fscanf(fp,"%d %d",&id1,&id2);
        push_back(id1,id2,w);
    	}

    }while(0);*/
    //doc danh sach ke
    do{
      char s[10000];
      char s1[1000];
      int w=1;
      fgets(s,10000,fp);
      for(int i=1;i<=m;++i){ 
          memset(s,10000,0);
          fgets(s,10000,fp);
          
          int k=0;
          sscanf(s,"%s",s1);
          k+=strlen(s1)+1;
          int id1=atoi(s1);
          
          while(k<strlen(s)){
    	       memset(s1,0,1000);
        	   sscanf(s+k,"%s",s1);
               int id2=atoi(s1);
               //printf("%d %d\n",id1,id2);
               k+=strlen(s1)+1;
               push_back(id1,id2,w);
          }

        }
    }while(0);


	fclose(fp);
	igraph_create(&g,&v,0,0);

}
void show_nameid(){
	for(int i=1;i<=n;++i)
		printf("name=%s id=%d key=%d\n",name[i],id[i],i);
}

void timduong(int a1,int a2){
	int n1=jrb_find_int(tree1,a1)->val.i;
	int n2=jrb_find_int(tree1,a2)->val.i;
	int cost=0;
	igraph_get_shortest_path_dijkstra(&g,&ve,&eg,n1,n2,&weight,IGRAPH_OUT);
	for(int i=0;i<igraph_vector_size(&ve);++i)printf("%d->",id[(int)VECTOR(ve)[i]]);
		printf("\n");
	for(int i=0;i<igraph_vector_size(&eg);++i)cost+=(int)VECTOR(weight)[i];
	if(cost>0)printf("chi phi :%d \n",cost);
    else printf("-1\n");
}

void bacvaomax(){
	int max=0;
	for(int i=1;i<=n;++i)if(max<cvector_size(V11[i]))max=cvector_size(V11[i]);
	printf("max=%d\n",max);
	for(int i=1;i<=n;++i)if(cvector_size(V11[i])==max)printf("%d\n",id[i]);
}


void bacvaomin(){
	int min=10000000;
	for(int i=1;i<=n;++i)if(min>cvector_size(V11[i]))min=cvector_size(V11[i]);
	printf("min=%d\n",min);
	for(int i=1;i<=n;++i)if(cvector_size(V11[i])==min)printf("%d\n",id[i]);
}

void bacramax(){
	int max=0;
	for(int i=1;i<=n;++i)if(max<cvector_size(V10[i]))max=cvector_size(V10[i]);
	printf("max=%d\n",max);
	for(int i=1;i<=n;++i)if(cvector_size(V10[i])==max)printf("%d\n",id[i]);
}

void bacramin(){
	int min=10000000;
	for(int i=1;i<=n;++i)if(min>cvector_size(V10[i]))min=cvector_size(V10[i]);
	printf("min=%d\n",min);
	for(int i=1;i<=n;++i)if(cvector_size(V10[i])==min)printf("%d\n",id[i]);
}

void cacdinhra1(int id1){
	int k=jrb_find_int(tree1,id1)->val.i;
	for(int i=0;i<cvector_size(V10[k]);++i)printf("%d ",id[V10[k][i]]);
	printf("\n");
}
void cacdinhvao1(int id1){
    int k=jrb_find_int(tree1,id1)->val.i;
	for(int i=0;i<cvector_size(V11[k]);++i)printf("%d ",id[V11[k][i]]);
	printf("\n");	
}

void cacdinhke(int id1){
    int k=jrb_find_int(tree1,id1)->val.i;
    for(int i=0;i<cvector_size(V0[k]);++i)printf("%d ",id[V0[k][i]]);
	printf("\n");
}

void idtoname(int id1){
	int k=jrb_find_int(tree1,id1)->val.i;
	printf("%s\n",name[k]);
}

int main(){
	readfile("inp.txt");
	printf("\n");
	show_nameid();
	printf("\n");
	igraph_vector_show(v);
	igraph_vector_show(weight);
	printf("\n");


    show_dsk(V0);
    printf("\n");
    show_dsk(V11);
    printf("\n");
    show_dsk(V10);

    printf("\n");
    idtoname(100);

}
