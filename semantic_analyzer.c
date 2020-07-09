//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "ast.h"
#include "symbol_table.h"
#include "semantic_analyzer.h"


char * termx[] = {"eps","$","NUM","RNUM","INTEGER","REAL","ID","BOOLEAN","OF","ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","RECORD",
         "TAGGED","UNION","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR",
         "FOR","IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF",
         "ENDDEF","DRIVERDEF","DRIVERENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK"};


bool check_assign(ast_node * root){
  if(root == NULL) return false;
  if(root->is_leaf == 0 && root->n.NL.nt == var_id_num){
  	 union s_ptr s;
  	 if(root->child->scope_tag ==1) s.inner_ptr = root->child->table_ptr.inner_ptr;
     else if(root->child->scope_tag==0) s.fun_ptr = root->child->table_ptr.fun_ptr;
     int pos = compute_hash_sk(root->child->n.L.t.value);
     v_node * node;
     if(root->child->scope_tag==1){
       node = s.inner_ptr->hash_var[pos];
       while(node!= NULL && strcmp(node->v_name,root->child->n.L.t.value)!=0) node=node->next;
       if(node != NULL && node->hash_var.flag == true) return true;
       else return false;
     }
     else if(root->child->scope_tag==0){
     	v_list * node = s.fun_ptr->hash_f.input;
     	while(node!= NULL && strcmp(node->v.v_name,root->child->n.L.t.value)!=0) node=node->next;
     	if(node!= NULL && node->v.flag == true) return true;
     	node = s.fun_ptr->hash_f.output;
     	while(node!= NULL && strcmp(node->v.v_name,root->child->n.L.t.value)!=0) node=node->next;
     	if(node!= NULL && node->v.flag == true) return true;
     	else return false;
     }
   }
 ast_node * ptr = root->child;
 while(ptr!= NULL){
   if(check_assign(ptr) == true) return true;
   ptr = ptr->next;
 }
 return false;
}

char * ntermx[] = {"program", "moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1",
        "output_plist","N2","dataType","range_arrays","type","moduleDef","statements","statement","ioStmt","boolConstt","var_id_num",
        "var","whichid","simpleStmt","assigmentStmt","whichStmt","lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional",
        "idList","N3","expression","U","new_NT","unary_op","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term",
        "N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt","caseStmts","N9","value","default",
        "iterativeStmt","range"};



void semantic_analyzer(ast_node * root){
  if(root == NULL) return;
  

 if(root->is_leaf == 0 && root->n.NL.nt == program) return semantic_analyzer(root->child);
 
  else if(root->is_leaf == 0 && root->n.NL.nt == moduleDeclarations) return semantic_analyzer(root->next);

  else if(root->is_leaf == 0 && root->n.NL.nt == otherModules){
  	ast_node * ptr = root->child;
  	while(ptr != NULL){
       semantic_analyzer(ptr);
       ptr = ptr->next;
  	} 
  	return semantic_analyzer(root->next);
  }

  else if(root->is_leaf == 0 && root->n.NL.nt == statements){
    ast_node * ptr = root->child;
    while(ptr!= NULL){
       semantic_analyzer(ptr);
       ptr = ptr->next;
  	} 
  	return semantic_analyzer(root->next);
    }
 
  else if(root->is_leaf == 0 && root->n.NL.nt == module){
    if(root->table_ptr.fun_ptr==NULL) return;
  	ast_node * temp =  root->child;
  	int line_no = root->child->n.L.t.line_number_var;
  	while(temp!= NULL && ( temp->is_leaf || temp->n.NL.nt != statements)) temp = temp->next;
  	if(temp!= NULL && temp->is_leaf == 0  && temp->n.NL.nt == statements) semantic_analyzer(temp);
    int pos = compute_hash_sk(root->child->n.L.t.value);
  	struct sym_func_node * ptr = hash_table[pos];
  	while(ptr!= NULL && strcmp(root->child->n.L.t.value, ptr->f_name)!= 0) ptr= ptr->next;
  	if( ptr!= NULL && ptr->both == false && ptr->has_call == true){
  		sem_err = 1;
  		printf("SEMANTIC ERROR : Module %s has both declaration and definition before every call, so redundancy and module is at line number %d\n",root->child->n.L.t.value,line_no);
        printf("------------------------------------------------------\n");
  	}
  	v_list* out = ptr->hash_f.output;
  	while(out!= NULL){
  	  if(out->v.flag == false){
  		sem_err = 1;
  		printf("SEMANTIC ERROR : Output variable %s of module is not assigned any value at line number %d\n",out->v.v_name,root->line_end);
        printf("------------------------------------------------------\n");  
  		}
  		out = out->next;
  	}
  	return ; 
  }	



  else if(root->is_leaf && strcmp("GET_VALUE", root->name)==0){
     union s_ptr s;
     ast_node * temp = root;
     if(temp->scope_tag==1) s.inner_ptr = temp->table_ptr.inner_ptr;
     else if(temp->scope_tag==0) s.fun_ptr = temp->table_ptr.fun_ptr;
     int pos = compute_hash_sk(temp->n.L.t.value);
     if(temp->scope_tag==1){
     	v_node * v ;
     	v = s.inner_ptr->hash_var[pos];
     	while(v!=NULL && strcmp(temp->n.L.t.value,v->v_name)!= 0) v = v->next;
     	if(v!= NULL)v->hash_var.flag = true;
     }
     else if(temp->scope_tag==0){
     	v_list * v_out = s.fun_ptr->hash_f.output; 
     	while(v_out !=NULL && strcmp(temp->n.L.t.value, v_out->v.v_name)!=0) v_out =v_out->next;
     	if(v_out != NULL) v_out->v.flag = true;
      v_out = s.fun_ptr->hash_f.input;
      while(v_out !=NULL && strcmp(temp->n.L.t.value, v_out->v.v_name)!=0) v_out =v_out->next;
      if(v_out != NULL) v_out->v.flag = true;
     }
     return;
  }


  else if(root->is_leaf ==0 && root->n.NL.nt == assignmentStmt){
  	ast_node * temp = root;
  	int line_no = temp->child->n.L.t.line_number_var;
  	ast_node * c = temp->child;
  	ast_node * rhs = c->next->next;
    if(rhs->is_leaf==1 && rhs->n.L.t.terminal==ASSIGNOP)rhs = rhs->next;
  	union type lhs_type, rhs_type;
  	int lhs_tag, rhs_tag;
  	if(rhs->tag==1) {
  		rhs_tag = rhs->tag;
  		rhs_type.basic_type = rhs->t.basic_type;
      lhs_tag = c->tag;
  		if(c->tag) lhs_type.basic_type = c->t.basic_type;
  		//else lhs_type.basic_type = c->t.a.ele_type;
      // if(c->tag==1)printf("in1 %d  %s %d %s\n", rhs_tag, termx[rhs->t.basic_type],lhs_tag, termx[c->t.basic_type]);
  		if((c->tag==0 && c->next->n.L.t.terminal==ASSIGNOP) || (c->tag==1 && (c->t.basic_type!=rhs->t.basic_type))||(c->tag==0 && c->next->n.L.t.terminal!=ASSIGNOP && c->t.a.ele_type!=rhs->t.basic_type)){
  			sem_err = 1;
  			printf("SEMANTIC ERROR : Type of expression on Left and Right side don't match at line number %d \n ", line_no);
  			printf("------------------------------------------------------\n");
  		}
  	}
  	else if(rhs->tag == 0){
  		lhs_tag  = c->tag;
        if(c->tag) lhs_type.basic_type = c->t.basic_type;
        else lhs_type.a = c->t.a;
        rhs_tag = rhs->tag;
        if(rhs->tag) rhs_type.basic_type = rhs->t.basic_type;
  		else rhs_type.a = rhs->t.a;
  		if(lhs_tag == 1 || (lhs_tag==0 && c->next->n.L.t.terminal!=ASSIGNOP)){
  			sem_err = 1;
  			printf("SEMANTIC ERROR : Type of expression on Left and Right side don't match at line number %d \n ", line_no);
  			printf("------------------------------------------------------\n");
  		}
  		else if(lhs_tag == rhs_tag && rhs_tag == 0 && c->next->n.L.t.terminal==ASSIGNOP && lhs_type.a.low.terminal == NUM && lhs_type.a.high.terminal==NUM && rhs_type.a.low.terminal==NUM && rhs_type.a.high.terminal== NUM) {
  			if(strcmp(lhs_type.a.low.value, rhs_type.a.low.value)!=0 || strcmp(lhs_type.a.high.value, rhs_type.a.high.value)!=0){
  				sem_err = 1;
  				printf("SEMANTIC ERROR : Assigining 2 static arrays but arrays are incompatible at line number %d \n",line_no);
  				printf("------------------------------------------------------\n");
  			}
  		}
  	}
     union s_ptr s;
     temp=temp->child;
     if(temp->scope_tag == 1)s.inner_ptr = temp->table_ptr.inner_ptr;
     else if(temp->scope_tag==0) s.fun_ptr = temp->table_ptr.fun_ptr;
     int pos = compute_hash_sk(temp->n.L.t.value);
     if(temp->scope_tag==1){
     	v_node * v ;
     	v = s.inner_ptr->hash_var[pos];
     	while(v!=NULL && strcmp(temp->n.L.t.value,v->v_name)!= 0) v = v->next;
     	if(v!= NULL)v->hash_var.flag = true;
     }
     else if(temp->scope_tag==0){
     	v_list * v_out = s.fun_ptr->hash_f.output; 
     	while(v_out !=NULL && strcmp(temp->n.L.t.value, v_out->v.v_name)!=0) v_out =v_out->next;
     	if(v_out != NULL) v_out->v.flag = true;
      v_out = s.fun_ptr->hash_f.input;
      while(v_out !=NULL && strcmp(temp->n.L.t.value, v_out->v.v_name)!=0) v_out =v_out->next;
      if(v_out != NULL) v_out->v.flag = true;
     } 
     return ;  
  }


 else if(root->is_leaf == 0 && root->n.NL.nt == moduleReuseStmt){
    ast_node * ptr =  root->child;
    if(ptr->is_leaf ==0) ptr= ptr->next;
    int pos = compute_hash_sk(ptr->n.L.t.value);
    struct sym_func_node * mod = hash_table[pos];
    int line_no = ptr->n.L.t.line_number_var;
  while(mod!= NULL && strcmp(ptr->n.L.t.value, mod->f_name)!=0) mod = mod->next;
  if(mod!= NULL){
    ast_node * o;
    v_list * out_ptr=NULL;
    out_ptr = mod->hash_f.output;
   if(root->child->is_leaf == 0 && root->child->n.NL.nt == optional){
    o = root->child->child->child;
    while(o!= NULL  && out_ptr != NULL){
     union s_ptr s;
     if(o->scope_tag==1)s.inner_ptr = o->table_ptr.inner_ptr;
     else if(o->scope_tag==0)s.fun_ptr = o->table_ptr.fun_ptr;
     int pos = compute_hash_sk(o->n.L.t.value);
     if(o->scope_tag==1){
     	v_node * v ;
     	v = s.inner_ptr->hash_var[pos];
     	while(v!=NULL && strcmp(o->n.L.t.value,v->v_name)!= 0) v = v->next;
     	if(v!= NULL)v->hash_var.flag = true;
      }
     else if(o->scope_tag==0) {
      v_list * v_out = s.fun_ptr->hash_f.output; 
      while(v_out !=NULL && strcmp(o->n.L.t.value, v_out->v.v_name)!=0) v_out =v_out->next;
      if(v_out != NULL) v_out->v.flag = true;
      v_out = s.fun_ptr->hash_f.input; 
      while(v_out !=NULL && strcmp(o->n.L.t.value, v_out->v.v_name)!=0) v_out =v_out->next;
      if(v_out != NULL) v_out->v.flag = true;
      }  
     if(o->tag != out_ptr->v.tag && o->tag!=-1){
    	sem_err = 1;
    	printf("SEMANTIC ERROR : Function return type doesn't match the type of variable being assigned at line number %d \n",line_no);
    	printf("------------------------------------------------------\n");
     }
     else{
    	if(o->tag == 1 && o->t.basic_type != out_ptr->v.t.basic_type){
    	  sem_err = 1;
    	  printf("SEMANTIC ERROR : Function return type doesn't match the type of variable being assigned at line number %d \n",line_no);
          printf("------------------------------------------------------\n");
    		}
    	else if(o->tag == 0 && o->t.a.low.terminal == NUM && o->t.a.high.terminal == NUM && out_ptr->v.t.a.low.terminal == NUM && out_ptr->v.t.a.high.terminal == NUM && (strcmp(o->t.a.low.value,out_ptr->v.t.a.low.value)!=0 || strcmp(o->t.a.high.value,out_ptr->v.t.a.high.value)!=0)){
    	  sem_err = 1;
    	  printf("SEMANTIC ERROR : Function return type doesn't match the type of variable being assigned at line number %d \n",line_no);
    	  printf("------------------------------------------------------\n");
    	 }
      }
    o = o->next;
    out_ptr= out_ptr->next;
    }
    if(o!= NULL || out_ptr != NULL){
    	sem_err = 1;
    	printf("SEMANTIC ERROR : Function return number of parameters doesn't match the number of variable being assigned at line number %d \n",line_no);
    	printf("------------------------------------------------------\n");
     }
   while(o!= NULL){
   	union s_ptr s;
    if(o->scope_tag==1)s.inner_ptr = o->table_ptr.inner_ptr;
    else if(o->scope_tag==0) s.fun_ptr = o->table_ptr.fun_ptr;
    int pos = compute_hash_sk(o->n.L.t.value);
    if(o->scope_tag==1){
     	v_node * v ;
     	v = s.inner_ptr->hash_var[pos];
     	while(v!=NULL && strcmp(o->n.L.t.value,v->v_name)!= 0) v = v->next;
     	if(v!= NULL)v->hash_var.flag = true;
     }
    else if(o->scope_tag==0){
     	v_list * v_out = s.fun_ptr->hash_f.output; 
     	while(v_out !=NULL && strcmp(o->n.L.t.value, v_out->v.v_name)!=0) v_out =v_out->next;
     	if(v_out != NULL) v_out->v.flag = true;
      v_out = s.fun_ptr->hash_f.input; 
      while(v_out !=NULL && strcmp(o->n.L.t.value, v_out->v.v_name)!=0) v_out =v_out->next;
      if(v_out != NULL) v_out->v.flag = true;
       }
   o = o->next;
   }
  }
 else if(root->child->is_leaf== 1 && root->child->n.L.t.terminal == ID){
 	if(mod->hash_f.output != NULL){
 		sem_err = 1;
    	printf("SEMANTIC ERROR : Function return number of parameters doesn't match the number of variable being assigned at line number %d \n",line_no);
    	printf("------------------------------------------------------\n");
 	}
 }

  out_ptr = mod->hash_f.input;

   if(ptr->next!= NULL){
    o = ptr->next->child;
   while(o!= NULL  && out_ptr != NULL){
    	if(o->tag != out_ptr->v.tag && o->tag!=-1){
   			sem_err = 1;
 			printf("SEMANTIC ERROR : Function input type doesn't match the type of variable being passed at line number %d \n",line_no);
  			printf("------------------------------------------------------\n");
    	}
    	else{
    		if(o->tag == 1 && o->t.basic_type != out_ptr->v.t.basic_type){
    		  sem_err = 1;
    		  printf("SEMANTIC ERROR : Function input type doesn't match the type of variable being passed at line number %d \n",line_no);
    		  printf("------------------------------------------------------\n");
   			}
   			else if(o->tag == 0 && o->t.a.low.terminal == NUM && o->t.a.high.terminal == NUM && out_ptr->v.t.a.low.terminal == NUM && out_ptr->v.t.a.high.terminal == NUM && (strcmp(o->t.a.low.value,out_ptr->v.t.a.low.value)!=0 || strcmp(o->t.a.high.value,out_ptr->v.t.a.high.value)!=0)){
    		  sem_err = 1;
   			  printf("SEMANTIC ERROR : Function input type doesn't match the type of variable being passed at line number %d \n",line_no);
    		  printf("------------------------------------------------------\n");
   			}
   			else if(o->tag == 0 && o->t.a.ele_type != out_ptr->v.t.a.ele_type){
    	         sem_err = 1;
    	         printf("SEMANTIC ERROR : Function array input variable element type doesn't match the type of variable being passes at line number %d \n",line_no);
    	         printf("------------------------------------------------------\n");
    	    }
    	    else if(o->tag == 0 && o->t.a.low.terminal == NUM && out_ptr->v.t.a.low.terminal == NUM && strcmp(o->t.a.low.value,out_ptr->v.t.a.low.value)!=0){
    	    	 sem_err = 1;
    	         printf("SEMANTIC ERROR : Function array input variable range value doesn't match the type of variable being passes at line number %d \n",line_no);
    	         printf("------------------------------------------------------\n");
    	    }
    	    else if(o->tag == 0 && o->t.a.high.terminal == NUM && out_ptr->v.t.a.high.terminal == NUM && strcmp(o->t.a.high.value,out_ptr->v.t.a.high.value)!=0){
    	    	 sem_err = 1;
    	         printf("SEMANTIC ERROR : Function array input variable range value doesn't match the type of variable being passes at line number %d \n",line_no);
    	         printf("------------------------------------------------------\n");
    	    }
 		}
    o = o->next;
  	out_ptr= out_ptr->next;
   }
    if(o!= NULL || out_ptr != NULL){
    	sem_err = 1;
   		printf("SEMANTIC ERROR : Function input number of parameters doesn't match the number of variable being passed at line number %d \n",line_no);
   		printf("------------------------------------------------------\n");
   	}
   }
   else{
      if(out_ptr!=NULL){
        sem_err = 1;
        printf("SEMANTIC ERROR : Function input number of parameters doesn't match the number of variable being passed at line number %d \n",line_no);
        printf("------------------------------------------------------\n");
      }
   }
 }
}





  else if(root->is_leaf ==0 && root->n.NL.nt == condionalStmt){
  	 int line_no = root->child->n.L.t.line_number_var;
     ast_node * ptr = root->child;
     if(ptr->tag == 0 || (ptr->tag && ptr->t.basic_type == REAL)){
     	sem_err = 1;
   		printf("SEMANTIC ERROR : In switch construct ccondition variable is not of type Integer or BOOLEAN at line number %d \n",line_no);
   		printf("------------------------------------------------------\n");
     }
     else{
       ast_node * c_ptr  = ptr->next;
       TOKEN t = ptr->t.basic_type;
       ptr = c_ptr->child;
       while(ptr!= NULL){
       	line_no = ptr->n.L.t.line_number_var;
       	if(ptr->tag!=-1 && ((t == INTEGER && ptr->n.L.t.terminal != NUM) || (t==BOOLEAN && ptr->n.L.t.terminal != TRUE && ptr->n.L.t.terminal!= FALSE))){
          sem_err = 1;
   		  printf("SEMANTIC ERROR : Case statement value type doesn't match type of condition variable at line number %d \n",line_no);
   		  printf("------------------------------------------------------\n");
       	}
        ptr=ptr->next;
       	if(ptr->is_leaf == 0 && ptr->n.NL.nt == statements) {
       		semantic_analyzer(ptr);
       		ptr = ptr->next;
       	}
       }
       if(c_ptr->next!=NULL){
         semantic_analyzer(c_ptr->next->child);
       }
       if(((t==INTEGER && c_ptr->next == NULL) ||(t == BOOLEAN && c_ptr->next!= NULL))&& root->child->tag!=-1){
       	line_no = root->line_end;
       	sem_err = 1;
   		printf("SEMANTIC ERROR : Default specifications doesn't match language requirements at line number %d \n",line_no);
   		printf("------------------------------------------------------\n");
       }    
     }
    return;
  }


 else if(root->is_leaf ==0 && root->n.NL.nt == iterativeStmt){
 	if(strcmp(root->name, "FOR") == 0){
 	   int line_no = root->child->n.L.t.line_number_var;
     bool flag_bef;
     union s_ptr s;
     if(root->child->scope_tag == 1 ) s.inner_ptr = root->child->table_ptr.inner_ptr;
     else if(root->child->scope_tag == 0) s.fun_ptr = root->child->table_ptr.fun_ptr;
     int pos = compute_hash_sk(root->child->n.L.t.value);
     if(root->child->scope_tag==1){
       v_node * node = s.inner_ptr->hash_var[pos];
       while(node!= NULL && strcmp(node->v_name,root->child->n.L.t.value)!=0) node=node->next;
       if(node!= NULL) flag_bef = node->hash_var.flag, node->hash_var.flag = false;
     }
     else if(root->child->scope_tag==0){
      v_list * list = s.fun_ptr->hash_f.input;
      while(list!= NULL && strcmp(root->child->n.L.t.value, list->v.v_name)!= 0) list=list->next;
      if(list!=NULL) flag_bef = list->v.flag, list->v.flag = false;  
      else{
        list = s.fun_ptr->hash_f.output;
        while(list!= NULL && strcmp(root->child->n.L.t.value, list->v.v_name)!= 0) list=list->next;
        if(list!=NULL) flag_bef = list->v.flag, list->v.flag = false;
      }
     }
       ast_node * ptr = root->child->next->next;
       semantic_analyzer(ptr);
       if(root->child->scope_tag==1) s.inner_ptr = root->child->table_ptr.inner_ptr;
       else if(root->child->scope_tag==0) s.fun_ptr = root->child->table_ptr.fun_ptr;
       if(root->child->scope_tag==1){
       v_node * node = s.inner_ptr->hash_var[pos];
       while(node!= NULL && strcmp(node->v_name,root->child->n.L.t.value)!=0) node=node->next;
       if(node!=NULL && node->hash_var.flag){
       	    sem_err = 1;
   		      printf("SEMANTIC ERROR : Loop variable assigned value inside for loop at line number %d \n",line_no);
   		      printf("------------------------------------------------------\n");
   		      return;
        }
       if(node!=NULL) node->hash_var.flag = flag_bef;
       }
       else if(root->child->scope_tag==0){
       	v_list * list = s.fun_ptr->hash_f.input;
       	while(list!= NULL && strcmp(root->child->n.L.t.value, list->v.v_name)!= 0) list=list->next;
        if(list!= NULL && list->v.flag){
       		sem_err = 1;
   		    printf("SEMANTIC ERROR : Loop variable assigned value inside for loop at line number %d \n",line_no);
   		    printf("------------------------------------------------------\n");
   		    return;
       	}
        if(list!=NULL) list->v.flag = flag_bef;
       	list = s.fun_ptr->hash_f.output;
       	while(list!= NULL && strcmp(root->child->n.L.t.value, list->v.v_name)!= 0) list=list->next;
        if(list!= NULL && list->v.flag){
       		sem_err = 1;
   		    printf("SEMANTIC ERROR : Loop variable assigned value inside for loop at line number %d \n",line_no);
   		    printf("------------------------------------------------------\n");
   		    return;
       	}
        if(list!=NULL) list->v.flag = flag_bef;
       }
       return;
 	 }
 	else{
      int line_no = root->line_begin;
      if(root->child->tag == 0 || (root->child->tag == 1 && root->child->t.basic_type!= BOOLEAN)){
      	sem_err = 1;
   		  printf("SEMANTIC ERROR : Type expression of condiition in while is not Boolean at line number %d \n",line_no);
   		  printf("------------------------------------------------------\n");
      }
      ast_node * ptr = root->child->next;
      semantic_analyzer(ptr);
      bool c = check_assign(root->child);
      if(c==false){
      	sem_err = 1;
   		  printf("SEMANTIC ERROR : No conditional variable used in while loop is assigned value  at line number %d \n",line_no);
   		  printf("------------------------------------------------------\n");
      }
      return;
 	}
 }

 return;

}
