//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#ifndef CODEDEF
#define CODEDEF

//extern int compute_hash(char * s);
extern void calculate_AR_size(Tuple* tuple);
extern short extract_int_value(char* arg);
extern v_node* get_info(char* arg, ast_node* node);
extern v_node* get_info1(char* arg, union s_ptr scope,int tag);
extern void generate_code(quadruple* quad, FILE* fp);
extern void process_tuple(Tuple* tuple, FILE* fp);
extern void processs_FUNCTION(Tuple* tuple, FILE* fp);
extern void process_RET(Tuple* tuple, FILE* fp);
extern void process_ASSIGNOP(Tuple* tuple, FILE* fp);
extern void process_ARITHOP(Tuple* tuple, FILE* fp);
extern void process_RELATIONALOP(Tuple *tuple, FILE *fp);
extern void process_PRINT1(Tuple* tuple,FILE* fp);
extern void process_GET_VALUE1(Tuple* tuple,FILE* fp);
extern void process_LABEL(Tuple* tuple, FILE* fp);
extern void process_GOTO(Tuple* tuple, FILE* fp);
extern void process_IF(Tuple* tuple, FILE* fp);
extern void process_UNARY1(Tuple* tuple, FILE* fp);
extern void process_call(Tuple* tuple,FILE* fp);
#endif
