compile: lexer.o parser.o ast.o symbol_table.o print_symbol_table.o  semantic_analyzer.o type.o offset.o codegen.o driver.o
	gcc driver.o lexer.o parser.o ast.o symbol_table.o print_symbol_table.o  semantic_analyzer.o type.o offset.o codegen.o -o compiler
driver.o: driver.c
	gcc -c driver.c
symbol_table.o: symbol_table.c
	gcc -c symbol_table.c
print_symbol_table.o: print_symbol_table.c
	gcc -c print_symbol_table.c
semantic_analyzer.o: semantic_analyzer.c
	gcc -c semantic_analyzer.c
type.o: type.c
	gcc -c type.c
offset.o: offset.c
	gcc -c offset.c
codegen.o: codegen.c
	gcc -c codegen.c
ast.o: ast.c
	gcc -c ast.c
parser.o: parser.c
	gcc -c parser.c
lexer.o: lexer.c
	gcc -c lexer.c
