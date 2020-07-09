//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)

#include <stdio.h>
#ifndef PARSE_INCLUDED
#define PARSE_INCLUDED
#include "parser.h"
#include "stack.h"

extern g_node_head* create_g_node_head(NON_TERMINAL nt);
extern g_node* create_g_node(bool is_term, int value);
extern g_node* first_gnode(g_node_head* h,int no,bool is_term);
extern g_node* dl_nodes(g_node* pnext,int no,bool is_term);
extern long long compute_hash(char *s); 
extern void init(struct node** chain);
extern void insert(char *token,int value, bool is_term,struct node** chain);
extern struct node* search(char *token,struct node** chain);
extern void print(struct node** chain);
extern void populateGrammar(struct node** chain);
extern void print_grammar();
extern void Grammar();
extern long long calc_first_help(int index);
extern void calculate_first();
extern void print_first_all();
extern long long calc_follow_help(int index);
extern long long calculate_follow();
extern void print_follow_all();
extern void create_parse_table();
extern void print_grammar_rule(int index);
extern void print_parse_table();
extern tree_node * parse(char* filename2);
extern void inorder(tree_node* root ,FILE* outfile,int f);
extern void inorder_console(tree_node* root ,int f);
#endif