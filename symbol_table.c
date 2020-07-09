//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#include "symbol_table.h"
#include "ast.h"
#include  "semantic_analyzer.h"

struct sym_func_node* hash_table[hash_size];
int sem_err = 0; 


void intialize_hash(){
    for(int i=0;i<hash_size;i++)
        hash_table[i]=NULL;
}

int compute_hash_sk(char * s){
    const int p = 31;
    int hash_value = 0;
    int p_pow = 1;
    for (int i=0;s[i]!='\0';i++) {
        if(isalpha(s[i]))
        {
        if(islower(s[i]))
        hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow) % hash_size;
        else
        hash_value = (hash_value + (s[i] - 'A' + 1) * p_pow) % hash_size;
        }
        else
        {
            int d=s[i];
            hash_value = (hash_value + (d+ 1) * p_pow) % hash_size;
        }
        p_pow = (p_pow * p) % hash_size;
    }
    return hash_value;
}


struct symbol_table_ptr search_sk(char * name, ast_node * root){
  int pos = compute_hash_sk(name);
  if(root == NULL) {
    struct symbol_table_ptr ans;
    ans.tag=-1;
    return ans;
  }
  if(root->is_leaf == 0 && root->n.NL.nt == statements && root->parent->n.NL.nt == program ){
     v_node* p = root->table_ptr.fun_ptr->hash_f.def->hash_var[pos];
       while(p!=NULL){
        if(strcmp(name,p->v_name) ==0 ){
            struct symbol_table_ptr ans;
            ans.tag = 1;
            ans.ptr.inner_ptr = root->table_ptr.fun_ptr->hash_f.def;
            ans.type_tag = p->hash_var.tag;
            if(ans.type_tag) ans.t.basic_type = p->hash_var.t.basic_type;
            else ans.t.a = p->hash_var.t.a;
            return ans;
        }
        p=p->next;
      }
    struct symbol_table_ptr ans;
    ans.tag = -1;
    return ans;
  }
  else if(root->is_leaf==0 && root->n.NL.nt == module ){
       v_node* p = root->table_ptr.fun_ptr->hash_f.def->hash_var[pos];
       while(p!=NULL){
        if(strcmp(name,p->v_name) ==0 ){
            struct symbol_table_ptr ans;
            ans.tag = 1;
            ans.ptr.inner_ptr = root->table_ptr.fun_ptr->hash_f.def;
            ans.type_tag = p->hash_var.tag;
            if(ans.type_tag) ans.t.basic_type = p->hash_var.t.basic_type;
            else ans.t.a = p->hash_var.t.a;
            return ans;
        }
        p=p->next;
      }
     v_list * ptr = root->table_ptr.fun_ptr->hash_f.input;
     while(ptr!= NULL){
        if(strcmp(name,ptr->v.v_name) ==0){
            struct symbol_table_ptr ans;
            ans.tag = 0;
            ans.ptr.fun_ptr = root->table_ptr.fun_ptr;
            ans.type_tag = ptr->v.tag;
            if(ans.type_tag) ans.t.basic_type = ptr->v.t.basic_type;
            else ans.t.a = ptr->v.t.a;
            return ans;
        }
        ptr=ptr->next;
     }
     ptr = root->table_ptr.fun_ptr->hash_f.output;
     while(ptr!= NULL){
        if(strcmp(name,ptr->v.v_name) ==0){
            struct symbol_table_ptr ans;
            ans.tag = 0;
            ans.ptr.fun_ptr = root->table_ptr.fun_ptr;
            ans.type_tag = ptr->v.tag;
            if(ans.type_tag) ans.t.basic_type = ptr->v.t.basic_type;
            else ans.t.a = ptr->v.t.a;
            return ans;
        }
        ptr=ptr->next;
     }
    struct symbol_table_ptr ans;
    ans.tag=-1;
    return ans;
  }
  else if(root->is_leaf==0 && (root->n.NL.nt == condionalStmt || root->n.NL.nt == iterativeStmt)){
    v_node* ptr = root->table_ptr.inner_ptr->hash_var[pos];
    while(ptr!=NULL){
        if(strcmp(name,ptr->v_name) ==0 ) {
            struct symbol_table_ptr ans;
            ans.tag = 1;
            ans.ptr.inner_ptr = root->table_ptr.inner_ptr;
            ans.type_tag = ptr->hash_var.tag;
            if(ans.type_tag) ans.t.basic_type = ptr->hash_var.t.basic_type;
            else ans.t.a = ptr->hash_var.t.a;
            return ans;
        }
        ptr=ptr->next;
    }
  }
  return search_sk(name,root->parent);
}



void check_exp(ast_node * root){
  if(root == NULL ) return;
  check_exp(root->child);
  if(root->is_leaf == 0 && root->n.NL.nt == var_id_num) {
    struct symbol_table_ptr ans = search_sk(root->child->n.L.t.value,root);
    if( ans.tag == -1){
        sem_err = 1;
        printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",root->child->n.L.t.value,root->child->n.L.t.line_number_var);
        printf("------------------------------------------------------\n");
        root->scope_tag=-1;
        root->tag = -1;
    }
    else{
        root->child->scope_tag = ans.tag;
        if(ans.tag) root->child->table_ptr.inner_ptr = ans.ptr.inner_ptr;
        else root->child->table_ptr.fun_ptr = ans.ptr.fun_ptr;
        root->tag = root->child->tag = ans.type_tag;
        if(ans.type_tag){
          if(root->child->next != NULL){
            sem_err = 1;
            printf("SEMANTIC ERROR : Accesing index of a variable of basic type at line number %d\n",root->child->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
          }
        root->t.basic_type = root->child->t.basic_type = ans.t.basic_type;
        }
        else {
            root->child->t.a = ans.t.a;  
            if(root->child->next != NULL && (root->child->next->n.L.t.terminal == ID || ans.t.a.low.terminal == ID || ans.t.a.high.terminal== ID))root->tag = 1, root->t.basic_type = ans.t.a.ele_type;
            else if(root->child->next == NULL)root->tag = 0, root->t.a = ans.t.a;
            else root->tag = 1, root->t.basic_type = ans.t.a.ele_type;
            if(ans.t.a.low.terminal!= ID && ans.t.a.high.terminal != ID){
               if(root->child->next!=NULL && root->child->next->n.L.t.terminal!= ID){
                 int low = atoi(root->child->t.a.low.value);
                 int high = atoi(root->child->t.a.high.value);
                 int index = atoi(root->child->next->n.L.t.value);
                 if(index < low || index > high){
                   sem_err = 1;
                   printf("SEMANTIC ERROR : Index out of bounds for static array %s at line number %d\n",root->child->n.L.t.value,root->child->next->n.L.t.line_number_var);
                   printf("------------------------------------------------------\n");
                 }
                }
               }
            }      
        }
    if(root->child->next != NULL && root->child->next->n.L.t.terminal == ID){
        struct symbol_table_ptr ans = search_sk(root->child->next->n.L.t.value, root);
        if( ans.tag == -1){
        sem_err = 1;
        printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",root->child->next->n.L.t.value,root->child->next->n.L.t.line_number_var);
        printf("------------------------------------------------------\n");
        root->child->next->tag = -1;
        root->child->scope_tag=-1; 
        }
        else{
          root->child->next->scope_tag = ans.tag;
          if(ans.tag) root->child->next->table_ptr.inner_ptr = ans.ptr.inner_ptr;
          else root->child->next->table_ptr.fun_ptr = ans.ptr.fun_ptr;
          root->child->tag = ans.type_tag;
          if(ans.type_tag) root->child->next->t.basic_type = ans.t.basic_type;
          else root->child->next->t.a = ans.t.a;
          if(root->child->tag == 0 && (ans.type_tag == 0 || ans.t.basic_type!= INTEGER)){
             sem_err = 1;
             printf("SEMANTIC ERROR : Variable used for array indexing is not of Integer type at line number %d\n",root->child->next->n.L.t.line_number_var);
             printf("------------------------------------------------------\n");
             
          }
        }
      }
  }
  check_exp(root->next);
}



struct sym_func_node* insert_fun(char * name, bool is_dec, int line_no){
  int val = compute_hash_sk(name);
  struct sym_func_node * ptr  = hash_table[val];
  struct sym_func_node * prev = hash_table[val];
  if(prev == NULL){
    struct sym_func_node * n = (struct sym_func_node*)malloc(sizeof(struct sym_func_node));
    hash_table[val] = n;
    strcpy(n->f_name,name);
    n->next = NULL;
    if(is_dec) n->has_dec = is_dec, n->has_def = false;
    else n->has_dec = false, n->has_def = true;
    n->both = false;
    n->has_call = false;
    return n;
  }
  while(ptr != NULL){
    if(strcmp(ptr->f_name,name)==0){
       if(is_dec) {
        // printf("Module declaration twice with same name\n");
        return ptr;
       }
       else {
        if(ptr->has_def){
        printf("SEMANTIC ERROR : Redeclaration of function of same name %s at line %d, ignoring the new declaration\n", name,line_no);
        printf("------------------------------------------------------\n");
        sem_err = 1;
        return NULL;
        }
        else return ptr; 
       }
     }
    prev = ptr;
    ptr = ptr->next;
    }
  struct sym_func_node * n = (struct sym_func_node*)malloc(sizeof(struct sym_func_node));
  n->next = NULL;
  strcpy(n->f_name,name);
  prev->next = n;
  if(is_dec) n->has_dec = is_dec, n->has_def = false;
  else n->has_dec= false , n->has_def = true;
  n->both = false;
  n->has_call=false;
  return n;
}

void fill_scope(ast_node * root, struct sym_scope * inner){
  
  if(root == NULL) return;
  ast_node * temp = root;
  ast_node * a = temp;
  ast_node * t;
  s_scope * curr =  NULL;
  if(temp->is_leaf ==0 && strcmp(temp->name,"FOR")==0){
    struct symbol_table_ptr ans = search_sk(temp->child->n.L.t.value,temp);
    if( ans.tag == -1){
      sem_err = 1;
      printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",temp->child->n.L.t.value,temp->child->n.L.t.line_number_var);
      printf("------------------------------------------------------\n");     
      temp->child->scope_tag = -1;
      temp->child->tag = -1;  
    }
    else {
        temp->child->scope_tag = ans.tag;
        if(ans.tag) temp->child->table_ptr.inner_ptr = ans.ptr.inner_ptr;
        else temp->child->table_ptr.fun_ptr = ans.ptr.fun_ptr;
        if(ans.type_tag == 0 || (ans.type_tag && ans.t.basic_type!=INTEGER)){
          sem_err = 1;
          printf("SEMANTIC ERROR : FOR Loop variable %s declared before but not of type Integer at line number %d\n",temp->child->n.L.t.value,temp->child->n.L.t.line_number_var);
          printf("------------------------------------------------------\n");  
          if(ans.tag){
            int pos = compute_hash_sk(temp->child->n.L.t.value);
            v_node * v_ptr =   ans.ptr.inner_ptr->hash_var[pos];
            while(v_ptr!=NULL && strcmp(v_ptr->v_name,temp->child->n.L.t.value)!=0)v_ptr=v_ptr->next;
            if(v_ptr!=NULL) v_ptr->hash_var.tag = 1, v_ptr->hash_var.t.basic_type = INTEGER;
          }
          else{
            v_list * list = ans.ptr.fun_ptr->hash_f.input;
            while(list != NULL && strcmp(temp->child->n.L.t.value,list->v.v_name)!=0)list=list->next;
            if(list!=NULL) list->v.tag = 1, list->v.t.basic_type = INTEGER;
            else{
              list = ans.ptr.fun_ptr->hash_f.output;
              while(list != NULL && strcmp(temp->child->n.L.t.value,list->v.v_name)!=0)list=list->next;
              if(list!=NULL) list->v.tag = 1, list->v.t.basic_type = INTEGER;
            }
          }
        }
        temp->child->tag = 1;
        temp->child->t.basic_type = INTEGER;
    }
    temp = temp->child->next->next;
    temp->table_ptr.inner_ptr = inner;
    temp->scope_tag =1;
    // temp = temp->child;
  }
  else if(temp->is_leaf ==0 && strcmp(temp->name,"WHILE") == 0){
   check_exp(temp->child->child);
   temp = temp->child->next; 
   temp->table_ptr.inner_ptr = inner;
   temp->scope_tag =1;
   // temp = temp->child;
   }
  else if (temp->is_leaf ==0 && temp->n.NL.nt == condionalStmt){
    struct symbol_table_ptr ans = search_sk(temp->child->n.L.t.value,temp);
    if( ans.tag == -1){
        sem_err = 1;
        printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",temp->child->n.L.t.value,temp->child->n.L.t.line_number_var);
        printf("------------------------------------------------------\n");
        temp->child->tag = -1;
        temp->child->scope_tag = -1;
    }
    else{
        temp->child->scope_tag = ans.tag;
        if(ans.tag) temp->child->table_ptr.inner_ptr = ans.ptr.inner_ptr;
        else temp->child->table_ptr.fun_ptr = ans.ptr.fun_ptr;
        temp->child->tag = ans.type_tag;
        if(temp->child->tag) temp->child->t.basic_type = ans.t.basic_type;
        else temp->child->t.a = ans.t.a;
    }

    temp = temp->child->next;
    temp->table_ptr.inner_ptr = inner;
    temp->scope_tag =1;
    if(temp->next != NULL) temp->next->table_ptr.inner_ptr = inner, temp->next->scope_tag =1;
    a = temp->next;
  } 
  if(root->n.NL.nt == condionalStmt) {
    temp = temp->child->next;
    while(temp!= NULL && temp->is_leaf)temp = temp->next;
    if(temp!= NULL){
    temp->table_ptr.inner_ptr = temp->parent->table_ptr.inner_ptr;
    temp->scope_tag =1;
    t = temp;
    temp = temp->child;
    }
    else t = temp;
   }
  else temp = temp->child;




  while(temp!= NULL){
    temp->table_ptr.inner_ptr = inner;
    temp->scope_tag =1;
  if(temp->is_leaf == 0 && temp->n.NL.nt == assignmentStmt){
    ast_node * c = temp->child;
    struct symbol_table_ptr ans = search_sk(c->n.L.t.value,temp);
    if(ans.tag==-1){
            sem_err = 1;
            printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",c->n.L.t.value, c->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
            c->tag = -1;
            c->scope_tag=-1;
        }
    else{
        c->scope_tag = ans.tag;
        if(ans.tag) c->table_ptr.inner_ptr = ans.ptr.inner_ptr;
        else c->table_ptr.fun_ptr = ans.ptr.fun_ptr;
        c->tag = ans.type_tag;
        if(c->tag) c->t.basic_type = ans.t.basic_type;
        else c->t.a = ans.t.a;
        if(c->tag==0 && c->t.a.low.terminal!=ID && c->t.a.high.terminal!=ID && c->next!=NULL && c->next->n.L.t.terminal == NUM){
          int l = atoi(c->t.a.low.value);
          int h = atoi(c->t.a.high.value);
          int ind = atoi(c->next->n.L.t.value);
          if(ind<l || ind>h){
            sem_err = 1;
            printf("SEMANTIC ERROR : Index out of bounds for static array %s at line number%d\n",c->n.L.t.value,c->next->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
          }
        }
    }
    if(c->tag == 1 && c->next->n.L.t.terminal == ID){
        sem_err = 1;
        printf("SEMANTIC ERROR : Variable of basic type has array index at line number %d\n",c->next->n.L.t.line_number_var);
        printf("------------------------------------------------------\n");
    }
    if(c->next->is_leaf && c->next->n.L.t.terminal == ID){
      struct symbol_table_ptr ans = search_sk(c->next->n.L.t.value,temp);
      if(ans.tag == -1){
        sem_err = 1;
            printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",c->next->n.L.t.value,c->next->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
            c->next->tag = -1;
            c->next->scope_tag=-1;
      }
      else{
        c->next->scope_tag = ans.tag;
        if(ans.tag) c->next->table_ptr.inner_ptr = ans.ptr.inner_ptr;
        else c->next->table_ptr.fun_ptr = ans.ptr.fun_ptr;
        c->next->tag = ans.type_tag;
        if(temp->child->tag == 0 && (ans.type_tag == 0 || ans.t.basic_type != INTEGER)){
          sem_err = 1;
          printf("SEMANTIC ERROR : Array index variable not of type integer at line number %d\n",c->next->n.L.t.line_number_var);
          printf("------------------------------------------------------\n");
        }
        if(ans.type_tag) c->next->t.basic_type = ans.t.basic_type;
        else c->next->t.a = ans.t.a;
      }
    }
    c= c->next->next;
    if(c->is_leaf == 1) c= c->next;
    if(c->n.NL.nt == U)c=c->child->next;
    if(c->is_leaf ==0 && c->n.NL.nt == var_id_num){
        struct symbol_table_ptr ans = search_sk(c->child->n.L.t.value,temp);
        if( ans.tag == -1){
        sem_err = 1;
        printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",c->child->n.L.t.value,c->child->n.L.t.line_number_var);
        printf("------------------------------------------------------\n");
        c->tag = -1;
        c->scope_tag=-1;
      }
    else{
        c->child->scope_tag = ans.tag;
        if(ans.tag) c->child->table_ptr.inner_ptr = ans.ptr.inner_ptr;
        else c->child->table_ptr.fun_ptr = ans.ptr.fun_ptr;
        c->tag = c->child->tag = ans.type_tag;
        if(ans.type_tag){
          if(c->child->next != NULL){
            sem_err = 1;
            printf("SEMANTIC ERROR : Accesing index of a variable of basic type at line number %d\n",c->child->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
          }
          c->t.basic_type = c->child->t.basic_type = ans.t.basic_type;
        }
        else {
            c->child->t.a = ans.t.a;  
            if(c->child->next != NULL && (c->child->next->n.L.t.terminal == ID || ans.t.a.low.terminal == ID || ans.t.a.high.terminal== ID))c->tag = 1, c->t.basic_type = ans.t.a.ele_type;
            else if(c->child->next == NULL)c->tag = 0, c->t.a = ans.t.a;
            else c->tag = 1, c->t.basic_type = ans.t.a.ele_type;
            if(c->tag == 0 && c->child->t.a.low.terminal!= ID && c->child->t.a.high.terminal!= ID && c->child->next!= NULL && c->child->next->n.L.t.terminal!=ID){
                int l = atoi(c->child->t.a.low.value);
                int h = atoi(c->child->t.a.high.value);
                int ind = atoi(c->child->next->n.L.t.value);
                if(ind < l || ind>h){
                 sem_err = 1;
                 printf("SEMANTIC ERROR : Index out of bound of static array %s at line number %d\n",c->child->n.L.t.value,c->child->n.L.t.line_number_var);
                 printf("------------------------------------------------------\n");
               }
              }
            }      
      }
      if(c->child->next != NULL){
          struct symbol_table_ptr p = search_sk(c->child->next->n.L.t.value,temp);
          if(p.tag == -1){
            sem_err = 1;
            printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",c->child->next->n.L.t.value,c->child->next->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
            c->child->next->tag=-1;
            c->child->next->scope_tag = -1;
          }
          else{
             c->child->next->scope_tag = p.tag;
             if(p.tag) c->child->next->table_ptr.inner_ptr = p.ptr.inner_ptr;
             else c->child->next->table_ptr.fun_ptr= p.ptr.fun_ptr;
             c->child->next->tag = p.type_tag;
             if(ans.type_tag)c->child->next->t.basic_type = p.t.basic_type;
             else c->child->next->t.a = p.t.a;
             if(ans.type_tag ==0 && (p.type_tag == 0 || p.t.basic_type!= INTEGER)){
              sem_err = 1;
              printf("SEMANTIC ERROR : Array variable index element not of type integer at line number %d\n",c->child->next->n.L.t.line_number_var);
              printf("------------------------------------------------------\n");
             }
          }
      }
    }
    else  check_exp(c);
  }
  else if((temp->is_leaf==0 && temp->n.NL.nt == ioStmt) || (temp->is_leaf == 1 && strcmp("GET_VALUE", temp->name)==0)) {
    if(temp->is_leaf) {
        struct symbol_table_ptr ans = search_sk(temp->n.L.t.value,temp);
        if(ans.tag == -1){
            sem_err = 1;
            printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",temp->n.L.t.value,temp->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
            temp->tag=-1;
            temp->scope_tag = -1;
        }
        else{
          temp->scope_tag = ans.tag;
          if(ans.tag) temp->table_ptr.inner_ptr = ans.ptr.inner_ptr;
          else temp->table_ptr.fun_ptr = ans.ptr.fun_ptr;
          temp->tag = ans.type_tag;
          if(temp->tag) temp->t.basic_type=ans.t.basic_type;
          else temp->t.a = ans.t.a;
       }
    }
    else{
        if(temp->child->is_leaf == 0){
         struct symbol_table_ptr ans = search_sk(temp->child->child->n.L.t.value,temp);
         if(ans.tag ==-1) {
            sem_err = 1;
            printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",temp->child->child->n.L.t.value,temp->child->child->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
            temp->child->child->tag=-1;
            temp->child->tag=-1;
            }
        else{
        temp->child->child->scope_tag = ans.tag;
        if(ans.tag) temp->child->child->table_ptr.inner_ptr = ans.ptr.inner_ptr;
        else temp->child->child->table_ptr.fun_ptr = ans.ptr.fun_ptr;
        temp->child->tag = temp->child->child->tag = ans.type_tag;
        if(ans.type_tag){
           if(temp->child->child->next != NULL){
            sem_err = 1;
            printf("SEMANTIC ERROR : Accesing index of a variable of basic type at line number %d \n",temp->child->child->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
           }
          temp->child->t.basic_type = temp->child->child->t.basic_type = ans.t.basic_type;
          }
        else {
            temp->child->child->t.a = ans.t.a;  
            if(temp->child->child->next != NULL && (temp->child->child->next->n.L.t.terminal == ID || ans.t.a.low.terminal == ID || ans.t.a.high.terminal== ID))temp->child->tag = 1,temp->t.basic_type = ans.t.a.ele_type;
            else if(temp->child->child->next == NULL)temp->child->tag = 0, temp->child->t.a = ans.t.a;
            else temp->child->tag = 1, temp->child->t.basic_type = ans.t.a.ele_type;
            if(ans.t.a.low.terminal!= ID && ans.t.a.high.terminal != ID){
               if(temp->child->child->next!= NULL && temp->child->child->next->n.L.t.terminal!= ID){
                 int low = atoi(temp->child->child->t.a.low.value);
                 int high = atoi(temp->child->child->t.a.high.value);
                 int index = atoi(temp->child->child->next->n.L.t.value);
                 if(index < low || index > high){
                   sem_err = 1;
                   printf("SEMANTIC ERROR : Index out of bounds for static array %s at line number %d \n",temp->child->child->n.L.t.value,temp->child->child->n.L.t.line_number_var);
                   printf("------------------------------------------------------\n");
                   }
                }
              }      
            }
         }
        if(temp->child->child->next != NULL && temp->child->child->next->n.L.t.terminal == ID){
        struct symbol_table_ptr ans = search_sk(temp->child->child->next->n.L.t.value, root);
        if( ans.tag == -1){
        sem_err = 1;
        printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d \n",temp->child->child->next->n.L.t.value,temp->child->child->next->n.L.t.line_number_var);
        printf("------------------------------------------------------\n");
        temp->child->child->next->tag = -1;
        temp->child->child->next->scope_tag = -1;
        }
        else{
          temp->child->child->next->scope_tag = ans.tag;
          if(ans.tag) temp->child->child->next->table_ptr.inner_ptr = ans.ptr.inner_ptr;
          else temp->child->child->next->table_ptr.fun_ptr = ans.ptr.fun_ptr;
          temp->child->child->tag = ans.type_tag;
          if(ans.type_tag) temp->child->child->next->t.basic_type = ans.t.basic_type;
          else temp->child->child->next->t.a = ans.t.a;
          if((ans.type_tag == 0 || ans.t.basic_type!= INTEGER) && (temp->child->child->tag == 0) ){
             sem_err = 1;
             printf("SEMANTIC ERROR : Variable used for array indexing is not of Integer type at line number %d\n",temp->child->child->next->n.L.t.line_number_var);
             printf("------------------------------------------------------\n");
             temp->child->child->next->t.a = ans.t.a;
          }
        }
       }
     }
    }
  }

 else if(temp->is_leaf ==0 && temp->n.NL.nt == moduleReuseStmt){
    ast_node * c = temp->child;
    if(c->n.NL.nt == optional){
        ast_node * b = c->child->child;
        while(b!= NULL){
           struct symbol_table_ptr ans = search_sk(b->n.L.t.value,temp);
         if(ans.tag == -1){
            sem_err = 1;
            printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",b->n.L.t.value,b->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
            b->tag=-1;
            b->scope_tag = -1;
           }
         else{
            b->scope_tag = ans.tag;
            if(ans.tag) b->table_ptr.inner_ptr = ans.ptr.inner_ptr;
            else b->table_ptr.fun_ptr  = ans.ptr.fun_ptr;
            b->tag = ans.type_tag;
            if(ans.type_tag) b->t.basic_type = ans.t.basic_type;
            else b->t.a = ans.t.a;
          }
           b=b->next;
        }
    c = c->next;
    }
    int pos = compute_hash_sk(c->n.L.t.value);
    struct sym_func_node * b = hash_table[pos];
    while(b!= NULL){
        if(strcmp(b->f_name , c->n.L.t.value) == 0){
          b->has_call = true;
          if((b->has_dec && !b->has_def) || (b->has_dec==false))   b->both = true;
         break;
        }
        b=b->next;
    }
    if(b==NULL) {
      printf("SEMANTIC ERROR : Function %s called with no previous definition and declaration at line number %d \n",c->n.L.t.value,c->n.L.t.line_number_var);
      printf("------------------------------------------------------\n");
      sem_err=1;
    }
    else{
      ast_node * foo = temp;
      while(foo!= NULL && foo->n.NL.nt!= module && foo->n.NL.nt!= program) foo  = foo->parent;
      if(foo!= NULL && foo->n.NL.nt == program){
        if(strcmp("DRIVER", c->n.L.t.value) == 0){
          printf("SEMANTIC ERROR : Recursion encountered of %s at line number %d \n",c->n.L.t.value,c->n.L.t.line_number_var);
          printf("------------------------------------------------------\n");
          sem_err=1;
        }
      }
      else if(foo!= NULL && foo->n.NL.nt == module){
        if(strcmp(c->n.L.t.value, foo->child->n.L.t.value) == 0){
          printf("SEMANTIC ERROR : Recursion encountered of %s at line number %d \n",c->n.L.t.value,c->n.L.t.line_number_var);
          printf("------------------------------------------------------\n");
          sem_err=1;
        }
      }
    }
   if(c->next != NULL){
    c= c->next->child;
    while(c!=NULL){
        struct symbol_table_ptr ans = search_sk(c->n.L.t.value,temp);
        if(ans.tag == -1){
            sem_err = 1;
            printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",c->n.L.t.value,c->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
            c->tag=-1;
            c->scope_tag=-1;
        }
        else{
            c->scope_tag = ans.tag;
            if(ans.tag) c->table_ptr.inner_ptr = ans.ptr.inner_ptr;
            else c->table_ptr.fun_ptr = ans.ptr.fun_ptr;
            c->tag = ans.type_tag;
            if(ans.type_tag) c->t.basic_type = ans.t.basic_type;
            else c->t.a = ans.t.a;
            
          }
        c = c->next;
      }
    } 
   }


   else if(temp->is_leaf==0 && temp->n.NL.nt == declareStmt){
    ast_node * b = temp->child;
    if(b->is_leaf || b->n.NL.nt == dataType)
        printf("Declare statement with no variable name, id list is empty\n");
    else{
    ast_node * c = temp->child->next;    
    union type t;
    int tag;
    bool is_static;
    if(c->is_leaf){
        tag = 1;
        t.basic_type = c->n.L.t.terminal;
    }
    else{
        tag = 0;
        c = c->child;
      if(c->child->n.L.t.terminal == ID){
          struct symbol_table_ptr p = search_sk(c->child->n.L.t.value,temp);
          if(p.tag == -1){
            sem_err = 1;
            printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",c->child->n.L.t.value,c->child->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
            t.a.tag_low = -1;
          }
       else{
         if(p.tag) t.a.scope_low.inner_ptr = p.ptr.inner_ptr;
         else t.a.scope_low.fun_ptr = p.ptr.fun_ptr;
         t.a.tag_low = p.tag;
         if(p.type_tag== 0 || (p.type_tag && p.t.basic_type != INTEGER)) {
           sem_err = 1;
           printf("SEMANTIC ERROR : Index of array %s not of type integer at line number %d \n", c->child->n.L.t.value,c->child->n.L.t.line_number_var);
           printf("------------------------------------------------------\n");
         }
        }
      }
      else t.a.tag_low = -1;
      if(c->child->next->n.L.t.terminal == ID){
        struct symbol_table_ptr p =  search_sk(c->child->next->n.L.t.value, temp);
        if(p.tag == -1){
            sem_err = 1;
            printf("SEMANTIC ERROR : Variable %s used before declaration at line number %d\n",c->child->next->n.L.t.value,c->child->next->n.L.t.line_number_var);
            printf("------------------------------------------------------\n");
            t.a.tag_high = -1;
          }
        else{
          if(p.tag) t.a.scope_high.inner_ptr = p.ptr.inner_ptr;
          else t.a.scope_high.fun_ptr = p.ptr.fun_ptr;
          t.a.tag_high = p.tag;
          if(p.type_tag== 0 || (p.type_tag && p.t.basic_type != INTEGER)) {
           sem_err = 1;
           printf("SEMANTIC ERROR : Index of array %s not of type integer at line number %d \n", c->child->next->n.L.t.value,c->child->next->n.L.t.line_number_var);
           printf("------------------------------------------------------\n");
         }
        }
      }
      else t.a.tag_high = -1;

        t.a.low = c->child->n.L.t;
        t.a.high = c->child->next->n.L.t;
        t.a.ele_type = c->next->n.L.t.terminal;
        if(t.a.high.terminal == ID || t.a.low.terminal == ID) is_static=false;
        else is_static=true;
    }
     b = b->child;
     while(b!= NULL){
      ast_node * par = temp;
      int flag =0;
      while(par!= NULL && par->n.NL.nt != module && par->n.NL.nt != condionalStmt && par->n.NL.nt!= iterativeStmt && par->n.NL.nt!=program) par = par->parent;
        if(par!=NULL && par->n.NL.nt == module){
          v_list * list = par->table_ptr.fun_ptr->hash_f.output; 
          while(list!= NULL){
              if(strcmp(list->v.v_name,b->n.L.t.value) == 0){
                printf("SEMANTIC ERROR : Variable %s redeclared in list of output parameters at line number %d\n",b->n.L.t.value, b->n.L.t.line_number_var);
                printf("------------------------------------------------------\n");  
                sem_err=1;
                if(tag == 1) list->v.tag = 1, list->v.t.basic_type = t.basic_type;
                flag =1;
                break;
              }
              list = list->next;
            }
        }
        if(flag == 0){
        int pos = compute_hash_sk(b->n.L.t.value);
        v_node * r = inner->hash_var[pos];
        while(r!= NULL && r->next!= NULL){
            if(strcmp(r->v_name,b->n.L.t.value)==0){
                printf("SEMANTIC ERROR Variable %s is redeclared in same scope at line number %d\n", b->n.L.t.value,b->n.L.t.line_number_var);
                printf("------------------------------------------------------\n");  
                sem_err=1;
                flag = 1;
                break;              
            }
            r = r->next;
        }
        if(r == NULL){
          inner->hash_var[pos] = (v_node*)malloc(sizeof(v_node));
          inner->hash_var[pos]->next = NULL;
          strcpy(inner->hash_var[pos]->v_name,b->n.L.t.value);
          r = inner->hash_var[pos];
        }
        else if(r->next == NULL){
            if(strcmp(r->v_name,b->n.L.t.value)==0){
                printf("SEMANTIC ERROR : Variable %s is redeclared in same scope at line number %d\n",b->n.L.t.value,b->n.L.t.line_number_var);
                printf("------------------------------------------------------\n");  
                sem_err=1;            
                flag = 1;
            }
            else {
                v_node * create = (v_node*)malloc(sizeof(v_node));
                r->next = create;
                create->next = NULL;
                r = r->next;
                strcpy(r->v_name,b->n.L.t.value);
            }
        }
        if(flag==0){
        r->hash_var.offset = 0;
        r->hash_var.flag = false;
        r->hash_var.is_static = is_static;
        strcpy(r->hash_var.v_name,b->n.L.t.value);
        r->hash_var.tag = tag;
        r->hash_var.t = t;
        ast_node * mn = temp;
        mn->scope_tag = 1;
        mn->table_ptr.inner_ptr = inner;
        while(mn->n.NL.nt != condionalStmt && mn->n.NL.nt != iterativeStmt && mn->n.NL.nt !=  module && !(mn->n.NL.nt == statements && mn->parent->n.NL.nt == program )) mn = mn->parent;
        r->hash_var.scope_begin = mn->line_begin;
        r->hash_var.scope_end = mn->line_end;
        mn = temp;
        while(mn->n.NL.nt!= module && mn->n.NL.nt!= program) mn=mn->parent;
        if(mn->n.NL.nt == program) strcpy(r->hash_var.module_name,"DRIVER");
        else strcpy(r->hash_var.module_name,mn->child->n.L.t.value);
        }
        }

        b=b->next;
     }
    }
   }

   else if(temp->is_leaf==0 && temp->n.NL.nt == condionalStmt){
      if(curr == NULL){
        curr = (struct sym_scope*)malloc(sizeof(struct sym_scope));
        for(int i=0; i<hash_size;i++)curr->hash_var[i] = NULL;
        curr->next = NULL;
        temp->table_ptr.inner_ptr = curr;
        temp->scope_tag = 1;
        inner->next = curr;
        fill_scope(temp,curr);        
      }
      else{
        curr->next = (struct sym_scope*)malloc(sizeof(struct sym_scope));
        curr = curr->next;
        for(int i=0; i<hash_size;i++)curr->hash_var[i] = NULL;
          curr->next = NULL;
        temp->table_ptr.inner_ptr = curr;
        temp->scope_tag = 1;        
        fill_scope(temp, curr);
      }
   }

   else if(temp->is_leaf==0 && temp->n.NL.nt == iterativeStmt){
    if(curr == NULL){
        curr = (struct sym_scope*)malloc(sizeof(struct sym_scope));
        for(int i=0; i<hash_size;i++)curr->hash_var[i] = NULL;
        curr->next = NULL;
        temp->table_ptr.inner_ptr = curr;
        temp->scope_tag =1;
        inner->next = curr;
        fill_scope(temp, curr);
        
      }
      else{
        curr->next = (struct sym_scope*)malloc(sizeof(struct sym_scope));
        curr = curr->next;
        for(int i=0; i<hash_size;i++)curr->hash_var[i] = NULL;
        curr->next = NULL;
        temp->table_ptr.inner_ptr = curr;
        temp->scope_tag = 1;
        fill_scope(temp, curr);
      }

   }
   
   if(root->n.NL.nt == condionalStmt){
     if(temp->next == NULL && t!= NULL && t->next != NULL){
      t = t->next;
        while(t!=NULL && t->is_leaf)t = t->next;
        if(t!=NULL){
        temp = t->child;
        t->table_ptr.inner_ptr = inner;
        t->scope_tag =1;
        }
        else{
          if(a!=NULL){
            temp = a->child->child; 
            a->child->table_ptr.inner_ptr = a->table_ptr.inner_ptr;
            a->child->scope_tag = 1;
            t = NULL;
            a = NULL;
          }
          else{
            break;
          }
        }
     }
     else if(temp->next ==NULL && t!=NULL && t->next == NULL && a!= NULL) {
        temp = a->child->child; 
        a->child->table_ptr.inner_ptr = a->table_ptr.inner_ptr;
        a->child->scope_tag = 1;
        t=NULL;
        a = NULL;
      }
    else if(temp->next == NULL && t!=NULL && t->next == NULL && a==NULL) {
      break;
    }
    else if(temp->next!=NULL) temp = temp->next;
    else if(t == NULL && a== NULL && temp->next == NULL) {
      break; 
    }
   }

   else temp = temp->next;
  }
  return ;
}




struct sym_func_node * fill_other(ast_node * temp){
    ast_node * mod_ptr;
    while(temp!= NULL){
     mod_ptr = temp->child;
      struct sym_func_node * ans = insert_fun(mod_ptr->n.L.t.value, false, mod_ptr->n.L.t.line_number_var);
      if(ans == NULL){
        int pos = compute_hash_sk(mod_ptr->n.L.t.value);
        struct sym_func_node* ptr = hash_table[pos];
        while(ptr!=NULL && strcmp(mod_ptr->n.L.t.value,ptr->f_name)!=0) ptr=ptr->next;
        temp->table_ptr.fun_ptr = NULL;
        temp = temp->next;
      }
  else{
      ans->has_def=true;
      ans->off_begin = 0;
      ans->off_end=0;
      mod_ptr->table_ptr.fun_ptr = ans;
      mod_ptr->scope_tag = 0;
      temp->table_ptr.fun_ptr  = ans;
      temp->scope_tag = 0;
      mod_ptr = mod_ptr->next;
      if(mod_ptr != NULL && mod_ptr->n.NL.nt == input_plist){
         ast_node* input_ptr = mod_ptr->child;
         v_list * curr;
         ans->hash_f.input = (v_list*)malloc(sizeof(v_list));
         curr = ans->hash_f.input;
         curr->v.offset=0;
         curr->v.flag = false;
         strcpy(curr->v.v_name,input_ptr->n.L.t.value);
         strcpy(curr->v.module_name,temp->child->n.L.t.value);
         curr->v.scope_begin = temp->line_begin;
         curr->v.scope_end = (temp->line_end);
         input_ptr = input_ptr->next;
         if(input_ptr->is_leaf){
            curr->v.tag = 1;
            curr->v.t.basic_type = input_ptr->n.L.t.terminal;
        }
         else{
            ast_node * t_ptr = input_ptr->child;
            curr->v.tag = 0;
            curr->v.t.a.ele_type = t_ptr->next->n.L.t.terminal;
            curr->v.t.a.low = t_ptr->child->n.L.t;
            curr->v.t.a.high = t_ptr->child->next->n.L.t;
            if(curr->v.t.a.low.terminal == ID || curr->v.t.a.high.terminal == ID) curr->v.is_static = 0;
            else curr->v.is_static = 1;
         }

         curr->next = NULL;
         input_ptr = input_ptr->next;
         while(input_ptr != NULL){
            curr->next = (v_list*)malloc(sizeof(v_list));
            curr = curr->next;
            curr->v.offset = 0;
            curr->v.flag = false;
            strcpy(curr->v.v_name,input_ptr->n.L.t.value);
            strcpy(curr->v.module_name,temp->child->n.L.t.value);
            curr->v.scope_begin = temp->line_begin;
            curr->v.scope_end = (temp->line_end);
            input_ptr = input_ptr->next;
            if(input_ptr->is_leaf){
              curr->v.tag = 1;
              curr->v.t.basic_type = input_ptr->n.L.t.terminal;
           }
            else{
               ast_node * t_ptr = input_ptr->child;
               curr->v.tag = 0;
               curr->v.t.a.ele_type = t_ptr->next->n.L.t.terminal;
               curr->v.t.a.low = t_ptr->child->n.L.t;
               curr->v.t.a.high = t_ptr->child->next->n.L.t;
               if(curr->v.t.a.low.terminal == ID || curr->v.t.a.high.terminal == ID) curr->v.is_static = 0;
               else curr->v.is_static = 1;
         }
            curr->next = NULL;
            input_ptr = input_ptr->next;
         }
         mod_ptr->table_ptr.fun_ptr = ans;
         mod_ptr->scope_tag = 0;
         mod_ptr=mod_ptr->next;
      }
      else ans->hash_f.input = NULL;
      if(mod_ptr != NULL && mod_ptr->n.NL.nt == output_plist){
         ast_node* output_ptr = mod_ptr->child;
         v_list * curr;
         ans->hash_f.output = (v_list*)malloc(sizeof(v_list));
         curr = ans->hash_f.output;
         curr->v.offset=0;
         curr->v.flag = false;
         strcpy(curr->v.v_name,output_ptr->n.L.t.value);
         strcpy(curr->v.module_name,temp->child->n.L.t.value);
         curr->v.scope_begin = temp->line_begin;
         curr->v.scope_end = temp->line_end;
         output_ptr = output_ptr->next;
         if(output_ptr->is_leaf){
            curr->v.tag = 1;
            curr->v.t.basic_type = output_ptr->n.L.t.terminal;
        }
         else{
            ast_node * t_ptr = output_ptr->child;
            curr->v.tag = 0;
            curr->v.t.a.ele_type = t_ptr->next->n.L.t.terminal;
            curr->v.t.a.low = t_ptr->child->n.L.t;
            curr->v.t.a.high = t_ptr->child->next->n.L.t;
            if(curr->v.t.a.low.terminal == ID || curr->v.t.a.high.terminal == ID) curr->v.is_static = 0;
            else curr->v.is_static = 1;
         }
         curr->next = NULL;
         output_ptr = output_ptr->next;
         while(output_ptr != NULL){
            curr->next = (v_list*)malloc(sizeof(v_list));
            curr = curr->next;
            curr->v.offset = 0;
            curr->v.flag = false;
            strcpy(curr->v.v_name,output_ptr->n.L.t.value);
            strcpy(curr->v.module_name,temp->child->n.L.t.value);
            curr->v.scope_begin = temp->line_begin;
            curr->v.scope_end = temp->line_end;
            output_ptr = output_ptr->next;
            if(output_ptr->is_leaf){
              curr->v.tag = 1;
              curr->v.t.basic_type = output_ptr->n.L.t.terminal;
           }
            else{
               printf("SEMANTIC ERROR : Output type is of Array type which is not allowed\n");
               printf("------------------------------------------------------\n");
               sem_err = 1;
               ast_node * t_ptr = output_ptr->child;
               curr->v.tag = 0;
               curr->v.t.a.ele_type = t_ptr->next->n.L.t.terminal;
               curr->v.t.a.low = t_ptr->child->n.L.t;
               curr->v.t.a.high = t_ptr->child->next->n.L.t;
               if(curr->v.t.a.low.terminal == ID || curr->v.t.a.high.terminal == ID) curr->v.is_static = 0;
               else curr->v.is_static = 1;
            }
            curr->next = NULL;
            output_ptr = output_ptr->next;
         }
         mod_ptr->table_ptr.fun_ptr = ans;
         mod_ptr->scope_tag = 0;
         mod_ptr = mod_ptr->next;
      }
      else ans->hash_f.output = NULL;
      if(mod_ptr!=NULL) {
        mod_ptr->table_ptr.fun_ptr = ans;
        mod_ptr->scope_tag = 0;
        ans->hash_f.def = (struct sym_scope*)malloc(sizeof(struct sym_scope));
        for(int i=0; i<hash_size;i++) ans->hash_f.def->hash_var[i] = NULL;
        ans->hash_f.def->next = NULL;
        fill_scope(mod_ptr, ans->hash_f.def);
       }
      temp = temp->next;
     }
    }
 }


void populate_symbol_table(ast_node * root){
 if(root->child == NULL){
   printf("Empty driver program, no modules, returning \n");
   return;
 }
 intialize_hash();
 ast_node* ptr = root->child;
 if(ptr->is_leaf ==0 && ptr->n.NL.nt == moduleDeclarations){
    ast_node* temp = ptr->child;
    while(temp!=NULL){
        struct sym_func_node * ans = insert_fun(temp->n.L.t.value, true,temp->n.L.t.line_number_var);
        ans->has_def = false;
        ans->off_begin = 0;
        ans->off_end = 0;
        temp = temp->next;
    }
   ptr=ptr->next;
 }
 if(ptr == NULL) return;
 if(ptr->is_leaf==0 && ptr->n.NL.nt == otherModules){
   fill_other(ptr->child);
   ptr = ptr->next;
}
if(ptr == NULL) return;
struct sym_func_node * ans = insert_fun("DRIVER",false,-1);
if(ans!=NULL){
ans->has_def = true;
ans->off_begin = 0;
ans->off_end = 0;
ans->hash_f.input = NULL;
ans->hash_f.output = NULL;
ans->hash_f.def = (struct sym_scope*)malloc(sizeof(struct sym_scope));
for(int i=0; i<hash_size;i++) ans->hash_f.def->hash_var[i] = NULL;
ans->hash_f.def->next = NULL;
ptr->table_ptr.fun_ptr = ans;
ptr->scope_tag = 0;
fill_scope(ptr, ans->hash_f.def);
}
else ptr->table_ptr.fun_ptr=NULL;

ptr = ptr->next;

if(ptr==NULL) return;
fill_other(ptr->child);
return;
}