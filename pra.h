//GROUP_23
//Akshika Goel (2016B5A70672P)
//Akriti Garg (2016B4A70480P)
//Shristi Kumari (2016B4A70574P)
//Pooja Tulsyan (2016B2A70721P)
#ifndef AAAA
#define AAAA

extern int syn_err ;

typedef enum{
	eps,$,NUM,RNUM,INTEGER,REAL,ID,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,RECORD,TAGGED,UNION,GET_VALUE,PRINT,USE,WITH,PARAMETERS,
	TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,PLUS,MINUS,MUL,DIV,LT,LE,GE,GT,EQ,NE,DEF,ENDDEF,
	DRIVERDEF,DRIVERENDDEF,COLON,RANGEOP,SEMICOL,COMMA,ASSIGNOP,SQBO,SQBC,BO,BC,COMMENTMARK,LABEL,GOTO,IF,U_MINUS,U_PLUS,FUNCTION,RET,CALL,PARAM,RETURN
}TOKEN;


typedef enum{
	program,moduleDeclarations,moduleDeclaration,otherModules,driverModule,module,ret,input_plist,N1,output_plist,N2,dataType,
	range_arrays,type,moduleDef,statements,statement,ioStmt,boolConstt,var_id_num,var,whichId,simpleStmt,assignmentStmt,whichStmt,
	lvalueIDStmt,lvalueARRStmt,inde,moduleReuseStmt,optional,idList,N3,expression,U,new_NT,unary_op,arithmeticOrBooleanExpr,N7,
	AnyTerm,N8,arithmeticExpr,N4,term,N5,factor,op1,op2,logicalOp,relationalOp,declareStmt,condionalStmt,caseStmts,N9,value,
	defaul,iterativeStmt,range
} NON_TERMINAL;


struct token_info{
int line_number_var;
TOKEN terminal;
char* value;
};

#endif


/*<<<driver program>>>
start

end

<<module empty>> takes input[a:boolean];
start
print(a);
end
<<module prog>> takes input[b:boolean];
start
print(b);
declare index:integer;
for(index in 1..15)
start
print(b);
end
end*/
