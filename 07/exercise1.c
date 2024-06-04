#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>


struct stack {
    int buf[128];
    int count;
    pthread_mutex_t mtx;
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

void* thread_push_pop(void* arg)
{
    struct stack* stk = (struct stack*)arg;

    for (int i = 0; i < 10; i++) {
        stack_push(stk, i);
        printf("%d\n", stack_pop(stk));
    }
    return NULL;
}



int main(int argc, char* argv[])
{
    struct stack stk;
    stack_init(&stk);
    pthread_t tid[2];
    
    for (int i=0; i<2; i++){
        pthread_create(&tid[i], NULL, thread_push_pop, &stk);
    }
    for (int i=0; i<2; i++){
        void* retval;
        pthread_join(tid[i], &retval);
    }
   
    return 0;
}
