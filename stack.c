#include <stdio.h>
#include <stdlib.h>

/*
    This implementation of a stack is a mishmash from a variety of sources:
    https://www.techiedelight.com/stack-implementation/
    https://www.geeksforgeeks.org/program-to-insert-an-element-at-the-bottom-of-a-stack/
    https://www.geeksforgeeks.org/print-stack-elements-from-top-to-bottom/
*/


struct stack
{
    int maxsize;
    int top;
    char *items;
};
 
struct stack* newStack(int capacity)
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
 
    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (char*)malloc(sizeof(char) * capacity);
 
    return pt;
}
 
int size(struct stack *pt) {
    return pt->top + 1;
}
 
int isEmpty(struct stack *pt) {
    return pt->top == -1;
}
 
int isFull(struct stack *pt) {
    return pt->top == pt->maxsize - 1;
}
 
void push(struct stack *pt, char x)
{
    if (isFull(pt))
    {
        printf("Overflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
 
    // printf("Inserting %c\n", x);
 
    // add an element and increment the top's index
    pt->items[++pt->top] = x;
}
 
char peek(struct stack *pt)
{
    // check for an empty stack
    if (!isEmpty(pt)) {
        return pt->items[pt->top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}
 
int pop(struct stack *pt)
{
    // check for stack underflow
    if (isEmpty(pt))
    {
        printf("Underflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
 
    // printf("Removing %c\n", peek(pt));
 
    // decrement stack size by 1 and (optionally) return the popped element
    return pt->items[pt->top--];
}
 
void insertToBottom(struct stack *pt, char x)
{
    struct stack *temp = newStack(size(pt));
 
    // Iterate until S becomes empty
    while (!isEmpty(pt)) {
 
        // Push the top element of S
        // into the stack temp

        push(temp, peek(pt));
 
        // Pop the top element of S
        pop(pt);
    }
 
    // Push N into the stack S
    push(pt, x);
 
    // Iterate until temp becomes empty
    // while (!temp.empty()) {
    while(!isEmpty(temp)) {
 
        // Push the top element of
        // temp into the stack S
        push(pt, peek(temp));
 
        // Pop the top element of temp
        pop(temp);
    }
 
}

void PrintStack(struct stack *pt) {
    if(isEmpty(pt)) {
        return;
    }

    char x = peek(pt);

    printf("%c ", x);
    pop(pt);

    PrintStack(pt);

    push(pt, x);
}
