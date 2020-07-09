//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#ifndef AST_INCLUDED
#define AST_INCLUDED
#include <stdio.h>
#include "astDef.h"

extern int ast_count;
extern int var_no;
extern int label_no;
ast_node* make_nonleaf_node(char* name,tree_node* root, ast_node* input1,ast_node* input2,ast_node* input3,ast_node* input4);
ast_node* make_leaf_node(char* name,tree_node* root);
ast_node* make_ast(tree_node* root);
void print_ast(ast_node* root ,FILE* outfile,int f);
void free_tree(tree_node* root);
void print_ast_console(ast_node* root, int f);
extern void print_ir_code(quadruple* list);
extern quadruple* generateIR(ast_node* root);  

#endif
