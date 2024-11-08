#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#define PHILOSOPHERS 5
#define DAYS 10000

static const char* names[] = {
    "Enryo", "Socrates", "Platon", "Aristoteles", "Kant"
};

pthread_t philosophers[PHILOSOPHERS];
pthread_mutex_t fork_mutex[PHILOSOPHERS];

static void eat(int phil, int fork1, int fork2)
{
    printf("%s: \"Yummy!\"\n", names[phil]);
}

void* philosopher_thread(void* arg)
{
    int phil = (int)(intptr_t)arg;
    unsigned int r = (phil << 16) + time(NULL);
    int left = phil;
    int right = (phil+1) % PHILOSOPHERS;
    int first = left < right ? left : right;
    int second = left < right ? right : left;
    int i;

    usleep(rand_r(&r) % 100000);

    for (i = 0; i < DAYS; i++) {
        /* Think for a while */
        usleep(rand_r(&r) % 10000);
        
        /* Staring to eat */
        pthread_mutex_lock(&fork_mutex[first]);
        printf("%s picked up fork %d\n", names[phil], first);
        pthread_mutex_lock(&fork_mutex[second]);
        printf("%s picked up fork %d\n", names[phil], second);

        eat(phil, left, right);

        printf("%s returned fork %d\n", names[phil], second);
        pthread_mutex_unlock(&fork_mutex[second]);
        printf("%s returned fork %d\n", names[phil], first);
        pthread_mutex_unlock(&fork_mutex[first]);
    }

    return NULL;
}


int main()
{
    int er, i;
    void* ret;

    for (i = 0; i < PHILOSOPHERS; i++) {
        er = pthread_mutex_init(&fork_mutex[i], NULL);
        if (er != 0) goto error;
    }
    for (i = 0; i < PHILOSOPHERS; i++) {
        er = pthread_create(&philosophers[i], NULL, philosopher_thread, (void*)(intptr_t)i);
        if (er != 0) goto error;
    }
    for (i = 0; i < PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], &ret);
    }
    printf("finished\n");
    return 0;

 error:
    fprintf(stderr, "ERROR\n");
    return -1;
}
