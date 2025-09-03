#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for operators (char stack)
char opStack[MAX];
int opTop = -1;

void pushOp(char c) {
    opStack[++opTop] = c;
}

char popOp() {
    return opStack[opTop--];
}

char peekOp() {
    return opStack[opTop];
}

int isEmptyOp() {
    return opTop == -1;
}

// Stack for evaluation (int stack)
int valStack[MAX];
int valTop = -1;

void pushVal(int v) {
    valStack[++valTop] = v;
}

int popVal() {
    return valStack[valTop--];
}

// Precedence function
int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
    }
    return -1;
}

// Convert infix to postfix
void infixToPostfix(char *exp, char *postfix) {
    int k = 0;
    for (int i = 0; exp[i]; i++) {
        char c = exp[i];

        // Skip spaces
        if (c == ' ') continue;

        // If digit, add to postfix
        if (isdigit(c)) {
            while (isdigit(exp[i])) {
                postfix[k++] = exp[i++];
            }
            postfix[k++] = ' ';
            i--; // step back
        }
        else if (c == '(') {
            pushOp(c);
        }
        else if (c == ')') {
            while (!isEmptyOp() && peekOp() != '(') {
                postfix[k++] = popOp();
                postfix[k++] = ' ';
            }
            popOp(); // remove '('
        }
        else { // operator
            while (!isEmptyOp() && precedence(c) <= precedence(peekOp())) {
                postfix[k++] = popOp();
                postfix[k++] = ' ';
            }
            pushOp(c);
        }
    }
    // Pop remaining operators
    while (!isEmptyOp()) {
        postfix[k++] = popOp();
        postfix[k++] = ' ';
    }
    postfix[k] = '\0';
}

// Evaluate postfix
int evaluatePostfix(char *postfix) {
    char *token = strtok(postfix, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            pushVal(atoi(token));
        } else {
            int val2 = popVal();
            int val1 = popVal();
            switch (token[0]) {
                case '+': pushVal(val1 + val2); break;
                case '-': pushVal(val1 - val2); break;
                case '*': pushVal(val1 * val2); break;
                case '/': pushVal(val1 / val2); break;
            }
        }
        token = strtok(NULL, " ");
    }
    return popVal();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    // Join arguments into a single string (for safety with spaces)
    char expr[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(expr, argv[i]);
    }

    char postfix[256];
    infixToPostfix(expr, postfix);

    int result = evaluatePostfix(postfix);
    printf("%d\n", result);

    return 0;
}
