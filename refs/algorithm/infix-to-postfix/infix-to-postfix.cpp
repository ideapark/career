/*
 * Copyright (C) Zhou Peng <lockrecv@qq.com>
 *
 * Infix to postfix expression
 */
#include <cstdlib>
#include <stack>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

#define IS_ADD(ch)       ((ch) == "+")
#define IS_MINUS(ch)     ((ch) == "-")
#define IS_MULTIPLY(ch)  ((ch) == "*")
#define IS_DIVIDE(ch)    ((ch) == "/")
#define IS_OPERATOR(ch)  (IS_ADD(ch) || IS_MINUS(ch) || IS_MULTIPLY(ch) || IS_DIVIDE(ch))

#define PRECEDENCE_LEVEL1(op)        (IS_ADD(op) || IS_MINUS(op))
#define PRECEDENCE_LEVEL2(op)        (IS_MULTIPLY(op) || IS_DIVIDE(op))
#define PRECEDENCE_HIGHER(op1, op2)  (PRECEDENCE_LEVEL2(op1) && PRECEDENCE_LEVEL1(op2))

string infixToPostfix(const string expression)
{
	ostringstream infixExpressoinWriter;

	for (int i = 0; i < expression.length(); i++) {
		if (IS_OPERATOR(expression.substr(i, 1)))
			infixExpressoinWriter << " " << expression.substr(i, 1) << " ";
		else
			infixExpressoinWriter << expression.substr(i, 1);
	}

	string token;
	stack<string> operatorStack;
	istringstream infixExpressionReader(infixExpressoinWriter.str());
	ostringstream postfixExpressionWriter;

	while (infixExpressionReader >> token) {
		if (IS_OPERATOR(token)) {
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

	if (IS_ADD(operatorString))
		result = left + right;

	if (IS_MINUS(operatorString))
		result = left - right;

	if (IS_MULTIPLY(operatorString))
		result = left * right;

	if (IS_DIVIDE(operatorString))
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
		if (IS_OPERATOR(token)) {
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

#define TEST(expression)  do { \
	string postfixExpression = infixToPostfix(expression); \
	cout << expression << ": "; \
	cout << postfixExpression  << ": "; \
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
