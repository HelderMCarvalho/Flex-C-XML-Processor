dicionario: main.c lex.yy.c
	gcc lex.yy.c -o dicionario -lfl

lex.yy.c: dicionario.l
	flex dicionario.l