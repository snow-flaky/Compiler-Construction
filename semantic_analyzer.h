//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#ifndef sem_an 
#define sem_an



void offset(ast_node * root, bool a);
int set_stmts(ast_node * temp, int off_count, s_scope* inner_ptr);
int set_dec_stmt(ast_node * temp, int off_count,s_scope* inner_ptr);
bool check_assign(ast_node * root);
void semantic_analyzer(ast_node * root);
struct type_def extract(ast_node * root);
void type_extractor(ast_node * root);
void print_activation_record(ast_node * root);
void printArrayVar(ast_node * root);
void printSymbolTable(ast_node * root);
void print_list(v_list * list, int option);
void print_scope(s_scope * inner, int level, int option);
void print_arr_var(struct var_def var, bool local);
void print_var(struct var_def var, int level, bool local);

#endif
