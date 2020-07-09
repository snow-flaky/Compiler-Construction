//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)
#include<string.h>
#include"parserDef.h"
#include<ctype.h>
int parse_count=0;

char * term1[] = {"eps","$","NUM","RNUM","INTEGER","REAL","ID","BOOLEAN","OF","ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","RECORD",
         "TAGGED","UNION","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR",
         "FOR","IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF",
         "ENDDEF","DRIVERDEF","DRIVERENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK"};  // for terminal string printing using array index 


char * nterm[] = {"program", "moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1",
        "output_plist","N2","dataType","range_arrays","type","moduleDef","statements","statement","ioStmt","boolConstt","var_id_num",
        "var","whichid","simpleStmt","assigmentStmt","whichStmt","lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional",
        "idList","N3","expression","U","new_NT","unary_op","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term",
        "N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt","caseStmts","N9","value","default",
        "iterativeStmt","range"}; // for non terminal string printing using array index

int LHS_COUNT = 57; // no of actual distinct non terminals
int TOKEN_COUNT = 64; // no of actual distinct terminals
int G_SIZE = 105;   

struct first_cell first[MAX_NT]; // for at max 80 non terminals
struct follow_cell follow[MAX_NT]; // for at max 80 non terminals

int parse_table[MAX_NT][MAX_T];
g_node_head **grammar;



stack* main_st=NULL; // main stack
stack* twin = NULL; // auxiliary stack

void push(int type, tree_node* node,bool is_term, int value)
{
    stack * ptr;
    if(type) ptr = main_st;
    else ptr = twin;
    stack * newNode = (stack *) malloc(sizeof(stack));

    newNode->ptr = node;
    newNode->is_term=is_term;
    if(is_term)
        newNode->elem.terminal=(TOKEN)value;
    else
        newNode->elem.nonterminal=(NON_TERMINAL)value;
    newNode->next = ptr;     
    ptr = newNode;
    if(type) main_st = ptr;
    else twin = ptr;
}

stack* pop(int type)
{
    struct stack * topNode;
    stack * ptr;
    if(type) ptr = main_st;
    else ptr = twin;
    if (ptr==NULL)
    {
        printf("Stack is empty.\n");
    }
    topNode = ptr;
    ptr = ptr->next;
    if(type) main_st = ptr;
    else twin = ptr;
    free(topNode);
    return topNode;
}


g_node_head* create_g_node_head(NON_TERMINAL nt){
	g_node_head *head = (g_node_head*)malloc(sizeof(g_node_head));
	head->non_terminal = nt;
	head->next = NULL;
	return head;
}



g_node* create_g_node(bool is_term, int value){
	g_node *g = (g_node*)malloc(sizeof(g_node));
	g->is_term = is_term;
	if(is_term) g->elem.terminal = (TOKEN)value;
	else g->elem.nonterminal = (NON_TERMINAL)value;
	g->next = NULL;
	g->prev = NULL;
	return g;
}


g_node* first_gnode(g_node_head* h,int no,bool is_term)
{
	g_node* pnext;
	pnext = h->next = create_g_node(is_term, no);
	pnext->prev=NULL;
	pnext->next=NULL;
	return pnext;
}


g_node* dl_nodes(g_node* pnext,int no,bool is_term)
{
	g_node* ptr;
	ptr=pnext->next=create_g_node(is_term,no);
	ptr->prev=pnext;
	ptr->next=NULL;

	return ptr;
}

long long compute_hash(char *s) 
{
    const int p = 31;
    long long hash_value = 0;
    long long p_pow = 1;
    for (int i=0;s[i]!='\0';i++) {
    	if(isalpha(s[i]))
    	{
    	if(islower(s[i]))
        hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow) % m;
    	else
    	hash_value = (hash_value + (s[i] - 'A' + 1) * p_pow) % m;
    	}
    	else
    	{
    		int d=s[i];
    		hash_value = (hash_value + (d+ 1) * p_pow) % m;
    	}
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}



void init(struct node** chain)
{
    int i;
    for(i = 0; i < m; i++)
        chain[i] = NULL;
}

void insert(char *token,int value, bool is_term,struct node** chain)
{
    //create a newnode with value
    struct node *newNode = malloc(sizeof(struct node));
    int i;
    for(i=0;token[i]!='\0';i++)
    	newNode->token[i]=token[i];
    newNode->token[i]='\0';
    if(is_term) newNode->elem.terminal = (TOKEN)value;
	else newNode->elem.nonterminal = (NON_TERMINAL)value;
    newNode->is_term = is_term;
    newNode->next=NULL;

    //calculate hash key
    long long key = compute_hash(newNode->token);

    //check if chain[key] is empty
    if(chain[key] == NULL)
        chain[key] = newNode;
    //collision
    else
    {
        //add the node at the end of chain[key].
        struct node *temp = chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}


struct node* search(char *token,struct node** chain)
{
    char str[50];
    int i;
    for(i=0;token[i]!='\0';i++)
    	str[i]=token[i];
    str[i]='\0';
    long long key = compute_hash(str);
    struct node *temp = chain[key];
    while(temp)
    {
        if(strcmp(temp->token,str)==0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void print(struct node** chain)
{
    int i;

    for(i = 0; i < m; i++)
    {
        struct node *temp = chain[i];
        printf("chain[%d]-->",i);
        while(temp)
        {
            printf("%s -->",temp->token);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void populateGrammar(struct node** chain)
{
	grammar = (g_node_head**)malloc(sizeof(g_node_head*)*NO_OF_GRAMMAR_RULES); //array of g_node_head pointers
	g_node *pnext;
	struct node* temp_node;
    int i=0,j=0,k=0,MAXCHAR=10000;
    char temp[100],temp1[100];
	FILE *fp;
    char str[MAXCHAR];
    char* filename = "grammar.txt";
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
        return;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
    	j=0;k=0;
    	while(str[j]==' '|| str[j]=='<')
    		j++;
    	while(str[j]!='>' && str[j]!=' ')
    		temp[k++]=str[j++];
    	temp[k]='\0';
    	k=0;
    	temp_node= search(temp,chain);    //search in hash
        if(temp_node!=NULL)
        {                                   
    	grammar[i]=create_g_node_head(temp_node->elem.nonterminal);
        }
    	while(str[j]==' '|| str[j]=='-'|| str[j]=='>' || str[j]=='<' || str[j] =='\n')
    		j++;
   		while(str[j]!='>' && str[j]!=' ' && str[j]!='\0' && str[j]!='|' && str[j]!='\n' && str[j]!='<') 
   			temp1[k++]=str[j++];
   		temp1[k]='\0';
   		temp_node= search(temp1,chain);
   		if(temp_node!=NULL)
   		{
   		if(temp_node->is_term)
   	    	pnext=first_gnode(grammar[i],temp_node->elem.terminal,temp_node->is_term);
   		else
   			pnext=first_gnode(grammar[i],temp_node->elem.nonterminal,temp_node->is_term);
   		}
    	while(str[j]!='\0')
    	{
    		k=0;
    		if(str[j]=='|')
    		{
    			j++;i++;
    			temp_node= search(temp,chain);
    			grammar[i]=create_g_node_head(temp_node->elem.nonterminal);
       			while(str[j]!='\0' && (str[j]==' '|| str[j]=='<'))
    				j++;
   				while(str[j]!='\0' && str[j]!=' ' && str[j]!='>' && str[j]!='|' && str[j]!='\n' && str[j]!='<')
   					temp1[k++]=str[j++];
   				temp1[k]='\0';
   			 	temp_node= search(temp1,chain);
   			 	if(temp_node!=NULL)
   			 	{
   			 	if(temp_node->is_term)
   	    			pnext=first_gnode(grammar[i],temp_node->elem.terminal,temp_node->is_term);
   	    		else
   	    			pnext=first_gnode(grammar[i],temp_node->elem.nonterminal,temp_node->is_term);
   	    		}
    		}
    		else
    		{
    			while(str[j]!='\0' && (str[j]==' '|| str[j]=='>' || str[j]=='<' || str[j]=='\n'))
    				j++;
    			while(str[j]!='\0' && str[j]!=' ' && str[j]!='>' && str[j]!='|' && str[j]!='\n' && str[j]!='<')
    				temp1[k++]=str[j++];
    			temp1[k]='\0';
   				temp_node= search(temp1,chain);
   				if(temp_node!=NULL)
   				{
   				if(temp_node->is_term)
   					pnext=dl_nodes(pnext,temp_node->elem.terminal,temp_node->is_term);
   				else
   					pnext=dl_nodes(pnext,temp_node->elem.nonterminal,temp_node->is_term);
   				}
    		}
    		
    	}
    	i++;
     }
    for(int j=0;j<i;j++)
	{
		grammar[j]->rule_no=j;
	}
	//fclose(fp);
	//print_grammar();
}


void print_grammar()
{
    g_node *pnext;
    for(int j=0;j<NO_OF_GRAMMAR_RULES;j++)
    {
     printf("%d %s ->",grammar[j]->rule_no, nterm[grammar[j]->non_terminal]);
     pnext=grammar[j]->next;
     while(pnext!=NULL)
     {
         if(pnext->is_term)
             printf("%s ",term1[pnext->elem.terminal]);
         else
             printf("%s ",nterm[pnext->elem.nonterminal]);
         pnext=pnext->next;
     }
     printf("\n");
    }
}

void Grammar()
{
    struct node *chain[m];
    init(chain);  
    insert("eps",eps,1,chain);    
    insert("$",$,1,chain);                   
    insert("NUM",NUM,1,chain);
    insert("RNUM",RNUM,1,chain);
    insert("INTEGER",INTEGER,1,chain);
    insert("REAL",REAL,1,chain);
    insert("ID",ID,1,chain);
    insert("BOOLEAN",BOOLEAN,1,chain);
    insert("OF",OF,1,chain);
    insert("ARRAY",ARRAY,1,chain);
    insert("START",START,1,chain);
    insert("END",END,1,chain);
    insert("DECLARE",DECLARE,1,chain);
    insert("MODULE",MODULE,1,chain);
    insert("DRIVER",DRIVER,1,chain);
    insert("PROGRAM",PROGRAM,1,chain);
    insert("RECORD",RECORD,1,chain);
    insert("TAGGED",TAGGED,1,chain);
    insert("UNION",UNION,1,chain);
    insert("GET_VALUE",GET_VALUE,1,chain);
    insert("PRINT",PRINT,1,chain);
    insert("USE",USE,1,chain);
    insert("WITH",WITH,1,chain);
    insert("PARAMETERS",PARAMETERS,1,chain);
    insert("TRUE",TRUE,1,chain);
    insert("FALSE",FALSE,1,chain);
    insert("TAKES",TAKES,1,chain);
    insert("INPUT",INPUT,1,chain);
    insert("RETURNS",RETURNS,1,chain);
    insert("AND",AND,1,chain);
    insert("OR",OR,1,chain);
    insert("FOR",FOR,1,chain);
    insert("IN",IN,1,chain);
    insert("SWITCH",SWITCH,1,chain);
    insert("CASE",CASE,1,chain);
    insert("BREAK",BREAK,1,chain);
    insert("DEFAULT",DEFAULT,1,chain);
    insert("WHILE",WHILE,1,chain);
    insert("PLUS",PLUS,1,chain);
    insert("MINUS",MINUS,1,chain);
    insert("MUL",MUL,1,chain);
    insert("DIV",DIV,1,chain);
    insert("LT",LT,1,chain);
    insert("LE",LE,1,chain);
    insert("GE",GE,1,chain);
    insert("GT",GT,1,chain);
    insert("EQ",EQ,1,chain);
    insert("NE",NE,1,chain);
    insert("DEF",DEF,1,chain);
    insert("ENDDEF",ENDDEF,1,chain);
    insert("DRIVERDEF",DRIVERDEF,1,chain);
    insert("DRIVERENDDEF",DRIVERENDDEF,1,chain);
    insert("COLON",COLON,1,chain);
    insert("RANGEOP",RANGEOP,1,chain);
    insert("SEMICOL",SEMICOL,1,chain);
    insert("COMMA",COMMA,1,chain);
    insert("ASSIGNOP",ASSIGNOP,1,chain);
    insert("SQBO",SQBO,1,chain);
    insert("SQBC",SQBC,1,chain);
    insert("BO",BO,1,chain);
    insert("BC",BC,1,chain);
    insert("COMMENTMARK",COMMENTMARK,1,chain);
    insert("program",program,0,chain);
    insert("moduleDeclarations",moduleDeclarations,0,chain);
    insert("moduleDeclaration",moduleDeclaration,0,chain);
    insert("otherModules",otherModules,0,chain);
    insert("driverModule",driverModule,0,chain);
    insert("module",module,0,chain);
    insert("ret",ret,0,chain);
    insert("input_plist",input_plist,0,chain);
    insert("N1",N1,0,chain);
    insert("output_plist",output_plist,0,chain);
    insert("N2",N2,0,chain);
    insert("dataType",dataType,0,chain);
    insert("range_arrays",range_arrays,0,chain);
    insert("type",type,0,chain);
    insert("moduleDef",moduleDef,0,chain);
    insert("statements",statements,0,chain);
    insert("statement",statement,0,chain);
    insert("ioStmt",ioStmt,0,chain);
    insert("boolConstt",boolConstt,0,chain);
    insert("var_id_num",var_id_num,0,chain);
    insert("var",var,0,chain);
    insert("whichId",whichId,0,chain);
    insert("simpleStmt",simpleStmt,0,chain);
    insert("assignmentStmt",assignmentStmt,0,chain);
    insert("whichStmt",whichStmt,0,chain);
    insert("lvalueIDStmt",lvalueIDStmt,0,chain);
    insert("lvalueARRStmt",lvalueARRStmt,0,chain);
    insert("index",inde,0,chain);
    insert("moduleReuseStmt",moduleReuseStmt,0,chain);
    insert("optional",optional,0,chain);
    insert("idList",idList,0,chain);
    insert("N3",N3,0,chain);
    insert("expression",expression,0,chain);
    insert("U",U,0,chain);
    insert("new_NT",new_NT,0,chain);
    insert("unary_op",unary_op,0,chain);
    insert("arithmeticOrBooleanExpr",arithmeticOrBooleanExpr,0,chain);
    insert("N7",N7,0,chain);
    insert("AnyTerm",AnyTerm,0,chain);
    insert("N8",N8,0,chain);
    insert("arithmeticExpr",arithmeticExpr,0,chain);
    insert("N4",N4,0,chain);
    insert("term",term,0,chain);
    insert("N5",N5,0,chain);
    insert("factor",factor,0,chain);
    insert("op1",op1,0,chain);
    insert("op2",op2,0,chain);
    insert("logicalOp",logicalOp,0,chain);
    insert("relationalOp",relationalOp,0,chain);
    insert("declareStmt",declareStmt,0,chain);
    insert("condionalStmt",condionalStmt,0,chain);
    insert("caseStmts",caseStmts,0,chain);
    insert("N9",N9,0,chain);
    insert("value",value,0,chain);
    insert("default",defaul,0,chain);
    insert("iterativeStmt",iterativeStmt,0,chain);
    insert("range",range,0,chain);
    populateGrammar(chain);
    // print_grammar();
}
                            //populating grammar


//     // ########## START ########

long long calc_first_help(int index){
 if(first[index].is_cal) return first[index].f;
 long long ans = first[index].f;
 long long mask = 0;
 long long temp = 0;
 bool flag = true;
 long long s = 1;
 for(int i=1;i<64;i++)
  mask = mask | (s<<i);
 for(int j=0; j < G_SIZE;j++){ 
   if(grammar[j]->non_terminal == index){
     struct g_node * ptr = grammar[j]->next;
     while(flag && ptr){
        if(ptr->is_term){
            ans = ans|(s<<(ptr->elem).terminal);
            flag = false;

        }
        else{
            temp = calc_first_help((ptr->elem).nonterminal);
            ans = ans|(temp&mask);
            if(temp%2) flag = true,ptr = ptr->next;
            else flag=false;
           } 
       }
      if(ptr == NULL) ans = ans|1;
     }
     flag = true;
   }
 first[index].f = ans;
 first[index].is_cal = true;
 return ans;
}



void calculate_first()//function for calculating first of all non terminals; 
{
    for(int i=0;i<LHS_COUNT;i++){
        first[i].f = 0;
        first[i].is_cal=false;
    }
    for(int i=0;i<LHS_COUNT;i++)
      calc_first_help(i);
}


void print_first_all(){
  long long temp;
  printf("NON_TERMINAL FIRST_SET\n");
  for(int j=0;j<LHS_COUNT;j++){
      printf("%s --> {", nterm[j]);
      temp = first[j].f;
      for( int k=0;k<TOKEN_COUNT;k++){
         if(temp%2) printf("%s,  ",term1[k]);
         temp = temp/2;
      }
      printf("}\n");
  }
}


long long calc_follow_help(int index){
  if(follow[index].is_cal) return follow[index].f;
 long long ans = follow[index].f;
 long long mask = 0;
 long long temp = 0;
 bool flag = true;
 int l_ind, temp_ind;
 long long s = 1;
 for(int i=1;i<64;i++)
  mask = mask | (s<<i);
 for(int j=0; j < G_SIZE;j++){ 
    l_ind = grammar[j]->non_terminal;
    struct g_node * ptr = grammar[j]->next;
    while(ptr){
        if((ptr->elem).nonterminal == index && !(ptr->is_term)){
            struct g_node* ptr1 = ptr->next;
            flag = true;
            while(flag && ptr1){
              temp_ind = (ptr1->elem).nonterminal;
              if(ptr1->is_term && ((ptr1->elem).terminal!=0)) {
                ans = ans|(s<<(ptr1->elem).terminal);
                flag=false;
                } 
              else if(ptr1->is_term && ((ptr1->elem).terminal==0)) ptr1 = NULL;
              else{
              temp = first[temp_ind].f;
              ans = ans|(temp & mask);
              if(temp%2) ptr1=ptr1->next,flag=true;
              else flag=false;
              }
            }
            if(ptr1 == NULL && l_ind!= index){
                temp = calc_follow_help(l_ind);
                ans = ans| temp;
            }
        }
      ptr= ptr->next;
    }  
   }  
 follow[index].f = ans;
 follow[index].is_cal = true;
 return ans;
}


long long calculate_follow(){
    for(int i=0;i<LHS_COUNT;i++){
        follow[i].f = 0;
        follow[i].is_cal=false;
    }
    follow[0].f = 2;
    for(int i=1;i<LHS_COUNT;i++)
      calc_follow_help(i);
}



void print_follow_all(){
  long long temp;
  printf("NON_TERMINAL FOLLOW_SET\n");
  for(int j=0;j<LHS_COUNT;j++){
      printf("%s--> {", nterm[j]); // 
      temp = follow[j].f;
      for(int k=0;k<TOKEN_COUNT;k++){
         if(temp%2) printf("%s,  ",term1[k]);
         temp = temp/2;
      }
      printf("}\n");
  }
}

void create_parse_table(){
  for(int i=0;i<MAX_NT;i++){
    for(int j=0;j<MAX_T;j++)
        parse_table[i][j]=-1;
  }
  int row_ind, c_ind;
  bool flag;
  long long first_rhs;
  long long temp;
  long long mask =0;
  long long lhs_fol;
  long long s = 1;
  for(int i=1;i<64;i++)
      mask = mask | (s<<i);
  for(int i=0;i<G_SIZE;i++){
     row_ind = grammar[i]->non_terminal;   
     struct g_node* ptr = grammar[i]->next;
     flag = true;
     first_rhs =0;
     while(flag && ptr){
        if(ptr->is_term && (ptr->elem).terminal) flag = false,first_rhs = first_rhs|(s<<((ptr->elem).terminal));
        else if(ptr->is_term && (ptr->elem).terminal == 0) ptr=NULL;
        else{
            temp = first[(ptr->elem).nonterminal].f;
            first_rhs = first_rhs|(temp&mask);
            if(temp%2) flag = true, ptr = ptr->next;
            else flag = false;
        }
     }
     if(ptr == NULL) {
        lhs_fol = follow[row_ind].f;
        for(int j=0;j<TOKEN_COUNT;j++){
           if(lhs_fol %2) parse_table[row_ind][j] = i;
           lhs_fol = lhs_fol/2;
        }
     }
     for(int j=0;j<TOKEN_COUNT;j++){
        if(first_rhs%2) parse_table[row_ind][j] = i;
        first_rhs = first_rhs/2;
     }

  }
}

void print_grammar_rule(int index){
    printf("%s ",nterm[grammar[index]->non_terminal]);
    printf("-->");
    struct g_node* ptr = grammar[index]->next;
    while(ptr){
        if(ptr->is_term) printf("%s ",term1[(ptr->elem).terminal]);
        else printf("%s ",nterm[(ptr->elem).nonterminal]);
        ptr=ptr->next;
    }
    printf("\n");
}


void print_parse_table(){
   for(int i=0;i<LHS_COUNT;i++){
     for(int j=0;j<TOKEN_COUNT;j++){
        // if(parse_table[0][j]==-1) printf("EMPTY\n");
        if(parse_table[i][j]==-1) continue;
        else {
            printf("%s %s \n",nterm[i], term1[j]);
            print_grammar_rule(parse_table[i][j]);
            printf("\n");
        }
        
     }
   }
}

tree_node * parse(char* filename2){
    struct nonleaf_node root_node;
    root_node.nt = program;
    root_node.child = NULL;
    root_node.parent = NULL;
    root_node.sibling = NULL;
    tree_node* root = (tree_node *)malloc(sizeof(tree_node));
    root->is_leaf  = false;
    root-> n.NL = root_node;
    push(1,NULL,true,$);
    push(1,root,false,program);
    fp1=fopen(filename2,"r");
    fseek(fp1,0,SEEK_SET);
    begin=0;
    forward=0;
    struct token_info lookahead = get_next_token();
    int count = 0;
    while(true){
         //if(count++ == 250) return 0;
        // printf("check %s %d %s    %s\n  ",term1[lookahead.terminal],main_st->is_term, main_st->is_term ? term1[main_st->elem.terminal]:nterm[main_st->elem.nonterminal],term111[lookahead.terminal]);
        if(main_st->is_term && main_st->elem.terminal == $){
            if(lookahead.terminal==$){
                //printf("SUCCESS \n");
                return root;
            }
            else{
                printf("Line %d ERROR reached, bottom of stack but not end of string yet returning  \n",lookahead.line_number_var);
                return root;
            }
        }        
        else if(main_st->is_term){
        	//printf("innn \n");
            if((main_st->elem).terminal == lookahead.terminal){
                (main_st->ptr)->n.L.t.line_number_var = lookahead.line_number_var;
                (main_st->ptr)->n.L.t.terminal=lookahead.terminal;
                (main_st->ptr)->n.L.t.value = (char*)malloc(MAX_TOKEN_LENGTH*sizeof(char));
                //printf("nnnnn\n");
                strcpy((main_st->ptr)->n.L.t.value,lookahead.value);
                //printf("wtf\n");
                pop(1);
                //printf("ppp\n");
                lookahead = get_next_token();
                //rintf("%s lookahead next %s \n",term1[lookahead.terminal],lookahead.value);
            }
            else{
                if(main_st->elem.terminal ==  SEMICOL){
                    printf("Line %d: ERROR in the input as missing semicolon. Expected ';'\n",lookahead.line_number_var-1);
                    printf("------------------------------------------------------\n");
                    //printf("ERROR RECOVERY BY POPPING STACK IN CASE OF SEMICOLON\n");
                    pop(1);
                }
                else{
                printf("Line %d: Error as next token and top of stack token donot match\n",lookahead.line_number_var);
                printf("------------------------------------------------------\n");
                //printf("ERROR RECOVERY BY POPPING STACK AND MOVING LOOKAHEAD at line number %d \n", lookahead.line_number_var);
                pop(1);
                lookahead = get_next_token();
                }
            }
        }
        else{
          int nt = (main_st->elem).nonterminal;
          int rule_no = parse_table[nt][lookahead.terminal];
          tree_node* treeptr  = main_st->ptr;
          if(parse_table[nt][lookahead.terminal] !=-1){
              g_node * gptr = grammar[rule_no]->next;
              treeptr->n.NL.child = (tree_node*)malloc(sizeof(tree_node));
              treeptr->n.NL.rule_number = rule_no+1;
              treeptr = treeptr->n.NL.child;
              treeptr->is_leaf = gptr->is_term;
              if(gptr->is_term){
                struct leaf_node lnode;
                lnode.child = NULL;
                lnode.parent = main_st->ptr;
                lnode.sibling = NULL;
                treeptr->n.L = lnode;
                if(gptr->elem.terminal == 0){
                    //printf("in\n");
                    treeptr->n.L.t.terminal = 0;
                    treeptr->n.L.t.value = "eps";
                    treeptr->n.L.t.line_number_var = -1;
                    // treeptr->n.L.t.value = (char*)malloc(4*sizeof(char));
                    // strcpy(treeptr->n.L.t.value,"eps");
                }                
                else {
                	// treeptr->n.L.t.value = (char*)malloc(MAX_TOKEN_LENGTH*sizeof(char));
                	// strcpy(treeptr->n.L.t.value,"");
                	push(0,treeptr,true,(gptr->elem).terminal);
                }
              }
              else{
                struct nonleaf_node nlnode;
                nlnode.child = NULL;
                nlnode.parent = main_st->ptr;
                nlnode.sibling = NULL;
                nlnode.nt = (gptr->elem).nonterminal;
                treeptr->n.NL = nlnode;
                push(0,treeptr,false,nlnode.nt);
              } 
              gptr = gptr->next;              
              while(gptr){
                //printf("wtf %s \n",gptr->is_term ? term1[gptr->elem.terminal]:nterm[gptr->elem.nonterminal]);
                 if(gptr->is_term){
                    struct leaf_node lnode;
                    lnode.child  = NULL;
                    lnode.sibling = NULL;
                    lnode.parent = main_st->ptr;
                    if(treeptr->is_leaf) {
                        treeptr->n.L.sibling = (tree_node*)malloc(sizeof(tree_node));
                        treeptr = treeptr->n.L.sibling;
                    }
                    else {
                        treeptr->n.NL.sibling = (tree_node*)malloc(sizeof(tree_node));
                        treeptr = treeptr->n.NL.sibling;
                    }
                    treeptr->is_leaf = true;
                    treeptr->n.L = lnode;
                    push(0,treeptr,true,(gptr->elem).terminal);
                 }
                 else{
                    struct nonleaf_node nlnode;
                    nlnode.parent = main_st->ptr;
                    nlnode.child = NULL;
                    nlnode.sibling = NULL;
                    nlnode.nt = (gptr->elem).nonterminal;
                    if(treeptr->is_leaf){
                    treeptr->n.L.sibling = (tree_node*)malloc(sizeof(tree_node));
                    treeptr = treeptr->n.L.sibling;
                    }
                    else{
                        treeptr->n.NL.sibling = (tree_node*)malloc(sizeof(tree_node));
                        treeptr = treeptr->n.NL.sibling;
                    }
                    treeptr->is_leaf=false;
                    treeptr->n.NL = nlnode;
                    push(0,treeptr,false,(gptr->elem).nonterminal);
                    //printf("%s bcdbcd \n",nterm[twin->elem.nonterminal]);

                 }
                 gptr=gptr->next;
              }
            pop(1);
              //printf("check %s \n",nterm[main_st->elem.nonterminal]);
              while(twin){              
                push(1,twin->ptr,twin->is_term, twin->is_term ?(twin->elem).terminal:(twin->elem).nonterminal);
                //printf("%s check \n",main_st->is_term ? term1[main_st->elem.terminal]: nterm[main_st->elem.nonterminal]);
                twin = twin->next;
              }
          }
          else{
          	printf("Line %d: Error recovery needed as corresponding parse table entry is empty\n",lookahead.line_number_var);
          	printf("------------------------------------------------------\n");
            //printf("ERROR RECOVERY, parse table entry is -1 at line number %d \n",lookahead.line_number_var);
            bool flag = true;
            int i;
            while(flag){
            long long fst = first[nt].f;
            long long fol = follow[nt].f;
             for(i=0;i<TOKEN_COUNT;i++){
                if(fst%2){
                    if(i == lookahead.terminal){
                        flag = false;
                        //printf("lookahead matches with first of top of stack, continuing\n");
                        break;
                     }
                }
                else if (fol%2){
                    if(i==lookahead.terminal) {
                        pop(1);
                        flag = false;
                        //printf("Lookahead matches with follow of top of stack, popping top of stack and continuing\n");
                        break;
                    }
                }                
                    fst = fst/2;
                    fol = fol/2;             
             }
             if(i==TOKEN_COUNT && lookahead.terminal!=$) lookahead = get_next_token();
             
             else if(i==TOKEN_COUNT && lookahead.terminal ==$){
                //printf("Couldn't recover, returning \n");
                return root;
             }
            }
          }
        }
    }
 return root;
}



void inorder(tree_node* root ,FILE* outfile,int f)
{
    if(root==NULL)
        return;
    if(root->is_leaf)
    {

        if(root->n.L.t.terminal==RNUM && root->n.L.parent!=NULL)
        {
            fprintf(outfile,"%s",root->n.L.t.value);
            //fprintf(outfile,"%s ",)
            for(int i=0;i<(21-strlen(root->n.L.t.value));i++)
                fprintf(outfile," ");
            fprintf(outfile,"%d",root->n.L.t.line_number_var);
            for(int i=0;i<18;i++)
                fprintf(outfile," ");
            fprintf(outfile,"%s",term1[root->n.L.t.terminal]);
            for(int i=0;i<(20-strlen(term1[root->n.L.t.terminal]));i++)
                fprintf(outfile," ");
            fprintf(outfile,"%0.6e",atof(root->n.L.t.value));
            for(int i=0;i<(20-strlen(root->n.L.t.value));i++)
                fprintf(outfile," ");
            fprintf(outfile,"%s",nterm[root->n.L.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.L.parent->n.NL.nt]));i++)
                fprintf(outfile," ");
            fprintf(outfile,"YES");
            for(int i=0;i<17;i++)
                fprintf(outfile," ");
            fprintf(outfile,"----\n");
            for(int i=0;i<150;i++)
                fprintf(outfile,"-");
            fprintf(outfile,"\n");
            parse_count++;
            //fprintf(outfile,"%s  %d  %s  %0.6e  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],atof(root->n.L.t.lexeme),nterm[root->n.L.parent->n.NL.nt]);//assuming parent is always a non-terminal
        }
        else if(root->n.L.t.terminal==NUM && root->n.L.parent!=NULL)
        {
            fprintf(outfile,"%s",root->n.L.t.value);
            for(int i=0;i<(21-strlen(root->n.L.t.value));i++)
                fprintf(outfile," ");
            fprintf(outfile,"%d",root->n.L.t.line_number_var);
            for(int i=0;i<18;i++)
                fprintf(outfile," ");
            fprintf(outfile,"%s",term1[root->n.L.t.terminal]);
            for(int i=0;i<(20-strlen(term1[root->n.L.t.terminal]));i++)
                fprintf(outfile," ");
            fprintf(outfile,"%d",atoi(root->n.L.t.value));
            for(int i=0;i<(20-strlen(root->n.L.t.value));i++)
                fprintf(outfile," ");
            fprintf(outfile,"%s",nterm[root->n.L.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.L.parent->n.NL.nt]));i++)
                fprintf(outfile," ");
            fprintf(outfile,"YES");
            for(int i=0;i<17;i++)
                fprintf(outfile," ");
            fprintf(outfile,"----\n");
            for(int i=0;i<150;i++)
                fprintf(outfile,"-");
            fprintf(outfile,"\n");
            parse_count++;
            //fprintf(outfile,"%s  %d  %s  %d  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],atoi(root->n.L.t.lexeme),nterm[root->n.L.parent->n.NL.nt]);//assuming parent is always a non-terminal
        }
        else if(root->n.L.parent!=NULL)
        {
            if(root->n.L.t.value!=NULL)
            {
            fprintf(outfile,"%s",root->n.L.t.value);
            for(int i=0;i<(21-strlen(root->n.L.t.value));i++)
                fprintf(outfile," ");
            }
            else
            {
            	fprintf(outfile,"----");
            	for(int i=0;i<17;i++)
                	fprintf(outfile," ");
            }
            fprintf(outfile,"%d",root->n.L.t.line_number_var);
            for(int i=0;i<18;i++)
                fprintf(outfile," ");
            fprintf(outfile,"%s",term1[root->n.L.t.terminal]);
            for(int i=0;i<(20-strlen(term1[root->n.L.t.terminal]));i++)
                fprintf(outfile," ");
            fprintf(outfile,"----");
            for(int i=0;i<16;i++)
                fprintf(outfile," ");
            fprintf(outfile,"%s",nterm[root->n.L.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.L.parent->n.NL.nt]));i++)
                fprintf(outfile," ");
            fprintf(outfile,"YES");
            for(int i=0;i<17;i++)
                fprintf(outfile," ");
            fprintf(outfile,"----\n");
            for(int i=0;i<150;i++)
                fprintf(outfile,"-");
            fprintf(outfile,"\n");
            parse_count++;
            //fprintf(outfile,"%s  %d  %s  ----  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],nterm[root->n.L.parent->n.NL.nt]);
        }
        if(root->n.L.parent!=NULL && f)
        {
            if(root->n.L.parent->n.NL.parent!=NULL)
            {
                fprintf(outfile,"----");
                for(int i=0;i<17;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"----");
                for(int i=0;i<15;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"NON_TERMINAL        ");
                fprintf(outfile,"----");
                for(int i=0;i<16;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"%s",nterm[root->n.L.parent->n.NL.parent->n.NL.nt]);
                for(int i=0;i<(25-strlen(nterm[root->n.L.parent->n.NL.parent->n.NL.nt]));i++)
                    fprintf(outfile," ");
                fprintf(outfile,"NO");
                for(int i=0;i<18;i++)
                    fprintf(outfile," ");
                fprintf(outfile, "%s\n",nterm[root->n.L.parent->n.NL.nt] );
                for(int i=0;i<150;i++)
                    fprintf(outfile,"-");
                fprintf(outfile,"\n");
                parse_count++;
                //fprintf(outfile,"----  ----  NON_TERMINAL  ----  %s  no  %s \n",nterm[root->n.L.parent->n.NL.parent->n.NL.nt],nterm[root->n.L.parent->n.NL.nt]);
            }
            else
            {
                fprintf(outfile,"----");
                for(int i=0;i<17;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"----");
                for(int i=0;i<15;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"NON_TERMINAL        ");
                fprintf(outfile,"----");
                for(int i=0;i<16;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"ROOT");
                for(int i=0;i<21;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"NO");
                for(int i=0;i<18;i++)
                    fprintf(outfile," ");
                fprintf(outfile, "%s\n",nterm[root->n.L.parent->n.NL.nt] );
                for(int i=0;i<150;i++)
                    fprintf(outfile,"-");
                fprintf(outfile,"\n");
                parse_count++;
                //fprintf(outfile,"----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.L.parent->n.NL.nt]);
            }
        }
        inorder(root->n.L.sibling,outfile,0);
        return;
    }
    else if(root->n.NL.child==NULL)
    {
        if(root->n.NL.parent!=NULL)
        {
            fprintf(outfile,"----");
            for(int i=0;i<17;i++)
                fprintf(outfile," ");
            fprintf(outfile,"----");
            for(int i=0;i<15;i++)
                fprintf(outfile," ");
            fprintf(outfile,"NON_TERMINAL        ");
            fprintf(outfile,"----");
            for(int i=0;i<16;i++)
                fprintf(outfile," ");
            fprintf(outfile,"%s",nterm[root->n.NL.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.NL.parent->n.NL.nt]));i++)
                fprintf(outfile," ");
            fprintf(outfile,"YES");
            for(int i=0;i<17;i++)
                fprintf(outfile," ");
            fprintf(outfile, "%s\n",nterm[root->n.NL.nt] );
            for(int i=0;i<150;i++)
                fprintf(outfile,"-");
            fprintf(outfile,"\n");
            parse_count++;
            //fprintf(outfile,"----  ----  NON_TERMINAL  ----  %s  yes  %s \n",nterm[root->n.NL.parent->n.NL.nt],nterm[root->n.NL.nt]);
        }
        else
        {
            fprintf(outfile,"----");
            for(int i=0;i<17;i++)
                fprintf(outfile," ");
            fprintf(outfile,"----");
            for(int i=0;i<15;i++)
                fprintf(outfile," ");
            fprintf(outfile,"NON_TERMINAL        ");
            fprintf(outfile,"----");
            for(int i=0;i<16;i++)
                fprintf(outfile," ");
            fprintf(outfile,"ROOT");
            for(int i=0;i<21;i++)
                fprintf(outfile," ");
            fprintf(outfile,"YES");
            for(int i=0;i<17;i++)
                fprintf(outfile," ");
            fprintf(outfile, "%s\n",nterm[root->n.NL.nt] );
            for(int i=0;i<150;i++)
                fprintf(outfile,"-");
            fprintf(outfile,"\n");
            parse_count++;
            //fprintf(outfile,"----  ----  NON_TERMINAL  ----  ROOT  yes  %s \n",nterm[root->n.NL.nt]);
        }
        if(root->n.NL.parent!=NULL && f)
        {
            if(root->n.NL.parent->n.NL.parent!=NULL)
            {
                fprintf(outfile,"----");
                for(int i=0;i<17;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"----");
                for(int i=0;i<15;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"NON_TERMINAL        ");
                fprintf(outfile,"----");
                for(int i=0;i<16;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"%s",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt]);
                for(int i=0;i<(25-strlen(nterm[root->n.NL.parent->n.NL.parent->n.NL.nt]));i++)
                    fprintf(outfile," ");
                fprintf(outfile,"NO");
                for(int i=0;i<18;i++)
                    fprintf(outfile," ");
                fprintf(outfile, "%s\n",nterm[root->n.NL.parent->n.NL.nt] );
                for(int i=0;i<150;i++)
                    fprintf(outfile,"-");
                fprintf(outfile,"\n");
                parse_count++;
                //fprintf(outfile,"----  ----  NON_TERMINAL  ----  %s  no  %s \n",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt],nterm[root->n.NL.parent->n.NL.nt]);
            }
            else
            {
                fprintf(outfile,"----");
                for(int i=0;i<17;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"----");
                for(int i=0;i<15;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"NON_TERMINAL        ");
                fprintf(outfile,"----");
                for(int i=0;i<16;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"ROOT");
                for(int i=0;i<21;i++)
                    fprintf(outfile," ");
                fprintf(outfile,"NO");
                for(int i=0;i<18;i++)
                    fprintf(outfile," ");
                fprintf(outfile, "%s\n",nterm[root->n.NL.parent->n.NL.nt] );
                for(int i=0;i<150;i++)
                    fprintf(outfile,"-");
                fprintf(outfile,"\n");
                parse_count++;
                //fprintf(outfile,"----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.NL.parent->n.NL.nt]);
            }
        }
        inorder(root->n.NL.sibling,outfile,0);
        return;
    }
    inorder(root->n.NL.child ,outfile,1);
    if(root->n.NL.parent!=NULL && f)
    {
        if(root->n.NL.parent->n.NL.parent!=NULL)
        {
            fprintf(outfile,"----");
            for(int i=0;i<17;i++)
                fprintf(outfile," ");
            fprintf(outfile,"----");
            for(int i=0;i<15;i++)
                fprintf(outfile," ");
            fprintf(outfile,"NON_TERMINAL        ");
            fprintf(outfile,"----");
            for(int i=0;i<16;i++)
                fprintf(outfile," ");
            fprintf(outfile,"%s",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.NL.parent->n.NL.parent->n.NL.nt]));i++)
                fprintf(outfile," ");
            fprintf(outfile,"NO");
            for(int i=0;i<18;i++)
                fprintf(outfile," ");
            fprintf(outfile, "%s\n",nterm[root->n.NL.parent->n.NL.nt] );
            for(int i=0;i<150;i++)
                fprintf(outfile,"-");
            fprintf(outfile,"\n");
            parse_count++;
            //fprintf(outfile,"----  ----  NON_TERMINAL  ----  %s  no  %s \n",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt],nterm[root->n.NL.parent->n.NL.nt]);
        }
        else
        {
            fprintf(outfile,"----");
            for(int i=0;i<17;i++)
                fprintf(outfile," ");
            fprintf(outfile,"----");
            for(int i=0;i<15;i++)
                fprintf(outfile," ");
            fprintf(outfile,"NON_TERMINAL        ");
            fprintf(outfile,"----");
            for(int i=0;i<16;i++)
                fprintf(outfile," ");
            fprintf(outfile,"ROOT");
            for(int i=0;i<21;i++)
                fprintf(outfile," ");
            fprintf(outfile,"NO");
            for(int i=0;i<18;i++)
                fprintf(outfile," ");
            fprintf(outfile, "%s\n",nterm[root->n.NL.parent->n.NL.nt] );
            for(int i=0;i<150;i++)
                fprintf(outfile,"-");
            fprintf(outfile,"\n");
            parse_count++;
            //fprintf(outfile,"----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.NL.parent->n.NL.nt]);
        }
    }
    inorder(root->n.NL.sibling,outfile,0);
}

void inorder_console(tree_node* root ,int f)
{
    if(root==NULL)
        return;
    if(root->is_leaf)
    {

        if(root->n.L.t.terminal==RNUM && root->n.L.parent!=NULL)
        {
            printf("%s",root->n.L.t.value);
            //printf("%s ",)
            for(int i=0;i<(21-strlen(root->n.L.t.value));i++)
                printf(" ");
            printf("%d",root->n.L.t.line_number_var);
            for(int i=0;i<18;i++)
                printf(" ");
            printf("%s",term1[root->n.L.t.terminal]);
            for(int i=0;i<(20-strlen(term1[root->n.L.t.terminal]));i++)
                printf(" ");
            printf("%0.6e",atof(root->n.L.t.value));
            for(int i=0;i<(20-strlen(root->n.L.t.value));i++)
                printf(" ");
            printf("%s",nterm[root->n.L.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.L.parent->n.NL.nt]));i++)
                printf(" ");
            printf("YES");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----\n");
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            parse_count++;
            //printf("%s  %d  %s  %0.6e  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],atof(root->n.L.t.lexeme),nterm[root->n.L.parent->n.NL.nt]);//assuming parent is always a non-terminal
        }
        else if(root->n.L.t.terminal==NUM && root->n.L.parent!=NULL)
        {
            printf("%s",root->n.L.t.value);
            for(int i=0;i<(21-strlen(root->n.L.t.value));i++)
                printf(" ");
            printf("%d",root->n.L.t.line_number_var);
            for(int i=0;i<18;i++)
                printf(" ");
            printf("%s",term1[root->n.L.t.terminal]);
            for(int i=0;i<(20-strlen(term1[root->n.L.t.terminal]));i++)
                printf(" ");
            printf("%d",atoi(root->n.L.t.value));
            for(int i=0;i<(20-strlen(root->n.L.t.value));i++)
                printf(" ");
            printf("%s",nterm[root->n.L.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.L.parent->n.NL.nt]));i++)
                printf(" ");
            printf("YES");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----\n");
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            parse_count++;
            //printf("%s  %d  %s  %d  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],atoi(root->n.L.t.lexeme),nterm[root->n.L.parent->n.NL.nt]);//assuming parent is always a non-terminal
        }
        else if(root->n.L.parent!=NULL)
        {
            if(root->n.L.t.value!=NULL)
            {
            printf("%s",root->n.L.t.value);
            for(int i=0;i<(21-strlen(root->n.L.t.value));i++)
                printf(" ");
            }
            else
            {
              printf("----");
              for(int i=0;i<17;i++)
                  printf(" ");
            }
            printf("%d",root->n.L.t.line_number_var);
            for(int i=0;i<18;i++)
                printf(" ");
            printf("%s",term1[root->n.L.t.terminal]);
            for(int i=0;i<(20-strlen(term1[root->n.L.t.terminal]));i++)
                printf(" ");
            printf("----");
            for(int i=0;i<16;i++)
                printf(" ");
            printf("%s",nterm[root->n.L.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.L.parent->n.NL.nt]));i++)
                printf(" ");
            printf("YES");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----\n");
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            parse_count++;
            //printf("%s  %d  %s  ----  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],nterm[root->n.L.parent->n.NL.nt]);
        }
        if(root->n.L.parent!=NULL && f)
        {
            if(root->n.L.parent->n.NL.parent!=NULL)
            {
                printf("----");
                for(int i=0;i<17;i++)
                    printf(" ");
                printf("----");
                for(int i=0;i<15;i++)
                    printf(" ");
                printf("NON_TERMINAL        ");
                printf("----");
                for(int i=0;i<16;i++)
                    printf(" ");
                printf("%s",nterm[root->n.L.parent->n.NL.parent->n.NL.nt]);
                for(int i=0;i<(25-strlen(nterm[root->n.L.parent->n.NL.parent->n.NL.nt]));i++)
                    printf(" ");
                printf("NO");
                for(int i=0;i<18;i++)
                    printf(" ");
                printf( "%s\n",nterm[root->n.L.parent->n.NL.nt] );
                for(int i=0;i<150;i++)
                    printf("-");
                printf("\n");
                parse_count++;
                //printf("----  ----  NON_TERMINAL  ----  %s  no  %s \n",nterm[root->n.L.parent->n.NL.parent->n.NL.nt],nterm[root->n.L.parent->n.NL.nt]);
            }
            else
            {
                printf("----");
                for(int i=0;i<17;i++)
                    printf(" ");
                printf("----");
                for(int i=0;i<15;i++)
                    printf(" ");
                printf("NON_TERMINAL        ");
                printf("----");
                for(int i=0;i<16;i++)
                    printf(" ");
                printf("ROOT");
                for(int i=0;i<21;i++)
                    printf(" ");
                printf("NO");
                for(int i=0;i<18;i++)
                    printf(" ");
                printf( "%s\n",nterm[root->n.L.parent->n.NL.nt] );
                for(int i=0;i<150;i++)
                    printf("-");
                printf("\n");
                parse_count++;
                //printf("----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.L.parent->n.NL.nt]);
            }
        }
        inorder_console(root->n.L.sibling,0);
        return;
    }
    else if(root->n.NL.child==NULL)
    {
        if(root->n.NL.parent!=NULL)
        {
            printf("----");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----");
            for(int i=0;i<15;i++)
                printf(" ");
            printf("NON_TERMINAL        ");
            printf("----");
            for(int i=0;i<16;i++)
                printf(" ");
            printf("%s",nterm[root->n.NL.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.NL.parent->n.NL.nt]));i++)
                printf(" ");
            printf("YES");
            for(int i=0;i<17;i++)
                printf(" ");
            printf( "%s\n",nterm[root->n.NL.nt] );
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            parse_count++;
            //printf("----  ----  NON_TERMINAL  ----  %s  yes  %s \n",nterm[root->n.NL.parent->n.NL.nt],nterm[root->n.NL.nt]);
        }
        else
        {
            printf("----");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----");
            for(int i=0;i<15;i++)
                printf(" ");
            printf("NON_TERMINAL        ");
            printf("----");
            for(int i=0;i<16;i++)
                printf(" ");
            printf("ROOT");
            for(int i=0;i<21;i++)
                printf(" ");
            printf("YES");
            for(int i=0;i<17;i++)
                printf(" ");
            printf( "%s\n",nterm[root->n.NL.nt] );
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            parse_count++;
            //printf("----  ----  NON_TERMINAL  ----  ROOT  yes  %s \n",nterm[root->n.NL.nt]);
        }
        if(root->n.NL.parent!=NULL && f)
        {
            if(root->n.NL.parent->n.NL.parent!=NULL)
            {
                printf("----");
                for(int i=0;i<17;i++)
                    printf(" ");
                printf("----");
                for(int i=0;i<15;i++)
                    printf(" ");
                printf("NON_TERMINAL        ");
                printf("----");
                for(int i=0;i<16;i++)
                    printf(" ");
                printf("%s",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt]);
                for(int i=0;i<(25-strlen(nterm[root->n.NL.parent->n.NL.parent->n.NL.nt]));i++)
                    printf(" ");
                printf("NO");
                for(int i=0;i<18;i++)
                    printf(" ");
                printf( "%s\n",nterm[root->n.NL.parent->n.NL.nt] );
                for(int i=0;i<150;i++)
                    printf("-");
                printf("\n");
                parse_count++;
                //printf("----  ----  NON_TERMINAL  ----  %s  no  %s \n",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt],nterm[root->n.NL.parent->n.NL.nt]);
            }
            else
            {
                printf("----");
                for(int i=0;i<17;i++)
                    printf(" ");
                printf("----");
                for(int i=0;i<15;i++)
                    printf(" ");
                printf("NON_TERMINAL        ");
                printf("----");
                for(int i=0;i<16;i++)
                    printf(" ");
                printf("ROOT");
                for(int i=0;i<21;i++)
                    printf(" ");
                printf("NO");
                for(int i=0;i<18;i++)
                    printf(" ");
                printf( "%s\n",nterm[root->n.NL.parent->n.NL.nt] );
                for(int i=0;i<150;i++)
                    printf("-");
                printf("\n");
                parse_count++;
                //printf("----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.NL.parent->n.NL.nt]);
            }
        }
        inorder_console(root->n.NL.sibling,0);
        return;
    }
    inorder_console(root->n.NL.child,1);
    if(root->n.NL.parent!=NULL && f)
    {
        if(root->n.NL.parent->n.NL.parent!=NULL)
        {
            printf("----");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----");
            for(int i=0;i<15;i++)
                printf(" ");
            printf("NON_TERMINAL        ");
            printf("----");
            for(int i=0;i<16;i++)
                printf(" ");
            printf("%s",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt]);
            for(int i=0;i<(25-strlen(nterm[root->n.NL.parent->n.NL.parent->n.NL.nt]));i++)
                printf(" ");
            printf("NO");
            for(int i=0;i<18;i++)
                printf(" ");
            printf( "%s\n",nterm[root->n.NL.parent->n.NL.nt] );
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            parse_count++;
            //printf("----  ----  NON_TERMINAL  ----  %s  no  %s \n",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt],nterm[root->n.NL.parent->n.NL.nt]);
        }
        else
        {
            printf("----");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----");
            for(int i=0;i<15;i++)
                printf(" ");
            printf("NON_TERMINAL        ");
            printf("----");
            for(int i=0;i<16;i++)
                printf(" ");
            printf("ROOT");
            for(int i=0;i<21;i++)
                printf(" ");
            printf("NO");
            for(int i=0;i<18;i++)
                printf(" ");
            printf( "%s\n",nterm[root->n.NL.parent->n.NL.nt] );
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            parse_count++;
            //printf("----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.NL.parent->n.NL.nt]);
        }
    }
    inorder_console(root->n.NL.sibling,0);
}

