//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<time.h>
#include "lexerDef.h"
#include  "parserDef.h"
#include "stack.h"
#include "ast.h"
#include "symbol_table.h"
#include "semantic_analyzer.h"
#include "codegenDef.h"


/*char * term1[] = {"eps","$","NUM","RNUM","INTEGER","REAL","ID","BOOLEAN","OF","ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","RECORD",
         "TAGGED","UNION","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR",
         "FOR","IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF",
         "ENDDEF","DRIVERDEF","DRIVERENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK"};  // for terminal string printing using array index 


char * nterm[] = {"program", "moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1",
        "output_plist","N2","dataType","range_arrays","type","moduleDef","statements","statement","ioStmt","boolConstt","var_id_num",
        "var","whichid","simpleStmt","assigmentStmt","whichStmt","lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional",
        "idList","N3","expression","U","new_NT","unary_op","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term",
        "N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt","caseStmts","N9","value","default",
        "iterativeStmt","range"};
*/

int main(int argc, char *argv[]){
 printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
 printf("LEVEL 4 :Symbol table/ AST/ Type Checking/ Semantic Rules modules work/ Handled Static and Dynamic arrays Type Checking and Code Generation \n");
 printf("--------------------------------------------------------------------------------------------------------------------------------------------\n\n");
 Grammar();
 calculate_first();
 calculate_follow();
 create_parse_table();
 int choice;
 syn_err = 0;
 sem_err = 0;
 int parse_nodes=0,ast_nodes=0,parse_node_size=sizeof(tree_node),ast_node_size=sizeof(struct ast_node)/3;
 while(1){
 	printf("Enter a choice out of the following :\n");
	printf("0 : EXIT\n");
	printf("1 : Printing token list\n");
	printf("2 : Print Parse Tree if code syntactically correct\n");
	printf("3 : Printing AST\n");
	printf("4 : Memory requirement of Parse Tree and AST\n");
	printf("5 : Print Symbol Table\n");
	printf("6 : Memory Requirement of Activation Record \n");
	printf("7 : Type and Width of Array Variable\n");
	printf("8 : Total Compile Time\n");
	printf("9 : Producing Assembly Code\n");
	printf("--------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	scanf("%d",&choice);


 	if(choice == 0) {
 		printf("Thank you\n");
 		return 0;
 	}


 	else if(choice==1){
		get_all_tokens(argv[1]);
		begin=0;
		forward=0;
		line_number=1;
		fseek(fp1,0,SEEK_SET);
		cap=0;		  
	}


	else if(choice == 2){
	 printf("\n\n**********Errors in one row cascade hence more than 1 errors are reported for a single line number ");
	 printf("can be considered as ONE.***********\n\n");
	 printf("LEXEME               LINE_NUMBER         TOKEN_NAME        VALUE_LF_NUMBER       PARENT_NODE_SYMBOL      IS_LEAF            NODE_SYMBOL\n");
	 for(int i=0;i<150;i++) printf("-");
	 printf("\n");
	 tree_node * root = parse(argv[1]);
	 inorder_console(root,1);
	 begin=0;
	 forward=0;
	 line_number=1;
	 cap=0;
	 fseek(fp1,0,SEEK_SET);
	}


	else if(choice == 3){
	 tree_node * root = parse(argv[1]);
	 if(syn_err == 0){
	    ast_node* ast_root=make_ast(root);
	    printf("Prints in Inorder way\n");
	    printf("LEXEME               LINE_NUMBER         TOKEN_NAME        VALUE_LF_NUMBER       PARENT_NODE_SYMBOL      IS_LEAF            NODE_SYMBOL\n");
	    for(int i=0;i<150;i++) printf("-");
	    printf("\n");
	    print_ast_console(ast_root,1);
	    begin=0;
        forward=0;
        line_number=1;
        cap=0;
        fseek(fp1,0,SEEK_SET);
       }
      else{
      	printf("Syntax Error encountered, can't print AST\n");
      }
	}


	else if(choice == 4){
		tree_node* root=parse(argv[1]);
		begin=0;
        forward=0;
        line_number=1;
        cap=0;
        fseek(fp1,0,SEEK_SET);
		ast_node* ast_root=make_ast(root);
		FILE* fp_parse=fopen("parseTree.txt", "w");
		FILE* fp_ast=fopen("ast.txt", "w");
		inorder(root, fp_parse,1);
		print_ast(ast_root, fp_ast, 1);
		parse_nodes=parse_count;
		ast_nodes=ast_count;
		printf("Parse tree number of nodes=%d                  Allocated memory=%d\n",parse_nodes,parse_nodes*parse_node_size);
			printf("AST number of nodes       =%d                  Allocated memory=%d\n",ast_nodes,ast_nodes*ast_node_size);
			float f=(float)(parse_nodes*parse_node_size-ast_nodes*ast_node_size)/(parse_nodes*parse_node_size);
			f=f*100;
			printf("Compression Efficiency=%f",f);
			printf("\n\n");
			fclose(fp_parse);
			fclose(fp_ast);
	}


	else if(choice == 5){
		tree_node * root = parse(argv[1]);
	    if(syn_err == 0){
          ast_node* ast_root=make_ast(root);
	      populate_symbol_table(ast_root);
	      offset(ast_root, true);
	      printSymbolTable(ast_root);
	    }
	    else {
	    	printf("Syntax error encountered, can't go to Stage 2\n");
	    }
	    begin=0;
        forward=0;
        line_number=1;
        cap=0;
        fseek(fp1,0,SEEK_SET);
	}


	else if(choice == 6){
		tree_node * root = parse(argv[1]);
	    if(syn_err == 0){
          ast_node* ast_root=make_ast(root);
	      populate_symbol_table(ast_root);
	      offset(ast_root, true);
	      printf("Function name   Activation Record Size\n");
	      print_activation_record(ast_root);
	    }
	    else {
	    	printf("Syntax error encountered, can't go to Stage 2\n");
	    }
	    begin=0;
        forward=0;
        line_number=1;
        cap=0;
        fseek(fp1,0,SEEK_SET);
	}


	else if(choice == 7){
		tree_node * root = parse(argv[1]);
	    if(syn_err == 0){
          ast_node* ast_root=make_ast(root);
	      populate_symbol_table(ast_root);
	      offset(ast_root, true);
	      printArrayVar(ast_root);
	    }
	    else {
	    	printf("Syntax error encountered, can't go to Stage 2\n");
	    }
	    begin=0;
        forward=0;
        line_number=1;
        cap=0;
        fseek(fp1,0,SEEK_SET);
	}


	else if(choice == 8){
		clock_t    start_time, end_time;
		double total_CPU_time, total_CPU_time_in_seconds;
		start_time = clock();
		tree_node * root = parse(argv[1]);
	    if(syn_err == 0){
          ast_node* ast_root=make_ast(root);
	      populate_symbol_table(ast_root);
	      offset(ast_root, true);
	      type_extractor(ast_root);
	      semantic_analyzer(ast_root);
	      if(syn_err == 0 && sem_err == 0) printf("Code compiles successfully\n");
	    }
	    else {
	    	printf("Syntax error encountered, can't go to Stage 2\n");
	    }
	    begin=0;
        forward=0;
        line_number=1;
        cap=0;
        fseek(fp1,0,SEEK_SET);
        end_time = clock();
		total_CPU_time  =  (double) (end_time - start_time);
		total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
		printf("Total CPU Time: %f\n", total_CPU_time);
		printf("Total CPU Time in Seconds: %f\n", total_CPU_time_in_seconds);
	}


	else if(choice == 9){
		tree_node * root = parse(argv[1]);
	    if(syn_err == 0){
          ast_node* ast_root=make_ast(root);
	      populate_symbol_table(ast_root);
	      offset(ast_root, false);
	      type_extractor(ast_root);
	      semantic_analyzer(ast_root);
	      begin=0;
          forward=0;
          line_number=1;
          cap=0;
          fseek(fp1,0,SEEK_SET);
	      if(syn_err == 0 && sem_err == 0) {
	    	printf("Code compiles successfully\n");
	    	quadruple *qd=generateIR(ast_root);
	    	//print_ir_code(qd);
	    	FILE* fp=fopen(argv[2], "w");
	    	generate_code(qd, fp);
	    	fclose(fp);
	    	// ******************************************* CODE GEN CALL ******************
	      }
	      else{
	      	printf("Errors exist can't go for Code Generation\n");
	      }
	    }	    
	}


	else{
		printf("Choose a valid option\n ");
	}
	printf("--------------------------------------------------------------------------------------------------------------------------\n");
  }
}


