//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)

#include <string.h>
#include "astDef.h"
#include <ctype.h>
#include <stdlib.h>

//FILE* fp_ast;
//fp_ast=fopen("AST_file.txt", "w");
int ast_count = 0;
char *nterm2[] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist", "N1",
                  "output_plist", "N2", "dataType", "range_arrays", "type", "moduleDef", "statements", "statement", "ioStmt", "boolConstt", "var_id_num",
                  "var", "whichid", "simpleStmt", "assigmentStmt", "whichStmt", "lvalueIDStmt", "lvalueARRStmt", "index", "moduleReuseStmt", "optional",
                  "idList", "N3", "expression", "U", "new_NT", "unary_op", "arithmeticOrBooleanExpr", "N7", "AnyTerm", "N8", "arithmeticExpr", "N4", "term",
                  "N5", "factor", "op1", "op2", "logicalOp", "relationalOp", "declareStmt", "condionalStmt", "caseStmts", "N9", "value", "default",
                  "iterativeStmt", "range"};

void print_ast_console(ast_node* root ,int f)
{
    if(root==NULL)
        return;
    if(root->is_leaf)
    {

        if(root->n.L.t.terminal==RNUM && root->parent!=NULL)
        {
            printf("%s",root->n.L.t.value);
            //printf("%s ",)
            for(int i=0;i<(21-strlen(root->n.L.t.value));i++)
                printf(" ");
            printf("%d",root->n.L.t.line_number_var);
            for(int i=0;i<18;i++)
                printf(" ");
            printf("%s",root->name);
            for(int i=0;i<(20-strlen(root->name));i++)
                printf(" ");
            printf("%0.6e",atof(root->n.L.t.value));
            for(int i=0;i<(20-strlen(root->n.L.t.value));i++)
                printf(" ");
            printf("%s",root->parent->name);
            for(int i=0;i<(25-strlen(root->parent->name));i++)
                printf(" ");
            printf("YES");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----\n");
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            ast_count++;
            //printf("%s  %d  %s  %0.6e  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],atof(root->n.L.t.lexeme),nterm[root->n.L.parent->n.NL.nt]);//assuming parent is always a non-terminal
        }
        else if(root->n.L.t.terminal==NUM && root->parent!=NULL)
        {
            printf("%s",root->n.L.t.value);
            for(int i=0;i<(21-strlen(root->n.L.t.value));i++)
                printf(" ");
            printf("%d",root->n.L.t.line_number_var);
            for(int i=0;i<18;i++)
                printf(" ");
            printf("%s",root->name);
            for(int i=0;i<(20-strlen(root->name));i++)
                printf(" ");
            printf("%d",atoi(root->n.L.t.value));
            for(int i=0;i<(20-strlen(root->n.L.t.value));i++)
                printf(" ");
            printf("%s",root->parent->name);
            for(int i=0;i<(25-strlen(root->parent->name));i++)
                printf(" ");
            printf("YES");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----\n");
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            ast_count++;

            //printf("%s  %d  %s  %d  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],atoi(root->n.L.t.lexeme),nterm[root->n.L.parent->n.NL.nt]);//assuming parent is always a non-terminal
        }
        else if(root->parent!=NULL)
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
            printf("%s",root->name);
            for(int i=0;i<(20-strlen(root->name));i++)
                printf(" ");
            printf("----");
            for(int i=0;i<16;i++)
                printf(" ");
            printf("%s",root->parent->name);
            for(int i=0;i<(25-strlen(root->parent->name));i++)
                printf(" ");
            printf("YES");
            for(int i=0;i<17;i++)
                printf(" ");
            printf("----\n");
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            ast_count++;

            //printf("%s  %d  %s  ----  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],nterm[root->n.L.parent->n.NL.nt]);
        }
        if(root->parent!=NULL && f)
        {
            if(root->parent->parent!=NULL)
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
                printf("%s",root->parent->parent->name);
                for(int i=0;i<(25-strlen(root->parent->parent->name));i++)
                    printf(" ");
                printf("NO");
                for(int i=0;i<18;i++)
                    printf(" ");
                printf( "%s\n",root->parent->name );
                for(int i=0;i<150;i++)
                    printf("-");
                printf("\n");
                ast_count++;

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
                printf( "%s\n",root->parent->name );
                for(int i=0;i<150;i++)
                    printf("-");
                printf("\n");
                ast_count++;

                //printf("----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.L.parent->n.NL.nt]);
            }
        }
        print_ast_console(root->next,0);
        return;
    }
    else if(root->child==NULL)
    {
        if(root->parent!=NULL)
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
            printf("%s",root->parent->name);
            for(int i=0;i<(25-strlen(root->parent->name));i++)
                printf(" ");
            printf("YES");
            for(int i=0;i<17;i++)
                printf(" ");
            printf( "%s\n",root->name );
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            ast_count++;

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
            printf( "%s\n",root->name );
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            ast_count++;

            //printf("----  ----  NON_TERMINAL  ----  ROOT  yes  %s \n",nterm[root->n.NL.nt]);
        }
        if(root->parent!=NULL && f)
        {
            if(root->parent->parent!=NULL)
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
                printf("%s",root->parent->parent->name);
                for(int i=0;i<(25-strlen(root->parent->parent->name));i++)
                    printf(" ");
                printf("NO");
                for(int i=0;i<18;i++)
                    printf(" ");
                printf( "%s\n",root->parent->name );
                for(int i=0;i<150;i++)
                    printf("-");
                printf("\n");
                ast_count++;

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
                printf( "%s\n",root->parent->name );
                for(int i=0;i<150;i++)
                    printf("-");
                printf("\n");
                ast_count++;

                //printf("----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.NL.parent->n.NL.nt]);
            }
        }
        print_ast_console(root->next,0);
        return;
    }
    print_ast_console(root->child ,1);
    if(root->parent!=NULL && f)
    {
        if(root->parent->parent!=NULL)
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
            printf("%s",root->parent->parent->name);
            for(int i=0;i<(25-strlen(root->parent->parent->name));i++)
                printf(" ");
            printf("NO");
            for(int i=0;i<18;i++)
                printf(" ");
            printf( "%s\n",root->parent->name );
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            ast_count++;

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
            printf( "%s\n",root->parent->name );
            for(int i=0;i<150;i++)
                printf("-");
            printf("\n");
            ast_count++;

            //printf("----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.NL.parent->n.NL.nt]);
        }
    }
    print_ast_console(root->next,0);
}

ast_node *make_nonleaf_node(char *name, tree_node *root, ast_node *input1, ast_node *input2, ast_node *input3, ast_node *input4)
{
  ast_node *temp;
  ast_node *k;
  if (input1 == NULL)
  {
    if (input2 == NULL)
    {
      if (input3 == NULL)
      {
        if (input4 == NULL)
          k = NULL;
        else
          k = input4;
      }
      else
      {
        temp = input3;
        k = temp;
        while (temp->next != NULL)
          temp = temp->next;
        temp->next = input4;
      }
    }
    else
    {
      temp = input2;
      k = temp;
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      if (input3 == NULL)
      {
        if (input4 == NULL)
          temp->next = NULL;
        else
          temp->next = input4;
      }
      else
      {
        temp->next = input3;
        while (temp->next != NULL)
          temp = temp->next;
        temp->next = input4;
      }
    }
  }
  else
  {
    temp = input1;
    k = temp;
    while (temp->next != NULL)
      temp = temp->next;
    if (input2 == NULL)
    {
      if (input3 == NULL)
      {
        if (input4 == NULL)
          temp->next = NULL;
        else
          temp->next = input4;
      }
      else
      {
        temp->next = input3;
        while (temp->next != NULL)
          temp = temp->next;
        temp->next = input4;
      }
    }
    else
    {
      temp->next = input2;
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      if (input3 == NULL)
      {
        if (input4 == NULL)
          temp->next = NULL;
        else
          temp->next = input4;
      }
      else
      {
        temp->next = input3;
        while (temp->next != NULL)
          temp = temp->next;
        temp->next = input4;
      }
    }
  }

  ast_node *node = (ast_node *)malloc(sizeof(ast_node));
  node->n.NL.nt = root->n.NL.nt;
  node->is_leaf = 0;
  node->rule_number = root->n.NL.rule_number; //???????????????????????????????//
  node->parent = NULL;
  node->next = NULL;
  node->child = k;
  node->name = (char *)malloc(40 * sizeof(char));
  strcpy(node->name, name);
  while (k != NULL)
  {
    k->parent = node;
    k = k->next;
  }
  return node;
}

ast_node *make_leaf_node(char *name, tree_node *root)
{
  ast_node *node = (ast_node *)malloc(sizeof(ast_node));
  node->is_leaf = 1;
  node->parent = NULL;
  node->next = NULL;
  node->child = NULL;
  node->n.L.t.terminal = root->n.L.t.terminal;
  node->n.L.t.line_number_var = root->n.L.t.line_number_var;
  node->n.L.t.value = (char *)malloc(40 * sizeof(char));
  strcpy(node->n.L.t.value, root->n.L.t.value);
  node->name = (char *)malloc(40 * sizeof(char));
  strcpy(node->name, name);
  return node;
}

void free_tree(tree_node *root)
{
  // printf("in\n");
  if (root == NULL)
    return;
  if (root->is_leaf)
  {
    free_tree(root->n.L.sibling);
    free(root);
    return;
  }
  else if (root->n.NL.child == NULL)
  {
    free_tree(root->n.NL.sibling);
    free(root);
    return;
  }
  free_tree(root->n.NL.child);
  free_tree(root->n.NL.sibling);
  free(root);
}

ast_node* make_ast(tree_node* root)
{
  
  switch(root->n.NL.rule_number)  
  {
    //<program>--><moduleDeclarations><otherModules1><driverModule><otherModules2>
    case 1:
    {
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* c=make_ast(root->n.NL.child->n.NL.sibling->n.NL.sibling);
      ast_node* d=make_ast(root->n.NL.child->n.NL.sibling->n.NL.sibling->n.NL.sibling);
      ast_node* ast_root=make_nonleaf_node("PROGRAM",root,a,b,c,d);
      ast_root->parent = NULL;
      // free_tree(root);
      return ast_root;
    }
   // <moduleDeclarations1>--><moduleDeclaration><moduleDeclarations2>
    case 2:
    {
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      //ast_node* ast_root=make_nonleaf_node("MODULE_DECLARATIONS",root,a,b,NULL,NULL);
      if(strcmp(nterm2[root->n.NL.parent->n.NL.nt],"moduleDeclarations")!=0)
      {
        ast_node* ast_root=make_nonleaf_node("MODULE_DECLARATIONS",root,a,b,NULL,NULL);
        //free(root);
        return ast_root;
      }
      else
      {
        a->next=b;
        //free(root);
        return a;
      }
     }
    //<moduleDeclarations1>-->eps
    case 3:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<moduleDeclaration>-->DECLARE MODULE ID SEMICOL
    case 4:
    {
      ast_node* a=make_leaf_node("DECLARE_MODULE_ID",root->n.NL.child->n.L.sibling->n.L.sibling);
      ////free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling);
      ////free(root->n.NL.child->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.NL.sibling);
       //free(root->n.NL.child);
       //free(root);
      return a;
    }
    //<otherModules1>--><module><otherModules2>
    case 5:
    {
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      if(root->n.NL.parent->n.NL.nt==program)
      {
        ast_node* ast_root=make_nonleaf_node("OTHER_MODULES", root,a,b,NULL,NULL);
        ////free(root);
        return ast_root;
      }
      else
      {
        a->next=b;
        ////free(root);
        return a;
      }
    }
    //<otherModules1>-->eps
    case 6:
    {
      // //free(root->n.NL.child);
      // //free(root);
      return NULL;
    }
    //<driverModule>-->DRIVERDEF DRIVER PROGRAM DRIVERENDDEF <moduleDef>
    case 7:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling);
      // //free(root->n.NL.child);
      // //free(root);
      return a;
    }
    //<module>-->DEF MODULE ID ENDDEF TAKES INPUT SQBO <input_plist> SQBC SEMICOL <ret><moduleDef>
    case 8:
    {
      ast_node* a=make_leaf_node("MODULE_ID",root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling);
      ast_node* d=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      ast_node* ast_root=make_nonleaf_node("MODULE",root,a,b,c,d);
      if(d!= NULL)  ast_root->line_begin = d->line_begin, ast_root->line_end = d->line_end;
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling);
      // //free(root->n.NL.child);
      // //free(root);
      return ast_root;
    }
    //<ret>-->RETURNS SQBO <output_plist> SQBC SEMICOL
    case 9:
    {
        ast_node* a=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling);
        // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling);
        // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling);
        // //free(root->n.NL.child->n.L.sibling);
        // //free(root->n.NL.child);
        // //free(root);
        return a;
    }
    //<ret>-->eps
    case 10:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<input_plist>-->ID COLON <dataType> <N1a>
    case 11:
    {
      ast_node* a=make_leaf_node("INPUT_ID",root->n.NL.child);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling);
      ast_node* ast_root=make_nonleaf_node("INPUT_PLIST",root,a,b,c,NULL);
      // //free(root->n.NL.child->n.L.sibling);
      // //free(root->n.NL.child);
      // //free(root);
      return ast_root;
    }
    //<N1a>-->COMMA ID COLON <dataType><N1b>
    case 12:
    {
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      ast_node* a=make_leaf_node("ID",root->n.NL.child->n.L.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling);
      a->next=b;
      b->next=c;
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling);
      // //free(root->n.NL.child);
      // //free(root);
      return a;
    }
    //<N1a>-->eps
    case 13:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<output_plist>-->ID COLON <type> <N2a>
    case 14:
    {
      ast_node* a=make_leaf_node("ID",root->n.NL.child);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling);
      ast_node* ast_root=make_nonleaf_node("OUTPUT_PLIST",root,a,b,c,NULL);
      // //free(root->n.NL.child->n.L.sibling);
      // //free(root->n.NL.child);
      // //free(root);
      return ast_root;
    }
    //<N2a>-->COMMA ID COLON <type> <N2b>
    case 15:
    {
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      ast_node* a=make_leaf_node("ID",root->n.NL.child->n.L.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling);
      a->next=b;
      b->next=c;
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling);
      // //free(root->n.NL.child);
      // //free(root);
      return a;
    }
    //<N2a>-->eps
    case 16:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<dataType>-->INTEGER
    case 17:
    {
      ast_node* a=make_leaf_node("INTEGER",root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<dataType>-->REAL
    case 18:
    {
      ast_node* a=make_leaf_node("REAL",root->n.NL.child);
      // //free(root->n.NL.child);
      // //free(root);
      return a;
    }
    //<dataType>-->BOOLEAN
    case 19:
    {
      ast_node* a=make_leaf_node("BOOLEAN",root->n.NL.child);
      // //free(root->n.NL.child);
      // //free(root);
      return a;
    }
    //<dataType>-->ARRAY SQBO <range_arrays> SQBC OF <type>
    case 20:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("ARRAY",root,a,b,NULL,NULL);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling);
      // //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling);
      // //free(root->n.NL.child->n.L.sibling);
      // //free(root->n.NL.child);
      // //free(root);
      return ast_root;
    }
    //<range_arrays>--><index1> RANGEOP <index2>
    case 21:
    {
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("RANGE_ARRAYS",root,a,b,NULL,NULL);
      // //free(root->n.NL.child->n.NL.sibling);
      // //free(root);
      return ast_root;
    }
    //<type>-->INTEGER
    case 22:
    {
      ast_node* a=make_leaf_node("INTEGER",root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<type>-->REAL
    case 23:
    {
      ast_node* a=make_leaf_node("REAL",root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<type>-->BOOLEAN
    case 24:
    {
      ast_node* a=make_leaf_node("BOOLEAN",root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<moduleDef>-->START <statements> END
    case 25:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<statements1>--><statement><statements2>
    case 26:
    {
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      // if(root->n.NL.parent->n.NL.nt==moduleDef || root->n.NL.parent->n.NL.nt == caseStmts || root->n.NL.parent->n.NL.nt == defaul || root->n.NL.parent->n.NL.nt == iterativeStmt || root->n.NL.parent->n.NL.nt == N9)
      if(root->n.NL.parent->n.NL.nt != statements)
      {
        ast_node* ast_root=make_nonleaf_node("STATEMENTS",root,a,b,NULL,NULL);

        if(root->n.NL.parent->n.NL.nt == moduleDef){ 
            tree_node * ptr = root->n.NL.parent->n.NL.child;
            ast_root->line_begin = ptr->n.L.t.line_number_var;
            ptr = ptr->n.L.sibling->n.NL.sibling;
            ast_root->line_end = ptr->n.L.t.line_number_var;
        }
        //free(root);
        return ast_root;
      }
      else
      {
        a->next=b;
        //free(root);
        return a;
      }
    }
    //<statements>-->eps
    case 27:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<statement>--><ioStmt>
    case 28:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<statement>--><simpleStmt>
    case 29:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<statement>--><declareStmt>
    case 30:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    // <statement>--><condionalStmt>
    case 31:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    // <statement>--><iterativeStmt>
    case 32:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<ioStmt>-->GET_VALUE BO ID BC
    case 33:
    {
      ast_node* a=make_leaf_node("GET_VALUE",root->n.NL.child->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<ioStmt>-->PRINT BO <var> BC SEMICOL
    case 34:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("PRINT",root,a,NULL,NULL,NULL);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<boolConstt>-->TRUE
    case 35:
    {
      ast_node* a=make_leaf_node("TRUE", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<boolConstt>-->FALSE
    case 36:
    {
      ast_node* a=make_leaf_node("FALSE", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<var_id_num>-->ID <whichId>
    case 37:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      ast_node* b=make_leaf_node("ID",root->n.NL.child );
      ast_node* ast_node=make_nonleaf_node("PRINT_ARRAY", root,b, a, NULL, NULL);
      //free(root->n.NL.child);
      //free(root);
      return ast_node;
    }
    //<var_id_num>-->NUM
    case 38:
    {
      ast_node* a=make_leaf_node("NUM", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<var_id_num>-->RNUM
    case 39:
    {      
      ast_node* a=make_leaf_node("RNUM", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<var>--><var_id_num>
    case 40:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<var>--><boolConstt>
    case 41:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<whichId>-->SQBO <index> SQBC
    case 42:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<whichId>-->eps
    case 43:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<simpleStmt>--><assignmentStmt>
    case 44:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<simpleStmt>--><moduleReuseStmt>
    case 45:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<assignmentStmt>-->ID <whichStmt>
    case 46:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      ast_node* b=make_leaf_node("ID", root->n.NL.child);
      ast_node* ast_root=make_nonleaf_node("ASSIGNMENTSTMT",root,b, a, NULL, NULL);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<whichStmt>--><lvalueIDStmt>
    case 47:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<whichStmt>--><lvalueARRStmt>
    case 48:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<lvalueIDStmt>-->ASSIGNOP<expression> SEMICOL
    case 49:
    {
      ast_node* a=make_leaf_node("ASSINGOP", root->n.NL.child);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling);
      a->next=b;
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<lvalueARRStmt>-->SQBO <index> SQBC ASSIGNOP <expression> SEMICOL
    case 50:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      ast_node* b=make_leaf_node("ASSINGOP", root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling);
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling);
      a->next=b;
      b->next=c;
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<index>-->NUM
    case 51:
    {
      ast_node* a=make_leaf_node("NUM", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<index>-->ID
    case 52:
    {
      ast_node* a=make_leaf_node("ID", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<moduleReuseStmt>--><optional>USE MODULE ID WITH PARAMETERS <idList> SEMICOL
    case 53:
    {
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* b=make_leaf_node("MODULE_ID", root->n.NL.child->n.NL.sibling->n.L.sibling->n.L.sibling);
      ast_node* c=make_ast(root->n.NL.child->n.NL.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("MODULEREUSESTMT",root, a, b, c, NULL);
      //free(root->n.NL.child->n.NL.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.NL.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.NL.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.NL.sibling->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.NL.sibling->n.L.sibling);
      //free(root->n.NL.child->n.NL.sibling);
      //free(root);
      return ast_root;
    }
    //<optional>-->SQBO <idList> SQBC ASSIGNOP
    case 54:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      ast_node* b=make_leaf_node("ASSINGOP", root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("OPTIONAL",root, a, b, NULL, NULL);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<optional>-->eps
    case 55:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<idList>-->ID <N3a>
    case 56:
    {
      ast_node* a=make_leaf_node("ID", root->n.NL.child);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("IDLIST",root, a, b, NULL, NULL);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<N3a>-->COMMA ID <N3b>
    case 57:
    {
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* a=make_leaf_node("ID", root->n.NL.child->n.L.sibling);
      a->next=b;
      //free(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<N3a>-->eps
    case 58:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<expression>--><arithmeticOrBooleanExpr>
    case 59:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<expression>--><U>
    case 60:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<U>--><unary_op><new_NT>
    case 61:
    {
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* ast_root=make_nonleaf_node("UNARY", root,a, b, NULL, NULL);
      //free(root);
      return ast_root;
    }
    //<new_NT>-->BO<arithmeticExpr>BC
    case 62:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<new_NT>--><var_id_num>
    case 63:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<unary_op>->PLUS
    case 64:
    {
      ast_node* a=make_leaf_node("PLUS", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<unary_op>->MINUS
    case 65:
    {
      ast_node* a=make_leaf_node("MINUS", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<arithmeticOrBooleanExpr>--><AnyTerm> <N7a>
    case 66:
    {
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* ast_root=make_nonleaf_node("AIRTHMETICBOOL",root,a, b, NULL, NULL);
      //free(root);
      return ast_root;
    }
    //<N7a>--><logicalOp><AnyTerm><N7b>
    case 67:
    {
      ast_node* c=make_ast(root->n.NL.child->n.NL.sibling->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      a->next=b;
      b->next=c;
      //free(root);
      return a;
    }
    //<N7a>-->eps
    case 68:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<AnyTerm>--><arithmeticExpr> <N8>     
    case 69:
    {
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* ast_root=make_nonleaf_node("AnyTerm",root, a, b, NULL, NULL);
      //free(root);
      return ast_root;
    }
    //<AnyTerm>--><boolConstt>
    case 70:
    {
      ast_node *a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<N8>--><relationalOp><arithmeticExpr>
    case 71:
    {
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      a->next=b;
      //free(root);
      return a;
    }
    //<N8>-->eps
    case 72:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<arithmeticExpr>--><term> <N4a>
    case 73:
    {
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* ast_root=make_nonleaf_node("AIRTHMETICEXPR",root, a, b, NULL, NULL);
      //free(root);
      return ast_root;
    }
    //<N4a>--><op1> <term> <N4b>
    case 74:
    {
      ast_node* c=make_ast(root->n.NL.child->n.NL.sibling->n.NL.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      a->next=b;
      b->next=c;
      //free(root);
      return a;
    }
    //<N4a>-->eps
    case 75:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<term>--><factor> <N5a>
    case 76:
    {
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      ast_node* ast_root=make_nonleaf_node("TERM",root, a, b, NULL, NULL);
      //free(root);
      return ast_root;
    }
    //<N5a>--><op2> <factor> <N5b>
    case 77:
    {
      ast_node* c=make_ast(root->n.NL.child->n.NL.sibling->n.NL.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.NL.sibling);
      ast_node* a=make_ast(root->n.NL.child);
      a->next=b;
      b->next=c;
      //free(root);
      return a;
    }
    //<N5a>-->eps
    case 78:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<factor>-->BO<arithmeticOrBooleanExpr> BC
    case 79:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<factor>--><var_id_num>
    case 80:
    {
      ast_node* a=make_ast(root->n.NL.child);
      //free(root);
      return a;
    }
    //<op1>-->PLUS
    case 81:
    {
      ast_node* a=make_leaf_node("PLUS", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<op1>-->MINUS
    case 82:
    {
      ast_node* a=make_leaf_node("MINUS", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<op2>-->MUL
    case 83:
    {
      ast_node* a=make_leaf_node("MUL", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<op2>-->DIV
    case 84:
    {
      ast_node* a=make_leaf_node("DIV", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<logicalOp>-->AND
    case 85:
    {
      ast_node* a=make_leaf_node("AND", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<logicalOp>-->OR
    case 86:
    {
      ast_node* a=make_leaf_node("OR", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<relationalOp>-->LT
    case 87:
    {
      ast_node* a=make_leaf_node("LT", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<relationalOp>-->LE
    case 88:
    {
      ast_node* a=make_leaf_node("LE", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<relationalOp>-->GT
    case 89:
    {
      ast_node* a=make_leaf_node("GT", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<relationalOp>-->GE
    case 90:
    {
      ast_node* a=make_leaf_node("GE", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<relationalOp>-->EQ
    case 91:
    {
      ast_node* a=make_leaf_node("EQ", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<relationalOp>-->NE
    case 92:
    {
      ast_node* a=make_leaf_node("NE", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<declareStmt>-->DECLARE <idList>COLON <dataType> SEMICOL
    case 93:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("DECLARESTMT",root, a, b, NULL, NULL);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<condionalStmt>-->SWITCH BO ID BC START <caseStmts><default>END
    case 94:
    {
      ast_node* a = make_leaf_node("ID",root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      ast_node* ast_root=make_nonleaf_node("SWITCH",root, a, b, c, NULL);
      ast_root->line_begin = root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.t.line_number_var;
      ast_root->line_end = root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.NL.sibling->n.L.t.line_number_var;
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling); 
      //free(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<caseStmts>-->CASE <value>COLON <statements> BREAK SEMICOL <N9a>       ?????????????????????
    case 95:
    {
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling);
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("CASESTMTS",root, a, b, c, NULL );
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling->n.NL.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<N9a>-->CASE <value> COLON<statements> BREAK SEMICOL<N9b>           ????????????????????????
    case 96:
    {
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling);
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling);
      a->next=b;
      b->next=c;
      //ast_node* ast_root("CASE", a, b, c, NULL );
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling->n.NL.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<N9a>-->eps
    case 97:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<value>-->NUM
    case 98:
    {
      ast_node* a=make_leaf_node("NUM", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<value>-->TRUE
    case 99:
    {
      ast_node* a=make_leaf_node("TRUE", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<value>-->FALSE
    case 100:
    {
      ast_node* a=make_leaf_node("FALSE", root->n.NL.child);
      //free(root->n.NL.child);
      //free(root);
      return a;
    }
    //<default>-->DEFAULT COLON<statements> BREAK SEMICOL
    case 101:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("DEFAULT",root,a, NULL, NULL, NULL);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<default>-->eps
    case 102:
    {
      //free(root->n.NL.child);
      //free(root);
      return NULL;
    }
    //<iterativeStmt>-->FOR BO ID IN <range> BC START <statements> END
    case 103:
    {
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling);
      ast_node* c=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling);
      ast_node* a=make_leaf_node("ID", root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("FOR",root, a, b, c, NULL);
      ast_root->line_begin = root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.t.line_number_var;
      ast_root->line_end = root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.t.line_number_var;
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<iterativeStmt>-->WHILE BO<arithmeticOrBooleanExpr> BC START <statements> END
    case 104:
    {
      ast_node* a=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling);
      ast_node* b=make_ast(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling);
      ast_node* ast_root=make_nonleaf_node("WHILE",root, a, b, NULL, NULL);
      ast_root->line_begin = root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.t.line_number_var;
      ast_root->line_end = root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.t.line_number_var;
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling->n.L.sibling);
      //free(root->n.NL.child->n.L.sibling->n.L.sibling->n.NL.sibling);
      //free(root->n.NL.child->n.L.sibling);
      //free(root->n.NL.child);
      //free(root);
      return ast_root;
    }
    //<range>-->NUM RANGEOP NUM
    case 105:
    {
     ast_node* a=make_leaf_node("NUM", root->n.NL.child);
     ast_node* b=make_leaf_node("NUM", root->n.NL.child->n.L.sibling->n.L.sibling);
     ast_node* ast_root=make_nonleaf_node("RANGE",root, a, b, NULL, NULL);
     //free(root->n.NL.child->n.L.sibling->n.L.sibling);
     //free(root->n.NL.child->n.L.sibling);
     //free(root->n.NL.child);
     //free(root);
     return ast_root; 
    }
  }
}



void print_ast(ast_node *root, FILE *outfile, int f)
{
  if (root == NULL)
    return;
  if (root->is_leaf)
  {

    if (root->n.L.t.terminal == RNUM && root->parent != NULL)
    {
      fprintf(outfile, "%s", root->n.L.t.value);
      //fprintf(outfile,"%s ",)
      for (int i = 0; i < (21 - strlen(root->n.L.t.value)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%d", root->n.L.t.line_number_var);
      for (int i = 0; i < 18; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s", root->name);
      for (int i = 0; i < (20 - strlen(root->name)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%0.6e", atof(root->n.L.t.value));
      for (int i = 0; i < (20 - strlen(root->n.L.t.value)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s", root->parent->name);
      for (int i = 0; i < (25 - strlen(root->parent->name)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "YES");
      for (int i = 0; i < 17; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "----\n");
      for (int i = 0; i < 150; i++)
        fprintf(outfile, "-");
      fprintf(outfile, "\n");
      ast_count++;
      //fprintf(outfile,"%s  %d  %s  %0.6e  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],atof(root->n.L.t.lexeme),nterm[root->n.L.parent->n.NL.nt]);//assuming parent is always a non-terminal
    }
    else if (root->n.L.t.terminal == NUM && root->parent != NULL)
    {
      fprintf(outfile, "%s", root->n.L.t.value);
      for (int i = 0; i < (21 - strlen(root->n.L.t.value)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%d", root->n.L.t.line_number_var);
      for (int i = 0; i < 18; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s", root->name);
      for (int i = 0; i < (20 - strlen(root->name)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%d", atoi(root->n.L.t.value));
      for (int i = 0; i < (20 - strlen(root->n.L.t.value)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s", root->parent->name);
      for (int i = 0; i < (25 - strlen(root->parent->name)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "YES");
      for (int i = 0; i < 17; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "----\n");
      for (int i = 0; i < 150; i++)
        fprintf(outfile, "-");
      fprintf(outfile, "\n");
      ast_count++;

      //fprintf(outfile,"%s  %d  %s  %d  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],atoi(root->n.L.t.lexeme),nterm[root->n.L.parent->n.NL.nt]);//assuming parent is always a non-terminal
    }
    else if (root->parent != NULL)
    {
      if (root->n.L.t.value != NULL)
      {
        fprintf(outfile, "%s", root->n.L.t.value);
        for (int i = 0; i < (21 - strlen(root->n.L.t.value)); i++)
          fprintf(outfile, " ");
      }
      else
      {
        fprintf(outfile, "----");
        for (int i = 0; i < 17; i++)
          fprintf(outfile, " ");
      }
      fprintf(outfile, "%d", root->n.L.t.line_number_var);
      for (int i = 0; i < 18; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s", root->name);
      for (int i = 0; i < (20 - strlen(root->name)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "----");
      for (int i = 0; i < 16; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s", root->parent->name);
      for (int i = 0; i < (25 - strlen(root->parent->name)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "YES");
      for (int i = 0; i < 17; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "----\n");
      for (int i = 0; i < 150; i++)
        fprintf(outfile, "-");
      fprintf(outfile, "\n");
      ast_count++;

      //fprintf(outfile,"%s  %d  %s  ----  %s  yes  ---- \n",root->n.L.t.lexeme,root->n.L.t.line_number_var,term1[root->n.L.t.terminal],nterm[root->n.L.parent->n.NL.nt]);
    }
    if (root->parent != NULL && f)
    {
      if (root->parent->parent != NULL)
      {
        fprintf(outfile, "----");
        for (int i = 0; i < 17; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "----");
        for (int i = 0; i < 15; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "NON_TERMINAL        ");
        fprintf(outfile, "----");
        for (int i = 0; i < 16; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "%s", root->parent->parent->name);
        for (int i = 0; i < (25 - strlen(root->parent->parent->name)); i++)
          fprintf(outfile, " ");
        fprintf(outfile, "NO");
        for (int i = 0; i < 18; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "%s\n", root->parent->name);
        for (int i = 0; i < 150; i++)
          fprintf(outfile, "-");
        fprintf(outfile, "\n");
        ast_count++;

        //fprintf(outfile,"----  ----  NON_TERMINAL  ----  %s  no  %s \n",nterm[root->n.L.parent->n.NL.parent->n.NL.nt],nterm[root->n.L.parent->n.NL.nt]);
      }
      else
      {
        fprintf(outfile, "----");
        for (int i = 0; i < 17; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "----");
        for (int i = 0; i < 15; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "NON_TERMINAL        ");
        fprintf(outfile, "----");
        for (int i = 0; i < 16; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "ROOT");
        for (int i = 0; i < 21; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "NO");
        for (int i = 0; i < 18; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "%s\n", root->parent->name);
        for (int i = 0; i < 150; i++)
          fprintf(outfile, "-");
        fprintf(outfile, "\n");
        ast_count++;

        //fprintf(outfile,"----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.L.parent->n.NL.nt]);
      }
    }
    print_ast(root->next, outfile, 0);
    return;
  }
  else if (root->child == NULL)
  {
    if (root->parent != NULL)
    {
      fprintf(outfile, "----");
      for (int i = 0; i < 17; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "----");
      for (int i = 0; i < 15; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "NON_TERMINAL        ");
      fprintf(outfile, "----");
      for (int i = 0; i < 16; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s", root->parent->name);
      for (int i = 0; i < (25 - strlen(root->parent->name)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "YES");
      for (int i = 0; i < 17; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s\n", root->name);
      for (int i = 0; i < 150; i++)
        fprintf(outfile, "-");
      fprintf(outfile, "\n");
      ast_count++;

      //fprintf(outfile,"----  ----  NON_TERMINAL  ----  %s  yes  %s \n",nterm[root->n.NL.parent->n.NL.nt],nterm[root->n.NL.nt]);
    }
    else
    {
      fprintf(outfile, "----");
      for (int i = 0; i < 17; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "----");
      for (int i = 0; i < 15; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "NON_TERMINAL        ");
      fprintf(outfile, "----");
      for (int i = 0; i < 16; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "ROOT");
      for (int i = 0; i < 21; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "YES");
      for (int i = 0; i < 17; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s\n", root->name);
      for (int i = 0; i < 150; i++)
        fprintf(outfile, "-");
      fprintf(outfile, "\n");
      ast_count++;

      //fprintf(outfile,"----  ----  NON_TERMINAL  ----  ROOT  yes  %s \n",nterm[root->n.NL.nt]);
    }
    if (root->parent != NULL && f)
    {
      if (root->parent->parent != NULL)
      {
        fprintf(outfile, "----");
        for (int i = 0; i < 17; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "----");
        for (int i = 0; i < 15; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "NON_TERMINAL        ");
        fprintf(outfile, "----");
        for (int i = 0; i < 16; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "%s", root->parent->parent->name);
        for (int i = 0; i < (25 - strlen(root->parent->parent->name)); i++)
          fprintf(outfile, " ");
        fprintf(outfile, "NO");
        for (int i = 0; i < 18; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "%s\n", root->parent->name);
        for (int i = 0; i < 150; i++)
          fprintf(outfile, "-");
        fprintf(outfile, "\n");
        ast_count++;

        //fprintf(outfile,"----  ----  NON_TERMINAL  ----  %s  no  %s \n",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt],nterm[root->n.NL.parent->n.NL.nt]);
      }
      else
      {
        fprintf(outfile, "----");
        for (int i = 0; i < 17; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "----");
        for (int i = 0; i < 15; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "NON_TERMINAL        ");
        fprintf(outfile, "----");
        for (int i = 0; i < 16; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "ROOT");
        for (int i = 0; i < 21; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "NO");
        for (int i = 0; i < 18; i++)
          fprintf(outfile, " ");
        fprintf(outfile, "%s\n", root->parent->name);
        for (int i = 0; i < 150; i++)
          fprintf(outfile, "-");
        fprintf(outfile, "\n");
        ast_count++;

        //fprintf(outfile,"----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.NL.parent->n.NL.nt]);
      }
    }
    print_ast(root->next, outfile, 0);
    return;
  }
  print_ast(root->child, outfile, 1);
  if (root->parent != NULL && f)
  {
    if (root->parent->parent != NULL)
    {
      fprintf(outfile, "----");
      for (int i = 0; i < 17; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "----");
      for (int i = 0; i < 15; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "NON_TERMINAL        ");
      fprintf(outfile, "----");
      for (int i = 0; i < 16; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s", root->parent->parent->name);
      for (int i = 0; i < (25 - strlen(root->parent->parent->name)); i++)
        fprintf(outfile, " ");
      fprintf(outfile, "NO");
      for (int i = 0; i < 18; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s\n", root->parent->name);
      for (int i = 0; i < 150; i++)
        fprintf(outfile, "-");
      fprintf(outfile, "\n");
      ast_count++;

      //fprintf(outfile,"----  ----  NON_TERMINAL  ----  %s  no  %s \n",nterm[root->n.NL.parent->n.NL.parent->n.NL.nt],nterm[root->n.NL.parent->n.NL.nt]);
    }
    else
    {
      fprintf(outfile, "----");
      for (int i = 0; i < 17; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "----");
      for (int i = 0; i < 15; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "NON_TERMINAL        ");
      fprintf(outfile, "----");
      for (int i = 0; i < 16; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "ROOT");
      for (int i = 0; i < 21; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "NO");
      for (int i = 0; i < 18; i++)
        fprintf(outfile, " ");
      fprintf(outfile, "%s\n", root->parent->name);
      for (int i = 0; i < 150; i++)
        fprintf(outfile, "-");
      fprintf(outfile, "\n");
      ast_count++;

      //fprintf(outfile,"----  ----  NON_TERMINAL  ----  ROOT  no  %s \n",nterm[root->n.NL.parent->n.NL.nt]);
    }
  }
  print_ast(root->next, outfile, 0);
}

char *tokarray[] = {"eps", "$", "NUM", "RNUM", "INTEGER", "REAL", "ID", "BOOLEAN", "OF", "ARRAY", "START", "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "RECORD", "TAGGED", "UNION", "GET_VALUE", "PRINT", "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS", "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "ENDDEF", "DRIVERDEF", "DRIVERENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "LABEL", "GOTO", "IF", "U_MINUS", "U_PLUS", "FUNCTION", "RET", "CALL", "PARAM", "RETURN"};

int label_no = 0;
int var_no = 0;

ast_node *insert_temp(ast_node *temp, char *temp_var_name, TOKEN basic_type)
{

  int size;
  if (basic_type == INTEGER)
    size = int_size;
  else if (basic_type == REAL)
    size = real_size;
  else
    size = bool_size;

  // printf("size=%d", size);

  if (temp == NULL)
    return NULL;
  ast_node *ans = (ast_node *)malloc(sizeof(ast_node));

  ans->name = "TEMP_VAR";
  ans->parent = NULL;
  ans->child = NULL;
  ans->next = NULL;
  ans->is_leaf = true;
  ans->tag = 1;
  ans->t.basic_type = basic_type;

  v_node *v = (v_node *)malloc(sizeof(v_node));
  v->next = NULL;
  strcpy(v->v_name, temp_var_name);
  v->hash_var.tag = 1;
  v->hash_var.t.basic_type = basic_type;
  strcpy(v->hash_var.v_name, temp_var_name);
  v->hash_var.flag = false;

  ast_node *par = temp;
  while (par != NULL && par->n.NL.nt != condionalStmt && par->n.NL.nt != iterativeStmt && par->n.NL.nt != module && !(par->n.NL.nt == statements && par->parent->n.NL.nt == program))
    par = par->parent;

  if (par != NULL)
  {
    int pos = compute_hash_sk(temp_var_name);
    v->hash_var.scope_begin = par->line_begin;
    v->hash_var.scope_end = par->line_end;

    if (par->n.NL.nt == module)
    {
      v->hash_var.offset = par->off_end_local;
      par->off_end_local += size;
      strcpy(v->hash_var.module_name, par->child->n.L.t.value);
      v_node *moo = par->table_ptr.fun_ptr->hash_f.def->hash_var[pos];
      if (moo == NULL)
      {
        par->table_ptr.fun_ptr->hash_f.def->hash_var[pos] = v;
        ans->scope_tag = 1;
        ans->table_ptr.inner_ptr = par->table_ptr.fun_ptr->hash_f.def;
        return ans;
      }
      while (moo->next != NULL)
        moo = moo->next;
      moo->next = v;
      ans->scope_tag = 1;
      ans->table_ptr.inner_ptr = par->table_ptr.fun_ptr->hash_f.def;
      return ans;
    }

    else if (par->n.NL.nt == statements)
    {
      v->hash_var.offset = par->off_end_local;
      par->off_end_local += size;
      strcpy(v->hash_var.module_name, "DRIVER");
      v_node *moo = par->table_ptr.fun_ptr->hash_f.def->hash_var[pos];
      if (moo == NULL)
      {
        par->table_ptr.fun_ptr->hash_f.def->hash_var[pos] = v;
        ans->scope_tag = 1;
        ans->table_ptr.inner_ptr = par->table_ptr.fun_ptr->hash_f.def;
        return ans;
      }
      while (moo->next != NULL)
        moo = moo->next;
      moo->next = v;
      ans->scope_tag = 1;
      ans->table_ptr.inner_ptr = par->table_ptr.fun_ptr->hash_f.def;
      return ans;
    }

    else
    {
      v_node *moo = par->table_ptr.inner_ptr->hash_var[pos];
      if (moo == NULL)
      {
        par->table_ptr.inner_ptr->hash_var[pos] = v;
        ans->scope_tag = 1;
        ans->table_ptr.inner_ptr = par->table_ptr.inner_ptr;
      }
      else
      {
        while (moo->next != NULL)
          moo = moo->next;
        moo->next = v;
        ans->scope_tag = 1;
        ans->table_ptr.inner_ptr = par->table_ptr.inner_ptr;
      }
      while (par != NULL && par->n.NL.nt != module && !(par->n.NL.nt == statements && par->parent->n.NL.nt == program))
        par = par->parent;
      if (par != NULL)
      {
        v->hash_var.offset = par->off_end_local;
        par->off_end_local += size;
        if (par->n.NL.nt == statements)
          strcpy(v->hash_var.module_name, "DRIVER");
        else
          strcpy(v->hash_var.module_name, par->child->n.L.t.value);
        return ans;
      }
    }
  }

  return temp;
}

char *generate_name()
{
  char *str = (char *)malloc(sizeof(char) * 10);
  sprintf(str, "t_grp%d", var_no);

  var_no++;

  return str;
}

char *generate_label()
{
  char *str = (char *)malloc(sizeof(char) * 10);
  sprintf(str, "L%d", label_no);
  label_no++;

  return str;
}

Tuple *make_tuple(TOKEN op, char *arg1, char *arg2, char *result, ast_node *node1, ast_node *node2, ast_node *node3)
{
  Tuple *temp = (Tuple *)malloc(sizeof(Tuple));

  temp->op = op;
  temp->arg1 = arg1;
  temp->arg2 = arg2;
  temp->result = result;

  temp->node1 = node1;
  temp->node2 = node2;
  temp->node3 = node3;

  temp->next = NULL;

  return temp;
}

void add_tuple(quadruple *qd, Tuple *temp_start, Tuple *temp_end)
{
  if (qd->head == NULL)
  {
    qd->head = temp_start;
    //INITIALIZE  THE QUADRUPLE
    qd->last = temp_end;
  }
  else
  {
    qd->last->next = temp_start;
    qd->last = temp_end;
  }
}

void process_MODULE(ast_node *node, quadruple *list)
{
  ast_node *modid = node->child;
  ast_node *iplist = modid->next;
  ast_node *oplist = iplist->next;

  ast_node *st;

  if (oplist == NULL)
  {
    Tuple *tup1 = make_tuple(FUNCTION, modid->n.L.t.value, NULL, NULL, modid, NULL, NULL);
    Tuple *tup2 = make_tuple(RET, modid->n.L.t.value, NULL, NULL, modid, NULL, NULL);
    tup1->next = tup2;
    node->tuple_start = tup1;
    node->tuple_end = tup2;
    return;
  }
  else if (oplist->next == NULL)
    st = oplist;
  else
    st = oplist->next;

  Tuple *tup1 = make_tuple(FUNCTION, modid->n.L.t.value, NULL, NULL, modid, NULL, NULL);
  tup1->next = st->tuple_start;

  Tuple *tup2 = make_tuple(RET, modid->n.L.t.value, NULL, NULL, modid, NULL, NULL);
  st->tuple_end->next = tup2;

  node->tuple_start = tup1;
  node->tuple_end = tup2;
}
void process_last(ast_node *node, quadruple *list)
{
  ast_node *temp = node->child;
  //printf("d");
  //  printf("HEY %s",temp->name);

  if (temp != NULL)
  {
    Tuple *stt = temp->tuple_start;
    Tuple *ste = temp->tuple_end;
    temp = temp->next;
    Tuple *prevtemp = ste;
    while (temp != NULL)
    {
      prevtemp->next = temp->tuple_start;
      ste = temp->tuple_end;
      prevtemp = ste;
      temp = temp->next;
    }
    node->tuple_start = stt;
    node->tuple_end = ste;
    //printf("hefkj");
    add_tuple(list, stt, ste);
  }
}

void process_MODULEREUSE(ast_node *node, quadruple *list)
{
  ast_node *option = node->child;
  if (strcmp(option->name, "OPTIONAL") == 0)
  {
    ast_node *idn = option->next; //OPTION CAN BE NULL RIGHT??
    ast_node *retn = idn->next;

    ast_node *temp1 = option->child;
    ast_node *temp2 = retn->child;

    Tuple *tup = make_tuple(CALL, idn->n.L.t.value, NULL, NULL, idn, NULL, NULL);
    Tuple *tup2 = make_tuple(PARAM, temp2->n.L.t.value, NULL, NULL, temp2, NULL, NULL);
    tup->next = tup2;
    Tuple *prevtemp = tup2;
    temp2 = temp2->next;

    while (temp2 != NULL)
    {

      tup2 = make_tuple(PARAM, temp2->n.L.t.value, NULL, NULL, temp2, NULL, NULL);
      prevtemp->next = tup2;
      prevtemp = tup2;
      temp2 = temp2->next;
    }

    Tuple *prevtemp2 = tup2;
    temp1 = temp1->child;
    while (temp1 != NULL)
    {
      if (strcmp(temp1->name, "ASSINGOP") == 0)
        break;

      Tuple *tup4 = make_tuple(RETURN, temp1->n.L.t.value, NULL, NULL, temp1, NULL, NULL);
      prevtemp2->next = tup4;
      prevtemp2 = tup4;
      temp1 = temp1->next;
    }
    node->tuple_start = tup;
    node->tuple_end = prevtemp2;
  }

  else
  {
    ast_node *idn = node->child;
    ast_node *inpn = idn->next;

    ast_node *temp2 = inpn->child;

    Tuple *tup = make_tuple(CALL, idn->n.L.t.value, NULL, NULL, idn, NULL, NULL);
    Tuple *tup2 = make_tuple(PARAM, temp2->n.L.t.value, NULL, NULL, temp2, NULL, NULL);
    tup->next = tup2;
    Tuple *prevtemp = tup2;
    temp2 = temp2->next;
    while (temp2 != NULL)
    {

      tup2 = make_tuple(PARAM, temp2->n.L.t.value, NULL, NULL, temp2, NULL, NULL);
      prevtemp->next = tup2;
      prevtemp = tup2;
      temp2 = temp2->next;
    }
    node->tuple_start = tup;
    node->tuple_end = prevtemp;
  }
}

void process_ARITHBOOL(ast_node *node, quadruple *list)
{
  ast_node *termn1 = node->child;
  ast_node *opn = termn1->next;

  if (opn != NULL)
  {
    Tuple *prevtup = NULL;
    Tuple *tup = NULL;

    ast_node *termn2 = opn->next;
    char *vart = NULL;

    vart = generate_name();

    ast_node *vartup = insert_temp(node, vart, BOOLEAN);
    vartup->n.L.t.terminal = ID;
    if (strcmp(opn->name, "AND") == 0)
    {

      tup = make_tuple(AND, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
      Tuple *tup00 = termn1->tuple_start;
      node->tuple_start = tup00;
      termn1->tuple_end->next = termn2->tuple_start;
      termn2->tuple_end->next = tup;
      node->tuple_end = tup;
    }
    else if (strcmp(opn->name, "OR") == 0)
    {
      tup = make_tuple(OR, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
      Tuple *tup00 = termn1->tuple_start;
      node->tuple_start = tup00;
      termn1->tuple_end->next = termn2->tuple_start;
      termn2->tuple_end->next = tup;
      node->tuple_end = tup;
    }
    prevtup = tup;
    opn = termn2->next;
    // termn1=opn->next;

    char *prevvar = vart;
    while (opn != NULL)
    {
      termn1 = opn->next;
      vart = generate_name();

      ast_node *vartup2 = insert_temp(node, vart, BOOLEAN);
      vartup2->n.L.t.terminal = ID;

      if (strcmp(opn->name, "AND") == 0)
      {
        tup = make_tuple(AND, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
        Tuple *tup00 = termn1->tuple_start;
        prevtup->next = tup00;
        termn1->tuple_end->next = tup;
        node->tuple_end = tup;
        prevtup = tup;
      }
      else if (strcmp(opn->name, "OR") == 0)
      {
        tup = make_tuple(OR, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
        Tuple *tup00 = termn1->tuple_start;
        prevtup->next = tup00;
        termn1->tuple_end->next = tup;
        node->tuple_end = tup;
        prevtup = tup;
      }
      prevvar = vart;
      vartup = vartup2;
      opn = termn1->next;
    }
  }
  else
  {

    node->tuple_start = termn1->tuple_start;
    node->tuple_end = termn1->tuple_end;
  }
}

void process_AnyTerm(ast_node *node, quadruple *list)
{
  ast_node *anytermn = node;
  if (strcmp(anytermn->name, "TRUE") == 0 || strcmp(anytermn->name, "FALSE") == 0)
  {
    char *tvar = generate_name();

    ast_node *vartup = insert_temp(node, tvar, BOOLEAN);
    vartup->n.L.t.terminal = ID;
    /* type of tvar is true or false*/
    Tuple *tup = make_tuple(ASSIGNOP, anytermn->n.L.t.value, NULL, tvar, anytermn, NULL, vartup /****/);

    node->tuple_start = tup;
    node->tuple_end = tup;
  }
  else
  {
    ast_node *termn1 = node->child;
    ast_node *opn = termn1->next;

    if (opn != NULL)
    {
      Tuple *prevtup = NULL;
      Tuple *tup = NULL;

      ast_node *termn2 = opn->next;
      char *vart = NULL;

      vart = generate_name();

      ast_node *vartup = insert_temp(node, vart, BOOLEAN);
      vartup->n.L.t.terminal = ID;

      if (strcmp(opn->name, "LE") == 0)
      {

        tup = make_tuple(LE, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
        Tuple *tup00 = termn1->tuple_start;
        node->tuple_start = tup00;
        termn1->tuple_end->next = termn2->tuple_start;
        termn2->tuple_end->next = tup;
        node->tuple_end = tup;
      }
      else if (strcmp(opn->name, "LT") == 0)
      {
        tup = make_tuple(LT, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
        Tuple *tup00 = termn1->tuple_start;
        node->tuple_start = tup00;
        termn1->tuple_end->next = termn2->tuple_start;
        termn2->tuple_end->next = tup;
        node->tuple_end = tup;
      }
      else if (strcmp(opn->name, "GT") == 0)
      {
        tup = make_tuple(GT, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
        Tuple *tup00 = termn1->tuple_start;
        node->tuple_start = tup00;
        termn1->tuple_end->next = termn2->tuple_start;
        termn2->tuple_end->next = tup;
        node->tuple_end = tup;
      }
      else if (strcmp(opn->name, "GE") == 0)
      {
        tup = make_tuple(GE, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
        Tuple *tup00 = termn1->tuple_start;
        node->tuple_start = tup00;
        termn1->tuple_end->next = termn2->tuple_start;
        termn2->tuple_end->next = tup;
        node->tuple_end = tup;
      }
      else if (strcmp(opn->name, "EQ") == 0)
      {
        tup = make_tuple(EQ, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
        Tuple *tup00 = termn1->tuple_start;
        node->tuple_start = tup00;
        termn1->tuple_end->next = termn2->tuple_start;
        termn2->tuple_end->next = tup;
        node->tuple_end = tup;
      }
      else if (strcmp(opn->name, "NE") == 0)
      {
        tup = make_tuple(NE, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
        Tuple *tup00 = termn1->tuple_start;
        node->tuple_start = tup00;
        termn1->tuple_end->next = termn2->tuple_start;
        termn2->tuple_end->next = tup;
        node->tuple_end = tup;
      }
      prevtup = tup;
      opn = termn2->next;
      // termn1=opn->next;

      char *prevvar = vart;
      while (opn != NULL)
      {
        termn1 = opn->next;
        vart = generate_name();

        ast_node *vartup2 = insert_temp(node, vart, BOOLEAN);
        vartup2->n.L.t.terminal = ID;
        if (strcmp(opn->name, "LT") == 0)
        {
          tup = make_tuple(LT, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
          Tuple *tup00 = termn1->tuple_start;
          prevtup->next = tup00;
          termn1->tuple_end->next = tup;
          node->tuple_end = tup;
          prevtup = tup;
        }
        else if (strcmp(opn->name, "LE") == 0)
        {
          tup = make_tuple(LE, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
          Tuple *tup00 = termn1->tuple_start;
          prevtup->next = tup00;
          termn1->tuple_end->next = tup;
          node->tuple_end = tup;
          prevtup = tup;
        }
        else if (strcmp(opn->name, "GT") == 0)
        {
          tup = make_tuple(GT, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
          Tuple *tup00 = termn1->tuple_start;
          prevtup->next = tup00;
          termn1->tuple_end->next = tup;
          node->tuple_end = tup;
          prevtup = tup;
        }
        else if (strcmp(opn->name, "GE") == 0)
        {
          tup = make_tuple(GE, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
          Tuple *tup00 = termn1->tuple_start;
          prevtup->next = tup00;
          termn1->tuple_end->next = tup;
          node->tuple_end = tup;
          prevtup = tup;
        }
        else if (strcmp(opn->name, "EQ") == 0)
        {
          tup = make_tuple(EQ, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
          Tuple *tup00 = termn1->tuple_start;
          prevtup->next = tup00;
          termn1->tuple_end->next = tup;
          node->tuple_end = tup;
          prevtup = tup;
        }
        else if (strcmp(opn->name, "NE") == 0)
        {
          tup = make_tuple(NE, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
          Tuple *tup00 = termn1->tuple_start;
          prevtup->next = tup00;
          termn1->tuple_end->next = tup;
          node->tuple_end = tup;
          prevtup = tup;
        }
        prevvar = vart;
        vartup = vartup2;
        opn = termn1->next;
      }
    }
    else
    {

      node->tuple_start = termn1->tuple_start;
      node->tuple_end = termn1->tuple_end;
    }
  }
}

void process_arith(ast_node *node, quadruple *list)
{
  ast_node *termn1 = node->child;
  ast_node *opn = termn1->next;

  if (opn != NULL)
  {
    Tuple *prevtup = NULL;
    Tuple *tup = NULL;

    ast_node *termn2 = opn->next;
    char *vart = NULL;

    vart = generate_name();
    ast_node *vartup = insert_temp(node, vart, INTEGER);
    vartup->n.L.t.terminal = ID;

    if (strcmp(opn->name, "PLUS") == 0)
    {

      tup = make_tuple(PLUS, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
      Tuple *tup00 = termn1->tuple_start;
      node->tuple_start = tup00;
      termn1->tuple_end->next = termn2->tuple_start;
      termn2->tuple_end->next = tup;
      node->tuple_end = tup;
    }
    else if (strcmp(opn->name, "MINUS") == 0)
    {
      tup = make_tuple(MINUS, termn1->tuple_end->result, termn2->tuple_end->result, vart, termn1->tuple_end->node3, termn2->tuple_end->node3, vartup /**/);
      Tuple *tup00 = termn1->tuple_start;
      node->tuple_start = tup00;
      termn1->tuple_end->next = termn2->tuple_start;
      termn2->tuple_end->next = tup;
      node->tuple_end = tup;
    }

    prevtup = tup;
    opn = termn2->next;
    // termn1=opn->next;

    char *prevvar = vart;
    while (opn != NULL)
    {
      termn1 = opn->next;
      vart = generate_name();

      ast_node *vartup2 = insert_temp(node, vart, INTEGER);
      vartup2->n.L.t.terminal = ID;

      if (strcmp(opn->name, "PLUS") == 0)
      {
        tup = make_tuple(PLUS, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
        Tuple *tup00 = termn1->tuple_start;
        prevtup->next = tup00;
        termn1->tuple_end->next = tup;
        node->tuple_end = tup;
        prevtup = tup;
      }
      else if (strcmp(opn->name, "MINUS") == 0)
      {
        tup = make_tuple(MINUS, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
        Tuple *tup00 = termn1->tuple_start;
        prevtup->next = tup00;
        termn1->tuple_end->next = tup;
        node->tuple_end = tup;
        prevtup = tup;
      }

      prevvar = vart;
      vartup = vartup2;
      opn = termn1->next;
    }
  }
  else
  {

    node->tuple_start = termn1->tuple_start;
    node->tuple_end = termn1->tuple_end;
  }
}
void process_TERM(ast_node *node, quadruple *list)
{
  ast_node *termn1 = node->child;
  ast_node *opn = termn1->next;

  if (opn != NULL)
  {
    Tuple *prevtup = NULL;
    Tuple *tup = NULL;

    ast_node *termn2 = opn->next;
    char *vart = NULL;

    vart = generate_name();

    ast_node *vartup = insert_temp(node, vart, INTEGER);
    vartup->n.L.t.terminal = ID;

    if (strcmp(opn->name, "MUL") == 0)
    {

      char *ar1 = NULL;
      ast_node *nd1 = NULL;

      char *ar2 = NULL;
      ast_node *nd2 = NULL;
      if (strcmp(termn1->name, "NUM") == 0)
      {
        ar1 = termn1->n.L.t.value;
        nd1 = termn1;
        termn1->tuple_start = NULL;
        termn1->tuple_end = NULL;
      }
      else if (strcmp(termn1->name, "RNUM") == 0)
      {
        ar1 = termn1->n.L.t.value;
        nd1 = termn1;
        termn1->tuple_start = NULL;
        termn1->tuple_end = NULL;
      }
      else if (strcmp(termn1->name, "PRINT_ARRAY") == 0)
      {
        if (termn1->child->next == NULL)
        {
          ar1 = termn1->child->n.L.t.value;
          nd1 = termn1->child;
        }
        else
        {
          char *var1 = generate_name();

          ast_node *vartup = insert_temp(node, var1, termn1->child->t.a.ele_type);
          vartup->n.L.t.terminal = ID;

          Tuple *tyu = make_tuple(ASSIGNOP, termn1->child->n.L.t.value, termn1->child->next->n.L.t.value, var1, termn1->child, termn1->child->next, vartup);
          termn1->tuple_start = tyu;
          termn1->tuple_end = tyu;
          ar1 = var1;
          nd1 = vartup;
        }
      }
      else if (strcmp(termn1->name, "AIRTHMETICBOOL") == 0)
      {

        ar1 = termn1->tuple_end->result;
        nd1 = termn1->tuple_end->node3;
      }

      if (strcmp(termn2->name, "NUM") == 0)
      {
        ar2 = termn2->n.L.t.value;
        nd2 = termn2;
        termn2->tuple_start = NULL;
        termn2->tuple_end = NULL;
      }
      else if (strcmp(termn2->name, "RNUM") == 0)
      {
        ar2 = termn2->n.L.t.value;
        nd2 = termn2;
        termn2->tuple_start = NULL;
        termn2->tuple_end = NULL;
      }
      else if (strcmp(termn2->name, "PRINT_ARRAY") == 0)
      {
        if (termn2->child->next == NULL)
        {
          ar2 = termn2->child->n.L.t.value;
          nd2 = termn2->child;
        }
        else
        {
          char *var1 = generate_name();
          ast_node *vartup = insert_temp(node, var1, termn2->child->t.a.ele_type);
          vartup->n.L.t.terminal = ID;

          Tuple *tyu = make_tuple(ASSIGNOP, termn2->child->n.L.t.value, termn2->child->next->n.L.t.value, var1, termn2->child, termn2->child->next, vartup);
          termn2->tuple_start = tyu;
          termn2->tuple_end = tyu;
          ar2 = var1;
          nd2 = NULL;
        }
      }
      else if (strcmp(termn2->name, "AIRTHMETICBOOL") == 0)
      {
        ar2 = termn2->tuple_end->result;
        nd2 = termn2->tuple_end->node3;
      }

      tup = make_tuple(MUL, ar1, ar2, vart, nd1, nd2, vartup /**/);
      Tuple *tup00 = termn1->tuple_start;
      Tuple *tup01 = termn2->tuple_start;
      Tuple *tup02 = termn1->tuple_end;
      Tuple *tup03 = termn2->tuple_end;

      if (tup00 != NULL && tup01 != NULL)
      {
        node->tuple_start = tup00;
        tup02->next = tup01;
        tup03->next = tup;
        node->tuple_end = tup;
      }
      else if (tup00 == NULL && tup01 != NULL)
      {
        node->tuple_start = tup01;
        tup03->next = tup;
        node->tuple_end = tup;
      }
      else if (tup00 != NULL && tup01 == NULL)
      {
        node->tuple_start = tup00;
        tup02->next = tup;
        node->tuple_end = tup;
      }
      else if (tup01 == NULL && tup02 == NULL)
      {
        node->tuple_start = tup;
        node->tuple_end = tup;
      }
    }
    else if (strcmp(opn->name, "DIV") == 0)
    {

      char *ar1 = NULL;
      ast_node *nd1 = NULL;

      char *ar2 = NULL;
      ast_node *nd2 = NULL;
      if (strcmp(termn1->name, "NUM") == 0)
      {
        ar1 = termn1->n.L.t.value;
        nd1 = termn1;
        termn1->tuple_start = NULL;
        termn1->tuple_end = NULL;
      }
      else if (strcmp(termn1->name, "RNUM") == 0)
      {
        ar1 = termn1->n.L.t.value;
        nd1 = termn1;
        termn1->tuple_start = NULL;
        termn1->tuple_end = NULL;
      }
      else if (strcmp(termn1->name, "PRINT_ARRAY") == 0)
      {
        if (termn1->child->next == NULL)
        {
          ar1 = termn1->child->n.L.t.value;
          nd1 = termn1->child;
        }
        else
        {
          char *var1 = generate_name();

          ast_node *vartup = insert_temp(node, var1, termn1->child->t.a.ele_type);
          vartup->n.L.t.terminal = ID;

          Tuple *tyu = make_tuple(ASSIGNOP, termn1->child->n.L.t.value, termn1->child->next->n.L.t.value, var1, termn1->child, termn1->child->next, vartup);
          termn1->tuple_start = tyu;
          termn1->tuple_end = tyu;
          ar1 = var1;
          nd1 = NULL;
        }
      }
      else if (strcmp(termn1->name, "AIRTHMETICBOOL") == 0)
      {
        ar1 = termn1->tuple_end->result;
        nd1 = termn1->tuple_end->node3;
      }

      if (strcmp(termn2->name, "NUM") == 0)
      {
        ar2 = termn2->n.L.t.value;
        nd2 = termn2;
        termn2->tuple_start = NULL;
        termn2->tuple_end = NULL;
      }
      else if (strcmp(termn2->name, "RNUM") == 0)
      {
        ar2 = termn2->n.L.t.value;
        nd2 = termn2;
        termn2->tuple_start = NULL;
        termn2->tuple_end = NULL;
      }
      else if (strcmp(termn2->name, "PRINT_ARRAY") == 0)
      {
        if (termn2->child->next == NULL)
        {
          ar2 = termn2->child->n.L.t.value;
          nd2 = termn2->child;
        }
        else
        {
          char *var1 = generate_name();

          ast_node *vartup = insert_temp(node, var1, termn1->child->t.a.ele_type);
          vartup->n.L.t.terminal = ID;

          Tuple *tyu = make_tuple(ASSIGNOP, termn1->child->n.L.t.value, termn1->child->next->n.L.t.value, var1, termn1->child, termn1->child->next, vartup);
          termn2->tuple_start = tyu;
          termn2->tuple_end = tyu;
          ar2 = var1;
          nd2 = NULL;
        }
      }
      else if (strcmp(termn2->name, "AIRTHMETICBOOL") == 0)
      {
        ar2 = termn2->tuple_end->result;
        nd2 = termn2->tuple_end->node3;
      }

      tup = make_tuple(DIV, ar1, ar2, vart, nd1, nd2, vartup /**/);
      Tuple *tup00 = termn1->tuple_start;
      Tuple *tup01 = termn2->tuple_start;
      Tuple *tup02 = termn1->tuple_end;
      Tuple *tup03 = termn2->tuple_end;

      if (tup00 != NULL && tup01 != NULL)
      {
        node->tuple_start = tup00;
        tup02->next = tup01;
        tup03->next = tup;
        node->tuple_end = tup;
      }
      else if (tup00 == NULL && tup01 != NULL)
      {
        node->tuple_start = tup01;
        tup03->next = tup;
        node->tuple_end = tup;
      }
      else if (tup00 != NULL && tup01 == NULL)
      {
        node->tuple_start = tup00;
        tup02->next = tup;
        node->tuple_end = tup;
      }
      else if (tup01 == NULL && tup02 == NULL)
      {
        node->tuple_start = tup;
        node->tuple_end = tup;
      }
    }

    prevtup = tup;
    opn = termn2->next;
    // termn1=opn->next;

    char *prevvar = vart;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (opn != NULL)
    {
      termn1 = opn->next;
      vart = generate_name();

      ast_node *vartup2 = insert_temp(node, vart, termn1->child->t.a.ele_type);
      vartup2->n.L.t.terminal = ID;

      if (strcmp(opn->name, "MUL") == 0)
      {
        char *ar1 = NULL;
        ast_node *nd1 = NULL;

        char *ar2 = NULL;
        ast_node *nd2 = NULL;
        if (strcmp(termn1->name, "NUM") == 0)
        {
          ar1 = termn1->n.L.t.value;
          nd1 = termn1;
          termn1->tuple_start = NULL;
          termn1->tuple_end = NULL;
        }
        else if (strcmp(termn1->name, "RNUM") == 0)
        {
          ar1 = termn1->n.L.t.value;
          nd1 = termn1;
          termn1->tuple_start = NULL;
          termn1->tuple_end = NULL;
        }
        else if (strcmp(termn1->name, "PRINT_ARRAY") == 0)
        {
          if (termn1->child->next == NULL)
          {
            ar1 = termn1->child->n.L.t.value;
            nd1 = termn1->child;
          }
          else
          {
            char *var1 = generate_name();

            ast_node *vartup = insert_temp(node, var1, termn1->child->t.a.ele_type);
            vartup->n.L.t.terminal = ID;

            Tuple *tyu = make_tuple(ASSIGNOP, termn1->child->n.L.t.value, termn1->child->next->n.L.t.value, var1, termn1->child, termn1->child->next, vartup);
            termn1->tuple_start = tyu;
            termn1->tuple_end = tyu;
            ar1 = var1;
            nd1 = NULL;
          }
        }
        else if (strcmp(termn1->name, "AIRTHMETICBOOL") == 0)
        {
          ar1 = termn1->tuple_end->result;
          nd1 = termn1->tuple_end->node3;
        }

        if (strcmp(termn2->name, "NUM") == 0)
        {
          ar2 = termn2->n.L.t.value;
          nd2 = termn2;
          termn2->tuple_start = NULL;
          termn2->tuple_end = NULL;
        }
        else if (strcmp(termn2->name, "RNUM") == 0)
        {
          ar2 = termn2->n.L.t.value;
          nd2 = termn2;
          termn2->tuple_start = NULL;
          termn2->tuple_end = NULL;
        }
        else if (strcmp(termn2->name, "PRINT_ARRAY") == 0)
        {
          if (termn2->child->next == NULL)
          {
            ar2 = termn2->child->n.L.t.value;
            nd2 = termn2->child;
          }
          else
          {
            char *var1 = generate_name();

            ast_node *vartup = insert_temp(node, var1, termn1->child->t.a.ele_type);
            vartup->n.L.t.terminal = ID;

            Tuple *tyu = make_tuple(ASSIGNOP, termn1->child->n.L.t.value, termn1->child->next->n.L.t.value, var1, termn1->child, termn1->child->next, vartup);
            termn2->tuple_start = tyu;
            termn2->tuple_end = tyu;
            ar2 = var1;
            nd2 = NULL;
          }
        }
        else if (strcmp(termn2->name, "AIRTHMETICBOOL") == 0)
        {
          ar2 = termn2->tuple_end->result;
          nd2 = termn2->tuple_end->node3;
        }

        tup = make_tuple(MUL, prevvar, termn1->tuple_end->result, vart, vartup /**/, termn1->tuple_end->node3, vartup2 /**/);
        Tuple *tup00 = NULL;
        if (termn1->tuple_start != NULL)
        {
          tup00 = termn1->tuple_start;
        }
        else if (termn2->tuple_start != NULL)
        {
          tup00 = termn2->tuple_start;
        }

        if (tup00 != NULL)
        {
          prevtup->next = tup00;
          tup00->next = tup;
        }
        else
        {
          prevtup->next = tup;
        }

        node->tuple_end = tup;
        prevtup = tup;
      }

      else if (strcmp(opn->name, "DIV") == 0)
      {
        char *ar1 = NULL;
        ast_node *nd1 = NULL;

        char *ar2 = NULL;
        ast_node *nd2 = NULL;
        if (strcmp(termn1->name, "NUM") == 0)
        {
          ar1 = termn1->n.L.t.value;
          nd1 = termn1;
          termn1->tuple_start = NULL;
          termn1->tuple_end = NULL;
        }
        else if (strcmp(termn1->name, "RNUM") == 0)
        {
          ar1 = termn1->n.L.t.value;
          nd1 = termn1;
          termn1->tuple_start = NULL;
          termn1->tuple_end = NULL;
        }
        else if (strcmp(termn1->name, "PRINT_ARRAY") == 0)
        {
          if (termn1->child->next == NULL)
          {
            ar1 = termn1->child->n.L.t.value;
            nd1 = termn1->child;
          }
          else
          {
            char *var1 = generate_name();

            ast_node *vartup = insert_temp(node, var1, termn1->child->t.a.ele_type);
            vartup->n.L.t.terminal = ID;

            Tuple *tyu = make_tuple(ASSIGNOP, termn1->child->n.L.t.value, termn1->child->next->n.L.t.value, var1, termn1->child, termn1->child->next, vartup);
            termn1->tuple_start = tyu;
            termn1->tuple_end = tyu;
            ar1 = var1;
            nd1 = NULL;
          }
        }
        else if (strcmp(termn1->name, "AIRTHMETICBOOL") == 0)
        {
          ar1 = termn1->tuple_end->result;
          nd1 = termn1->tuple_end->node3;
        }

        if (strcmp(termn2->name, "NUM") == 0)
        {
          ar2 = termn2->n.L.t.value;
          nd2 = termn2;
          termn2->tuple_start = NULL;
          termn2->tuple_end = NULL;
        }
        else if (strcmp(termn2->name, "RNUM") == 0)
        {
          ar2 = termn2->n.L.t.value;
          nd2 = termn2;
          termn2->tuple_start = NULL;
          termn2->tuple_end = NULL;
        }
        else if (strcmp(termn2->name, "PRINT_ARRAY") == 0)
        {
          if (termn2->child->next == NULL)
          {
            ar2 = termn2->child->n.L.t.value;
            nd2 = termn2->child;
          }
          else
          {
            char *var1 = generate_name();

            ast_node *vartup = insert_temp(node, var1, termn1->child->t.a.ele_type);
            vartup->n.L.t.terminal = ID;

            Tuple *tyu = make_tuple(ASSIGNOP, termn1->child->n.L.t.value, termn1->child->next->n.L.t.value, var1, termn1->child, termn1->child->next, vartup);
            termn2->tuple_start = tyu;
            termn2->tuple_end = tyu;
            ar2 = var1;
            nd2 = NULL;
          }
        }
        else if (strcmp(termn2->name, "AIRTHMETICBOOL") == 0)
        {
          ar2 = termn2->tuple_end->result;
          nd2 = termn2->tuple_end->node3;
        }

        tup = make_tuple(DIV, prevvar, termn1->tuple_end->result, vart, NULL /**/, termn1->tuple_end->node3, NULL /**/);
        Tuple *tup00 = NULL;
        if (termn1->tuple_start != NULL)
        {
          tup00 = termn1->tuple_start;
        }
        else if (termn2->tuple_start != NULL)
        {
          tup00 = termn2->tuple_start;
        }

        if (tup00 != NULL)
        {
          prevtup->next = tup00;
          tup00->next = tup;
        }
        else
        {
          prevtup->next = tup;
        }

        node->tuple_end = tup;
        prevtup = tup;
        vartup=vartup2;
      }
    }
  }
  else
  {
    char *ar1 = NULL;
    ast_node *nd1 = NULL;

    if (strcmp(termn1->name, "NUM") == 0)
    {

      char *var1 = generate_name();

      ast_node *vartup = insert_temp(node, var1, INTEGER);
      vartup->n.L.t.terminal = ID;
      // if (vartup->n.L.t.terminal == ID)
      //   printf("\n VALUE %s\n", tokarray[termn1->n.L.t.terminal]);
      vartup->n.L.t.value = termn1->n.L.t.value;

      Tuple *tyu = make_tuple(ASSIGNOP, termn1->n.L.t.value, NULL, var1, termn1, NULL, vartup);
      node->tuple_start = tyu;
      node->tuple_end = tyu;
    }
    else if (strcmp(termn1->name, "RNUM") == 0)
    {

      char *var1 = generate_name();

      ast_node *vartup = insert_temp(node, var1, REAL);
      vartup->n.L.t.terminal = ID;

      vartup->n.L.t.value = termn1->n.L.t.value;

      Tuple *tyu = make_tuple(ASSIGNOP, termn1->n.L.t.value, NULL, var1, termn1, NULL, vartup);
      node->tuple_start = tyu;
      node->tuple_end = tyu;
    }
    else if (strcmp(termn1->name, "PRINT_ARRAY") == 0)
    {
      if (termn1->child->next == NULL)
      {

        char *var1 = generate_name();
        TOKEN tt;
        if (termn1->child->n.L.t.terminal == TRUE)
        {
          tt = BOOLEAN;
        }
        else if (termn1->child->n.L.t.terminal == FALSE)
        {
          tt = BOOLEAN;
        }
        else if (termn1->child->n.L.t.terminal == NUM)
        {
          tt = INTEGER;
        }
        else if (termn1->child->n.L.t.terminal == RNUM)
        {
          tt = REAL;
        }
        else if (termn1->child->n.L.t.terminal == INTEGER)
        {
          tt = INTEGER;
        }
        else if (termn1->child->n.L.t.terminal == REAL)
        {
          tt = REAL;
        }
        else if (termn1->child->n.L.t.terminal == ID)
        {
          tt = termn1->child->t.basic_type;
        }

        ast_node *vartup = insert_temp(node, var1, tt);
        vartup->n.L.t.terminal = ID;

        Tuple *tyu = make_tuple(ASSIGNOP, termn1->child->n.L.t.value, NULL, var1, termn1->child, NULL, vartup);
        node->tuple_start = tyu;
        node->tuple_end = tyu;
      }
      else
      {
        char *var1 = generate_name();

        ast_node *vartup = insert_temp(node, var1, termn1->child->t.a.ele_type);
        vartup->n.L.t.terminal = ID;

        Tuple *tyu = make_tuple(ASSIGNOP, termn1->child->n.L.t.value, termn1->child->next->n.L.t.value, var1, termn1->child, termn1->child->next, vartup);

        node->tuple_start = tyu;
        node->tuple_end = tyu;
      }
    }
    else if (strcmp(termn1->name, "AIRTHMETICBOOL") == 0)
    {
      node->tuple_start = termn1->tuple_start;
      node->tuple_end = termn1->tuple_end;
    }
  }
}

void process_DRIVER(ast_node *node, quadruple *list)
{
  ast_node *childn = node->child;

  ast_node *temp = childn;
  Tuple *finst = NULL;
  Tuple *finen = NULL;
  Tuple *prevtemp = NULL;
  while (strcmp(temp->name, "DECLARESTMT") == 0)
  {
    temp = temp->next;
  }
  if (temp != NULL)
  {
    //printf("in statemens");
    finst = temp->tuple_start;
    finen = temp->tuple_end;
    temp = temp->next;
  }
  prevtemp = finen;
  while (temp != NULL)

  {
    if (strcmp(temp->name, "DECLARESTMT") == 0)
    {
      temp = temp->next;
      continue;
    }
    prevtemp->next = temp->tuple_start;
    finen = temp->tuple_end;
    prevtemp = finen;
    temp = temp->next;
    //printf("in statemens");
  }

  Tuple *tup1 = make_tuple(FUNCTION, "DRIVER", NULL, NULL, NULL, NULL, NULL);
  tup1->next = finst;

  Tuple *tup2 = make_tuple(RET, "DRIVER", NULL, NULL, NULL, NULL, NULL);
  finen->next = tup2;

  node->tuple_start = tup1;
  node->tuple_end = tup2;

  add_tuple(list, node->tuple_start, node->tuple_end);
}
void process_STATEMENTS(ast_node *node, quadruple *list)
{
  ast_node *childn = node->child;

  ast_node *temp = childn;
  Tuple *finst = NULL;
  Tuple *finen = NULL;
  Tuple *prevtemp = NULL;
  while (strcmp(temp->name, "DECLARESTMT") == 0)
  {
    temp = temp->next;
  }
  if (temp != NULL)
  {
    //printf("in statemens");
    finst = temp->tuple_start;
    finen = temp->tuple_end;
    temp = temp->next;
  }
  prevtemp = finen;
  while (temp != NULL)
  {
    if (strcmp(temp->name, "DECLARESTMT") == 0)
    {
      temp = temp->next;
      continue;
    }
    prevtemp->next = temp->tuple_start;
    finen = temp->tuple_end;
    prevtemp = finen;
    temp = temp->next;
    //printf("in statemens");
  }
  node->tuple_start = finst;

  node->tuple_end = finen;
}
void process_UNARY(ast_node *node, quadruple *list)
{
  ast_node *temp = node->child;
  if (strcmp(temp->name, "PLUS") == 0)
  {

    if (temp->next->next == NULL && strcmp("AIRTHMETICEXPR", temp->next->name) != 0)
    {
      char *tvar = generate_name();
      ast_node *vartup = insert_temp(node, tvar, INTEGER);
      vartup->n.L.t.terminal = ID;

      /* tvar's type is same as temp->next*/

      Tuple *tup = make_tuple(U_PLUS, temp->next->n.L.t.value, NULL, tvar, temp->next, NULL, vartup /*  */);
      node->tuple_start = tup;
      node->tuple_end = tup;
    }
    else if (temp->next->next == NULL && strcmp("AIRTHMETICEXPR", temp->next->name) == 0)
    {
      char *tvar = generate_name();
      ast_node *vartup = insert_temp(node, tvar, INTEGER);
      vartup->n.L.t.terminal = ID;

      Tuple *tup = make_tuple(U_PLUS, temp->next->tuple_end->result, NULL, tvar, temp->next->tuple_end->node3, NULL, vartup /*  */);

      node->tuple_start = temp->next->tuple_start;
      temp->next->tuple_end->next = tup;
      node->tuple_end = tup;
    }
    else if (temp->next->next != NULL)
    {
      char *tvar1 = generate_name();
      ast_node *vartup = insert_temp(node, tvar1, INTEGER);
      vartup->n.L.t.terminal = ID;
      /* type of tvar1 is same as type of temp->next*/

      Tuple *tup = make_tuple(ASSIGNOP, temp->next->n.L.t.value, temp->next->next->n.L.t.value, tvar1, temp->next, temp->next->next, vartup /**/);

      char *tvar2 = generate_name();
      /* type same as tvar1*/
      ast_node *vartup2 = insert_temp(temp->next, tvar2, INTEGER);
      vartup2->n.L.t.terminal = vartup->n.L.t.terminal;

      Tuple *tup2 = make_tuple(U_PLUS, tvar1, NULL, tvar2, vartup /**/, NULL, vartup2 /**/);

      tup->next = tup2;
      node->tuple_start = tup;
      node->tuple_end = tup2;
    }
  }
  if (strcmp(temp->name, "MINUS") == 0)
  {

    if (temp->next->next == NULL && strcmp("AIRTHMETICEXPR", temp->next->name) != 0)
    {
      char *tvar = generate_name();

      ast_node *vartup = insert_temp(node, tvar, INTEGER);
      vartup->n.L.t.terminal = ID;

      Tuple *tup = make_tuple(U_MINUS, temp->next->n.L.t.value, NULL, tvar, temp->next, NULL, vartup);
      node->tuple_start = tup;
      node->tuple_end = tup;
    }
    else if (temp->next->next == NULL && strcmp("AIRTHMETICEXPR", temp->next->name) == 0)

    {
      char *tvar = generate_name();
      ast_node *vartup = insert_temp(node, tvar, INTEGER);
      vartup->n.L.t.terminal = ID;

      Tuple *tup = make_tuple(U_MINUS, temp->next->tuple_end->result, NULL, tvar, temp->next->tuple_end->node3, NULL, vartup /*  */);

      node->tuple_start = temp->next->tuple_start;
      temp->next->tuple_end->next = tup;
      node->tuple_end = tup;
    }
    else if (temp->next->next != NULL)
    {
      char *tvar1 = generate_name();
      ast_node *vartup = insert_temp(node, tvar1, INTEGER);
      vartup->n.L.t.terminal = ID;

      Tuple *tup = make_tuple(ASSIGNOP, temp->next->n.L.t.value, temp->next->next->n.L.t.value, tvar1, temp->next, temp->next->next, vartup);
      char *tvar2 = generate_name();
      ast_node *vartup2 = insert_temp(temp->next, tvar2, INTEGER);
      vartup2->n.L.t.terminal = vartup->n.L.t.terminal;

      Tuple *tup2 = make_tuple(U_MINUS, tvar1, NULL, tvar2, vartup, NULL, vartup2);
      tup->next = tup2;

      node->tuple_start = tup;
      node->tuple_end = tup2;
    }
  }
}
void process_ASSIGN(ast_node *node, quadruple *list)
{
  if (strcmp(node->child->next->name, "ASSINGOP") == 0)
  {
    ast_node *childn = node->child;
    ast_node *exp = childn->next->next;
    Tuple *temp = exp->tuple_end;
    Tuple *tup0 = exp->tuple_start;

    Tuple *tup = make_tuple(ASSIGNOP, temp->result, NULL, childn->n.L.t.value, temp->node3, NULL, childn);
    temp->next = tup;
    node->tuple_start = tup0;
    node->tuple_end = tup;
  }
  else
  {
    ast_node *childn = node->child;
    ast_node *ind = childn->next;
    ast_node *exp = childn->next->next->next;
    Tuple *temp = exp->tuple_end;
    Tuple *tup0 = exp->tuple_start;

    Tuple *tup = make_tuple(ASSIGNOP, temp->result, ind->n.L.t.value, childn->n.L.t.value, temp->node3, ind, childn);
    temp->next = tup;
    node->tuple_start = tup0;
    node->tuple_end = tup;
  }
}
void process_PRINT(ast_node *node, quadruple *list)
{
  if (strcmp(node->child->name, "PRINT_ARRAY") == 0)
  {

    if (node->child->child->next == NULL)
    {
      Tuple *tup = make_tuple(PRINT, node->child->child->n.L.t.value, NULL, NULL, node->child->child, NULL, NULL);

      node->tuple_start = tup;
      node->tuple_end = tup;
    }
    else
    {

      Tuple *tup = make_tuple(PRINT, node->child->child->n.L.t.value, node->child->child->next->n.L.t.value, NULL, node->child->child, node->child->child->next, NULL);

      node->tuple_start = tup;
      node->tuple_end = tup;
    }
  }
  else
  {
    Tuple *tup = make_tuple(PRINT, node->child->n.L.t.value, NULL, NULL, node->child, NULL, NULL);
    node->tuple_start = tup;
    node->tuple_end = tup;
  }
}
void process_GET_VALUE(ast_node *node, quadruple *list)
{
  Tuple *tup = make_tuple(GET_VALUE, node->n.L.t.value, NULL, NULL, node, NULL, NULL);

  node->tuple_start = tup;
  node->tuple_end = tup;
}

void process_SWITCH(ast_node *node, quadruple *list)
{
  ast_node *child1 = node->child;
  ast_node *stmtnode = child1->next;
  ast_node *defnode = stmtnode->next;

  ast_node *temp = stmtnode->child;

  char *var1 = child1->n.L.t.value;
  char *var2 = generate_name();
  /* Type of var2 is boolean*/
  ast_node *vartup = insert_temp(node, var2, BOOLEAN);
  vartup->n.L.t.terminal = ID;

  char *test = generate_label();

  Tuple *temp0 = make_tuple(GOTO, test, NULL, NULL, NULL, NULL, NULL);
  Tuple *temp01 = make_tuple(LABEL, test, NULL, NULL, NULL, NULL, NULL);

  char *lab = generate_label();
  char *next = generate_label();

  Tuple *temp1 = make_tuple(LABEL, lab, NULL, NULL, NULL, NULL, NULL);
  temp0->next = temp1;

  Tuple *ass = make_tuple(EQ, temp->n.L.t.value, var1, var2, temp, child1, vartup /****/);
  temp01->next = ass;

  Tuple *ifcon = make_tuple(IF, lab, NULL, var2, NULL, NULL, vartup /**/);
  ass->next = ifcon;

  ast_node *st = temp->next;
  temp1->next = st->tuple_start;

  // st->tuple_start->prev=temp1;
  // st->tuple_start->prev->next=temp1;
  // temp1->prev=st->tuple_start->prev;

  Tuple *temp2 = make_tuple(GOTO, next, NULL, NULL, NULL, NULL, NULL);
  st->tuple_end->next = temp2;
  temp = temp->next->next;

  Tuple *prevtemp = temp2;
  Tuple *prevtemp2 = ifcon;

  while (temp->next->next != NULL)
  {
    lab = generate_label();

    temp1 = make_tuple(LABEL, lab, NULL, NULL, NULL, NULL, NULL);
    prevtemp->next = temp1;

    st = temp->next;
    temp1->next = st->tuple_start;

    // st->tuple_start->prev=temp1;
    // st->tuple_start->prev->next=temp1;
    // temp1->prev=st->tuple_start->prev;
    var2 = generate_name();

    vartup = insert_temp(node, var2, BOOLEAN);
    vartup->n.L.t.terminal = ID;

    /* type is boolean*/

    temp2 = make_tuple(GOTO, next, NULL, NULL, NULL, NULL, NULL);
    prevtemp = temp2;

    st->tuple_end->next = temp2;

    ass = make_tuple(EQ, temp->n.L.t.value, var1, var2, temp, child1, vartup);
    prevtemp2->next = ass;
    ifcon = make_tuple(IF, lab, NULL, var2, NULL, NULL, vartup /**/);
    ass->next = ifcon;
    prevtemp2 = ifcon;

    temp = temp->next->next;
  }
  lab = generate_label();

  temp1 = make_tuple(LABEL, lab, NULL, NULL, NULL, NULL, NULL);
  prevtemp->next = temp1;

  st = temp->next;
  temp1->next = st->tuple_start;

  // st->tuple_start->prev=temp1;
  // st->tuple_start->prev->next=temp1;
  // temp1->prev=st->tuple_start->prev;
  var2 = generate_name();

  vartup = insert_temp(node, var2, BOOLEAN);
  vartup->n.L.t.terminal = ID;

  temp2 = make_tuple(GOTO, next, NULL, NULL, NULL, NULL, NULL);
  prevtemp = temp2;
  st->tuple_end->next = temp2;

  temp2->next = temp01;

  ass = make_tuple(EQ, temp->n.L.t.value, var1, var2, temp, child1, vartup);
  prevtemp2->next = ass;

  ifcon = make_tuple(IF, lab, NULL, var2, NULL, NULL, vartup);
  ass->next = ifcon;

  Tuple *lastt = NULL;
  if (defnode == NULL)
  {
    lastt = make_tuple(LABEL, next, NULL, NULL, NULL, NULL, NULL);
    ifcon->next = lastt;
  }
  else
  {
    lab = generate_label();
    Tuple *defa = make_tuple(LABEL, lab, NULL, NULL, NULL, NULL, NULL);
    ifcon->next = defa;
    st = defnode->child->child;
    defa->next = st->tuple_start;

    lastt = make_tuple(LABEL, next, NULL, NULL, NULL, NULL, NULL);
    st->tuple_end->next = lastt;
  }

  node->tuple_start = temp0;
  node->tuple_end = lastt;

  // list->last->next=temp0;
  // list->last=lastt;
}
void process_WHILE(ast_node *node, quadruple *list)
{
  ast_node *childn = node->child;

  ast_node *st = childn->next;

  char *label1 = generate_label();
  char *label2 = generate_label();
  char *label3 = generate_label();

  Tuple *tup00 = childn->tuple_start;
  Tuple *tup01 = childn->tuple_end;

  Tuple *tup1 = make_tuple(LABEL, label1, NULL, NULL, NULL, NULL, NULL);
  Tuple *tup2 = make_tuple(LABEL, label2, NULL, NULL, NULL, NULL, NULL);
  Tuple *tup3 = make_tuple(LABEL, label3, NULL, NULL, NULL, NULL, NULL);
  Tuple *tup4 = make_tuple(IF, label3, NULL, childn->tuple_end->result, NULL, NULL, childn);
  Tuple *tup5 = make_tuple(GOTO, label1, NULL, NULL, NULL, NULL, NULL);
  Tuple *tup6 = make_tuple(GOTO, label2, NULL, NULL, NULL, NULL, NULL);

  // childn->tuple_end->next=tup2;
  // tup2->prev=childn->tuple_end;
  tup01->next = tup2;
  tup2->next = tup4;
  // tup4->prev=tup2;

  tup4->next = tup5;
  // tup5->prev=tup4;

  tup5->next = tup3;
  // tup3->prev=tup5;

  tup3->next = st->tuple_start;
  // st->tuple_start->prev->next=tup3;

  // st->tuple_start->prev=tup3;
  st->tuple_end->next = tup6;

  // tup6->prev=st->tuple_end;
  tup6->next = tup1;

  node->tuple_start = tup00;
  node->tuple_end = tup1;
  // list->last=tup1;
}

void process_FOR(ast_node *node, quadruple *list)
{

  ast_node *childnode1 = node->child;
  ast_node *childnode2 = childnode1->next;
  ast_node *childnode3 = childnode2->next;
  //printf("fwf%s\n", tokarray[childnode1->n.L.t.terminal]);
  char *label1 = generate_label();
  char *label2 = generate_label();
  char *label3 = generate_label();

  char *var1 = generate_name();
  /*type of var 1 is boolean */
  ast_node *vartup = insert_temp(node, var1, BOOLEAN);
  vartup->n.L.t.terminal = ID;

  Tuple *tup01 = make_tuple(ASSIGNOP, childnode2->child->n.L.t.value, NULL, childnode1->n.L.t.value, childnode2->child, NULL, childnode1);
  Tuple *tup02 = make_tuple(LE, childnode1->n.L.t.value, childnode2->child->next->n.L.t.value, var1, childnode1, childnode2->child, vartup /**/);

  //tup01->next = tup02;

  Tuple *tup1 = make_tuple(LABEL, label1, NULL, NULL, NULL, NULL, NULL);
  Tuple *tup2 = make_tuple(LABEL, label2, NULL, NULL, NULL, NULL, NULL);
  Tuple *tup3 = make_tuple(LABEL, label3, NULL, NULL, NULL, NULL, NULL);

  Tuple *tup4 = make_tuple(IF, label3, NULL, var1, NULL, NULL, vartup/**/); //DONT HAVE A NODE FOR TEMPORARY VARIABLE HOWW TO TELL THE SCOPE
  Tuple *tup5 = make_tuple(GOTO, label1, NULL, NULL, NULL, NULL, NULL);
  Tuple *tup6 = make_tuple(GOTO, label2, NULL, NULL, NULL, NULL, NULL);
  tup01->next=tup2;
  tup2->next=tup02;

  char *n1 = "1";
  ast_node *nd = (ast_node *)malloc(sizeof(ast_node));
  nd->n.L.t.terminal = NUM;
  nd->n.L.t.value = n1;
  nd->tuple_start = NULL;
  nd->tuple_end = NULL;
  Tuple *tup7 = make_tuple(PLUS, childnode1->n.L.t.value, n1, childnode1->n.L.t.value, childnode1, nd, childnode1);
  // tup02->next = tup2;

  tup02->next = tup4;
  // tup4->prev=tup2;

  tup4->next = tup5;
  // tup5->prev=tup4;

  tup5->next = tup3;
  // tup3->prev=tup5;

  tup3->next = childnode3->tuple_start;
  // childnode3->tuple_start->prev->next=tup3;

  // childnode3->tuple_start->prev=tup3;
  childnode3->tuple_end->next = tup7;
  tup7->next = tup6;
  // tup6->prev=childnode3->tuple_end;

  tup6->next = tup1;

  node->tuple_start = tup01; //
  node->tuple_end = tup1;
  // list->last=tup1;
}

quadruple *initialize_tuples()
{
  quadruple *qd = (quadruple *)malloc(sizeof(quadruple));
  qd->head = NULL;
  qd->last = NULL;

  return qd;
}

void checktype(ast_node *node, quadruple *list)
{
  // if(node->name=="RANGE")
  //  process_rangeop(node,list);
  // }
  // printf("%s  ", node->name);
  if (strcmp(node->name, "PROGRAM") == 0)
  {
    return;
  }
  else if (strcmp(node->name, "SWITCH") == 0)
  {
    process_SWITCH(node, list);
  }

  else if (strcmp(node->name, "WHILE") == 0)
  {
    process_WHILE(node, list);
  }
  else if (strcmp(node->name, "FOR") == 0)
  {
    process_FOR(node, list);
  }
  else if (strcmp(node->name, "GET_VALUE") == 0)
  {
    process_GET_VALUE(node, list);
  }
  else if (strcmp(node->name, "PRINT") == 0)
  {
    process_PRINT(node, list);
  }
  else if (strcmp(node->name, "ASSIGNMENTSTMT") == 0)
  {
    process_ASSIGN(node, list);
  }
  else if (strcmp(node->name, "UNARY") == 0)
  {
    process_UNARY(node, list);
  }

  else if (strcmp(node->name, "STATEMENTS") == 0)
  {
    if (strcmp(node->parent->name, "PROGRAM") == 0)
      process_DRIVER(node, list);

    else
      process_STATEMENTS(node, list);
  }

  else if (strcmp(node->name, "WHILE") == 0)
  {
    process_WHILE(node, list);
  }
  else if (strcmp(node->name, "FOR") == 0)
  {
    process_FOR(node, list);
  }
  else if (strcmp(node->name, "GET_VALUE") == 0)
  {
    process_GET_VALUE(node, list);
  }
  else if (strcmp(node->name, "PRINT") == 0)
  {
    process_PRINT(node, list);
  }
  else if (strcmp(node->name, "ASSIGNMENTSTMT") == 0)
  {
    process_ASSIGN(node, list);
  }
  else if (strcmp(node->name, "UNARY") == 0)
  {
    process_UNARY(node, list);
  }
  else if (strcmp(node->name, "AIRTHMETICBOOL") == 0) //1. TBD
  {
    process_ARITHBOOL(node, list);
  }
  else if (strcmp(node->name, "STATEMENTS") == 0)
  {
    if (strcmp(node->parent->name, "PROGRAM") == 0)
      process_DRIVER(node, list);

    else
      process_STATEMENTS(node, list);
  }
  else if (strcmp(node->name, "MODULE") == 0)
  {
    process_MODULE(node, list);
  }
  else if (strcmp(node->name, "MODULEREUSESTMT") == 0)
  {
    process_MODULEREUSE(node, list);
  }
  else if (strcmp(node->name, "OTHER_MODULES") == 0)
  {
    process_last(node, list);
  }
  else if (strcmp(node->name, "AIRTHMETICEXPR") == 0)
  {
    process_arith(node, list);
  }
  else if (strcmp(node->name, "AnyTerm") == 0)
  {
    process_AnyTerm(node, list);
  }
  else if ((strcmp(node->name, "TRUE") == 0) && (node->parent != NULL) && (strcmp(node->parent->name, "AIRTHMETICBOOL") == 0))
  {
    process_AnyTerm(node, list);
  }
  else if ((strcmp(node->name, "FALSE") == 0) && (node->parent != NULL) && (strcmp(node->parent->name, "AIRTHMETICBOOL") == 0))
  {
    process_AnyTerm(node, list);
  }
  else if (strcmp(node->name, "TERM") == 0)
  {
    process_TERM(node, list);
  }
  else
  {
    return;
  }
}

void generateIRUtil(ast_node *node, quadruple *list)
{

  if (node == NULL)
    return;
  ast_node *childnode = node->child;
  //printf("ndk");
  while (childnode != NULL)
  {
    generateIRUtil(childnode, list);
    childnode = childnode->next;
  }
  // printf("%s ", node->name);
  if (node != NULL)
    checktype(node, list);
}
quadruple *generateIR(ast_node *root) //THIS WILL BE CALLED for the first time
{
  label_no = 0;
  var_no = 0;
  quadruple *list = initialize_tuples();

  generateIRUtil(root, list);
  return list;
}

void print_tuple(Tuple *temp)
{
  char *null = "NULL";
  if (temp->op != -1)
    printf("%-15s", tokarray[temp->op]);
  else
    printf("%-15s", null);

  if (temp->arg1 != NULL)
    printf("%-15s", temp->arg1);
  else
    printf("%-15s", null);

  if (temp->arg2 != NULL)
    printf("%-15s", temp->arg2);
  else
    printf("%-15s", null);

  if (temp->result != NULL)
    printf("%-15s", temp->result);
  else
    printf("%-15s", null);

  printf("\n");
}

void print_ir_code(quadruple *list)
{

  printf("\n\n---------------------------Printing Intermediate Code Quadruples----------------------------\n\n");
  char *arg1 = "arg1";
  char *arg2 = "arg2";
  char *result = "result";
  char *op = "Op";
  printf("%-15s%-15s%-15s%-15s\n\n", op, arg1, arg2, result);

  Tuple *temp = list->head;
  char *null = "NULL";
  while (temp != NULL)
  {
    // print("qvfcbfnoyrpung.pbz/pung/frperg+ebbz")
    print_tuple(temp);
    temp = temp->next;
  }

  printf("\n\n-------------------------------Intermediate Code Printed-------------------------------\n\n");
}