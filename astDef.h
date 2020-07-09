//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#ifndef abc
#define abc
#include <stdbool.h>
#include "parserDef.h"
#include "lexerDef.h"
#include "pra.h"
#include "stack.h"
#include "symbol_table_def.h"
#include "symbol_table.h"


extern int ast_count;


// typedef struct ast_node ast_node;


struct ast_nonleaf_node{
  NON_TERMINAL nt;
};

struct ast_leaf_node{
  struct token_info t;
};

struct symbol_table_ptr{
  union s_ptr ptr;
  int tag; // 0 if fun_ptr, 1 if inner_ptr, else -1
  union type t;
  int type_tag;
};

/******************************************/
struct tuple{
	TOKEN op;
	char* arg1;
	char* arg2;
	char* result;

	struct tuple* next;


	ast_node *node1,*node2,*node3;

};

typedef struct tuple Tuple;

struct quadruple{
	Tuple* head;
	Tuple* last;
	
};
typedef struct quadruple quadruple;
/*************************************/


struct ast_node{
  char* name;
  union {
   struct ast_nonleaf_node NL;
   struct ast_leaf_node L;
  }n;
  bool is_leaf;                    
  int rule_number;
  ast_node* parent;
  ast_node* child;
  ast_node* next;  
  int off_end_local;
  int off_end_param;
  int line_begin;
  int line_end;
  union type t;
  int tag;
  union s_ptr table_ptr;
  int scope_tag; // 0 for func ptr, 1 for inner ptr  
    Tuple* tuple_start;
  Tuple* tuple_end;                
};

//extern FILE* fp_ast;


#endif

