//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)



#include <math.h>
#include <string.h>
#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include "pra.h"
#include "astDef.h"
#include "symbol_table.h"
char *tokarray1[] = {"eps", "$", "NUM", "RNUM", "INTEGER", "REAL", "ID", "BOOLEAN", "OF", "ARRAY", "START", "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "RECORD", "TAGGED", "UNION", "GET_VALUE", "PRINT", "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS", "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "ENDDEF", "DRIVERDEF", "DRIVERENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "LABEL", "GOTO", "IF", "U_MINUS", "U_PLUS", "FUNCTION", "RET", "CALL", "PARAM", "RETURN"};


// struct tuple{
//         TOKEN op;
//         char* arg1;
//         char* arg2;
//         char* result;
//         struct tuple* next;
//         struct ast_node *node1, *node2, *node3;
// };

// typedef struct tuple Tuple;

// struct quadruple{
//         Tuple* head;
//         Tuple* last;
//         int total_tuples;
// };
// typedef struct quadruple quadruple;

int rl=1; 

struct AR{
    char name[20];
    int size;
};

struct AR AR_info[7]; 

int global_AR_index=0;
int label=0;

#include "codegenDef.h"


v_node * get_info(char * name, ast_node* root){
int pos = compute_hash_sk(name);
if(root->scope_tag == -1) return NULL;

if(root->scope_tag == 0){
v_node * ans = (v_node*)malloc(sizeof(v_node));
strcpy(ans->v_name, name);
ans->next =  NULL;
v_list * ptr = root->table_ptr.fun_ptr->hash_f.input;
     while(ptr!= NULL){
        if(strcmp(name,ptr->v.v_name) ==0){
            ans->hash_var = ptr->v;            
            return ans;
        }
        ptr=ptr->next;
     }
     ptr = root->table_ptr.fun_ptr->hash_f.output;
     while(ptr!= NULL){
        if(strcmp(name,ptr->v.v_name) ==0){
            ans->hash_var = ptr->v;            
            return ans;
        }
        ptr=ptr->next;    
}
    }

    else{
    v_node * ptr = root->table_ptr.inner_ptr->hash_var[pos];
    while(ptr != NULL){
    if(strcmp(name, ptr->v_name) == 0) return ptr;
    ptr  = ptr->next;
    }
    return ptr;
    }
 }
 
 
 v_node * get_info1(char* name,  union s_ptr scope, int tag)
 {
int pos = compute_hash_sk(name);
if(tag == -1) return NULL;

if(tag == 0){
v_node * ans = (v_node*)malloc(sizeof(v_node));
strcpy(ans->v_name, name);
ans->next =  NULL;
v_list * ptr = scope.fun_ptr->hash_f.input;
     while(ptr!= NULL){
        if(strcmp(name,ptr->v.v_name) ==0){
            ans->hash_var = ptr->v;            
            return ans;
        }
        ptr=ptr->next;
     }
     ptr = scope.fun_ptr->hash_f.output;
     while(ptr!= NULL){
        if(strcmp(name,ptr->v.v_name) ==0){
            ans->hash_var = ptr->v;            
            return ans;
        }
        ptr=ptr->next;    
}
    }

    else{
    v_node * ptr = scope.inner_ptr->hash_var[pos];
    while(ptr != NULL){
    if(strcmp(name, ptr->v_name) == 0) return ptr;
    ptr  = ptr->next;
    }
    return ptr;
    }
 }




short extract_int_value(char* arg){
        int len=strlen(arg);
        short num=0;
        for(int i=0; i<len; i++){
            num=num*10+(arg[i]-'0');
        }
        return num;
}


void calculate_AR_size(Tuple* tuple){
        int i=0;
        while(tuple!=NULL){

            if(tuple->op==FUNCTION){
                int sum=0;
                strcpy(AR_info[i].name,tuple->arg1);
                AR_info[i].size=240;
                i++;
                // while(tuple->op!=RET){
                //     if(tuple->result!=NULL)
                //     {
                //     v_node* res_ptr=get_info(tuple->result, tuple->node3);
                //     if(res_ptr->hash_var.tag==1){
                //         if(res_ptr->hash_var.t.basic_type==INTEGER)
                //             sum=sum+2;
                //         else if(res_ptr->hash_var.t.basic_type==BOOLEAN)
                //             sum=sum+1;
                //         else if(res_ptr->hash_var.t.basic_type==REAL)
                //             sum+=4;
                //     }
                //     else{
                //         if(res_ptr->hash_var.is_static==1){
                //             short low=extract_int_value(res_ptr->hash_var.t.a.low.value);
                //             short high=extract_int_value(res_ptr->hash_var.t.a.high.value);
                //             sum=sum+(high-low+1)+8;
                //         }
                //         else
                //             sum+=8;
                //     }
                // }
                //     tuple=tuple->next;
                //     if(sum==0)
                //         sum=50;
                // }
                //char[i]=tuple->arg1+'='+sum;
                // strcpy(AR_info[i].name,tuple->arg1);
                // AR_info[i].size=sum;
                // i++;
            }
            tuple=tuple->next;
        }
}


// v_node* get_info1(char* arg,  union s_ptr scope, int tag){ //gives offset and dataType
//     int pos = compute_hash(arg);
//     v_node* ptr;
//     if(scstrcmp(ope.fun_ptr,NULL ==0)&& scopstrcmp(e.inner_ptr,NULL)==0)
//         return NULL;
//     if(tag==0)
//         ptr = scope.fun_ptr->hash_f.def->hash_var[pos];
//     else
//         ptr = scope.inner_ptr->hash_var[pos];

//     while(ptr!=NULL)
//     {
//         if(strcmp(arg,ptr->v_name)==0 )
//         {
//             return ptr;
//         }
//             ptr=ptr->next;
//     }
//     return ptr;
// }

void generate_code(quadruple* quad, FILE* fp)
{

    fprintf(fp, "extern printf\nextern scanf\nSECTION .data\nfmt1: db \"Input: Enter an integer value\", 10, 0\nfmt2: db \"Input: Enter a real value\", 10, 0\nfmt3: db \"Input: Enter a boolean value\", 10, 0\nfmtinput1: db \"%%d\",0\nfmtinput2: db \"%%f\",0\n");
    fprintf(fp,"fmt4: db \"Input: Enter %%d array elements of integer type for range \",0\nfmtto: db \"to \",0\nfmt5: db \"Input: Enter %%d array elements of real type for range\",0\nfmt6: db \"Input: Enter %%d array elements of boolean type for range\",0\n");
    fprintf(fp,"\nfmtarray: db \"Output:\",0\nfmtint:   db \"%%d \",0\nfmtreal:  db\"%%f \",0\nTr: db\"TRUE \",0\nFa:   db\"FALSE \",0\nNL: db \"\",10,0\nfmterror: db\"RUN TIME ERROR:  Array index out of bound\",10, 0\n\n\n");
    fprintf(fp, "SECTION .text\nglobal main\n");
     Tuple* tuple=quad->head;

    calculate_AR_size(tuple);
// strcpy(AR_info[0].name,tuple->arg1);
//                 AR_info[0].size=240;
    tuple=quad->head;

    while(tuple!=NULL){
            process_tuple(tuple, fp);
            tuple= tuple->next;
    }
        fclose(fp);
}


void process_FUNCTION(Tuple* tuple, FILE* fp)
{ 
    for(int i=0; i<7; i++)
    {
        if(strcmp(tuple->arg1, AR_info[i].name)==0)
        {
        global_AR_index=i;
        break;
        }
    }

    if(strcmp(AR_info[global_AR_index].name,"DRIVER")==0)
    {
      fprintf(fp, "%s:\n", "main");
      fprintf(fp, "push\trbp\nmov\trbp, rsp\nsub\trsp, 400\n"); 
    } 
    else{
        fprintf(fp, "%s:\n", AR_info[global_AR_index].name);
        fprintf(fp, "push\trbp\nmov\tr15, rbp\nmov\trbp, rsp\nmov\t r14,rsp\nsub\t rsp,128\n");
    }
}

void process_RET(Tuple* tuple, FILE* fp)
{
    if(strcmp(tuple->arg1, "DRIVER")==0)
        fprintf(fp, "leave\nret\n");
    else
        fprintf(fp, "mov\t rsp,r14\npop\trbp\nmov\trbp,r15\nret\n");
} 

void process_ASSIGNOP(Tuple* tuple, FILE* fp)
{


            v_node* lhs_ptr=get_info(tuple->result, tuple->node3);

            if(lhs_ptr->hash_var.tag==1)
            {

                
                 if(tuple->node1->n.L.t.terminal==ID && tuple->arg2==NULL)
                 {
                     
                    v_node* rhs_ptr=get_info(tuple->arg1, tuple->node1);

                    if(lhs_ptr->hash_var.t.basic_type==INTEGER)
                    {
                        if(tuple->node1->scope_tag==1)
                            fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", rhs_ptr->hash_var.offset);
                         else
                             fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", rhs_ptr->hash_var.offset);
                        if(tuple->node3->scope_tag==1)
                            fprintf(fp, "mov\tDWORD[rbp-%d], eax\n", lhs_ptr->hash_var.offset);
                        else
                        fprintf(fp, "mov\tDWORD[rbp+24+%d], eax\n", lhs_ptr->hash_var.offset);   
                     }
                    else
                    {
                         if(tuple->node1->scope_tag==1)
                            fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", rhs_ptr->hash_var.offset);
                          else
                             fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", rhs_ptr->hash_var.offset);

                         if(tuple->node3->scope_tag==1)
                            fprintf(fp, "mov\tDWORD[rbp-%d], eax\n", lhs_ptr->hash_var.offset);
                            else
                            fprintf(fp, "mov\tDWORD[rbp+24+%d], eax\n", lhs_ptr->hash_var.offset);
                     }
                }
                 else if(tuple->node1->n.L.t.terminal==ID && tuple->arg2!=NULL)
                 {
                    v_node* ptr=get_info(tuple->arg1, tuple->node1);
                    v_node* ptr2;
                    if(strcmp(tuple->node2->name,"NUM")!=0)
                        ptr2=get_info(tuple->arg2, tuple->node2);
                    else
                        ptr2=NULL;
                    if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal==NUM)
                    {
                        fprintf(fp,"mov\tr12,%d\nmov\tr14,%d\n",atoi(ptr->hash_var.t.a.low.value),atoi(ptr->hash_var.t.a.high.value));        
                    }
                    else
                    {
                        v_node* lowptr;
                        v_node* highptr;
                        if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal!=NUM)
                        {
                            highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                            if(ptr->hash_var.t.a.tag_high==1)
                                fprintf(fp,"mov\tr12,%d\nmovsx\tr14,DWORD[rbp-%d]\n",atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
                            else
                                fprintf(fp,"mov\tr12,%d\nmovsx\tr14,DWORD[rbp+24+%d]\n",atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
                        }
                        else if(ptr->hash_var.t.a.low.terminal!=NUM && ptr->hash_var.t.a.high.terminal==NUM)
                        {  
                            lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                            if(ptr->hash_var.t.a.tag_low==1)
                                fprintf(fp,"movsx\tr12,DWORD[rbp-%d]\nmov\tr14,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
                            else
                                fprintf(fp,"movsx\tr12,DWORD[rbp+24+%d]\nmov\tr14,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
                        }
                        else
                        {
                            lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                            highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                            if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==1)
                                fprintf(fp,"movsx\tr12,DWORD[rbp-%d]\nmovsx\tr14,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==0)
                                fprintf(fp,"movsx\tr12,DWORD[rbp-%d]\nmovsx\tr14,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else if(ptr->hash_var.t.a.tag_low==0 && ptr->hash_var.t.a.tag_high==1)
                                fprintf(fp,"movsx\tr12,DWORD[rbp+24+%d]\nmovsx\tr14,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else
                                fprintf(fp,"movsx\tr12,DWORD[rbp+24+%d]\nmovsx\t14,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                        }
                    }
                    if(ptr2!=NULL && tuple->node2->scope_tag==1)
                        fprintf(fp,"movsx\trax,DWORD[rbp-%d]\n",ptr2->hash_var.offset);
                    else if(ptr2!=NULL && tuple->node2->scope_tag==0)
                        fprintf(fp,"movsx\trax,DWORD[rbp+24+%d]\n",ptr2->hash_var.offset);
                    else
                        fprintf(fp,"mov\trax,%d\n",atoi(tuple->node2->n.L.t.value));
                    fprintf(fp,"cmp\trax,r12\njl PL%d\ncmp\tr14,rax\njl\tPL%d\nmov\tr13,QWORD[rbp-%d]\n",label,label,ptr->hash_var.offset);
                    fprintf(fp,"sub\trax,r12\n");
                    if(ptr->hash_var.t.a.ele_type==INTEGER)
                    {
                        if(tuple->node3->scope_tag==1)
                            fprintf(fp,"mov\teax,DWORD[r13+rax*4]\nmov\tDWORD[rbp-%d],eax\n",lhs_ptr->hash_var.offset);
                        else
                            fprintf(fp,"mov\teax,DWORD[r13+rax*4]\nmov\tDWORD[rbp+24+%d],eax\n",lhs_ptr->hash_var.offset);
                    }
                    else if(ptr->hash_var.t.a.ele_type==REAL)
                        fprintf(fp,"movss\txmm0,DWORD[r13+rax*4]\nmovss\tDWORD[rbp-%d],xmm0\n",lhs_ptr->hash_var.offset);
                    else
                    {
                        if(tuple->node3->scope_tag==1)
                            fprintf(fp,"mov\teax,BYTE[r13+rax*4]\nmov\tBYTE[rbp-%d],al\n",lhs_ptr->hash_var.offset);
                        else
                            fprintf(fp,"mov\teax,BYTE[r13+rax*4]\nmov\tBYTE[rbp+24+%d],al\n",lhs_ptr->hash_var.offset);
                    }
                    fprintf(fp,"jmp\tPL%d\nPL%d:\nmov\tedi,fmterror\ncall\tprintf\nleave\nret\nPL%d:\n",label+1,label,label+1);
                    label+=2;
                 }
             else 
             {
                 if(tuple->node1->n.L.t.terminal==NUM)
                 {
                     int num=extract_int_value(tuple->arg1);   
                     fprintf(fp, "mov\teax, %d\n", num);
                     if(tuple->node3->scope_tag==1)
                          fprintf(fp, "mov\tDWORD[rbp-%d], eax\n", lhs_ptr->hash_var.offset);
                     else
                         fprintf(fp, "mov\tDWORD[rbp+24+%d], eax\n", lhs_ptr->hash_var.offset);
                }
                 else if(tuple->node1->n.L.t.terminal==TRUE)
                 {
                            //int num=1;
                    fprintf(fp, "mov\teax, %d\n", 1);
                    if(tuple->node3->scope_tag==1)
                          fprintf(fp, "mov\tDWORD[rbp-%d], eax\n", lhs_ptr->hash_var.offset);
                    else
                            fprintf(fp, "mov\tDWORD[rbp+24+%d], eax\n", lhs_ptr->hash_var.offset);
                }
                else if(tuple->node1->n.L.t.terminal==FALSE)
                {
                            //int num=0;
                    fprintf(fp, "mov\teax, %d\n", 0);
                    if(tuple->node3->scope_tag==1)
                         fprintf(fp, "mov\tDWORD[rbp-%d], eax\n", lhs_ptr->hash_var.offset);
                    else
                          fprintf(fp, "mov\tDWORD[rbp+24+%d], eax\n", lhs_ptr->hash_var.offset);
                }
              //  fprintf(fp,"++++++++++++++");
            }
        }
            else
            {
                if(tuple->node1->n.L.t.terminal==ID && tuple->arg2==NULL)
                {
                    v_node* ptr=lhs_ptr;
                    if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal==NUM)
                    {
                        fprintf(fp,"mov\tr12,%d\nmov\tr14,%d\n",atoi(ptr->hash_var.t.a.low.value),atoi(ptr->hash_var.t.a.high.value));        
                    }
                    else
                    {
                        v_node* lowptr;v_node* highptr;
                        if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal!=NUM)
                        {
                            highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                            if(ptr->hash_var.t.a.tag_high==1)
                                fprintf(fp,"mov\tr12,%d\nmovsx\tr14,DWORD[rbp-%d]\n",atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
                            else
                                fprintf(fp,"mov\tr12,%d\nmovsx\tr14,DWORD[rbp+24+%d]\n",atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
                        }
                        else if(ptr->hash_var.t.a.low.terminal!=NUM && ptr->hash_var.t.a.high.terminal==NUM)
                        {  
                            lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                            if(ptr->hash_var.t.a.tag_low==1)
                                fprintf(fp,"movsx\tr12,DWORD[rbp-%d]\nmov\tr14,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
                            else
                                fprintf(fp,"movsx\tr12,DWORD[rbp+24+%d]\nmov\tr14,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
                        }
                        else
                        {
                            lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                            highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                            if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==1)
                                fprintf(fp,"movsx\tr12,DWORD[rbp-%d]\nmovsx\tr14,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==0)
                                fprintf(fp,"movsx\tr12,DWORD[rbp-%d]\nmovsx\tr14,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else if(ptr->hash_var.t.a.tag_low==0 && ptr->hash_var.t.a.tag_high==1)
                                fprintf(fp,"movsx\tr12,DWORD[rbp+24+%d]\nmovsx\tr14,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else
                                fprintf(fp,"movsx\tr12,DWORD[rbp+24+%d]\nmovsx\tr14,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                        }

                    }
                    v_node* ptr1=get_info(tuple->arg1, tuple->node1);
                    if(ptr1->hash_var.t.a.low.terminal==NUM && ptr1->hash_var.t.a.high.terminal==NUM)
                    {
                        fprintf(fp,"mov\tr13,%d\nmov\tr15,%d",atoi(ptr1->hash_var.t.a.low.value),atoi(ptr1->hash_var.t.a.high.value));        
                    }
                    else
                    {
                        v_node* lowptr;
                        v_node* highptr;
                        if(ptr1->hash_var.t.a.low.terminal==NUM && ptr1->hash_var.t.a.high.terminal!=NUM)
                        {
                            highptr=get_info1(ptr1->hash_var.t.a.high.value,ptr1->hash_var.t.a.scope_high,ptr1->hash_var.t.a.tag_high);
                            if(ptr1->hash_var.t.a.tag_high==1)
                                fprintf(fp,"mov\tr13,%d\nmovsx\tr15,DWORD[rbp-%d]\n",atoi(ptr1->hash_var.t.a.low.value),highptr->hash_var.offset);
                            else
                                fprintf(fp,"mov\tr13,%d\nmovsx\tr15,DWORD[rbp+24+%d]\n",atoi(ptr1->hash_var.t.a.low.value),highptr->hash_var.offset);
                        }
                        else if(ptr1->hash_var.t.a.low.terminal!=NUM && ptr1->hash_var.t.a.high.terminal==NUM)
                        {
                            lowptr=get_info1(ptr1->hash_var.t.a.low.value,ptr1->hash_var.t.a.scope_low,ptr1->hash_var.t.a.tag_low);
                            if(ptr1->hash_var.t.a.tag_low==1)
                                fprintf(fp,"movsx\tr13,DWORD[rbp-%d]\nmov\tr15,%d\n",lowptr->hash_var.offset,atoi(ptr1->hash_var.t.a.high.value));
                            else
                                fprintf(fp,"movsx\tr13,DWORD[rbp+24+%d]\nmov\tr15,%d\n",lowptr->hash_var.offset,atoi(ptr1->hash_var.t.a.high.value));
                        }
                        else
                        {
                            lowptr=get_info1(ptr1->hash_var.t.a.low.value,ptr1->hash_var.t.a.scope_low,ptr1->hash_var.t.a.tag_low);
                            highptr=get_info1(ptr1->hash_var.t.a.high.value,ptr1->hash_var.t.a.scope_high,ptr1->hash_var.t.a.tag_high);
                            if(ptr1->hash_var.t.a.tag_low==1 && ptr1->hash_var.t.a.tag_high==1)
                                fprintf(fp,"movsx\tr13,DWORD[rbp-%d]\nmovsx\tr15,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else if(ptr1->hash_var.t.a.tag_low==1 && ptr1->hash_var.t.a.tag_high==0)
                                fprintf(fp,"movsx\tr13,DWORD[rbp-%d]\nmovsx\tr15,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else if(ptr1->hash_var.t.a.tag_low==0 && ptr1->hash_var.t.a.tag_high==1)
                                fprintf(fp,"movsx\tr13,DWORD[rbp+24+%d]\nmovsx\tr15,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else
                                fprintf(fp,"movsx\tr13,DWORD[rbp+24+%d]\nmovsx\tr15,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                        }
                    }
                    fprintf(fp,"cmp r12,r13\njne PL%d\ncmp r14,r15\njne PL%d\nmov rax,QWORD[rbp-%d]\nmov QWORD[rbp-%d],rax\njmp PL%d\nPL%d:\nmov edi,fmterror\ncall printf\nleave\nret\nPL%d:\n",label,label,ptr1->hash_var.offset,ptr->hash_var.offset,label+1,label,label+1);
                    label+=2;
                }
                else
                {
                    






                    v_node* ptr=lhs_ptr;
                    v_node* ptr2;
                    if(tuple->node2->n.L.t.terminal==ID)
                        ptr2=get_info(tuple->arg2, tuple->node2);
                    else
                        ptr2=NULL;
                    if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal==NUM)
                    {
                        int size=atoi(ptr->hash_var.t.a.high.value)-atoi(ptr->hash_var.t.a.low.value);
                        fprintf(fp,"mov r12,%d\nmov r14,%d\n",atoi(ptr->hash_var.t.a.low.value),atoi(ptr->hash_var.t.a.high.value));
                        fprintf(fp,"mov [rbp-%d],rbp\nsub QWORD[rbp-%d],%d\n",ptr->hash_var.offset,ptr->hash_var.offset,(ptr->hash_var.offset+8+size*4));          
                    }
                    else
                    {
                        v_node* lowptr;
                        v_node* highptr;
                        if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal!=NUM)
                        {
                            highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                            if(ptr->hash_var.t.a.tag_high==1)
                                fprintf(fp,"mov r12,%d\nmovsx r14,DWORD[rbp-%d]\n",atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
                            else
                                fprintf(fp,"mov r12,%d\nmovsx r14,DWORD[rbp+24+%d]\n",atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
                        }
                        else if(ptr->hash_var.t.a.low.terminal!=NUM && ptr->hash_var.t.a.high.terminal==NUM)
                        {  
                            lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                            if(ptr->hash_var.t.a.tag_low==1)
                                fprintf(fp,"movsx r12,DWORD[rbp-%d]\nmov r14,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
                            else
                                fprintf(fp,"movsx r12,DWORD[rbp+24+%d]\nmov r14,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
                        }
                        else
                        {
                            lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                            highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                            if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==1)
                                fprintf(fp,"movsx r12,DWORD[rbp-%d]\nmovsx r14,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==0)
                                fprintf(fp,"movsx r12,DWORD[rbp-%d]\nmovsx r14,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else if(ptr->hash_var.t.a.tag_low==0 && ptr->hash_var.t.a.tag_high==1)
                                fprintf(fp,"movsx r12,DWORD[rbp+24+%d]\nmovsx r14,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                            else
                                fprintf(fp,"movsx r12,DWORD[rbp+24+%d]\nmovsx r14,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                        }
                        fprintf(fp,"mov r15,r14\nsub r15,r12\nmov [rbp-%d],rbp\nsub QWORD[rbp-%d],%d\nmov r13,r14\nsal r13,2\nsub QWORD[rbp-%d],r13\n",ptr->hash_var.offset,ptr->hash_var.offset,AR_info[global_AR_index].size,ptr->hash_var.offset);
            
                        AR_info[global_AR_index].size+=80;

                    }
                    if(ptr2!=NULL && tuple->node2->scope_tag==1)
                        fprintf(fp,"movsx rax,DWORD[rbp-%d]\n",ptr2->hash_var.offset);
                    else if(ptr2!=NULL && tuple->node2->scope_tag==0)
                        fprintf(fp,"movsx rax,DWORD[rbp+24+%d]\n",ptr2->hash_var.offset);
                    else
                        fprintf(fp,"mov rax,%d\n",atoi(tuple->node2->n.L.t.value));
                    fprintf(fp,"cmp rax,r12\njl PL%d\ncmp r14,rax\njl PL%d\nmov r13,QWORD[rbp-%d]\n",label,label,ptr->hash_var.offset);
                    fprintf(fp,"sub rax,r12\n");
                    if(tuple->node1->n.L.t.terminal==ID)
                    {
                        v_node* rhs_ptr=get_info(tuple->arg1, tuple->node1);
                        if(ptr->hash_var.t.a.ele_type==INTEGER)
                        {
                            if(tuple->node1->scope_tag==1)
                                fprintf(fp,"mov r12d,DWORD[rbp-%d]\nmov DWORD[r13+rax*4],r12d\n",rhs_ptr->hash_var.offset);
                            else
                                fprintf(fp,"mov r12d,DWORD[rbp+24+%d]\nmov DWORD[r13+rax*4],r12d\n",rhs_ptr->hash_var.offset);
                        }
                        else if(ptr->hash_var.t.a.ele_type==REAL)
                            fprintf(fp,"movss xmm0,DWORD[rbp-%d]\nmovss DWORD[r13+rax*4],xmm0\n",rhs_ptr->hash_var.offset);
                        else
                        {
                            if(tuple->node1->scope_tag==1)
                                fprintf(fp,"mov r12b,BYTE[rbp-%d]\nmov BYTE[r13+rax*4],r12b\n",rhs_ptr->hash_var.offset);
                            else
                                fprintf(fp,"mov r12b,BYTE[rbp+24+%d]\nmov BYTE[r13+rax*4],r12b\n",rhs_ptr->hash_var.offset);
                        }
                        fprintf(fp,"jmp PL%d\nPL%d:\nmov edi,fmterror\ncall printf\nleave\nret\nPL%d:\n",label+1,label,label+1);
                        label+=2;
                    }
                    else
                    {
                        if(strcmp(tuple->node1->name,"NUM")==0)
                            fprintf(fp,"mov r12d,%d\nmov DWORD[r13+rax*4],r12d\n",atoi(tuple->node1->n.L.t.value));
                        else if(strcmp(tuple->node1->name,"RNUM")==0)
                            fprintf(fp,"mov r12d,__float32__(%f)\nmov DWORD[r13+rax*4],r12d\n",atof(tuple->node1->n.L.t.value));
                        else if(strcmp(tuple->node1->name,"TRUE")==0)
                            fprintf(fp,"mov r12b,1\nmov BYTE[r13+rax*1],r12b\n");
                        else
                            fprintf(fp,"mov r12b,0\nmov BYTE[r13+rax*4],r12b\n");
                        fprintf(fp,"jmp PL%d\nPL%d:\nmov edi,fmterror\ncall printf\nleave\nret\nPL%d:\n",label+1,label,label+1);
                        label+=2;
                    }
                }
            }
}


void process_ARITHOP(Tuple* tuple, FILE* fp)
{
    v_node* res_ptr=get_info(tuple->result, tuple->node3);

    if(tuple->node1->n.L.t.terminal==ID)
    {
        v_node*arg1_ptr=get_info(tuple->arg1, tuple->node1);
        if(tuple->node2->n.L.t.terminal==ID)
        {   
            v_node* arg2_ptr=get_info(tuple->arg2, tuple->node2);
            if(res_ptr->hash_var.t.basic_type==INTEGER)
            {
                if(tuple->node1->scope_tag==1)
                    fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
                else
                    fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
                if(tuple->node2->scope_tag==1)
                    fprintf(fp, "mov\tedx, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
                else
                    fprintf(fp, "mov\tedx, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
            }
            else
            {
                if(tuple->node1->scope_tag==1)
                    fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
                else
                    fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
                if(tuple->node2->scope_tag==1)
                    fprintf(fp, "mov\tedx, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
                else
                    fprintf(fp, "mov\tedx, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
            }
        }
        else if(tuple->node2->n.L.t.terminal==NUM)
        {
            short num=extract_int_value(tuple->arg2);
            if(tuple->node1->scope_tag==1)
                fprintf(fp,"mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
            else
              fprintf(fp,"mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
           fprintf(fp,"mov\tedx, %d\n", num);        
       }
        else if(tuple->node2->n.L.t.terminal==TRUE)
        {          
            if(tuple->node1->scope_tag==1)
                    fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
            else
                fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);               
            fprintf(fp, "mov\tedx, %d\n", 1);
        }
        else if(tuple->node2->n.L.t.terminal==FALSE)
        {
            if(tuple->node1->scope_tag==1)
                fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
            else
                fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
            fprintf(fp, "mov\tedx, %d\n", 0);
        }
    }

    else if(tuple->node2->n.L.t.terminal==ID)
    {
        v_node* arg2_ptr=get_info(tuple->arg2, tuple->node2);
        if(tuple->node1->n.L.t.terminal==NUM)
        {
            short num=extract_int_value(tuple->arg1);
            if(tuple->node2->scope_tag==1)
                fprintf(fp,"mov\teax, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
            else
                fprintf(fp,"mov\teax, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
            fprintf(fp,"mov\tedx, %d\n", num);
        }
        else if(tuple->node1->n.L.t.terminal==TRUE)
        {
            if(tuple->node2->scope_tag==1)
                fprintf(fp,"mov\teax, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
             else
                fprintf(fp,"mov\teax, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
            fprintf(fp,"mov\tedx, %d\n", 1);            
        }
        else if(tuple->node1->n.L.t.terminal==FALSE)
        {
            if(tuple->node2->scope_tag==1)
                fprintf(fp,"mov\teax, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
            else
              fprintf(fp,"mov\teax, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
            fprintf(fp,"mov\tedx, %d\n", 0);
        }          
    }
    else 
    {
        if(tuple->node1->n.L.t.terminal==NUM&&tuple->node2->n.L.t.terminal==NUM)
        {
          short num1=extract_int_value(tuple->arg1);
          short num2=extract_int_value(tuple->arg2);
          fprintf(fp,"mov\teax, %d\n", num1);
          fprintf(fp,"mov\tedx, %d\n", num2);
      }
      else 
      {
          if(tuple->node1->n.L.t.terminal==TRUE && tuple->node2->n.L.t.terminal==TRUE)
          {
            fprintf(fp,"mov\teax, %d\n", 1);
            fprintf(fp,"mov\tedx, %d\n", 1);
        }
        else if(tuple->node1->n.L.t.terminal==TRUE && tuple->node2->n.L.t.terminal==FALSE)
        {
            fprintf(fp,"mov\teax, %d\n", 1);
            fprintf(fp,"mov\tedx, %d\n", 0);
        }
        else if(tuple->node1->n.L.t.terminal==FALSE && tuple->node2->n.L.t.terminal==TRUE)
        {
            fprintf(fp,"mov\teax, %d\n", 0);
            fprintf(fp,"mov\tedx, %d\n", 1); 
        }
        else if(tuple->node1->n.L.t.terminal==FALSE && tuple->node2->n.L.t.terminal==FALSE)
        {
            fprintf(fp,"mov\teax, %d\n", 0);
            fprintf(fp,"mov\tedx, %d\n", 0);
        }
    }
    } 
    if(res_ptr->hash_var.t.basic_type==INTEGER)
    {
        if(tuple->op==PLUS)
          fprintf(fp,"ADD\teax, edx\n");
      else if(tuple->op==MINUS)
          fprintf(fp,"SUB\teax, edx\n");
      else if(tuple->op==MUL)
          fprintf(fp,"IMUL\teax, edx\n");
      else if(tuple->op==DIV)
          fprintf(fp,"IDIV\teax, edx\n");
      else if(tuple->op==AND)
          fprintf(fp,"AND\teax, edx\n");
      else if(tuple->op==OR)
          fprintf(fp,"OR\teax, edx\n");
      if(tuple->node3->scope_tag==1)
          fprintf(fp,"mov\tDWORD[rbp-%d], eax\n", res_ptr->hash_var.offset);
      else
          fprintf(fp,"mov\tDWORD[rbp+24+%d], eax\n", res_ptr->hash_var.offset);
    }
    else
    {
        if(tuple->op==PLUS)
          fprintf(fp,"ADD\teax, edx\n");
      else if(tuple->op==MINUS)
          fprintf(fp,"SUB\teax, edx\n");
      else if(tuple->op==MUL)
          fprintf(fp,"MUL\teax, edx\n");
      else if(tuple->op==DIV)
          fprintf(fp,"DIV\teax, edx\n");
      else if(tuple->op==AND)
          fprintf(fp,"AND\teax, edx\n");
      else if(tuple->op==OR)
          fprintf(fp,"OR\teax, edx\n");
      if(tuple->node3->scope_tag==1)
          fprintf(fp,"mov\tDWORD[rbp-%d], eax\n", res_ptr->hash_var.offset); 
      else
          fprintf(fp,"mov\tDWORD[rbp+24+%d], eax\n", res_ptr->hash_var.offset); 
    }
}
int rlh=0;
void process_RELATIONALOP(Tuple *tuple, FILE *fp)
{

    v_node* res_ptr=get_info(tuple->result, tuple->node3);
    if(tuple->node1->n.L.t.terminal==ID) 
    {
        v_node* arg1_ptr=get_info(tuple->arg1, tuple->node1);
        if(tuple->node2->n.L.t.terminal==ID) 
        {
            v_node* arg2_ptr=get_info(tuple->arg2, tuple->node2);
            if(res_ptr->hash_var.t.basic_type==INTEGER)
            {
                if(tuple->node1->scope_tag==1)
                    fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
                else
                    fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
                if(tuple->node2->scope_tag==1)
                    fprintf(fp, "mov\tedx, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
                else
                    fprintf(fp, "mov\tedx, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
                fprintf(fp,"CMP\teax, edx\n");
        }
    else
    {
        if(tuple->node1->scope_tag==1)
              fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
        else
              fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
        if(tuple->node2->scope_tag==1)
              fprintf(fp, "mov\tedx, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
        else
              fprintf(fp, "mov\tedx, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
        fprintf(fp, "CMP\teax, edx\n");
    }
  }
    else if(tuple->node2->n.L.t.terminal==NUM)
    {
      short num=extract_int_value(tuple->arg2);
      if(tuple->node1->scope_tag==1)
        fprintf(fp,"mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
    else
        fprintf(fp,"mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
    fprintf(fp,"mov\tedx, %d\n", num); 
    fprintf(fp, "CMP\teax, edx\n");
    }
    else if(tuple->node2->n.L.t.terminal==TRUE)
    {
      if(tuple->node1->scope_tag==1)
        fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
    else
        fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);               
    fprintf(fp, "mov\tedx, %d\n", 1);
    fprintf(fp, "CMP\teax, edx\n");
    }
    else if(tuple->node2->n.L.t.terminal==FALSE)
    {
      if(tuple->node1->scope_tag==1)
        fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
    else
        fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
    fprintf(fp, "mov\tedx, %d\n", 0);
    fprintf(fp, "CMP\teax, edx\n");
    }
    }
    else if(tuple->node2->n.L.t.terminal==ID)
    {
        v_node* arg2_ptr=get_info(tuple->arg2, tuple->node2);
        if(tuple->node1->n.L.t.terminal==NUM)
        {
          short num=extract_int_value(tuple->arg1);
          if(tuple->node2->scope_tag==1)
            fprintf(fp,"mov\teax, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
        else
            fprintf(fp,"mov\teax, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
        fprintf(fp,"mov\tedx, %d\n", num);
        fprintf(fp, "CMP\teax, edx\n");
    }
    else if(tuple->node1->n.L.t.terminal==TRUE)
    {
      if(tuple->node2->scope_tag==1)
        fprintf(fp,"mov\teax, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
    else
        fprintf(fp,"mov\teax, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
    fprintf(fp,"mov\tedx, %d\n", 1);  
    fprintf(fp, "CMP\teax, edx\n");           
    }
    else if(tuple->node1->n.L.t.terminal==FALSE)
    {
      if(tuple->node2->scope_tag==1)
        fprintf(fp,"mov\teax, DWORD[rbp-%d]\n", arg2_ptr->hash_var.offset);
    else
        fprintf(fp,"mov\teax, DWORD[rbp+24+%d]\n", arg2_ptr->hash_var.offset);
    fprintf(fp,"mov\tedx, %d\n", 0);
    fprintf(fp, "CMP\teax, edx\n");
    }          
    }
    else
    {
        if(tuple->node1->n.L.t.terminal==NUM && tuple->node2->n.L.t.terminal==NUM)
        {
          short num1=extract_int_value(tuple->arg1);
          short num2=extract_int_value(tuple->arg2);
          fprintf(fp,"mov\teax, %d\n", num1);
          fprintf(fp,"mov\tedx, %d\n", num2);
          fprintf(fp, "CMP\teax, edx\n");
      }
      else 
      {
          if(tuple->node1->n.L.t.terminal==TRUE && tuple->node2->n.L.t.terminal==TRUE)
          {
            fprintf(fp,"mov\teax, %d\n", 1);
            fprintf(fp,"mov\tedx, %d\n", 1);
            fprintf(fp, "CMP\teax, edx\n");
        }

        else if(tuple->node1->n.L.t.terminal==TRUE && tuple->node2->n.L.t.terminal==FALSE)
        {
            fprintf(fp,"mov\teax, %d\n", 1);
            fprintf(fp,"mov\tedx, %d\n", 0);
            fprintf(fp, "CMP\teax, edx\n");
        }
        else if(tuple->node1->n.L.t.terminal==FALSE && tuple->node2->n.L.t.terminal==TRUE)
        {
            fprintf(fp,"mov\teax, %d\n", 0);
            fprintf(fp,"mov\tedx, %d\n", 1); 
            fprintf(fp, "CMP\teax, edx\n");
        }
        else if(tuple->node1->n.L.t.terminal==FALSE && tuple->node2->n.L.t.terminal==FALSE)
        {
            fprintf(fp,"mov\teax, %d\n", 0);
            fprintf(fp,"mov\tedx, %d\n", 0);
            fprintf(fp, "CMP\teax, edx\n");
        }
    }
    }
    if(tuple->op==LT)
    {
        fprintf(fp, "JL\tRL%d\n", rl);
        rl++;
    }
    else if(tuple->op==LE)
    {
        fprintf(fp, "JLE\tRL%d\n", rl);
        rl++;
    }
    else if(tuple->op==GT)
    {
      fprintf(fp, "JG\tRL%d\n", rl);
      rl++;
    }
    else if(tuple->op==GE)
    {
      fprintf(fp, "JGE\tRL%d\n", rl);
      rl++;                   
    }
    else if(tuple->op==EQ)
    {
      fprintf(fp, "JE\tRL%d\n", rl);
      //fprintf(fp, "")
      rl++;
    }
    else if(tuple->op==NE)
    {
      fprintf(fp, "JNE\tRL%d\n", rl);
      rl++;
    }
    fprintf(fp, "JMP\tRL%d\n", rl);
    rl++;
    if(tuple->node3->scope_tag==1)
        fprintf(fp,"RL%d:\tmov\tDWORD[rbp-%d], %d\n", rl-2,res_ptr->hash_var.offset,1);
        
    else
        fprintf(fp,"RL%d:\tmov\tDWORD[rbp+24+%d], %d\n", rl-2,res_ptr->hash_var.offset,1);
    fprintf(fp, "jmp\t rlh%d\n", rlh);
    if(tuple->node3->scope_tag==1)
        fprintf(fp,"RL%d:\tmov\tDWORD[rbp-%d], %d\n", rl-1,res_ptr->hash_var.offset,0);  
        
    else
        fprintf(fp,"RL%d:\tmov\tDWORD[rbp+24+%d], %d\n", rl-1,res_ptr->hash_var.offset,0);
    fprintf(fp, "rlh%d:\n", rlh);
    rlh++;
}

void process_PRINT1(Tuple* tuple,FILE* fp)
{
    v_node* ptr;
    if(tuple->node1->n.L.t.terminal==ID)
        ptr=get_info(tuple->arg1, tuple->node1);
    else
        ptr=NULL;
    if(ptr->hash_var.tag==0 && (tuple->arg2==NULL))
    {
        fprintf(fp,"mov edi ,fmtarray\ncall printf\n");
        if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal==NUM)
        {
            int size= atoi(ptr->hash_var.t.a.high.value)-atoi(ptr->hash_var.t.a.low.value);
            fprintf(fp,"mov r14,%d\n",size);          /********************************************************/
        }
        else
        {
            v_node* lowptr;
            v_node *highptr;
            if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal!=NUM)
            {
                highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                if(ptr->hash_var.t.a.tag_high==1)
                    fprintf(fp,"movsx r14,DWORD[rbp-%d]\nsub r14,%d\n",highptr->hash_var.offset,atoi(ptr->hash_var.t.a.low.value));
                else
                    fprintf(fp,"movsx r14,DWORD[rbp+24+%d]\nsub r14,%d\n",highptr->hash_var.offset,atoi(ptr->hash_var.t.a.low.value));
            }
            else if(ptr->hash_var.t.a.low.terminal!=NUM && ptr->hash_var.t.a.high.terminal==NUM)
            {
                lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                if(ptr->hash_var.t.a.tag_low==1)
                    fprintf(fp,"movsx r12,DWORD[rbp-%d]\nmov r14,%d\nsub r14,r12\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
                else
                    fprintf(fp,"movsx r12,DWORD[rbp+24+%d]\nmov r14,%d\nsub r14,r12\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
            }
            else
            {
                lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==1)
                    fprintf(fp,"movsx r12,DWORD[rbp-%d]\nmovsx r14,DWORD[rbp-%d]\nsub r14,r12\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                else if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==0)
                    fprintf(fp,"movsx r12,DWORD[rbp-%d]\nmovsx r14,DWORD[rbp+24+%d]\nsub r14,r12\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                else if(ptr->hash_var.t.a.tag_low==0 && ptr->hash_var.t.a.tag_high==1)
                    fprintf(fp,"movsx r12,DWORD[rbp+24+%d]\nmovsx r14,DWORD[rbp-%d]\nsub r14,r12\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                else
                    fprintf(fp,"movsx r12,WORD[rbp+24+%d]\nmovsx r14,WORD[rbp+24+%d]\nsub r14,r12\n",lowptr->hash_var.offset,highptr->hash_var.offset);
            }
        }
        if(ptr->hash_var.t.a.ele_type==INTEGER)
            fprintf(fp,"mov r12,0\nmov r13,QWORD[rbp-%d]\nPL%d:\ncmp r12,r14\njg PL%d\nmov rax,r12\nmov eax,DWORD[r13+rax*4]\nmov esi,eax\nmov edi,fmtint\nmov eax, 0\ncall printf\ninc  r12\njmp PL%d\nPL%d: ",ptr->hash_var.offset,label,label+1,label,label+1);
        else if(ptr->hash_var.t.a.ele_type==REAL)
            fprintf(fp,"mov r12,0\nmov r13,QWORD[rbp-%d]\nPL%d:\ncmp r12,r14\njg PL%d\nmov rax,r12\nmovss xmm0,DWORD[r13+rax*4]\ncvtss2sd xmm0, xmm0\nmov edi,fmtreal\nmov eax, 1\ncall printf\ninc  r12\njmp PL%d\nPL%d: ",ptr->hash_var.offset,label,label+1,label,label+1);
        else if(ptr->hash_var.t.a.ele_type==BOOLEAN)
            fprintf(fp,"mov r12,0\nmov r13,QWORD[rbp-%d]\nPL%d:\ncmp r12,r14\njg PL%d\nmov rax,r12\nmovzx eax,BYTE[r13+rax*4]\nmov esi,eax\ncmp eax,0\nje Z%d\nmov edi,Tr\njmp Z%d\nZ%d:mov edi,Fa\nmov eax, 0\nZ%d:call printf\ninc  r12\njmp PL%d\nPL%d: ",ptr->hash_var.offset,label,label+1,label,label+1,label,label+1,label,label+1);
        label+=2;
        fprintf(fp,"mov edi, NL\ncall printf\n");
    }
    else if(ptr->hash_var.tag==0 && strcmp(tuple->arg2,"NULL")!=0)
    {
        fprintf(fp,"mov edi ,fmtarray\ncall printf\n");
        v_node* ptr2;
        if(strcmp(tuple->node2->name,"NUM")!=0)
            ptr2=get_info(tuple->arg2, tuple->node2);
        else
            ptr2=NULL;
        if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal==NUM)
        {
            fprintf(fp,"mov r12,%d\nmov r14,%d\n",atoi(ptr->hash_var.t.a.low.value),atoi(ptr->hash_var.t.a.high.value));          /********************************************************/
        }
        else
        {
            v_node* lowptr;v_node* highptr;
            if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal!=NUM)
            {
                highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                if(ptr->hash_var.t.a.tag_high==1)
                    fprintf(fp,"mov r12,%d\nmovsx r14,DWORD[rbp-%d]\n",atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
                else
                    fprintf(fp,"mov r12,%d\nmovsx r14,DWORD[rbp+24+%d]\n",atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
            }
            else if(ptr->hash_var.t.a.low.terminal!=NUM && ptr->hash_var.t.a.high.terminal==NUM)
            {
                lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                if(ptr->hash_var.t.a.tag_low==1)
                    fprintf(fp,"movsx r12,DWORD[rbp-%d]\nmov r14,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
                else
                    fprintf(fp,"movsx r12,DWORD[rbp+24+%d]\nmov r14,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value));
            }
            else
            {
                lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==1)
                    fprintf(fp,"movsx r12,DWORD[rbp-%d]\nmovsx r14,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                else if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==0)
                    fprintf(fp,"movsx r12,DWORD[rbp-%d]\nmovsx r14,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                else if(ptr->hash_var.t.a.tag_low==0 && ptr->hash_var.t.a.tag_high==1)
                    fprintf(fp,"movsx r12,DWORD[rbp+24+%d]\nmovsx r14,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
                else
                    fprintf(fp,"movsx r12,DWORD[rbp+24+%d]\nmovsx r14,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset);
            }
        }
        if(ptr2!=NULL && tuple->node2->scope_tag==1)
            fprintf(fp,"mov rax,[rbp-%d]\n",ptr2->hash_var.offset);
        else if(ptr2!=NULL && tuple->node2->scope_tag==0)
            fprintf(fp,"mov rax,[rbp+24+%d]\n",ptr2->hash_var.offset);
        else
            fprintf(fp,"mov rax,%d\n",atoi(tuple->node2->n.L.t.value));
        fprintf(fp,"cmp rax,r12\njl PL%d\ncmp r14,rax\njl PL%d\nmov r13,QWORD[rbp-%d]\n",label,label,ptr->hash_var.offset);
        fprintf(fp,"sub rax,r12\n");
        if(ptr->hash_var.t.a.ele_type==INTEGER)
            fprintf(fp,"mov eax,DWORD[r13+rax*4]\nmov esi,eax\nmov edi,fmtint\nmov eax, 0\ncall printf\n");
        else if(ptr->hash_var.t.a.ele_type==REAL)
            fprintf(fp,"cvtss2sd xmm0,DWORD[r13+rax*4]\nmov edi,fmtreal\nmov eax, 1\ncall printf\nmov eax,0\n");
        else
            fprintf(fp,"movzx eax,BYTE[r13+rax*4]\nmov esi,eax\ncmp eax,0\nje Z%d\nmov edi,Tr\njmp Z%d\nZ%d:mov edi,Fa\nmov eax, 0\nZ4%dcall printf\n",label,label+1,label,label+1);
        fprintf(fp,"jmp PL%d\nPL%d:\nmov edi,fmterror\ncall printf\nleave\nret\nPL%d:",label+1,label,label+1);
        fprintf(fp,"mov edi, NL\ncall printf\n");
        label+=2;
    }
    else
    {
        if(ptr!=NULL)
        {
            fprintf(fp,"mov edi ,fmtarray\ncall printf\n");
            if(ptr->hash_var.t.basic_type==INTEGER)
            {
                if(tuple->node1->scope_tag==1)
                    fprintf(fp,"mov eax,DWORD[rbp-%d]\nmov esi,eax\nmov edi,fmtint\nmov eax, 0\ncall printf\n",ptr->hash_var.offset);
                else
                    fprintf(fp,"mov eax,DWORD[rbp+24+%d]\nmov esi,eax\nmov edi,fmtint\nmov eax, 0\ncall printf\n",ptr->hash_var.offset);
            }
            else if(ptr->hash_var.t.basic_type==REAL)
            {
                if(tuple->node1->scope_tag==1)
                    fprintf(fp,"cvtss2sd xmm0, DWORD[rbp-%d]\nmov edi,fmtreal\nmov eax, 1\ncall printf\nmov eax,0\n",ptr->hash_var.offset);
                else
                    fprintf(fp,"cvtss2sd xmm0, DWORD[rbp+24+%d]\nmov edi,fmtreal\nmov eax, 1\ncall printf\nmov eax,0\n",ptr->hash_var.offset);
            }
            else
            {
                if(tuple->node1->scope_tag==1)
                    fprintf(fp,"movzx eax,BYTE[rbp-%d]\nmov esi,eax\ncmp eax,0\nje Z%d\nmov edi,Tr\njmp Z%d\nZ%d:mov edi,Fa\nmov eax, 0\nZ%d:call printf\n",ptr->hash_var.offset,label,label+1,label,label+1);
                else
                    fprintf(fp,"movzx eax,BYTE[rbp+24+%d]\nmov esi,eax\ncmp eax,0\nje Z%d\nmov edi,Tr\njmp Z%d\nZ%d:mov edi,Fa\nmov eax, 0\nZ%d:call printf\n",ptr->hash_var.offset,label,label+1,label,label+1);
                label+=2;
            }
            fprintf(fp,"mov edi, NL\ncall printf\n");
        }
        else
        {
            fprintf(fp,"mov edi ,fmtarray\ncall printf\n");
            if(strcmp(tuple->node1->name,"NUM")==0)
                fprintf(fp,"mov eax,%d\nmov esi,eax\nmov edi,fmtint\nmov eax, 0\ncall printf\n",atoi(tuple->node1->n.L.t.value));
            else if(strcmp(tuple->node1->name,"RNUM")==0)
                fprintf(fp,"mov eax,__float32__(%f)\nmovd xmm0,eax\ncvtss2sd xmm0,xmm0\nmov edi,fmtreal\nmov eax, 1\ncall printf\nmov eax,0\n",atof(tuple->node1->n.L.t.value));
            else if(strcmp(tuple->node1->name,"TRUE")==0)
                fprintf(fp,"mov edi,Tr\nmov eax,0\ncall printf\n");
            else
                fprintf(fp,"mov edi,Fa\nmov eax,0\ncall printf\n");
            fprintf(fp,"mov edi, NL\ncall printf\n");
        }
    }
}

void process_GET_VALUE1(Tuple* tuple,FILE* fp)
{
    v_node* ptr=get_info(tuple->arg1, tuple->node1);
    if(ptr->hash_var.tag==0)
    {
        if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal==NUM)
        {
            int size=atoi(ptr->hash_var.t.a.high.value)-atoi(ptr->hash_var.t.a.low.value);
            if(ptr->hash_var.t.a.ele_type==INTEGER)
            {
                fprintf(fp,"mov esi,%d\nmov edi,fmt4\ncall printf\nmov esi,%d\nmov edi,fmtint\ncall printf\nmov edi,fmtto\ncall printf\nmov esi,%d\nmov edi,fmtint\ncall printf\n",size+1,atoi(ptr->hash_var.t.a.low.value),atoi(ptr->hash_var.t.a.high.value));
                fprintf(fp,"mov edi, NL\ncall printf\n");
                fprintf(fp,"mov r14,%d\nmov [rbp-%d],rbp\nsub QWORD[rbp-%d],%d\n",size,ptr->hash_var.offset,ptr->hash_var.offset,(ptr->hash_var.offset+8+size*4));
            }
            else if(ptr->hash_var.t.a.ele_type==REAL)
            {
                fprintf(fp,"mov esi,%d\nmov edi,fmt5\ncall printf\nmov esi,%d\nmov edi,fmtint\ncall printf\nmov edi,fmtto\ncall printf\nmov esi,%d\nmov edi,fmtint\ncall printf\n",size+1,atoi(ptr->hash_var.t.a.low.value),atoi(ptr->hash_var.t.a.high.value));
                fprintf(fp,"mov edi, NL\ncall printf\n");
                fprintf(fp,"mov r14,%d\nmov [rbp-%d],rbp\nsub QWORD[rbp-%d],%d\n",size,ptr->hash_var.offset,ptr->hash_var.offset,(ptr->hash_var.offset+8+size*4));
            }
            else
            {
                fprintf(fp,"mov esi,%d\nmov edi,fmt6\ncall printf\nmov esi,%d\nmov edi,fmtint\ncall printf\nmov edi,fmtto\ncall printf\nmov esi,%d\nmov edi,fmtint\ncall printf\n",size+1,atoi(ptr->hash_var.t.a.low.value),atoi(ptr->hash_var.t.a.high.value));
                fprintf(fp,"mov edi, NL\ncall printf\n");
                fprintf(fp,"mov r14,%d\nmov [rbp-%d],rbp\nsub QWORD[rbp-%d],%d\n",size,ptr->hash_var.offset,ptr->hash_var.offset,(ptr->hash_var.offset+8+size*4));
            }    
        }
        else
        {
            v_node* lowptr;v_node *highptr;
            if(ptr->hash_var.t.a.low.terminal==NUM && ptr->hash_var.t.a.high.terminal!=NUM)
            {
                highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                if(ptr->hash_var.t.a.tag_high==1)
                    fprintf(fp,"mov r14d,DWORD[rbp-%d]\nsub r14d,%d\nmov r12d,%d\nmov r13d,DWORD[rbp-%d]\n",highptr->hash_var.offset,atoi(ptr->hash_var.t.a.low.value),atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
                else
                    fprintf(fp,"mov r14d,DWORD[rbp+24+%d]\nsub r14d,%d\nmov r12d,%d\nmov r13d,DWORD[rbp+24+%d]\n",highptr->hash_var.offset,atoi(ptr->hash_var.t.a.low.value),atoi(ptr->hash_var.t.a.low.value),highptr->hash_var.offset);
            }
            else if(ptr->hash_var.t.a.low.terminal!=NUM && ptr->hash_var.t.a.high.terminal==NUM)
            {
                lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                if(ptr->hash_var.t.a.tag_low==1)
                    fprintf(fp,"mov r12d,DWORD[rbp-%d]\nmov r14d,%d\nsub r14d,r12d\nmov r13d,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value),atoi(ptr->hash_var.t.a.high.value));
                else
                    fprintf(fp,"mov r12d,DWORD[rbp+24+%d]\nmov r14d,%d\nsub r14d,r12d\nmov r13d,%d\n",lowptr->hash_var.offset,atoi(ptr->hash_var.t.a.high.value),atoi(ptr->hash_var.t.a.high.value));
            }
            else
            {
                lowptr=get_info1(ptr->hash_var.t.a.low.value,ptr->hash_var.t.a.scope_low,ptr->hash_var.t.a.tag_low);
                highptr=get_info1(ptr->hash_var.t.a.high.value,ptr->hash_var.t.a.scope_high,ptr->hash_var.t.a.tag_high);
                if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==1)
                    fprintf(fp,"mov r12d,DWORD[rbp-%d]\nmov r14d,DWORD[rbp-%d]\nsub r14d,r12d\nmovsx r13,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset,highptr->hash_var.offset);
                else if(ptr->hash_var.t.a.tag_low==1 && ptr->hash_var.t.a.tag_high==0)
                    fprintf(fp,"mov r12d,DWORD[rbp-%d]\nmov r14d,DWORD[rbp+24+%d]\nsub r14d,r12d\nmovsx r13,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset,highptr->hash_var.offset);
                else if(ptr->hash_var.t.a.tag_low==0 && ptr->hash_var.t.a.tag_high==1)
                    fprintf(fp,"mov r12d,DWORD[rbp+24+%d]\nmov r14d,DWORD[rbp-%d]\nsub r14d,r12d\nmovsx r13,DWORD[rbp-%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset,highptr->hash_var.offset);
                else
                    fprintf(fp,"mov r12d,DWORD[rbp+24+%d]\nmov r14d,DWORD[rbp+24+%d]\nsub r14d,r12d\nmovsx r13,DWORD[rbp+24+%d]\n",lowptr->hash_var.offset,highptr->hash_var.offset,highptr->hash_var.offset);
            }
            if(ptr->hash_var.t.a.ele_type==INTEGER)
            {
                fprintf(fp,"inc r14d\nmov esi,r14d\nmov edi,fmt4\ncall printf\ndec r14d\nmov esi,r12d\nmov edi,fmtint\ncall printf\nmov edi,fmtto\ncall printf\nmov esi,r13d\nmov edi,fmtint\ncall printf\nmovsx r14,r14d\n");
                fprintf(fp,"mov edi, NL\ncall printf\n");
                /***********************/fprintf(fp,"mov [rbp-%d],rbp\nsub QWORD[rbp-%d],%d\nmov r13,r14\nsal r13,2\nsub QWORD[rbp-%d],r13\n",ptr->hash_var.offset,ptr->hash_var.offset,AR_info[global_AR_index].size,ptr->hash_var.offset);
            }
            else if(ptr->hash_var.t.a.ele_type==REAL)
            {
                fprintf(fp,"inc r14d\nmov esi,r14d\nmov edi,fmt5\ncall printf\ndec r14d\nmov esi,r12d\nmov edi,fmtint\ncall printf\nmov edi,fmtto\ncall printf\nmov esi,r13d\nmov edi,fmtint\ncall printf\nmovsx r14,r14d\n");
                fprintf(fp,"mov edi, NL\ncall printf\n");
                /***********************/fprintf(fp,"mov [rbp-%d],rbp\nsub QWORD[rbp-%d],%d\nmov r13,r14\nsal r13,2\nsub QWORD[rbp-%d],r13\n",ptr->hash_var.offset,ptr->hash_var.offset,AR_info[global_AR_index].size,ptr->hash_var.offset);
            }
            else
            {
                fprintf(fp,"inc r14d\nmov esi,r14d\nmov edi,fmt6\ncall printf\ndec r14d\nmov esi,r12d\nmov edi,fmtint\ncall printf\nmov edi,fmtto\ncall printf\nmov esi,r13d\nmov edi,fmtint\ncall printf\nmovsx r14,r14d\n");
                fprintf(fp,"mov edi, NL\ncall printf\n");
                /***********************/fprintf(fp,"mov [rbp-%d],rbp\nsub QWORD[rbp-%d],%d\nmov r13,r14\nsal r13,2\nsub QWORD[rbp-%d],r13\n",ptr->hash_var.offset,ptr->hash_var.offset,AR_info[global_AR_index].size,ptr->hash_var.offset);
            }
            AR_info[global_AR_index].size+=80;
        }
        if(ptr->hash_var.t.a.ele_type==INTEGER)
            fprintf(fp,"mov r12,0\nPL%d:cmp r12,r14\njg PL%d\nmov rax,QWORD[rbp-%d]\nmov rdx,r12\n sal rdx,2\nadd rax,rdx\nmov rsi,rax\nmov edi,fmtinput1\nmov eax,0\ncall scanf\ninc r12\njmp PL%d\nPL%d: ",label,label+1,ptr->hash_var.offset,label,label+1);
        else if(ptr->hash_var.t.a.ele_type==REAL)
            fprintf(fp,"mov r12,0\nPL%d:cmp r12,r14\njg PL%d\nmov rax,QWORD[rbp-%d]\nmov rdx,r12\n sal rdx,2\nadd rax,rdx\nmov rsi,rax\nmov edi,fmtinput2\nmov eax,0\ncall scanf\ninc r12\njmp PL%d\nPL%d: ",label,label+1,ptr->hash_var.offset,label,label+1);
        else
            fprintf(fp,"mov r12,0\nPL%d:cmp r12,r14\njg PL%d\nmov rax,QWORD[rbp-%d]\nmov rdx,r12\n sal rdx,2\nadd rax,rdx\nmov rsi,rax\nmov edi,fmtinput1\nmov eax,0\ncall scanf\ninc r12\njmp PL%d\nPL%d: ",label,label+1,ptr->hash_var.offset,label,label+1);
        label+=2;
    }
    else
    {
        if(ptr->hash_var.t.basic_type==INTEGER)
        {
            fprintf(fp,"mov edi ,fmt1\ncall printf\n");
            if(tuple->node1->scope_tag==1)
                fprintf(fp,"lea rax, [rbp-%d]\nmov rsi, rax\nmov edi, fmtinput1\nmov eax, 0\ncall scanf\n",ptr->hash_var.offset);
            else
                fprintf(fp,"lea rax, [rbp+24+%d]\nmov rsi, rax\nmov edi, fmtinput1\nmov eax, 0\ncall scanf\n",ptr->hash_var.offset);
        }
        else if(ptr->hash_var.t.basic_type==REAL)
        {
            fprintf(fp,"mov edi ,fmt2\ncall printf\n");
            fprintf(fp,"lea rax, [rbp-%d]\nmov rsi, rax\nmov edi, fmtinput2\nmov eax, 0\ncall scanf\n",ptr->hash_var.offset);
        }
        else
        {  
            fprintf(fp,"mov edi ,fmt3\ncall printf\n");
            if(tuple->node1->scope_tag==1)
                fprintf(fp,"lea rax, [rbp-%d]\nmov rsi, rax\nmov edi, fmtinput1\nmov eax, 0\ncall scanf\n",ptr->hash_var.offset);
            else
                fprintf(fp,"lea rax, [rbp+24+%d]\nmov rsi, rax\nmov edi, fmtinput1\nmov eax, 0\ncall scanf\n",ptr->hash_var.offset);
        }

    }
}


void process_LABEL(Tuple* tuple, FILE* fp)
{
        fprintf(fp, "%s:\n", tuple->arg1);
}

void process_GOTO(Tuple* tuple, FILE* fp)
{
        fprintf(fp, "JMP\t%s\n", tuple->arg1);
}

void process_IF(Tuple* tuple, FILE* fp){

        //v_node* res_ptr; 
        if(tuple->node3->n.L.t.terminal==ID){
            v_node* res_ptr=get_info(tuple->result, tuple->node3);
            fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", res_ptr->hash_var.offset);
            fprintf(fp, "cmp\teax, 1\n");
            fprintf(fp, "je %s\n", tuple->arg1);
       }
         else{
            if(tuple->node3->n.L.t.terminal==TRUE || strcmp(tuple->result, "1")==0)
            fprintf(fp, "jmp %s\n", tuple->arg1);
        }
        
        // //else
            //fprintf(fp, "jmp %s\n", tuple->arg1);
}

void process_UNARY1(Tuple* tuple, FILE* fp)
{
    v_node* res_ptr=get_info(tuple->result, tuple->node3);

    if(tuple->op==U_MINUS)
    {
          if(tuple->node1->n.L.t.terminal==ID){
            v_node* arg1_ptr=get_info(tuple->arg1, tuple->node1);
            if(tuple->node1->scope_tag==1)
                fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
            else
                fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
            fprintf(fp, "neg\teax");
            if(tuple->node3->scope_tag==1)
                fprintf(fp, "mov\tDWORD[rbp-%d], eax\n", res_ptr->hash_var.offset);
            else
                fprintf(fp, "mov\tDWORD[rbp+24+%d], eax\n", res_ptr->hash_var.offset);
        }
        else{
            short num=extract_int_value(tuple->arg1);
            fprintf(fp, "mov\teax, %d\n", num);
            fprintf(fp, "neg\teax");
            if(tuple->node3->scope_tag==1)
                fprintf(fp, "mov\tDWORD[rbp-%d], eax\n", res_ptr->hash_var.offset);
            else
                fprintf(fp, "mov\tDWORD[rbp+24+%d], eax\n", res_ptr->hash_var.offset);
        }
    }

    else
    {
        if(tuple->node1->n.L.t.terminal==ID){
            v_node* arg1_ptr=get_info(tuple->arg1, tuple->node1);
            if(tuple->node1->scope_tag==1)
                fprintf(fp, "mov\teax, DWORD[rbp-%d]\n", arg1_ptr->hash_var.offset);
            else
                fprintf(fp, "mov\teax, DWORD[rbp+24+%d]\n", arg1_ptr->hash_var.offset);
            if(tuple->node3->scope_tag==1)
                fprintf(fp, "mov\tDWORD[rbp-%d], eax\n", res_ptr->hash_var.offset);
            else
                fprintf(fp, "mov\tDWORD[rbp+24+%d], eax\n", res_ptr->hash_var.offset);
        }
        else{
            short num=extract_int_value(tuple->arg1);
            fprintf(fp, "mov\teax, %d\n", num);
            if(tuple->node3->scope_tag==1)
                fprintf(fp, "mov\tDWORD[rbp-%d], eax\n", res_ptr->hash_var.offset);
            else
                fprintf(fp, "mov\tDWORD[rbp+24+%d], eax\n", res_ptr->hash_var.offset);
        }
    }
}

void process_call(Tuple* tuple, FILE* fp)
{
    char func[30];int s=0;
    strcpy(func,tuple->arg1);
    while(tuple->next->op==PARAM)
    {
        tuple=tuple->next;
        if(tuple->node1->n.L.t.terminal==ID)
        {
            v_node* ptr=get_info(tuple->arg1, tuple->node1);
            if(ptr->hash_var.t.basic_type==INTEGER)
            {
                s+=8;
                if(tuple->node1->scope_tag==1)
                    fprintf(fp,"mov eax,[rbp-%d]\n",ptr->hash_var.offset);
                else
                    fprintf(fp,"mov eax,[rbp+24+%d]\n",ptr->hash_var.offset);
                fprintf(fp,"mov DWORD[rsp+%d],eax\n",s);
            }
            else if(ptr->hash_var.t.basic_type==BOOLEAN)
            {
                s+=8;
                if(tuple->node1->scope_tag==1)
                    fprintf(fp,"mov al,[rbp-%d]\n",ptr->hash_var.offset);
                else
                    fprintf(fp,"mov al,[rbp+24+%d]\n",ptr->hash_var.offset);
                fprintf(fp,"mov BYTE[rsp+%d],al\n",s);
            }
        }
        else
        {
            if(strcmp(tuple->node1->name,"NUM")==0)
            {
                s+=8;
                fprintf(fp,"mov eax,%d\n",atoi(tuple->node1->n.L.t.value));
                fprintf(fp,"mov DWORD[rsp+%d],eax\n",s);
            }
            else if(strcmp(tuple->node1->name,"TRUE")==0)
            {
                s+=8;
                fprintf(fp,"mov BYTE[rsp+%d],1\n",s);
            }
            else if(strcmp(tuple->node1->name,"FALSE")==0)
            {
                s+=8;
                fprintf(fp,"mov BYTE[rsp+%d],0\n",s);
            }
        }
    }
    fprintf(fp,"call %s\n",func);
    while(tuple->next->op==RETURN)
    {
        tuple=tuple->next;
        if(tuple->node1->n.L.t.terminal==ID)
        {
            v_node* ptr=get_info(tuple->arg1, tuple->node1);
            if(ptr->hash_var.t.basic_type==INTEGER)
            {
                s+=8;
                fprintf(fp,"mov eax,DWORD[rsp+%d]\n",s);
                if(tuple->node1->scope_tag==1)
                    fprintf(fp,"mov [rbp-%d],eax\n",ptr->hash_var.offset);
                else
                    fprintf(fp,"mov [rbp+24+%d],eax\n",ptr->hash_var.offset);
            }
            else if(ptr->hash_var.t.basic_type==BOOLEAN)
            {
                s+=8;
                fprintf(fp,"mov al,BYTE[rsp+%d]\n",s);
                if(tuple->node1->scope_tag==1)
                    fprintf(fp,"mov [rbp-%d],al\n",ptr->hash_var.offset);
                else
                    fprintf(fp,"mov [rbp+24+%d],al\n",ptr->hash_var.offset);
            }
        }
    }
}

void process_tuple(Tuple* tuple, FILE* fp)
{
        if(tuple->op==FUNCTION){
            process_FUNCTION(tuple, fp);
        }
        else if(tuple->op==RET){
            process_RET(tuple, fp);
        }
        else if(tuple->op==ASSIGNOP){
            process_ASSIGNOP(tuple, fp);
        }
        else if(tuple->op==PLUS||tuple->op==MINUS||tuple->op==MUL||tuple->op==DIV||tuple->op==AND||tuple->op==OR){
            process_ARITHOP(tuple, fp);
        }
        else if(tuple->op==LT||tuple->op==LE||tuple->op==GT||tuple->op==GE||tuple->op==EQ||tuple->op==NE){
            process_RELATIONALOP(tuple, fp);
        }
        else if(tuple->op==PRINT){
            process_PRINT1(tuple, fp);
        }
        else if(tuple->op==GET_VALUE){
            process_GET_VALUE1(tuple, fp);
        }
        else if(tuple->op==LABEL){
            process_LABEL(tuple, fp);
        }
        else if(tuple->op==GOTO){
            process_GOTO(tuple, fp);
        }
        else if(tuple->op==IF){
            process_IF(tuple, fp);
        }
        else if(tuple->op==U_MINUS||tuple->op==U_PLUS){
            process_UNARY1(tuple, fp);
        }
        else if(tuple->op==CALL)
        {
            process_call(tuple, fp);
        }
}
