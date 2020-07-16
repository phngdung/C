#include <igraph.h>
#include <jrb.h>
#include <jval.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int id = 0;
int size = 0;
int check = 0;
int jset_insert_str(JRB tree, char *key, Jval val){
    char* m =(char*)malloc(strlen(key)+1);
    strcpy(m,key);
  if(jrb_find_str(tree, m)==NULL)
  {
      jrb_insert_str(tree,m,val);
      return 1;
  }
}
void print_vector(igraph_vector_t *v, JRB tree) {
    long int i;
    long int a;
    
    for (i = 0; i < igraph_vector_size(v); i++) {
        a=(long int) VECTOR(*v)[i];
        JRB h = jrb_find_int(tree,a);
        printf("%s ",h->val.s);
    }
}
int main(int argc, char *argv[])
{
    JRB key_id = make_jrb();
    JRB id_key = make_jrb();
    igraph_vector_t v;
    char word[11];
    JRB q;
    int i=0;
    igraph_t g;
    igraph_bool_t isdag;
    FILE *p;
    FILE *k;
    if((p=fopen("/home/phungson/hyouteisan/ex/bt_tren_lop/inp.txt","r"))==NULL)
        {
            printf("Loi ko mo file\n");
            return -1;
        }
    while(fscanf(p,"%s",word) != EOF)
    {
        size++;
        check = jset_insert_str(key_id,word,(Jval){.i = id});
        
        if(check == 1)
        {
            char* s =(char*)malloc(strlen(word)+1);
            strcpy(s,word);
            jrb_insert_int(id_key,id,(Jval){.s=s});  
            id++;
            check =0;

        }
    }
    igraph_vector_init(&v, size);
    fclose(p);
    if((p=fopen("/home/phungson/hyouteisan/ex/inp.txt","r"))==NULL)
        {
            printf("Loi ko mo file\n");
            return -1;
        }
    while(fscanf(p,"%s",word) != EOF)
    {
        q = jrb_find_str(key_id,word);
        VECTOR(v)[i]=q->val.i;
        i++;
    }
    igraph_create(&g,&v,0,1);
    igraph_is_dag(&g,&isdag);
    if(!isdag)
        {
            printf("-1");
            return -1;
        }
    igraph_topological_sorting(&g,&v,1);
    igraph_destroy(&g);
    print_vector(&v, id_key);
    jrb_free_tree(key_id);
    jrb_free_tree(id_key);
    fclose(p);  
}