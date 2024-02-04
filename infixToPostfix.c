// Jai Shri Ram
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

// Function to push an element onto the stack
int push(char s[], int *t, char ch) {
    s[++(*t)] = ch;
}

// Function to pop an element from the stack
char pop(char s[], int *t) {
    return s[(*t)--];
}

// Function to determine the precedence of operators
int precedence(char ch) {
    if(ch == '#') return -1;
    else if(ch == '(') return 0;
    else if(ch == '+' || ch == '-') return 1;
    else if(ch == '%' || ch == '*' || ch == '/') return 2;
    else if(ch == '^') return 3;
}

int main() {
    char inExp[50], stack[50], pExp[50], ch;
    int top = -1, i = 0, j = 0;

    // Input: Infix Expression
    printf("Enter the Infix Expression: ");
    scanf("%s", inExp);

    // Initialize the stack with '#' as the bottom marker
    push(stack, &top, '#');

    // Process each character in the infix expression
    for(i = 0; inExp[i] != '\0'; ++i) {
        ch = inExp[i];

        // If the character is an operand, append it to the postfix expression
        if(isalnum(ch)) {
            pExp[j++] = ch;
        } else if(ch == '(') {
            // If the character is '(', push it onto the stack
            push(stack, &top, ch);
        } else if(ch == ')') {
            // If the character is ')', pop operators from the stack and append to postfix until '(' is encountered
            while(stack[top] != '(') {
                pExp[j++] = pop(stack, &top);
            }
            // Pop '(' from the stack
            pop(stack, &top);
        } else {
            // If the character is an operator, handle precedence and associativity
            while(precedence(stack[top]) >= precedence(ch)) {
                // Pop operators from the stack and append to postfix until a lower precedence operator is encountered
                if((ch == '^') && (stack[top] == '^'))
                    break;
                pExp[j++] = pop(stack, &top);
            }
            // Push the current operator onto the stack
            push(stack, &top, ch);
        }
    }

    // Pop any remaining operators from the stack and append to postfix
    while(stack[top] != '#') {
        pExp[j++] = pop(stack, &top);
    }

    // Null-terminate the postfix expression
    pExp[j] = '\0';

    // Output the results
    printf("\nInfix Expression is %s\n", inExp);
    printf("\nPostfix Expression is %s\n", pExp);

    return 0;    
}
