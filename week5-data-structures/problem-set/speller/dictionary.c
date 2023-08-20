// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int idx = hash(word);
    node *cursor = table[idx];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int acum = 0;
    while(*word)
    {
        acum += toupper(*word);
        word++;
    }
    return acum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    node *cursor;
    // set hash table to null
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // open dictionary file
    FILE *infile = fopen(dictionary, "rt");
    if (!infile)
    {
        printf("Error: could not open dictionary file %s\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(infile, "%s", word) > 0)
    {
        unsigned int idx = hash(word);
        // crear nuevo nodo
        node *tmp = malloc(sizeof(node));
        if (!tmp)
        {
            unload();
            return false;
        }
        strcpy(tmp->word, word);
        tmp->next = NULL;
        // agregar el nuevo nodo al final
        if (table[idx] == NULL)
        {
            table[idx] = tmp;
        }
        else
        {
            cursor = table[idx];
            while (cursor->next)
            {
                cursor = cursor->next;
            }
            cursor->next = tmp;
        }
    }
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int count = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            count++;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        table[i] = NULL;
        node *tmp;
        while (cursor)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
    return true;
}
