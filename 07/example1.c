#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

void* thread_entry(void* arg)
{
    int i;
    
    for (i = 0; i < (intptr_t)arg; i++) {
        sleep(1);
        printf("Hello!\n");
    }

    return NULL;
}


int main()
{
    int er;
    void* retval;
    pthread_t tid;
    
    er = pthread_create(&tid, NULL, thread_entry, (void*)5);
    if (er != 0) {
        fprintf(stderr, "ERROR: pthread_create failed\n");
        return -1;
    }

    er = pthread_join(tid, &retval);
    if (er != 0) {
        fprintf(stderr, "ERROR: pthread_join failed\n");
        return -1;
        
    }

    printf("Thread returned %p", retval);
    return 0;
}