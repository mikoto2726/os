#include <stdio.h>
#include <pthread.h>

int sum = 0;

void* thread_entry(void* arg)
{
    int i;

    for (i = 0; i < 1000000; i++) {
        sum += 1;
    }

    return NULL;
}


int main()
{
    pthread_t tid1, tid2;
    void* ret;
    int er;

    er = pthread_create(&tid1, NULL, thread_entry, NULL);
    if (er != 0) goto error;
    er = pthread_create(&tid2, NULL, thread_entry, NULL);
    if (er != 0) goto error;
    
    pthread_join(tid1, &ret);
    pthread_join(tid2, &ret);
    
    printf("sum = %d\n", sum);
    return 0;

 error:
    fprintf(stderr, "ERROR\n");
    return -1;
}