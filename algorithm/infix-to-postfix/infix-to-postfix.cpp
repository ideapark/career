/*
 * Copyright (C) Zhou Peng <lockrecv@qq.com> 
 *
 * Infix to postfix expression
 */
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

string calcPostfixExpression(const string postfixExpression)
{
    return "Not implemented yet!";
}

#define TEST(expression)  do {                   \
    cout << expression << ": ";                  \
    cout << infixToPostfix(expression) << endl;  \
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
