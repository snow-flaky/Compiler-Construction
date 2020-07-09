//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#ifndef sym_tab
#define sym_tab


#include "symbol_table_def.h"

 // typedef struct ast_node ast_node;

int compute_hash_sk(char * s);
struct symbol_table_ptr search_sk(char * name, ast_node * root);
void check_exp(ast_node * root);
struct sym_func_node* insert_fun(char * name, bool is_dec, int line_no);
void fill_scope(ast_node * root, struct sym_scope * inner);
struct sym_func_node * fill_other(ast_node * temp);
void populate_symbol_table(ast_node * root);

#endif