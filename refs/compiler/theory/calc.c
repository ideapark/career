/*
 * Simple integer arithmetic calculator
 * according to the EBNF:
 *
 * <expr> -> <term> { <addop> <term> }
 * <addop> -> + | -
 * <term> -> <factor> { <mulop> <factor> }
 * <mulop> -> *
 * <factor> -> ( <expr> ) | Number
 *
 * Inputs a line of text from stdin
 * Outputs "Error" or the result.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * global token variable
 */
char token;

/*
 * function prototypes for recursive calls
 */
int expr(void);
int term(void);
int factor(void);

void error(void)
{
	fprintf(stderr, "Error\n");
	exit(1);
}

void match(char expectedToken)
{
	if (token == expectedToken)
		token = getchar();
	else
		error();
}

int main(void)
{
	int result;
	token = getchar(); /* load token with first character for lookahead */

	result = expr();
	if (token == '\n')  /* check for end of line */
		printf("Result = %d\n", result);
	else
		error();  /* extraneous chars on line */
	return 0;
}

int expr(void)
{
	int temp = term();
	while (token == '+' || token == '-') {
		switch (token) {
		case '+':
			match('+');
			temp += term();
			break;
		case '-':
			match('-');
			temp -= term();
			break;
		}
	}
	return temp;
}

int term(void)
{
	int temp = factor();
	while (token == '*') {
		match('*');
		temp *= factor();
	}
	return temp;
}

int factor(void)
{
	int temp;
	if (token == '(') {
		match('(');
		temp = expr();
		match(')');
	} else if (isdigit(token)) {
		ungetc(token, stdin);
		scanf("%d", &temp);
		token = getchar();
	} else {
		error();
	}
	return temp;
}
