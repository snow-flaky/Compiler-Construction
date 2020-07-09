//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)
#include <stdbool.h>
#ifndef AAA
#define AAA
#include "lexerDef.h"
#include "pra.h"

struct first_cell{
  long long f;
  bool is_cal;
};

struct node
{
    char token[50];
    union {
        TOKEN terminal;
        NON_TERMINAL nonterminal;
    }elem;
    
    bool is_term;
    struct node *next;
};


struct follow_cell{
  long long f;
  bool is_cal;
};

typedef struct {
  NON_TERMINAL non_terminal;
  int rule_no;
  struct g_node *next;
} g_node_head;

typedef struct g_node{
  bool is_term;
  union{
    TOKEN terminal;
    NON_TERMINAL nonterminal;
  }elem;
  struct g_node *next;
  struct g_node *prev; //doubly linked list
}g_node;

extern int parse_count;
extern int LHS_COUNT ; // no of actual distinct non terminals
extern int TOKEN_COUNT ; // no of actual distinct terminals
extern int G_SIZE ;   // total no of rules in grammar
#define MAX_NT  80   // maximum possible no of non terminals
#define MAX_T   64     // maximum possible no of terminals which is size of long long
#define MAX_TOKEN_LENGTH 40
#define m 307
extern struct first_cell first[MAX_NT]; // for at max 80 non terminals
extern struct follow_cell follow[MAX_NT]; // for at max 80 non terminals
extern int parse_table[MAX_NT][MAX_T];
#define NO_OF_GRAMMAR_RULES 105
extern g_node_head **grammar;
#endif
