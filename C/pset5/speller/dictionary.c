// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Will increase as words are loaded into dictionary
unsigned int dictionary_size = 0;

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
    unsigned int h = hash(word);

    // Create new node
    node *cursor;

    // Create temporary pointer to what list is pointing to
    if (table[h] != NULL)
    {
        cursor = table[h];
    }
    else
    {
        return false;
    }

    // As long as the node is not null...
    while (cursor != NULL)
    {
        // Compare words case insensitively
        if (strcasecmp(cursor->word, word) == 0)
        {
           return true;
        }
        else
        {
            // Set the temporary node to equal the next node
            cursor = cursor->next;
        }
    }

    free(cursor);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function illustration
    // Brenda Anderson 2018 (curiouskiwi)
    // Available from https://github.com/curiouskiwi/cs50x-help/blob/master/hash.c
    uint32_t hash = 0;
    while (*word)
    {
        hash = (hash << 2) ^ (*word | 0x20);
        word++;
    }

    // Return a value between 0 and 65535
    return (int) ((hash >> 16) ^ (hash & 0xffff));
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialise word variable
    char word[LENGTH + 1];

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return 2;
    }

    // Loop through words, hashing each one
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return 3;
        }

        // Copy word to new node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash word to obtain hash value
        unsigned int h = hash(word);

        if (table[h] == NULL)
        {
            table[h] = new_node;
        }

        // If there's already a node at this index...
        else if (table[h] != NULL)
        {
            // If there's only one node...
            if (table[h]->next == NULL)
            {
                // Head will point to new node
                table[h]->next = new_node;
            }
            // If there's more than one node, insert new node at the head of linked list
            else
            {
                new_node->next = table[h]->next;
                table[h]->next = new_node;
            }
        }

        // Increment dictionary size by 1 (word)
        dictionary_size++;
    }

    // Close file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Create cursor node
    node *cursor;

    // Create temporary node
    node *tmp;

    // Loop through hash table
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            cursor = table[i];
            tmp = cursor;

            // While there are more nodes in the linked list...
            while (cursor->next != NULL)
            {
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
            }
            free(cursor);
        }
    }
    return true;
}
