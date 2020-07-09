//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "ast.h"
#include "symbol_table.h"
#include "semantic_analyzer.h"


/*// returns type as INTEGER REAL BOOLEAN ARRAY eps if type unknown
struct type_def{
 union type t;
 TOKEN tag;
};*/

struct type_def extract(ast_node * root){
  // printf("in\n");

  if(root->is_leaf==0 && root->n.NL.nt == arithmeticOrBooleanExpr){
  	ast_node * temp = root->child;
  	struct type_def t, t_prev;
  	t_prev.tag = eps;
  	int line_no;
  	while(temp!= NULL){
      if(temp->is_leaf==1){
        // printf("%d line1 %s \n", temp->n.L.t.line_number_var, temp->n.L.t.value);
        int tok = temp->n.L.t.terminal;
        if(tok == NUM) t.tag = INTEGER;
        else if(tok == RNUM) t.tag = REAL;
        else t.tag = BOOLEAN;
      }
      // printf("call arbool\n"),
  		else t = extract(temp);

  		if(t.tag == eps && t_prev.tag == eps) t_prev = t;
  		else if(t.tag == t_prev.tag && t.tag == BOOLEAN) t_prev = t;
  		else if((t.tag != t_prev.tag && t.tag!=eps && t_prev.tag != eps )||(t.tag == t_prev.tag && !(t.tag == BOOLEAN))) {
  			if(t.tag==ARRAY) printf("SEMANTIC ERROR : ARRAY used in arithmeticOrBooleanExpr at line number %d \n",line_no);
  			else printf("SEMANTIC ERROR : Type mismatch error in arithmeticOrBooleanExpr at line number %d \n",line_no);
  			printf("------------------------------------------------------\n");
  			sem_err = 1;
  			t_prev.tag = eps;
  		}
  		else if(t.tag!= eps && t_prev.tag== eps) t_prev = t;
  	  if(temp->next!= NULL) {
            line_no = temp->next->n.L.t.line_number_var;
  	    	temp = temp->next->next;
  	    }
  		else temp=temp->next;
  	}

  	return t_prev;
  }

  else if(root->is_leaf == 0 && root->n.NL.nt == AnyTerm){
  	ast_node * temp = root->child;
  	struct type_def t, t_prev;
  	t_prev.tag = eps;
  	int line_no;
  	while(temp!= NULL){
      if(temp->is_leaf==1){
        // printf("%d line2 %s \n", temp->n.L.t.line_number_var,temp->n.L.t.value);
        int tok = temp->n.L.t.terminal;
        if(tok == NUM) t.tag = INTEGER;
        else if(tok == RNUM) t.tag = REAL;
        else t.tag = BOOLEAN;
      }
      // printf("call anyterm\n"),
  		else t = extract(temp);
  		if(t.tag == eps && t_prev.tag == eps) t_prev = t;
  		else if(t.tag == t_prev.tag && (t.tag == REAL || t.tag== INTEGER)) t_prev = t;
  		else if((t.tag != t_prev.tag && t.tag!=eps && t_prev.tag != eps )||(t.tag == t_prev.tag && !(t.tag == INTEGER || t.tag == REAL))) {
  			if(t.tag==ARRAY) printf("SEMANTIC ERROR : ARRAY used in relational operator at line number %d \n",line_no);
  			else printf("SEMANTIC ERROR : Type mismatch error in relational operator at line number %d \n",line_no);
  			printf("------------------------------------------------------\n");
  			sem_err = 1;
  			t_prev.tag = eps;
  		}
  		else if(t.tag!= eps && t_prev.tag== eps) t_prev = t;
  	    if(temp->next!= NULL) {
  	    	line_no = temp->next->n.L.t.line_number_var;
  	    	temp = temp->next->next;
  	    }
  		else temp=temp->next;
  	}
  	if(root->child->next == NULL) return t_prev;
  	else if(t_prev.tag != eps) t_prev.tag = BOOLEAN;
  	return t_prev;
  }

  else if(root->is_leaf == 0 && root->n.NL.nt == arithmeticExpr){
  	ast_node * temp = root->child;
  	struct type_def t, t_prev;
  	t_prev.tag = eps;
  	int line_no;
  	while(temp!= NULL){
      if(temp->is_leaf==1){
        // printf("%d line3 %s \n", temp->n.L.t.line_number_var,temp->n.L.t.value);
        int tok = temp->n.L.t.terminal;
        if(tok == NUM) t.tag = INTEGER;
        else if(tok == RNUM) t.tag = REAL;
        else t.tag = BOOLEAN;
      }
      // printf("call arex\n"),
  		else t = extract(temp);
  		if(t.tag == eps && t_prev.tag == eps) t_prev = t;
  		else if(t.tag == t_prev.tag && (t.tag == INTEGER || t.tag == REAL)) t_prev = t;
  		else if((t.tag != t_prev.tag && t.tag!=eps && t_prev.tag != eps )||(t.tag == t_prev.tag && !(t.tag == INTEGER || t.tag == REAL))) {
  			if(t.tag==ARRAY) printf("SEMANTIC ERROR : ARRAY used in arithmeticExpr at line number %d \n",line_no);
  			else printf("SEMANTIC ERROR : Type mismatch error in arithmeticExpr at line number %d \n",line_no);
  			printf("------------------------------------------------------\n");
  			sem_err = 1;
  			t_prev.tag = eps;
  		}
  		else if(t.tag!= eps && t_prev.tag== eps) t_prev = t;
  	    if(temp->next!= NULL) {
            line_no = temp->next->n.L.t.line_number_var;
  	    	temp = temp->next->next;
  	    }
  		else temp=temp->next;
  	}
  	return t_prev;
  }

  else if(root->is_leaf == 0 && root->n.NL.nt == term){
  	ast_node * temp = root->child;
  	struct type_def t, t_prev;
  	t_prev.tag = eps;
  	int line_no;
  	while(temp!= NULL){
      // printf("Do\n");
      if(temp->is_leaf==1){
         // printf("%d line4 %s \n", temp->n.L.t.line_number_var,temp->n.L.t.value);
        int tok = temp->n.L.t.terminal;
        if(tok == NUM) t.tag = INTEGER;
        else if(tok == RNUM) t.tag = REAL;
        else t.tag = BOOLEAN;
      }
      // printf("call term\n" ),
  		else t = extract(temp);
  		if(t.tag == t_prev.tag && t.tag == eps) t_prev=t;
  		else if(t.tag == t_prev.tag && (t.tag == INTEGER || t.tag == REAL)) t_prev = t;
  		else if((t.tag != t_prev.tag && t.tag!=eps && t_prev.tag != eps )||(t.tag == t_prev.tag && !(t.tag == INTEGER || t.tag == REAL))) {
  			if(t.tag==ARRAY) printf("SEMANTIC ERROR : ARRAY used in arithmeticOrBooleanExpr at line number %d \n",line_no);
  			else printf("SEMANTIC ERROR : Type mismatch error in arithmeticExpr at line number %d \n",line_no);
  			printf("------------------------------------------------------\n");
  			sem_err = 1;
  			t_prev.tag  = eps;
  		}
  		else if(t.tag != eps && t_prev.tag == eps)t_prev = t;
  	    if(temp->next!= NULL) {
  	    	line_no = temp->next->n.L.t.line_number_var;
  	    	temp = temp->next->next;
  	    }
  		else temp=temp->next;
  	}
  	return t_prev;
  }

  else if(root->is_leaf==1 && (root->n.L.t.terminal == NUM || root->n.L.t.terminal == RNUM || root->n.L.t.terminal==BOOLEAN ) ) {
    //printf("%d line5 %s \n", root->n.L.t.line_number_var, root->n.L.t.value);
  	struct type_def ans;
  	int tok = root->n.L.t.terminal;
  	if(tok == NUM) ans.tag = INTEGER;
  	else if(tok == RNUM) ans.tag = REAL;
  	else ans.tag = BOOLEAN;
  	return ans;
  }

  else if (root->is_leaf == 0 && root->n.NL.nt == var_id_num){
     //printf("%d line6 %s \n", root->child->n.L.t.line_number_var, root->child->n.L.t.value);
  	struct type_def ans;
  	if(root->tag == -1)ans.tag = eps;
  	else if(root->tag) ans.tag = root->t.basic_type;
  	else ans.tag= ARRAY, ans.t.a = root->t.a;
  	return ans;
  }

  // else return extract(root->child);
}

/*char * termx[] = {"eps","$","NUM","RNUM","INTEGER","REAL","ID","BOOLEAN","OF","ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","RECORD",
         "TAGGED","UNION","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR",
         "FOR","IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF",
         "ENDDEF","DRIVERDEF","DRIVERENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK"};

*/

void type_extractor(ast_node * root){
 if(root == NULL) return;
 // if(root->is_leaf==1) printf("%s hhh\n", root->n.L.t.value);
 if(root->is_leaf==0 && root->n.NL.nt==module){
   if(root->table_ptr.fun_ptr==NULL) return type_extractor(root->next);
   else{
     type_extractor(root->child);
     type_extractor(root->next);
     return;
   }
 }
 if(root->is_leaf == 0  && root->n.NL.nt == arithmeticOrBooleanExpr) {
	struct type_def ans = extract(root);
  // printf("ans %s \n",termx[ans.tag]);
	if(ans.tag == eps) root->tag = -1;
	else if(ans.tag == ARRAY) root->tag = 0, root->t.a = ans.t.a;
	else root->tag = 1, root->t.basic_type = ans.tag;
  type_extractor(root->next);
  return;
 }
 else if(root->is_leaf == 0 && root->n.NL.nt == U){
 	ast_node* ptr = root->child->next;
 	if(ptr->is_leaf == 0 && ptr->n.NL.nt == arithmeticExpr){
 		struct type_def ans;
 	    ans = extract(ptr);
 	    if(ans.tag == eps) root->tag=-1;
 	    else if(ans.tag == INTEGER) root->tag=1, root->t.basic_type = INTEGER;
 	    else if(ans.tag == REAL) root->tag=1, root->t.basic_type = REAL;
 	    else if(ans.tag == BOOLEAN) root->tag=1, root->t.basic_type = BOOLEAN;
 	    else if(ans.tag == ARRAY) root->tag = 0, root->t.a = ans.t.a;

    }
 	else if(ptr->is_leaf){
 		if(ptr->n.L.t.terminal == NUM) root->tag = 1, root->t.basic_type = INTEGER;
 		else if(ptr->n.L.t.terminal == RNUM) root->tag=1, root->t.basic_type = REAL;
 		else root->tag=1, root->t.basic_type = BOOLEAN;
 	}
 	else {
 		if(ptr->tag == -1) root->tag = -1;
 		else if(ptr->tag) root->tag = 1, root->t.basic_type = ptr->t.basic_type;
 		else root->tag=0, root->t.a = ptr->t.a;
 	}
  type_extractor(root->next);
  return;
 }
 type_extractor(root->child);
 type_extractor(root->next);
}

