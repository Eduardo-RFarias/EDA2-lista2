#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 101
#define NULL_VALUE -1

typedef struct kv
{
    int key;
    int value;
} KV;

void ht_count(KV *table, int grade)
{
    if (table[grade].key == NULL_VALUE)
    {
        table[grade].key = grade;
        table[grade].value = 1;
    }
    else
    {
        table[grade].value++;
    }
}

void ht_clear(KV *table)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        table[i].key = NULL_VALUE;
    }
}

int qsort_cmp(const void *a, const void *b)
{
    KV *kv1 = (KV *)a;
    KV *kv2 = (KV *)b;

    // make sure NULL_VALUE is always at the end
    if (kv1->key == NULL_VALUE && kv2->key == NULL_VALUE)
        return 0;
    if (kv1->key == NULL_VALUE)
        return 1;
    if (kv2->key == NULL_VALUE)
        return -1;

    // if value is equal, sort by key in descending order
    if (kv1->value == kv2->value)
    {
        return kv2->key - kv1->key;
    }

    // sort by value in descending order
    return kv2->value - kv1->value;
}

int main()
{
    KV table[HASH_SIZE];
    ht_clear(table);

    int n;
    scanf("%d", &n);

    int grade;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &grade);
        ht_count(table, grade);
    }

    qsort(table, HASH_SIZE, sizeof(KV), qsort_cmp);

    printf("%d\n", table[0].key);

    return 0;
}