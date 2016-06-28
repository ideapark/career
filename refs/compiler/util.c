#include "global.h"
#include "util.h"

/*
 * Procedure printToken prints a token
 * and its lexeme to the listing file
 */
void printToken(TokenType token, const char *tokenString)
{
	switch (token) {
	case IF:
	case THEN:
	case ELSE:
	case END:
	case REPEAT:
	case UNTIL:
	case READ:
	case WRITE:
		fprintf(listing, "reserved word: %s\n", tokenString);
		break;
	case ASSIGN:
		fprintf(listing, ":=\n");
		break;
	case LT:
		fprintf(listing, "<\n");
		break;
	case EQ:
		fprintf(listing, "=\n");
		break;
	case LPAREN:
		fprintf(listing, "(\n");
		break;
	case RPAREN:
		fprintf(listing, ")\n");
		break;
	case SEMI:
		fprintf(listing, ";\n");
		break;
	case PLUS:
		fprintf(listing, "+\n");
		break;
	case MINUS:
		fprintf(listing, "-\n");
		break;
	case TIMES:
		fprintf(listing, "*\n");
		break;
	case OVER:
		fprintf(listing, "/\n");
		break;
	case ENDFILE:
		fprintf(listing, "EOF\n");
		break;
	case NUM:
		fprintf(listing, "NUM, val= %s\n", tokenString);
		break;
	case ID:
		fprintf(listing, "ID, name= %s\n", tokenString);
		break;
	case ERROR:
		fprintf(listing, "ERROR, %s\n", tokenString);
		break;
	default:  /* should never happen */
		fprintf(listing, "Unknown token: %d\n", token);
	}
}

/*
 * Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode *newStmtNode(StmtKind kind)
{
	int i;

	TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
	if (t == NULL) {
		fprintf(listing, "Out of memory error at line %d\n", lineno);
	} else {
		for (i = 0; i < MAXCHILDREN; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = StmtK;
		t->kind.stmt = kind;
		t->lineno = lineno;
	}
	return t;
}

/*
 * Function newExpNode creates a new expression
 * node for syntax tree construction
 */
TreeNode *newExpNode(ExpKind kind)
{
	int i;

	TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
	if (t == NULL) {
		fprintf(listing, "Out of memory error at line %d\n", lineno);
	} else {
		for (i = 0; i < MAXCHILDREN; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = ExpK;
		t->kind.exp = kind;
		t->lineno = lineno;
		t->type = Void;
	}
	return t;
}

/*
 * Function copyString allocates and makes a new
 * copy of an existing string
 */
char *copyString(char *s)
{
	int n;
	char *t;

	if (s == NULL)
		return NULL;
	n = strlen(s) + 1;
	t = malloc(n);
	if (t = NULL)
		fprintf(listing, "Out of memory error at line %d\n", lineno);
	else
		strcpy(t, s);
	return t;
}

/*
 * Variable indentno is used by printTree to
 * store current number of spaces ot indent
 */
static indentno = 0;
