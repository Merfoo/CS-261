#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */

void processFile(FILE *file);

/****************************************/

int main (int argc, const char * argv[]) {
    /*Write this*/
    FILE *file;

    if(argc < 2)
    {
        printf("A file name must be supplied!\n");
        return 0;
    }

    file = fopen(argv[1], "r");

    if(!file)
    {
        printf("Error openining file %s\n", argv[1]);
        return 0;
    }
    
    printf("Opened %s successfully!\n", argv[1]);
    
    processFile(file);

    fclose(file);
}

void processFile(FILE *file)
{
    int i;
    char *word;
    struct hashMap *map;
    struct hashLink *cur;

    word = 0;
    map = (struct hashMap *) malloc(sizeof(struct hashMap));
    initMap(map, 100);

    while(1)
    {
        word = getWord(file);
        
        if(!word)
            break;

        printf("Words! %s\n", word);
       
        if(containsKey(map, word))
            insertMap(map, word, *atMap(map, word) + 1);

        else
            insertMap(map, word, 1);
    }

    i = 0;

    for(i = 0; i < map->tableSize; i++)
    {
        cur = map->table[i];

        while(cur)
        {
            printf("%s: %d\n", cur->key, cur->value);
            cur = cur->next;
        }
    }

    freeMap(map);
    free(map);
}

char* getWord(FILE *file)
{
    int v;
    int cap;
    int size;
    char *word;

    cap = 5;
    size = 0;
    word = (char *) malloc(sizeof(char) * cap);
    assert(word);

    while(1)
    {
        char c;

        v = fgetc(file);
        
        if(v == EOF)
            break;

        c = (char) v;
        
        if(v == ' ' || v == '.' || v == '\n' || v == '\r')
        {
            if(size == 0)
                continue;

            break;
        }

        if(size + 1 >= cap)
        {
            char *tmp;
            int i;

            cap *= 2;
            tmp = (char *) malloc(sizeof(char) * cap);

            i = 0;
            
            while(i < size)
            {
                tmp[i] = word[i];
                i++;
            }

            free(word);
            word = tmp;
        }

        word[size++] = c;
    }

    if(size == 0 && v == EOF)
    {
        free(word);
        return 0;
    }

    word[size] = '\0';
    return word;
}
