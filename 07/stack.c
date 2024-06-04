#include <stdio.h>
#include <stdlib.h>

struct stack {
    int buf[128];
    int count;
};

void stack_init(struct stack* stk)
{
    stk->count = 0;
}

void stack_push(struct stack* stk, int val)
{
    stk->buf[stk->count++] = val;
}

int stack_pop(struct stack* stk)
{
    if (stk->count <= 0) {
        fprintf(stderr, "ERROR: stack is empty\n");
        abort();
    }

    return stk->buf[--stk->count];
}


int main(int argc, char* argv[])
{
    struct stack stk;

    stack_init(&stk);

    stack_push(&stk, 1);
    stack_push(&stk, 2);
    stack_push(&stk, 3);
    stack_push(&stk, 4);
    printf("poped: %d\n", stack_pop(&stk));
    printf("poped: %d\n", stack_pop(&stk));
    stack_push(&stk, 5);
    stack_push(&stk, 6);
    printf("poped: %d\n", stack_pop(&stk));
    stack_push(&stk, 7);
    printf("poped: %d\n", stack_pop(&stk));
    printf("poped: %d\n", stack_pop(&stk));
    printf("poped: %d\n", stack_pop(&stk));
    printf("poped: %d\n", stack_pop(&stk));
    
    return 0;
}