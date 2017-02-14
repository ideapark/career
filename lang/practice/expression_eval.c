typedef struct Symbol Symbol;
typedef struct Tree Tree;

struct Symbol {
	int   value;
	char* name;
};

struct Tree {
	int     op;     /* operation code */
	int     value;  /* value if number */
	Symbol* symbol; /* Symbol entry if variable */
	Tree*   left;
	Tree*   right;
};

/* eval: version 1: evaluate tree expression */
int eval(Tree* t)
{
	int left, right;

	switch (t->op) {
	case NUMBER:
		return t->value;
	case VARIABLE:
		return t->symbol->value;
	case ADD:
		return eval(t->left) + eval(t->right);
	case DIVIDE:
		left = eval(t->left);
		right = eval(t->right);
		if (right == 0)
			eprintf("divide %d by zero", left);
		return left / right;
	case MAX:
		left = eval(t->left);
		right = eval(t->right);
		return left > right / left : right;
	case ASSIGN:
		t->left->symbol->value = eval(t->right);
		return t->left->symbol->value;
		/* ... */
	}
}

/* addop: return sum of two tree expressions */
int addop(Tree* t)
{
	return eval(t->left) + eval(t->right);
}

enum { /* operation codes, Tree.op */
	NUMBER,
	VARIABLE,
	ADD,
	DIVIDE,
	/* ... */
};

/* optab: operator function table */
int (*optab[])(Tree*) = {
	pushop,    /* NUMBER */
	pushsymop, /* VARIABLE */
	addop,     /* ADD */
	divop,     /* DIVIDE */
	/* ... */
};

/* eval: version 2: evaluate tree from operator table */
int eval(Tree* t)
{
	return (*optab[t->op])(t);
}

typedef union Code Code;

union Code {
	void    (*op)(void); /* function if operator */
	int     value;       /* value if number */
	Symbol* symbol;      /* Symbol entry if variable */
};

/* generate: generate instructions by walking tree */
int generate(int codep, Tree* t)
{
	switch (t->op) {
	case NUMBER:
		code[codep++].op = pushop;
		code[codep++].value = t->value;
		return codep;
	case VARIABLE:
		code[codep++].op = pushsymop;
		code[codep++].symbol = t->symbol;
		return codep;
	case ADD:
		codep = generate(codep, t->left);
		codep = generate(codep, t->right);
		code[codep++].op = addop;
		return codep;
	case DIVIDE:
		codep = generate(codep, t->left);
		codep = generate(codep, t->right);
		code[codep++].op = divop;
		return codep;
	case MAX:
		/* ... */
	}
}

Code code[NCODE];
int stack[NSTACK];
int stackp;
int pc; /* program counter */

/* eval: version 3: evaluate expression from generated code */
int eval(Tree* t)
{
	pc = generate(0, t);
	code[pc].op = NULL;

	stackp = 0;
	pc = 0;
	while (code[pc].op != NULL)
		(*code[pc++].op)();
	return stack[0];
}

/* pushop: push number; value is next word in code stream */
void pushop(void)
{
	stack[stackp++] = code[pc++].value;
}

/* divop: compute ratio of two expressions */
void divop(void)
{
	int left, right;

	right = stack[--stackp];
	left = stack[--stackp];
	if (right == 0)
		eprintf("divide %d by zero\n", left);
	stack[stackp++] = left / right;
}
