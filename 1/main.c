#include <stdio.h>
#include <stdlib.h>

// Load factor of 0.7 (70%)
// 5000/0.7 ~~ 7143, closest prime number is 7151.
#define HASHSIZE 7151
#define MAX_COLLISIONS 15
#define NULL_VALUE -1

#define HASH(x) (x % HASHSIZE)
#define JUMP(x) ((x + 1) % HASHSIZE)

typedef struct kv
{
    int key;
    int value;
} KV;

void ht_clear(KV *table)
{
    // Loop through the table and set all positions to NULL_VALUE
    for (int i = 0; i < HASHSIZE; i++)
    {
        table[i].key = NULL_VALUE;
    }
}

KV ht_count(KV *table, int key)
{
    int hash;
    int collisions;

    // Loop until we find a free position or we reach the maximum number of collisions,
    for (hash = HASH(key), collisions = 0;
         table[hash].key != NULL_VALUE && collisions < MAX_COLLISIONS;
         hash = JUMP(hash), collisions++)
    {
        // If we find the number, we increment its value and return it
        if (table[hash].key == key)
        {
            table[hash].value++;
            return table[hash];
        }
    }

    // If we reached the maximum number of collisions, we exit the program with error code 1
    if (collisions == MAX_COLLISIONS)
    {
        fprintf(stderr, "Maximum number of collisions reached!\n");
        exit(1);
    }

    // If we found a free position, we insert the number and return it
    table[hash].key = key;
    table[hash].value = 1;

    return table[hash];
}

int main()
{
    KV table[HASHSIZE];

    int N;
    scanf("%d", &N);

    while (N != 0)
    {
        // Clear the table for each test case
        ht_clear(table);

        KV greatest;
        greatest.value = 0;

        for (int A, i = 0; i < N; i++)
        {
            scanf("%d", &A);
            KV current = ht_count(table, A);

            if (current.value > greatest.value)
            {
                greatest = current;
            }
        }

        printf("%d\n", greatest.key);

        // Read the next N and loop
        scanf("%d", &N);
    }

    return 0;
}