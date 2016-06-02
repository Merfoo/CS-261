#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

int stringHash(char *str)
{
    #if HASHING_FUNCTION == 1
        return stringHash1(str);
    
    #else
        return stringHash2(str);

    #endif
}
void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  /*write this*/
    int i = 0;

    for(i = 0; i < ht->tableSize; i++)
    {
        struct hashLink *cur = ht->table[i];

        while(cur)
        {
            struct hashLink *next = cur->next;
            free(cur->key);
            free(cur);
            cur = next;
        }

        ht->table[i] = NULL;
    }

    free(ht->table);
}

void _resizeTable(struct hashMap *ht)
{
    int i;
    struct hashMap *nht;
    nht = (struct hashMap *) malloc(sizeof(struct hashMap));
    assert(nht);

    /*printf("Resizing table!\n");*/
    initMap(nht, ht->tableSize * 2);

    for(i = 0; i < ht->tableSize; i++)
    {
        struct hashLink *cur;
        cur = ht->table[i];

        while(cur)
        {
            struct hashLink *next;
            next = cur->next;
            
            insertMap(nht, cur->key, cur->value);
            free(cur);
            cur = next;
        }
    }

    free(ht->table);
    ht->table = nht->table;
    ht->tableSize = nht->tableSize;
    ht->count = nht->count;
    free(nht);
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
    /*assert(ht);*/

    /* Check if key already exists, if so just replace its value */
    ValueType *val;

    val = atMap(ht, k);

    if(val)
        *val = v;

    /* Create and insert new key if doesn't exist */
    else
    {
        int idx;
        struct hashLink *item;

        idx = stringHash(k) % ht->tableSize;
        item = (struct hashLink *) malloc(sizeof(struct hashLink));
        assert(item);

        item->key = k;
        item->value = v;
        item->next = ht->table[idx];

        ht->table[idx] = item;
        ht->count++;

        /*printf("%d :: %d\n", ht->count, ht->tableSize);*/
        if(tableLoad(ht) > 4)
            _resizeTable(ht);
    }
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
    /*assert(ht);*/

    struct hashLink *cur = ht->table[stringHash(k) % ht->tableSize];

    while(cur)
    {
        if(strcmp(cur->key, k) == 0)
            return &(cur->value);

        cur = cur->next;
    }

    return 0;
}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
    /*assert(ht);*/

    struct hashLink *cur;

    cur = ht->table[stringHash(k) % ht->tableSize];

    while(cur)
    {
        if(strcmp(cur->key, k) == 0)
            return 1;

        cur = cur->next;
    }

    return 0;
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
    /*assert(ht);*/

    int idx;
    struct hashLink *cur;
    struct hashLink *pre;
    
    idx = stringHash(k) % ht->tableSize;
    cur = ht->table[idx];
    pre = 0;

    while(cur)
    {
        if(strcmp(cur->key, k) == 0)
        {
            if(!pre)
                ht->table[idx] = cur->next;

            else
                pre->next = cur->next;

            free(cur->key);
            free(cur);
            ht->count--;
            return;
        }

        pre = cur;
        cur = cur->next;
    }

    printf("Couldn't find key %s\n", k);
}   

int sizeMap (struct hashMap *ht)
{  /*write this*/
    assert(ht);

    return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
    /*assert(ht);*/

    int buckets;
    int i;
    
    buckets = 0;
    i = 0;

    for(i = 0; i < ht->tableSize; i++)
        if(ht->table[i])
            buckets++;

    return buckets;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
    assert(ht);

    return ht->tableSize - capacityMap(ht);
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
    assert(ht);

    return (float) ht->count / (float) ht->tableSize;
}
