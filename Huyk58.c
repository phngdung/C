#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "libfdr/jrb.h"
#include "c-vector/cvector.h"

JRB tree1,tree2;
  igraph_vector_t v;
  igraph_vector_t weight;
int n,m;
int *V[1000001];
int readfile(char *filename){
	FILE *fp=NULL;
    tree1=make_jrb();
    tree2=make_jrb();
    igraph_vector_init(&v,0);
	fp=fopen(filename,"rt");
	if(fp==NULL){return 0;}
	fscanf(fp,"%d%d",&n,&m);
	char s[200];
	int idex=0;
	for(int i=0;i<n;++i){
     idex=-1;
     memset(s,0,200);
     fscanf(fp,"%s%d",s,&idex);
     jrb_insert_str(tree1,strdup(s),(Jval){.i=idex});
     jrb_insert_int(tree2,idex,(Jval){.s=strdup(s)});
  	}
  	int idex1;
  	for(int i=0;i<m;++i){
  	 fscanf(fp,"%d%d",&idex,&idex1);
     igraph_vector_push_back(&v,idex);
  	 igraph_vector_push_back(&v,idex1);
  	 cvector_push_back(V[idex],idex1);
  	}
}
void help_fc(){
	printf("Supported command: help, i2n, n2i, cc, cr, odg, rel.\n");
}
void about_fc(){
	printf("C advanced 20142 final exam.\n");
}
void id_to_name(int key){
	printf("%s\n",jrb_find_int(tree2,key)->val.s);
}
void name_to_id(char *name){
	printf("%d\n",jrb_find_str(tree1,name)->val.i);
}
void fc_cc(int k1,int k2){
	int A[1000001];
	for(int i=0;i<1000001;++i)A[i]=0;
    for(int i=0;i<cvector_size(V[k1]);++i)A[V[k1][i]]++;
    for(int i=0;i<cvector_size(V[k2]);++i)A[V[k2][i]]++;
    for(int i=0;i<1000001;++i)if(A[i]==2)printf("%s\n",jrb_find_int(tree2,i)->val.s);
}
void fc_cr(int k1,int k2){
	int *vector=NULL;
	for(int i=0;i<1000001;++i)
	{
		int k=0;
		for(int j=0;j<cvector_size(V[i]);++j)if(V[i][j]==k1||V[i][j]==k2)k++;
	    if(k==2)cvector_push_back(vector,i);
	}
	for(int i=0;i<cvector_size(vector);++i)printf("%s\n",jrb_find_int(tree2,vector[i])->val.s);
}
void fc_odg(int k){
	if(k==0)for(JRB str=jrb_first(tree1);str!=jrb_nil(tree1);str=jrb_next(str))printf("%s\n",str->key);
	else for(int i=0;i<1000001;++i)if(cvector_size(V[i])>k)printf("%s\n",jrb_find_int(tree2,i)->val.s);
}
void fc_rel(int k){
    int A[1000001];
    memset(A,0,1000001*4);
	for(int i=0;i<cvector_size(V[k]);++i){
		A[V[k][i]]=1;
	    int l=V[k][i];
		for(int j=0;j<cvector_size(V[l]);++j)
			{   
				A[V[l][j]]=1;
			}
	}
    for(int i=0;i<1000001;++i)if(A[i]==1)printf("%s\n",jrb_find_int(tree2,i)->val.s);
}
int main(int argc,char* argv[]){
    readfile(argv[2]);   
    if(strcmp(argv[1],"help")==0)help_fc();
    if(strcmp(argv[1],"about")==0)about_fc();
    if(strcmp(argv[1],"in2")==0)id_to_name(atoi(argv[3]));
    if(strcmp(argv[1],"2ni")==0)name_to_id(argv[3]);
    if(strcmp(argv[1],"cc")==0)fc_cc(atoi(argv[3]),atoi(argv[4]));
    if(strcmp(argv[1],"cr")==0)fc_cr(atoi(argv[3]),atoi(argv[4]));
    if(strcmp(argv[1],"odg")==0)fc_odg(atoi(argv[3]));
	if(strcmp(argv[1],"rel")==0)fc_rel(atoi(argv[3]));
	return 0;
}

