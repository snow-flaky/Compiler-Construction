//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include<string.h>
    #include<stdbool.h>
    #include<ctype.h>
    #include"pra.h"
    #include "lexer.h"
    char * term111[] = {"eps","$","NUM","RNUM","INTEGER","REAL","ID","BOOLEAN","OF","ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","RECORD",
                   "TAGGED","UNION","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR",
                   "FOR","IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF",
                   "ENDDEF","DRIVERDEF","DRIVERENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK"};  // for terminal string printing using array index 


     char * nterm111[] = {"program", "moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1",
                    "output_plist","N2","dataType","range_arrays","type","moduleDef","statements","statement","ioStmt","boolConstt","var_id_num",
                    "var","whichid","simpleStmt","assigmentStmt","whichStmt","lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional",
                    "idList","N3","expression","U","new_NT","unary_op","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term",
                    "N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt","caseStmts","N9","value","default",
                    "iterativeStmt","range"}; // for non terminal string printing using array index

    struct node1
    {
        char token[50];
        union {
            TOKEN terminal;
            NON_TERMINAL nonterminal;
        }elem;
        
        bool is_term;
        struct node1 *next;
    };

    FILE*fp1;
    char filebuffer1[buffer_size];
    char filebuffer2[buffer_size];
    int state;
    int line_number=1;
    FILE* source_code;
    FILE* modified_code;

    int forward=0;
    int begin=0;
    int cap;

    int syn_err = 0;

    struct node1**temp111;

    struct node1* chaim[m];

    void remove_comment(){
     char c1,c2;
        while((c1=fgetc(source_code))!=EOF)   
        {
            if(c1=='\n'){
                fputc('\n',modified_code);
            }
            if(c1=='*')    
            {
                c2=fgetc(source_code);  
                if(c2=='*')  
                return;
            }
       }
    }
    void check_comment(char c){
        char d;
        if(c =='*')   
        {
            if((d=fgetc(source_code))=='*')   
                     remove_comment();  
            else
            {
                fputc(c,modified_code);
                fputc(d,modified_code);
            }
        }
        else
            fputc(c,modified_code);
    }

    void removeCommentsfunc(char* filename){
        char c;
        source_code = fopen (filename,"r") ;  
        modified_code = fopen ("modified.txt","w") ;    
        while((c=fgetc(source_code))!=EOF)       
            check_comment(c);  
        fseek(modified_code, 0, SEEK_SET); 
        //fclose(modified_code);
    }
    void init1()
    {
        int i;
        for(i = 0; i < m; i++)
            chaim[i] = NULL;
    }

    long long compute_hash1(char *s) 
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



    void insert1(char *token,int value, bool is_term)
    {
        //create a newnode1 with value
        struct node1 *newnode1 = malloc(sizeof(struct node1));
        int i;
        for(i=0;token[i]!='\0';i++)
            newnode1->token[i]=token[i];
        newnode1->token[i]='\0';
        if(is_term) newnode1->elem.terminal = (TOKEN)value;
        else newnode1->elem.nonterminal = (NON_TERMINAL)value;
        newnode1->is_term = is_term;
        newnode1->next = NULL;

        //calculate hash key
        long long key = compute_hash1(newnode1->token);

        //check if chaim[key] is empty
        if(chaim[key] == NULL)
            chaim[key] = newnode1;
        //collision
        else
        {
            //add the node1 at the end of chaim[key].
            struct node1 *temp = chaim[key];
            while(temp->next!=NULL)
            {
                temp = temp->next;
            }

            temp->next = newnode1;
        }
    }

    struct node1* search1(char *token)
    {
        char str[50];
        int i;
        for(i=0;token[i]!='\0';i++)
            str[i]=token[i];
        str[i]='\0';
        long long key = compute_hash1(str);
        struct node1 *temp = chaim[key];
        while(temp)
        {
            if(strcmp(temp->token,str)==0)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    size_t getStream(char* filebuffer){
        size_t abc = fread(filebuffer, sizeof(char), buffer_size, fp1);
        if(abc<buffer_size)
        {
            filebuffer[abc]='$';
            filebuffer[abc+1]='\0';
            return abc+1;
        }
        return abc;

    }

    struct token_info transition()
    {
    char c;

    c=filebuffer1[begin];

    state=0;
    int flag=0;
    while(forward<cap){

    switch(state)
    {

    case 0: {
            if(c=='+')
            {

                struct token_info t={line_number,PLUS,"+"};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {


                    cap=getStream(filebuffer1);
                        begin=0;
                    forward=0;
        
                    }
                return t;
            }   
            else if(c=='-')
            {
                struct token_info t={line_number,MINUS,"-"};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {


                    cap=getStream(filebuffer1);
                        begin=0;
                    forward=0;
        
                    }
                return t;
            }
            else if(c=='/')
            {
                struct token_info t={line_number,DIV,"/"};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {


                    cap=getStream(filebuffer1);
                        begin=0;
                    forward=0;
        
                    }
                return t;
            }
            else if(c==';')
            {
                struct token_info t={line_number,SEMICOL,";"};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {


                    cap=getStream(filebuffer1);
                        begin=0;
                    forward=0;
        
                    }
                return t;
            }
            else if(c==',')
            {
                struct token_info t={line_number,COMMA,","};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {

                    cap=getStream(filebuffer1);
                        begin=0;
                    forward=0;
        
                    }
                return t;
            }
            else if(c=='[')
            {
                struct token_info t={line_number,SQBO,"["};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {

                    cap=getStream(filebuffer1);
                        begin=0;
                    forward=0;
        
                    }
                return t;
            }
            else if(c==']')
            {
                struct token_info t={line_number,SQBC,"]"};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {
                    cap=getStream(filebuffer1);
                    begin=0;
                    forward=0;
                    }
                return t;
            }
            else if(c=='(')
            {
                struct token_info t={line_number,BO,"("};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {
                    cap=getStream(filebuffer1);
                    begin=0;
                    forward=0;
                    }
                return t;
            }
            else if(c==')')
            {
                struct token_info t={line_number,BC,")"};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {
                    cap=getStream(filebuffer1);
                    begin=0;
                    forward=0;
                    }
                return t;
            }
            else if(c=='.')
            {
                state=11;
                forward++;
                break;
            }
            else if(c=='=')
            {
                state=13;
                forward++;
                break;
            }
            else if(c=='-')
            {
                state=15;
                forward++;
                break;
            }
            else if(c==':')
            {
                state=17;
                forward++;
                break;
            }
            else if(c=='<')
            {
                state=20;
                forward++;
                break;
            }
            else if(c=='>')
            {
                state=24;
                forward++;
                break;
            }
            else if((c>='a' && c<='z')|| (c>='A' && c<='Z'))
            {   
                state=28;
                forward++;
                break;
            }
            else if(c>='0' && c<='9')
            {
                state=30;
                forward++;
                break;
            }
            else if(c==' ' || c=='\t')
            {
                state=0;
                forward++;
                begin=forward;
                break;
            }
            else if(c=='*')
            {
                state=39;
                forward++;
                break;
            }
            else if(c=='\n' )
            {
                state=0;
                line_number++;
                forward++;
                begin=forward;
                break;
            }
            else if(c=='$')
            {
                forward++;
                struct token_info t={-1,$,"$"};
                return t;
            }
            else
            {
                char c1;
                c1=filebuffer1[begin];  
                printf("LEXICAL ERROR OCCURED AT LINE %d. Cannot identify %c as valid.\n------------------------------------------------------\n",line_number,c1);
                state=0;
                forward++;
                begin=forward;
                syn_err = 1;
                break;
            }   
            }

    case 11:{
            if(c=='.')
            {
                struct token_info t={line_number,RANGEOP,".."};
                state=0;
                forward++;
                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {
                    cap=getStream(filebuffer1);
                        begin=0;
                    forward=0;
        
                    }
                return t;
            }   
            else
            {
                printf("LEXICAL ERROR OCCURED AT LINE %d. Cannot identify '.'.\n---------------------------------------------------\n",line_number);
                state=0;
                syn_err = 1;
                begin=forward;
                break;
            }       
            }       
    case 13:
            {
            if(c=='=')
            {
                struct token_info t={line_number,EQ,"=="};
                state=0;
                forward++;

                begin=forward;
                if(begin==buffer_size && forward==begin)
                    {

                    cap=getStream(filebuffer1);
                        begin=0;
                    forward=0;
        
                    }
                return t;
            }   
                else
            {
                printf("LEXICAL ERROR OCCURED AT LINE %d.Cannot identify '=' as valid.\n------------------------------------------------\n",line_number);
                forward;
                state=0;
                begin=forward;
                syn_err = 1;
                break;
            }   
            }       
    case 15:
            {
                if(c=='=')
                {
                    struct token_info t={line_number,NE,"!="};
                    state=0;
                    forward++;
                    begin=forward;
                    if(begin==buffer_size && forward==begin)
                    {

                    //printf("hdkk");
                    cap=getStream(filebuffer1);
                    begin=0;
                    forward=0;
        
                    }

                    return t;
                }
                else
            {
                printf("LEXICAL ERROR OCCURED AT LINE %d, Cannot identify '!' as valid.\n-------------------------------------------------\n",line_number);
                forward;
                state=0;
                begin=forward;
                syn_err = 1;
                break;
            }   
            }       
    case 17:{
                if(c=='=')
                {
                    struct token_info t={line_number,ASSIGNOP,":="};
                    state=0;
                    forward++;
                    begin=forward;
                    //printf("here %d %d",forward,begin);
                    if(begin==buffer_size && forward==begin)
                    {

                    cap=getStream(filebuffer1);
                        begin=0;
                    forward=0;
        
                    }

                    return t;
                }
                else
                {
                    struct token_info t={line_number,COLON,":"};
                    state=0;
                    begin=forward;
                    return t;
                }
            }

    case 20:{
                if(c=='=')
                {
                    struct token_info t={line_number,LE,"<="};
                    state=0;
                    forward++;
                    begin=forward;
                    return t;
                }
                else if(c=='<')
                {
                    state=50;
                    forward++;
                    break;
                }
                else
                {
                    struct token_info t={line_number,LT,"<"};
                    state=0;
                    begin=forward;
                    return t;
                }   

            }
    case 50:{
                if(c=='<')
                {
                    struct token_info t={line_number,DRIVERDEF,"<<<"};
                    state=0;
                    forward++;
                    begin=forward;
                    return t;   
                }
                else
                {
                    struct token_info t={line_number,DEF,"<<"};
                    state=0;
                    forward;
                    begin=forward;
                    return t;
                }
            }               
    case 24:{
                if(c=='=')
                {
                    struct token_info t={line_number,GE,">="};
                    state=0;
                    forward++;
                    begin=forward;
                    return t;
                }
                else if(c=='>')
                {
                    state=51;
                    forward++;
                    break;
                }
                else
                {
                    struct token_info t={line_number,GT,">"};
                    state=0;
                    begin=forward;
                    return t;
                }
            }       
    case 51:{
                if(c=='>')
                {
                    struct token_info t={line_number,DRIVERENDDEF,">>>"};
                    state=0;
                    forward++;
                    begin=forward;
                    return t;
                }
                else
                {
                    struct token_info t={line_number,ENDDEF,">>"};
                    state=0;
                    forward;

                    begin=forward;
                    return t;
                }
            }

    case 28:{
        
            if((c>='a'&& c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9')|| c=='_')
            {
                forward++;
                state=28;
                break;
            }

            else
            {
                char value[21];
                int j=0;

                if(flag==0)
                {
                    
                    if(forward-begin>20)
                    {
                        int jk=0;
                        char tempval[2*buffer_size+1];
                        for(int i=begin;i<forward;i++)
                        {
                            tempval[jk++]=filebuffer1[i];
                        }
                        tempval[jk]='\0';
                        printf("IDENTIFIER EXCEEDS LENGTH 20 AT LINE NUMBER %d. Cannot tokenize %s\n--------------------------------------------------\n",line_number,tempval);
                        
                        begin=forward;
                        state=0;
                        break;
                    }
                    int in=0;
                    for(int var=begin;var<forward;var++)
                    {
                        value[in++]=filebuffer1[var];
                    }
                    value[in]='\0';

                    
                }
                
                else
                {
                    
                    if((forward+(buffer_size-begin))>20)
                    {
                        int jk=0;
                        char tempval[2*buffer_size+1];
                        for(int i=begin;i<buffer_size;i++)
                        {
                            tempval[jk++]=filebuffer2[i];
                        }
                        for(int i=0;i<forward;i++)
                        {
                            tempval[jk++]=filebuffer1[i];
                        }
                        tempval[jk]='\0';
                        printf("IDENTIFIER EXCEEDS AT LINE NUMBER %d. Cannot tokenize %s\n-----------------------------------------------------------\n",line_number,tempval);
                        begin=forward;
                        state=0;
                        break;
                    }
                    else
                    {
                        int in=0;
                        
                        for(int var=begin;var<=buffer_size-1;var++)
                        {
                            value[in++]=filebuffer2[var];
                        }
                        for(int var=0;var<forward;var++)
                        {
                            value[in++]=filebuffer1[var];
                        }
                        value[in]='\0';

                    }

                }
                        state=0;
                        begin=forward;
                        flag=0;
                          struct node1* tnode1=search1(value);
                            if(tnode1==NULL)
                            {
                                struct token_info t={line_number,ID,value};
                                        return t;
                            }
                            else
                            {
                                
                                
                                struct token_info t1={line_number,tnode1->elem.terminal,value};
                                        return t1;
                            }
                        
                        

                            struct token_info t={line_number,ID,value};
                    return t;
            }
            }
    case 30:{
                if(c=='.')
                {
                    state=32;
                    forward++;
                    break;
                }
                else if(c>='0' && c<='9')
                {
                    state=30;
                    forward++;
                    break;
                }
                else
                {
                    char value[1024];
                    int j=0;
                    if(flag==0)
                {
                    
                    int in=0;
                    for(int var=begin;var<forward;var++)
                    {
                        value[in++]=filebuffer1[var];
                    }
                    value[in]='\0';
                }
                
                else
                {
                        int in=0;
                        for(int var=begin;var<=buffer_size-1;var++)
                        {
                            value[in++]=filebuffer2[var];

                        }
                        for(int var=0;var<forward;var++)
                        {
                            value[in++]=filebuffer1[var];
                        }
                        value[in]='\0';
                }       
                    
                    begin=forward;
                    state=0;
                    
                    struct token_info t9={line_number,NUM,value};
                    return t9;
                }
            }   
    case 32:{
                if(c>='0' && c<='9')
                {
                    state=33;
                    forward++;
                    break;
                }

                else if(c=='.')
                {
                    forward=forward-2;
                    char value[1024];
                    int j=0;
                    
                    if(flag==0)
                {
                    
                    int in=0;
                    for(int var=begin;var<=forward;var++)
                    {
                        value[in++]=filebuffer1[var];
                    }
                    value[in]='\0';
                    
                }
                
                else
                {
                        int in=0;
                        for(int var=begin;var<=buffer_size-1;var++)
                        {
                            value[in++]=filebuffer2[var];

                        }
                        for(int var=0;var<=forward;var++)
                        {
                            value[in++]=filebuffer1[var];
                        }
                        value[in]='\0';
                }       
                    
                    begin=forward+1;
                    forward=begin;
                    state=11; 
                    struct token_info t9={line_number,NUM,value};
                    return t9;
                }
                    
                else
                {
                    char tempval1[2*buffer_size+1];
                    if(flag==0)
                {
                    
                    int in=0;
                    for(int var=begin;var<forward;var++)
                    {
                        tempval1[in++]=filebuffer1[var];
                    }
                    tempval1[in]='\0';   
                }
                
                else
                {
                        int in=0;
                        for(int var=begin;var<=buffer_size-1;var++)
                        {
                            tempval1[in++]=filebuffer2[var];

                        }
                        for(int var=0;var<forward;var++)
                        {
                            tempval1[in++]=filebuffer1[var];
                        }
                        tempval1[in]='\0';
                }       
                    printf("LEXICAL ERROR OCCURED AT LINE %d. Cannot accept '%s'\n-------------------------------------------------------\n",line_number,tempval1);
                    syn_err = 1;
                    state=0;
                    begin=forward;
                    break;
                }

            }   
    case 33:{
            if(c>='0' && c<='9')
                {
                    state=33;
                    forward++;
                    break;
                }
                else if(c=='e' || c=='E')
                {
                    state=35;
                    forward++;
                    break;
                }
                else
                {
                    char value[1024];
                    int j=0;
                    
                    if(flag==0)
                {
                    
                    
                    int in=0;
                    for(int var=begin;var<forward;var++)
                    {
                        value[in++]=filebuffer1[var];
                    }
                    value[in]='\0';
                    
                }
                
                else
                {
                        int in=0;
                        for(int var=begin;var<=buffer_size-1;var++)
                        {
                            value[in++]=filebuffer2[var];

                        }
                        for(int var=0;var<forward;var++)
                        {
                            value[in++]=filebuffer1[var];
                        }
                        value[in]='\0';
                }       
                    begin=forward;
                    state=0;
                    struct token_info t9={line_number,RNUM,value};
                    return t9;
                }
            }   
    case 35:{

            if(c=='+' || c=='-')
            {
                state=36;
                forward++;
                break;
            }
            else if(c>='0' && c<='9')
            {
                state=37;
                forward++;
                break;
            }
            else
                {
                    char tempval2[2*buffer_size+1];
                    if(flag==0)
                {
                    
                    
                    int in=0;
                    for(int var=begin;var<forward;var++)
                    {
                        tempval2[in++]=filebuffer1[var];
                    }
                    tempval2[in]='\0';
                }
                
                else
                {
                        int in=0;
                        for(int var=begin;var<=buffer_size-1;var++)
                        {
                            tempval2[in++]=filebuffer2[var];

                        }
                        for(int var=0;var<forward;var++)
                        {
                            tempval2[in++]=filebuffer1[var];
                        }
                        tempval2[in]='\0';
                }
                    printf("LEXICAL ERROR OCCURED AT LINE %d, Cannot accept '%s'\n------------------------------------------------------------\n",line_number,tempval2);
                    syn_err = 1;
                    state=0;
                    begin=forward;
                    break;
                }

            }
    case 36:{
        if(c>='0' && c<='9')
        {
            state=37;
            forward++;
            break;
        }
        else
                {
                    char tempval1[2*buffer_size+1];
                    if(flag==0)
                {
                    int in=0;
                    for(int var=begin;var<forward;var++)
                    {
                        tempval1[in++]=filebuffer1[var];
                    }
                    tempval1[in]='\0';
                }
                
                else
                {
                        int in=0;
                        for(int var=begin;var<=buffer_size-1;var++)
                        {
                            tempval1[in++]=filebuffer2[var];

                        }
                        for(int var=0;var<forward;var++)
                        {
                            tempval1[in++]=filebuffer1[var];
                        }
                        tempval1[in]='\0';
                    }
                    printf("LEXICAL ERROR OCCURED AT LINE %d. Cannot accept '%s'\n---------------------------------------------------\n",line_number,tempval1);
                    state=0;
                    begin=forward;
                    syn_err = 1;
                    break;
                }
    }   
    case 37:{
        if(c>='0' && c<='9')
        {
            state=37;
            forward++;
            break;
        }
        else
        {
        char value[1024];
                    int j=0;
                    if(flag==0)
                {

                    int in=0;
                    for(int var=begin;var<forward;var++)
                    {
                        value[in++]=filebuffer1[var];
                    }
                    value[in]='\0';
                }
                
                else
                {
                        int in=0;
                        for(int var=begin;var<=buffer_size-1;var++)
                        {
                            value[in++]=filebuffer2[var];
                            //printf("char=%c",filebuffer2[var]);

                        }
                        for(int var=0;var<forward;var++)
                        {
                            value[in++]=filebuffer1[var];
                        }
                        value[in]='\0';
                }       

                    begin=forward;
                    state=0;
                    struct token_info t9={line_number,RNUM,value};
                    return t9;
                }   

    }                   
    case 39:{
                if(c=='*')
                {
                    state=41;
                    forward++;
                    break;
                }
                else
                {
                    struct token_info t={line_number,MUL,"*"};
                    state=0;
                    begin=forward;
                    return t;

                }
            }
    case 41:{
                if(c=='*')
                {
                    state=42;
                    forward++;
                    break;
                }
                else if(c=='\n')
                {
                    state=41;
                    line_number++;
                    forward++;
                    break;
                }
                else
                {
                    state=41;
                    forward++; 
                    if(forward == buffer_size){
                        cap = getStream(filebuffer1);
                        begin=0;
                        forward=0;
                    }     
                    break;
                }

            }               
    case 42:{
                if(c=='*')
                {
                    forward++;
                    begin=forward;
                    state=0;
                    break;
                }
                else if(c=='\n')
                {                       // SHOULD WE ALLOW **  *\n*
                    state=42;
                    line_number++;
                    forward++;
                    break;
                }
                else
                {
                    state=41;
                    forward++;
                    break;
                }
            }

    }
    if(begin==buffer_size && forward==begin)
    {

        cap=getStream(filebuffer1);
        begin=0;
        forward=0;
        
    }

    else if(forward==buffer_size && begin<forward)
    {

        char temp[buffer_size];
        memcpy(temp,filebuffer1,sizeof(filebuffer1));
        
        memcpy(filebuffer1,filebuffer2,sizeof(filebuffer2));
        
        cap=getStream(filebuffer1);
        memcpy(filebuffer2,temp,sizeof(temp));
        
        forward=0;
        flag=1;
    }
    c=filebuffer1[forward]; 
    }
    struct  token_info t1={-1,$,"null"};

    return t1;
    }
    
    struct token_info get_next_token()
    {
    init1(chaim);
    // printf("oooo\n");
        insert1("eps",eps,1);    
        insert1("$",$,1);                   //init1 array of list to NULL 
        insert1("integer",INTEGER,1);
        insert1("real",REAL,1);
        insert1("id",ID,1);
        insert1("boolean",BOOLEAN,1);
        insert1("of",OF,1);
        insert1("array",ARRAY,1);
        insert1("start",START,1);
        insert1("end",END,1);
        insert1("declare",DECLARE,1);
        insert1("module",MODULE,1);
        insert1("driver",DRIVER,1);
        insert1("program",PROGRAM,1);
        insert1("record",RECORD,1);
        insert1("tagged",TAGGED,1);
        insert1("union",UNION,1);
        insert1("get_value",GET_VALUE,1);
        insert1("print",PRINT,1);
        insert1("use",USE,1);
        insert1("with",WITH,1);
        insert1("parameters",PARAMETERS,1);
        insert1("true",TRUE,1);
        insert1("false",FALSE,1);
        insert1("takes",TAKES,1);
        insert1("input",INPUT,1);
        insert1("returns",RETURNS,1);
        insert1("AND",AND,1);
        insert1("OR",OR,1);
        insert1("for",FOR,1);
        insert1("in",IN,1);
        insert1("switch",SWITCH,1);
        insert1("case",CASE,1);
        insert1("break",BREAK,1);
        insert1("default",DEFAULT,1);
        insert1("while",WHILE,1);

    if(cap==0)
        cap=getStream(filebuffer1);
        // printf("toooo\n");
        struct token_info y=transition(); 
        // printf("pppp\n"); 
        return y;
    }

    void get_all_tokens(char* filename1){
        init1(chaim);
        insert1("eps",eps,1);    
        insert1("$",$,1);                   //init1 array of list to NULL 
        insert1("integer",INTEGER,1);
        insert1("real",REAL,1);
        insert1("id",ID,1);
        insert1("boolean",BOOLEAN,1);
        insert1("of",OF,1);
        insert1("array",ARRAY,1);
        insert1("start",START,1);
        insert1("end",END,1);
        insert1("declare",DECLARE,1);
        insert1("module",MODULE,1);
        insert1("driver",DRIVER,1);
        insert1("program",PROGRAM,1);
        insert1("record",RECORD,1);
        insert1("tagged",TAGGED,1);
        insert1("union",UNION,1);
        insert1("get_value",GET_VALUE,1);
        insert1("print",PRINT,1);
        insert1("use",USE,1);
        insert1("with",WITH,1);
        insert1("parameters",PARAMETERS,1);
        insert1("true",TRUE,1);
        insert1("false",FALSE,1);
        insert1("takes",TAKES,1);
        insert1("input",INPUT,1);
        insert1("returns",RETURNS,1);
        insert1("AND",AND,1);
        insert1("OR",OR,1);
        insert1("for",FOR,1);
        insert1("in",IN,1);
        insert1("switch",SWITCH,1);
        insert1("case",CASE,1);
        insert1("break",BREAK,1);
        insert1("default",DEFAULT,1);
        insert1("while",WHILE,1);

    fp1=fopen(filename1,"r");
        cap=getStream(filebuffer1);

        printf("line_number");
        for(int i=0;i<2;i++)
                    printf(" ");
        printf("lexeme");
        for(int i=0;i<20;i++)
                    printf(" ");
        printf("Token_name\n------------------------------------------------\n");
        while(1)
        {
            struct token_info y=transition();

           
        if(y.line_number_var==-1)
            break;
        else
            {  
            
            int yuu=30-(strlen(y.value));
         
            
                printf("%d",y.line_number_var);
                for(int i=0;i<12;i++)
                    printf(" ");
                printf("%s",y.value);
                for(int i=0;i<yuu;i++)
                    printf(" ");
                printf("%s\n------------------------------------------------\n",term111[y.terminal]);
            
            
            }
        } 
    }