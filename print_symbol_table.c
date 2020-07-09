//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include  "ast.h"
#include "symbol_table.h"
#include "semantic_analyzer.h"
#include "string.h"
#include <ctype.h>


void print_var(struct var_def var, int level, bool local){
	int count = 0;
	int low,high;
	for(int i = 0; ((i < max_var_len) && var.v_name[i]!='\0');i++){
		printf("%c", var.v_name[i]);
		count++;
	}
	while(count < (max_var_len+1)) printf(" "), count++;
	count = 0;
	for(int i = 0; ((i < max_var_len) && var.module_name[i]!='\0');i++){
		printf("%c", var.module_name[i]);
		count++;
	}
	while(count < (max_var_len+1)) printf(" "), count++;
	int n_b = 0, n_e =0;
	int s_begin = var.scope_begin, s_end = var.scope_end;
	while(s_begin>0) n_b++, s_begin = s_begin/10;
	while(s_end>0) n_e++, s_end  = s_end/10;
	printf("%d",var.scope_begin);
	while(n_b<3) printf(" "), n_b++;
	printf("-");
	printf(" %d", var.scope_end);
	while(n_e <10) printf(" "),n_e++;
	TOKEN type;
	if(var.tag) type = var.t.basic_type;
	else type = ARRAY;
	int width;
	if (type == INTEGER) width = int_size;
	else if(type == REAL) width = real_size;
	else if(type == BOOLEAN) width = bool_size;
	else{
        if(local){
        	if(var.is_static) {
    		     low = atoi(var.t.a.low.value);
    		     high = atoi(var.t.a.high.value);
    		     int ele_size;
    		     TOKEN ele_type;
    		     ele_type = var.t.a.ele_type;
    		     if(ele_type  == INTEGER ) ele_size = int_size;
    		     else if(ele_type == REAL) ele_size = real_size;
    		     else ele_size = bool_size;    		     
        		width = arr_base_size+(high-low+1)*ele_size;
        	}
        	else width = arr_base_size;

        }
        else{
        	width = arr_base_size+2*int_size;
        }
	}
	s_begin = width;
	while(s_begin>0) n_b++, s_begin = s_begin/10;
	printf("%d",width);
	while(n_b<10) printf(" "),n_b++;
	if(type == ARRAY) printf("yes    ");
	else printf("no     ");
	if(type == ARRAY && var.is_static == true) printf("static    ");
	else if(type == ARRAY && var.is_static == false) printf("dynamic   ");
	else printf("--------  ");
	if(type == ARRAY){
		printf("[");
		if(var.is_static){
			low = atoi(var.t.a.low.value);
			s_begin = low;
			while(s_begin>0) n_b++, s_begin = s_begin/10;
	        printf("%d",low);
	        while(n_b<4) printf(" "),n_b++;
			printf(",");
			high = atoi(var.t.a.high.value);
			s_begin = high;
			while(s_begin>0) n_b++, s_begin = s_begin/10;
	        printf("%d",high);
		    printf("]    ");		

		}
		else printf("%s,%s]   ",var.t.a.low.value,var.t.a.high.value);		
	}
    else printf("--------  ");
    if(type == INTEGER) printf("INTEGER    ");
    else if(type == REAL) printf("REAL       ");
    else if(type == BOOLEAN) printf("BOOLEAN    ");
    else {
    	type = var.t.a.ele_type;
    	if(type == INTEGER) printf("INTEGER    ");
        else if(type == REAL) printf("REAL       ");
        else if(type == BOOLEAN) printf("BOOLEAN    ");
    }
    s_begin = var.offset;
    n_b=0;
    while(s_begin>0) n_b++, s_begin = s_begin/10;
	printf("%d",var.offset);
	while(n_b<10) printf(" "),n_b++;
	printf("%d",level);
	printf("\n----------------------------------------------------------------------------------------------------------------------------\n");
}


void print_arr_var(struct var_def var, bool local){
	if(var.tag == 1) return;
	int count = 0;
	int low, high;
	for(int i = 0; ((i < max_var_len) && var.module_name[i]!='\0');i++){
		printf("%c", var.module_name[i]);
		count++;
	}
	while(count < (max_var_len+1)) printf(" "), count++;

	int n_b = 0, n_e =0;
	int s_begin = var.scope_begin, s_end = var.scope_end;
	while(s_begin>0) n_b++, s_begin = s_begin/10;
	while(s_end>0) n_e++, s_end  = s_end/10;
	printf("%d",var.scope_begin);
	while(n_b<3) printf(" "), n_b++;
	printf("-");
	printf("%d", var.scope_end);
	while(n_e <10) printf(" "),n_e++;

	count = 0;
	for(int i = 0; ((i < max_var_len) && var.v_name[i]!='\0');i++){
		printf("%c", var.v_name[i]);
		count++;
	}
	while(count < (max_var_len+1)) printf(" "), count++;

	if(var.is_static == true) printf("static      ");
	else printf("dynamic     ");

	if(var.is_static){
			low = atoi(var.t.a.low.value);
			s_begin = low;
			while(s_begin>0) n_b++, s_begin = s_begin/10;
	        printf("[%d",low);
	        while(n_b<4) printf(" "),n_b++;
			printf(",");
			high = atoi(var.t.a.high.value);
			s_begin = high;
			while(s_begin>0) n_b++, s_begin = s_begin/10;
	        printf("%d",high);
	        while(n_b<4) printf(" "),n_b++;
		    printf("]     ");			
		}
	else printf("[%s,%s]   ",var.t.a.low.value,var.t.a.high.value);	

	TOKEN type = var.t.a.ele_type;
	if(type == INTEGER) printf("INTEGER ");
    else if(type == REAL) printf("REAL    ");
    else if(type == BOOLEAN) printf("BOOLEAN ");

    printf("\n----------------------------------------------------------------------------------------------------------------------------\n");	
}




void print_scope(s_scope * inner, int level, int option){
    v_node * p_var;
    for(int i=0;i<hash_size;i++){
      p_var = inner->hash_var[i];
      while(p_var != NULL){
      	if(option == 1) print_var(p_var->hash_var,level, true);
      	else print_arr_var(p_var->hash_var, true);
      	p_var = p_var->next;
      }
    }
}


void print_list(v_list * list, int option){
  while(list!= NULL){
    if(option == 1) print_var(list->v,0, false);
    else print_arr_var(list->v,false);
  	list = list->next;
  }
}

void print_statements(ast_node * root, int level, int option){
	if(root==NULL) return;
	while(root!=NULL){
		if(root->is_leaf == 0 && root->n.NL.nt == condionalStmt){
			print_scope(root->table_ptr.inner_ptr, level, option);
			ast_node* temp = root->child->next;
			if(temp!=NULL && temp->is_leaf == 0 && temp->n.NL.nt == caseStmts){
				ast_node * ptr = temp->child;
				while(ptr!=NULL){
					if(ptr->is_leaf == 0 && ptr->n.NL.nt == statements) print_statements(ptr->child,level+1,option);
				 ptr = ptr->next;
				}
			 temp = temp->next;
			}
			if(temp!=NULL && temp->is_leaf==0)print_statements(temp->child->child,level+1,option);
		}
		else if(root->is_leaf==0 && root->n.NL.nt ==iterativeStmt){
			print_scope(root->table_ptr.inner_ptr,level, option);
			if(root->is_leaf== 0 && strcmp(root->name,"FOR")==0)print_statements(root->child->next->next->child,level+1,option);
			else print_statements(root->child->next->child,level+1,option);
		}
		root = root->next;
	}
}




void printSymbolTable(ast_node * root){
 if(root == NULL) return;
 printf("PRINTING SYMBOL TABLE\n");
 printf("----------------------------------------------------------------------------------------------------------------------------\n");
 if(root!=NULL && root->is_leaf == 0 && root->n.NL.nt == program) root = root->child;
 if(root!=NULL && root->is_leaf ==0 && root->n.NL.nt == moduleDeclarations) root = root->next;
 if(root!= NULL && root->is_leaf == 0 && root->n.NL.nt == otherModules){
 	ast_node * temp = root->child;
 	while(temp!=NULL){
 		if(temp->table_ptr.fun_ptr!=NULL){
 		print_list(temp->table_ptr.fun_ptr->hash_f.input,1);
 		print_list(temp->table_ptr.fun_ptr->hash_f.output,1);
 		print_scope(temp->table_ptr.fun_ptr->hash_f.def,1,1);
 		ast_node* ptr = temp->child;
 		while(ptr!=NULL && (ptr->is_leaf || (ptr->is_leaf!=0 && ptr->n.NL.nt!=statements))) ptr = ptr->next;
 		print_statements(ptr->child,1,1);
 	   }
 	   temp = temp->next;
 	}
 	root=root->next;
 }
 if(root!=NULL && root->is_leaf==0 && root->n.NL.nt == statements){
 	ast_node* temp = root;
 	if(temp->table_ptr.fun_ptr!=NULL){
 	print_scope(temp->table_ptr.fun_ptr->hash_f.def,1,1);
 	print_statements(temp->child,2,1);
     }
 	root=root->next;
 }
 if(root!=NULL && root->is_leaf==0 && root->n.NL.nt==otherModules){
 	ast_node * temp = root->child;
 	while(temp!=NULL){
 		if(temp->table_ptr.fun_ptr!= NULL){
 		print_list(temp->table_ptr.fun_ptr->hash_f.input,1);
 		print_list(temp->table_ptr.fun_ptr->hash_f.output,1);
 		print_scope(temp->table_ptr.fun_ptr->hash_f.def,1,1);
 		ast_node* ptr = temp->child;
 		while(ptr!=NULL && (ptr->is_leaf || (ptr->is_leaf!=0 && ptr->n.NL.nt!=statements))) ptr = ptr->next;
 		print_statements(ptr->child,2,1);
 	   }
 	   temp = temp->next;
 	}
 }
}




void printArrayVar(ast_node * root){
	if(root == NULL) return;
 printf("PRINTING ARRAY VARIABLES\n");
 printf("----------------------------------------------------------------------------------------------------------------------------\n");
 if(root!=NULL && root->is_leaf == 0 && root->n.NL.nt == program) root = root->child;
 if(root!=NULL && root->is_leaf ==0 && root->n.NL.nt == moduleDeclarations) root = root->next;
 if(root!= NULL && root->is_leaf == 0 && root->n.NL.nt == otherModules){
 	ast_node * temp = root->child;
 	while(temp!=NULL){
 		if(temp->table_ptr.fun_ptr!=NULL){
 		print_list(temp->table_ptr.fun_ptr->hash_f.input,2);
 		print_list(temp->table_ptr.fun_ptr->hash_f.output,2);
 		print_scope(temp->table_ptr.fun_ptr->hash_f.def,1,2);
 		ast_node* ptr = temp->child;
 		while(ptr!=NULL && (ptr->is_leaf || (ptr->is_leaf!=0 && ptr->n.NL.nt!=statements))) ptr = ptr->next;
 		print_statements(ptr->child,1,2);
 	   }
 	   temp = temp->next;
 	}
 	root=root->next;
 }
 if(root!=NULL && root->is_leaf==0 && root->n.NL.nt == statements){
 	ast_node* temp = root;
 	if(temp->table_ptr.fun_ptr!=NULL){
 	print_scope(temp->table_ptr.fun_ptr->hash_f.def,1,2);
 	print_statements(temp->child,2,2);
     }
 	root=root->next;
 }
 if(root!=NULL && root->is_leaf==0 && root->n.NL.nt==otherModules){
 	ast_node * temp = root->child;
 	while(temp!=NULL){
 		if(temp->table_ptr.fun_ptr!= NULL){
 		print_list(temp->table_ptr.fun_ptr->hash_f.input,2);
 		print_list(temp->table_ptr.fun_ptr->hash_f.output,2);
 		print_scope(temp->table_ptr.fun_ptr->hash_f.def,1,2);
 		ast_node* ptr = temp->child;
 		while(ptr!=NULL && (ptr->is_leaf || (ptr->is_leaf!=0 && ptr->n.NL.nt!=statements))) ptr = ptr->next;
 		print_statements(ptr->child,2,2);
 	   }
 	   temp = temp->next;
 	}
 }

}



void print_activation_record(ast_node * root){
  if(root == NULL) return;
  ast_node * temp ;
  ast_node * ptr = root->child;
  if(ptr!= NULL && ptr->n.NL.nt == moduleDeclarations) ptr = ptr->next;
  if(ptr!= NULL && ptr->is_leaf == 0 && ptr->n.NL.nt == otherModules){
  	temp = ptr->child;
  	while(temp!=NULL){
  		int count = 0;
  		char ch = temp->child->n.L.t.value[0];
  		while(ch!= '\0'){
  			printf("%c",ch);
  			count++;
  			ch = temp->child->n.L.t.value[count];
  		}
  		while(count <  max_var_len +1)printf(" "), count++;
  	printf("%d\n", temp->off_end_local);
  	temp = temp->next;
  	}
  	ptr = ptr->next;
  }
  if(ptr!= NULL && ptr->is_leaf == 0  && ptr->n.NL.nt == statements){
  	printf("DRIVER");
  	int count = 6;
  	while(count<max_var_len+1) printf(" "), count++;
  	printf("%d\n", ptr->off_end_local);
  	ptr = ptr->next;
  }
  if(ptr!=NULL && ptr->is_leaf ==0 && ptr->n.NL.nt == otherModules){
  	temp = ptr->child;
  	while(temp!=NULL){
  		int count = 0;
  		char ch = temp->child->n.L.t.value[0];
  		while(ch!= '\0'){
  			printf("%c",ch);
  			count++;
  			ch = temp->child->n.L.t.value[count];
  		}
  		while(count <  max_var_len +1)printf(" "), count++;
  	printf("%d\n", temp->off_end_local);
  	temp = temp->next;
  	}
  }
}



