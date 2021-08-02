#include <stdio.h>
#include <string.h>
struct stack{
    char a[50];
    int top;
}st;
int openingParantheses() {
    if (st.a[st.top] == '(')return 1;
    return 0;
}
int isEmpty() {
    if (st.top == -1) return 1;
    return 0;
}
char stack_top() {
    return st.a[st.top];
}
int hasHigherPrecedence(char t,char c) {
    if (isEmpty())return 1;
    if (t == '/')return 1;
    if (t == '*' && c != '/') return 1;
    if (t == '+' && c != '/' && c != '*')return 1;
    return 0;
}
void pop() {
    st.top--;
}
void push(char ch) {
    st.a[++st.top] = ch;
}
void infix(char exp[]) {
    char temp[50];
    int k = 0;
    for (int i = 0; i < strlen(exp); i++) {
        char ch = exp[i];
        if (ch != '/' && ch != '*' && ch != '+' && ch != '-' && ch != '(' && ch != ')') {
            temp[k++] = ch;
        } else if (ch == '/' || ch == '+' || ch == '*' || ch == '-') {
            while (!isEmpty() && hasHigherPrecedence(stack_top(), ch) && !openingParantheses()) {
                temp[k++] = stack_top();
                pop();
            }
            push(ch);
        } else if (ch == '(')push(ch);
        else if (ch == ')') {
            while (!isEmpty() && !openingParantheses()) {
                temp[k++] = stack_top();
                pop();
            }
            pop();
        }
    }
    while (!isEmpty()) {
        char ch = stack_top();
        temp[k++] = ch;
        pop();
    }
    temp[k] = '\0';
    puts(temp);
}
int main() {
    char exp[50];
    st.top = -1;
    gets(exp);
    infix(exp);
}
