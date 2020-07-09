//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#ifndef symDef
#define symDef

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pra.h"

#define hash_size 41
#define max_var_len 20

int int_size ;
int real_size ;
int bool_size ;
int arr_base_size; 


typedef struct sym_scope s_scope;
typedef struct var_list v_list;
typedef struct sym_func_node f_node;
typedef struct var_def_node v_node;

typedef struct ast_node ast_node;

union s_ptr{
  f_node * fun_ptr;
  s_scope * inner_ptr;
};

struct array_type{
 struct token_info low;
 struct token_info high;
 TOKEN ele_type;
 union s_ptr scope_low;
 int tag_low;    // 0 if fun_ptr, 1 if inner_ptr, -1 if not declared
 union s_ptr scope_high;
 int tag_high;   // 0 if fun_ptr, 1 if inner_ptr, -1 if not declared
};



union type{
 struct array_type a;
 TOKEN basic_type;
};

struct type_def{
 union type t;
 TOKEN tag;
};


struct var_def{
 union type t;
 int tag; // tag=1 if basic type, 0 for array
 char v_name[max_var_len+1];
 int offset;
 bool flag;
 int is_static;
 char module_name[max_var_len+1];
 int scope_begin;
 int scope_end;
};


struct var_def_node{
 char v_name[max_var_len+1];
 struct var_def hash_var;
 v_node * next;
};

struct sym_scope{
 struct var_def_node * hash_var[hash_size];
 s_scope * next;
 //s_scope * inner;
};

struct var_list{
	struct var_def v;
	v_list * next;
};

struct sym_fun{
 v_list * input;
 v_list * output;
 struct sym_scope * def;
};

struct sym_func_node{
	char f_name[max_var_len+1];
	int off_begin;
    int off_end;
    bool has_dec;
    bool has_def;
    bool has_call;
    bool both;
    struct sym_fun hash_f;
    f_node* next;
};

extern struct sym_func_node* hash_table[hash_size];
extern int sem_err; 
// global var so value = 0, if 1 means there is error and so dont go to interm code generation

#endif