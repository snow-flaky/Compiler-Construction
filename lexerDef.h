//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)
#include <stdio.h>
#include "lexer.h"
#define LEX_DEF_INCLUDED

extern long long compute_hash1(char *s);
extern void insert1(char *token,int value, bool is_term);
extern struct node1* search1(char *token);
extern size_t getStream(char* filebuffer);
extern struct token_info transition();
extern void get_all_tokens(char* filename1);
extern struct token_info get_next_token();
extern void removeCommentsfunc(char* filename);
extern void check_comment(char c);
extern void remove_comment(char* filename);
extern void init();