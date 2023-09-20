#include <stdlib.h>
#include <stdio.h>

#define PRESIDENTS_HASH_SIZE 90
#define SENATORS_HASH_SIZE 900
#define FEDERAL_DEPUTIES_HASH_SIZE 9000
#define STATE_DEPUTIES_HASH_SIZE 90000

#define NULL_VALUE 0

typedef struct kv
{
    int key;
    int value;
} KV;

void ht_count(KV *table, int code, int offset)
{
    int hash = code - offset;

    if (table[hash].key == NULL_VALUE)
    {
        table[hash].key = code;
        table[hash].value = 1;
    }
    else
    {
        table[hash].value++;
    }
}

// comparator function for qsort
// sort by value in descending order. if the values are equal, sort by key in descending order.
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

    // if the values are equal, sort by key (descending order)
    if (kv_a->value == kv_b->value)
    {
        return kv_b->key - kv_a->key;
    }

    // sort by value (descending order)
    return kv_b->value - kv_a->value;
}

int main()
{
    KV *presidents = calloc(PRESIDENTS_HASH_SIZE, sizeof(KV));
    KV *senators = calloc(SENATORS_HASH_SIZE, sizeof(KV));
    KV *federalDeputies = calloc(FEDERAL_DEPUTIES_HASH_SIZE, sizeof(KV));
    KV *stateDeputies = calloc(STATE_DEPUTIES_HASH_SIZE, sizeof(KV));

    int S, F, E;
    scanf("%d %d %d", &S, &F, &E);

    int nullVotes = 0;
    int presidentVotes = 0;
    int validVotes = 0;

    int code;
    while (scanf("%d", &code) != EOF)
    {
        if (code <= 0)
        {
            nullVotes++;
            continue;
        }

        if (code <= 99)
        {
            ht_count(presidents, code, 10);
            presidentVotes++;
        }
        else if (code <= 999)
        {
            ht_count(senators, code, 100);
        }
        else if (code <= 9999)
        {
            ht_count(federalDeputies, code, 1000);
        }
        else if (code <= 99999)
        {
            ht_count(stateDeputies, code, 10000);
        }

        validVotes++;
    }

    // sort the tables
    qsort(presidents, PRESIDENTS_HASH_SIZE, sizeof(KV), qsort_cmp);
    qsort(senators, SENATORS_HASH_SIZE, sizeof(KV), qsort_cmp);
    qsort(federalDeputies, FEDERAL_DEPUTIES_HASH_SIZE, sizeof(KV), qsort_cmp);
    qsort(stateDeputies, STATE_DEPUTIES_HASH_SIZE, sizeof(KV), qsort_cmp);

    // print the votes count
    printf("%d %d\n", validVotes, nullVotes);

    // print the elected president, or "Segundo turno" if there isn't one (more than 50% of the votes)
    if (presidents[0].value > presidentVotes / 2)
    {
        printf("%d\n", presidents[0].key);
    }
    else
    {
        printf("Segundo turno\n");
    }

    // print the elected senators
    for (int i = 0; i < S; i++)
    {
        printf("%d ", senators[i].key);
    }
    printf("\n");

    // print the elected federal deputies
    for (int i = 0; i < F; i++)
    {
        printf("%d ", federalDeputies[i].key);
    }
    printf("\n");

    // print the elected state deputies
    for (int i = 0; i < E; i++)
    {
        printf("%d ", stateDeputies[i].key);
    }
    printf("\n");

    free(presidents);
    free(senators);
    free(federalDeputies);
    free(stateDeputies);

    return 0;
}