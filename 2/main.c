#include <stdio.h>
#include <stdlib.h>

// This specific hash table implementation is basically a histogram.
// There is only 95 possible keys (Printable ASCII values, SPACE to ~), and the value is the number of times
// that key was inserted in the table. So, there is no possibility of
// collision.
#define TABLE_SIZE 95
#define NULL_VALUE 0

// the hash function is the key minus the first printable ASCII value (32)
#define HASH(key) ((int)key - 32)

typedef struct kv
{
    char key;
    int value;
} KV;

void ht_clear(KV *table)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i].key = NULL_VALUE;
    }
}

void ht_count(KV *table, char key)
{
    int hash = HASH(key);

    // if the key is not in the table, insert it
    if (table[hash].key == NULL_VALUE)
    {
        table[hash].key = key;
        table[hash].value = 1;
    }
    // if the key is already in the table, increment its value
    else
    {
        table[hash].value++;
    }
}

// comparator function for qsort
// sort by value in ascending order. if the values are equal, sort by key in ascending order.
// if the key is NULL_VALUE, sort it to the end of the array.
int qsort_cmp(const void *a, const void *b)
{
    KV *kv_a = (KV *)a;
    KV *kv_b = (KV *)b;

    // if both keys are NULL_VALUE, they are equal, therefore return 0 (don't matter the order)
    if (kv_a->key == NULL_VALUE && kv_b->key == NULL_VALUE)
    {
        return 0;
    }

    // move the NULL_VALUE keys to the end of the array
    if (kv_a->key == NULL_VALUE)
    {
        return 1;
    }
    if (kv_b->key == NULL_VALUE)
    {
        return -1;
    }

    // if the values are equal, sort by key (ascending order)
    if (kv_a->value == kv_b->value)
    {
        return kv_a->key - kv_b->key;
    }

    // sort by value (ascending order)
    return kv_a->value - kv_b->value;
}

int main()
{
    KV table[TABLE_SIZE];

    // read the first char
    char key = getchar();

    // while there is input
    while (key != EOF)
    {
        // for each line, clear the table
        ht_clear(table);

        // read a char until the end of the line or the end of the file
        while (key != '\n' && key != EOF)
        {
            ht_count(table, key);
            // read the next char
            key = getchar();
        }

        // sort the table as if it was a simple array
        qsort(table, TABLE_SIZE, sizeof(KV), qsort_cmp);

        // print the inserted chars in order (the NULL_VALUE keys are already in the end of the array,
        // so print until the first NULL_VALUE key)
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (table[i].key == NULL_VALUE)
                break;

            printf("%d %d\n", table[i].key, table[i].value);
        }

        printf("\n");

        // read the next char
        key = getchar();
    }

    return 0;
}