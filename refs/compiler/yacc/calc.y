%{
/*
 * exp --> exp addop term | term
 * addop --> + | -
 * term --> term mulop factor | factor
 * mulop --> *
 * factor --> ( exp ) | number
 */
#include <stdio.h>
#include <ctype.h>
%}

%token NUMBER

%%

command : exp { printf("%d\n", $1); }
        ; /* allows printing of the result */

exp : exp '+' term { $$ = $1 + $3; }
    | exp '-' term { $$ = $1 - $3; }
    | term { $$ = $1; }
    ;

term : term '*' factor { $$ = $1 * $3; }
     | factor { $$ = $1; }
     ;

factor : NUMBER       { $$ = $1; }
       | '(' exp ')'  { $$ = $2; }
       ;

%%

int main(void)
{
	return yyparse();
}

int yylex(void)
{
	int c;
	while ((c = getchar()) == ' ')
		;
	/* eliminates blanks */
	if (isdigit(c)) {
		ungetc(c, stdin);
		scanf("%d", &yylval);
		return (NUMBER);
	}
	if (c == '\n')
		return 0;
	/* makes the parse stop */
	return (c);
}

/*
 * allows for printing of an error message
 */
int yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
	return 0;
}
