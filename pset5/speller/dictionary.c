// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdint.h>

#include "dictionary.h"

// my variables
int dictcount = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    if (table[index] == NULL)
    {
        return false;
    }
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}


unsigned int hash(const char *word)
{
    uint32_t hash = 0;
    while (*word)
    {
        hash = (hash << 2) ^ (int) tolower(*word); //(*s | 0x20);
        word++;
    }
    return (unsigned int)((hash >> 16) ^ (hash & 0xffff));
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary file for reading
    FILE *dic = fopen(dictionary, "r");
    if (!dic) // check that the file openned successfully
    {
        return false;
    }
    char word[46]; // temporary holder for word
    // read words from file
    while (fscanf(dic, "%s", word) != EOF)
    {
        // create node to store the new scanned word in hash table
        node *n = malloc(sizeof(node));
        if (!n)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;

        unsigned int index = hash(word);

        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        dictcount++;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *temp = table[i];
            node *cursor = temp;
            while (temp->next != NULL)
            {
                cursor = temp->next;
                free(temp);
                temp = cursor;
            }
            free(temp);
        }
    }
    return true;
}
