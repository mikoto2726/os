#include <stdio.h>

typedef struct {
    const char* name;
    int balance;
} account;

void transfer(account* sender, account* receiver, int amount)
{
    if (sender->balance < amount) {
        return;
    }
    sender->balance -= amount;
    receiver->balance += amount;
}


int main()
{
    account a = {
        .name = "alice",
        .balance = 10000,
    };
    account b = {
        .name = "bob",
        .balance = 5000,
    };
    int i;

    for (i = 0; i < 1000000; i++) {
        transfer(&a, &b, 1000);
        transfer(&b, &a, 1000);
    }

    printf("%s has %d yen\n", a.name, a.balance);
    printf("%s has %d yen\n", b.name, b.balance);
        
    return 0;
}