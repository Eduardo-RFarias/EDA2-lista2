#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 7207
#define PRIME 31
#define MAX_COLLISIONS 10
#define NULL_VALUE -1

#define HASH(x) (x % HASHSIZE)
#define HASH2(x) (PRIME + (x % (HASHSIZE - PRIME)))
#define JUMP(x, y) ((x + y) % HASHSIZE)

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
    int offset;
    int collisions;

    // Loop until we find a free position or we reach the maximum number of collisions,
    for (hash = HASH(key), offset = HASH2(key), collisions = 0;
         table[hash].key != NULL_VALUE && collisions < MAX_COLLISIONS;
         hash = JUMP(hash, offset), collisions++)
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