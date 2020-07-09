//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)
#ifndef CHECK3
#define CHECK3
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pra.h"

#define MAX_LEXEME_LENGTH 40 // just taking it twice of size of identifier

typedef struct t_node tree_node;

struct nonleaf_node{
  NON_TERMINAL nt;
  int rule_number;
  tree_node * child;
  tree_node* parent;
  tree_node* sibling;
};

struct leaf_node{
  struct token_info t;
  tree_node * child;
  tree_node * parent;
  tree_node * sibling;
};

union node11{
   struct nonleaf_node NL;
   struct leaf_node L;
};

struct t_node{
    union node11 n;
    bool is_leaf;  
};

typedef struct stack
{
    bool is_term;
    union{
        TOKEN terminal;
        NON_TERMINAL nonterminal;
    }elem;
    tree_node* ptr; 
    struct stack* next;
}stack;

#endif
