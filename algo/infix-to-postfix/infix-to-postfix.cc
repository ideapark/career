/*
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 *
 * Infix to postfix expression
 */

#include <cstdlib>
#include <stack>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

#define ADD(ch)       ((ch) == "+")
#define MINUS(ch)     ((ch) == "-")
#define MULTIPLY(ch)  ((ch) == "*")
#define DIVIDE(ch)    ((ch) == "/")
#define OPERATOR(ch)  (ADD(ch) || MINUS(ch) || MULTIPLY(ch) || DIVIDE(ch))

#define PRECEDENCE_LEVEL1(op)        (ADD(op) || MINUS(op))
#define PRECEDENCE_LEVEL2(op)        (MULTIPLY(op) || DIVIDE(op))
#define PRECEDENCE_HIGHER(op1, op2)  (PRECEDENCE_LEVEL2(op1) && PRECEDENCE_LEVEL1(op2))

string infixToPostfix(const string expression)
{
	ostringstream infixExpressoinWriter;

	for (long unsigned int i = 0; i < expression.length(); i++) {
		if (OPERATOR(expression.substr(i, 1)))
			infixExpressoinWriter << " " << expression.substr(i, 1) << " ";
		else
			infixExpressoinWriter << expression.substr(i, 1);
	}

	string token;
	stack<string> operatorStack;
	istringstream infixExpressionReader(infixExpressoinWriter.str());
	ostringstream postfixExpressionWriter;

	while (infixExpressionReader >> token) {
		if (OPERATOR(token)) {
			while (!operatorStack.empty()) {
				const string &topOperator = operatorStack.top();
				if (PRECEDENCE_HIGHER(token, topOperator)) {
					break;
				} else {
					postfixExpressionWriter << " " << topOperator << " ";
					operatorStack.pop();
				}
			}
			operatorStack.push(token);
		} else {
			postfixExpressionWriter << " " << token << " ";
		}
	}

	while (!operatorStack.empty()) {
		const string &topOperator = operatorStack.top();
		postfixExpressionWriter << " " << topOperator << " ";
		operatorStack.pop();
	}

	return postfixExpressionWriter.str();
}

static string doCalculation(const string leftOperand,
			    const string rightOperand,
			    const string operatorString)
{
	unsigned int left = atoi(leftOperand.c_str());
	unsigned int right = atoi(rightOperand.c_str());
	unsigned int result = 0;

	if (ADD(operatorString))
		result = left + right;

	if (MINUS(operatorString))
		result = left - right;

	if (MULTIPLY(operatorString))
		result = left * right;

	if (DIVIDE(operatorString))
		result = left / right;

	ostringstream stringWriter;

	stringWriter << result;

	return stringWriter.str();
}

string calcPostfixExpression(const string postfixExpression)
{
	string token;
	stack<string> calculationStack;
	istringstream postfixExpressionReader(postfixExpression);

	while (postfixExpressionReader >> token) {
		if (OPERATOR(token)) {
			const string rightOperand = calculationStack.top();
			calculationStack.pop();
			const string leftOperand = calculationStack.top();
			calculationStack.pop();

			string result = doCalculation(leftOperand, rightOperand, token);
			calculationStack.push(result);
		} else {
			calculationStack.push(token);
		}
	}

	return calculationStack.top();
}

#define TEST(expression)  do {						\
		string postfixExpression = infixToPostfix(expression);	\
		cout << expression << ": ";				\
		cout << postfixExpression  << ": ";			\
		cout << calcPostfixExpression(postfixExpression) << endl; \
	} while (0)

int main(void)
{
	TEST("12 + 2 * 8 - 9");
	TEST("12 / 2 * 8 + 9");
	TEST("12 / 2 * 8 - 9");
	TEST("12 + 2 * 8 + 9");
	TEST("12 * 2 * 8 * 9");

	return 0;
}
