//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "symbol_table.h"
#include "ast.h"
#include "semantic_analyzer.h"



int set_dec_stmt(ast_node * temp, int off_count,s_scope* inner_ptr ){

    ast_node * id_ptr = temp->child;
    	if(id_ptr->is_leaf == 0 && id_ptr->n.NL.nt == idList){
    		id_ptr = id_ptr->child;
    		while(id_ptr!= NULL){
    		 int pos = compute_hash_sk(id_ptr->n.L.t.value);
    		 v_node * v_var = inner_ptr->hash_var[pos];
    		 while(v_var != NULL && strcmp(id_ptr->n.L.t.value, v_var->v_name)!=0) v_var = v_var->next;
    		 if(v_var != NULL) {
    		 	v_var->hash_var.offset = off_count;
    		 	int c;
    		 	if(temp->child->next->is_leaf){
    		 	  if(temp->child->next->n.L.t.terminal == INTEGER) c = int_size;
    	          else if(temp->child->next->n.L.t.terminal == REAL) c = real_size;
    	          else c = bool_size;
    		 	}
    		 	else{
    		 	 c = arr_base_size;
    	         if(temp->child->next->child->child->n.L.t.terminal == NUM && temp->child->next->child->child->next->n.L.t.terminal == NUM){
    		     int low,high;
    		     low = atoi(temp->child->next->child->child->n.L.t.value);
    		     high = atoi(temp->child->next->child->child->next->n.L.t.value);
    		     int ele_size;
    		     TOKEN ele_type;
    		     ele_type = temp->child->next->child->next->n.L.t.terminal;
    		     if(ele_type  == INTEGER ) ele_size = int_size;
    		     else if(ele_type == REAL) ele_size = real_size;
    		     else ele_size = bool_size;
    		     c+= (high-low+1)*ele_size;
    		 	 }
    		    }
    		    off_count+=c;
    	     }
    	      id_ptr = id_ptr->next;
            }
        }
   return off_count;
}


// takes pointer to stmts, inserts starting from offset off_count, and increments it and return last offset 

int set_stmts(ast_node * temp, int off_count, s_scope* inner_ptr){
	if(temp == NULL) return off_count;
	temp = temp->child;
	while(temp!= NULL){
    	if(temp->is_leaf == 0 && temp->n.NL.nt == declareStmt) off_count =  set_dec_stmt(temp,off_count, inner_ptr);
     	

     	else if(temp->is_leaf == 0 && temp->n.NL.nt == condionalStmt){
    		ast_node * p = temp->child->next;
    		if(p!=NULL && p->is_leaf == 0 && p->n.NL.nt == caseStmts){
    			ast_node * case_ptr = p->child;
    			while(case_ptr!= NULL){
    			  while(case_ptr!=NULL && case_ptr->is_leaf)case_ptr=case_ptr->next;
    			  if(case_ptr!= NULL){
    			    off_count = set_stmts(case_ptr,off_count,temp->table_ptr.inner_ptr);
    			    case_ptr = case_ptr->next;
    			  }
    			 }
    			 p=p->next;
    		}

    		if(p!=NULL && p->is_leaf == 0){
    			off_count = set_stmts(p->child,off_count,temp->table_ptr.inner_ptr);
    		}
    	}


    	else if(temp->is_leaf == 0 && temp->n.NL.nt == iterativeStmt){
    		if(strcmp(temp->name, "FOR")==0){
    			off_count = set_stmts(temp->child->next->next,off_count,temp->table_ptr.inner_ptr);
    		}
    		else{
    			off_count = set_stmts(temp->child->next,off_count, temp->table_ptr.inner_ptr);
    		}
    	}

     temp = temp->next;
    }

    return off_count;
}


// if print_sym = true then arr_base size = 8 else arr_base_size = 1

void offset(ast_node * root, bool print_sym){
    if(print_sym) {
        arr_base_size = 1;
        int_size = 2;
        real_size=4;
        bool_size = 1;
    }
    else {
        arr_base_size = 8;
        int_size = 8;
        real_size = 8;
        bool_size = 8;
     }
  if(root == NULL) return ;
  if(root->is_leaf == 0 && root->n.NL.nt == module){
    if(root->table_ptr.fun_ptr == NULL) return;
    int off_count = 0;
    ast_node * ptr = root->child->next;
    if(ptr!= NULL && ptr->is_leaf == 0 && ptr->n.NL.nt == input_plist){
       ast_node * temp = ptr->child;
       v_list * v_ptr  = root->table_ptr.fun_ptr->hash_f.input;
       while(temp!= NULL){         
         while(v_ptr!= NULL && strcmp(temp->n.L.t.value, v_ptr->v.v_name)!= 0) v_ptr = v_ptr->next;
         if(v_ptr!= NULL) {
         	v_ptr->v.offset = off_count;
         	int c;
         	if(temp->next->is_leaf){
         		if(temp->next->n.L.t.terminal == INTEGER) c = int_size;
         		else if(temp->next->n.L.t.terminal == REAL) c = real_size;
         		else c = bool_size;
         	}
         	else{
         		c = arr_base_size;
         		c = c+2*int_size;
         	}
            off_count += c;
          }
        v_ptr = v_ptr->next;
       	temp = temp->next->next;
       }
     ptr = ptr->next;
    }

    if(ptr!= NULL && ptr->is_leaf == 0 && ptr->n.NL.nt == output_plist){
       ast_node * temp = ptr->child;
       v_list * v_ptr  = root->table_ptr.fun_ptr->hash_f.output;
       while(temp!= NULL){         
         while(v_ptr!= NULL && strcmp(temp->n.L.t.value, v_ptr->v.v_name)!= 0) v_ptr = v_ptr->next;
         if(v_ptr!= NULL) {
         	v_ptr->v.offset = off_count;
         	int c;
         	if(temp->next->is_leaf){
         		if(temp->next->n.L.t.terminal == INTEGER) c = int_size;
         		else if(temp->next->n.L.t.terminal == REAL) c = real_size;
         		else c = bool_size;
         	}
         	else{
         		c = arr_base_size;
         		c+=2*int_size;
         	}
            off_count += c;
          }
        v_ptr = v_ptr->next;
       	temp = temp->next->next;
       }
     ptr = ptr->next;
     root->off_end_param = off_count;
    }

   if(ptr!= NULL && ptr->is_leaf == 0 && ptr->n.NL.nt == statements){
        if(ptr->table_ptr.fun_ptr!= NULL){
   	    off_count = 0;
    	off_count = set_stmts(ptr,off_count,root->table_ptr.fun_ptr->hash_f.def);
    }
   }
    root->off_end_local = off_count;
    return offset(root->next, print_sym);
  }


//case of driver module with no module ast node

  else if(root->is_leaf == 0 && root->n.NL.nt == statements && root->parent->n.NL.nt == program){ 
  	int off_count = 0;
  	off_count = set_stmts(root,off_count, root->table_ptr.fun_ptr->hash_f.def);
  	root->off_end_local = off_count;
    root->off_end_param = 0;
    offset(root->next, print_sym);
  }


  offset(root->child, print_sym);
  offset(root->next, print_sym);	
  return;
}