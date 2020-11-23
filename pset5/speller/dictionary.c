// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576; // first three letters in a word

// Hash table
node *table[N];

// Current size of hashtable
int s = 0;

// Custom functions
node *insert_node(const char* val); // fastest
void free_list_recursively(node *n);
node *append_node(const char* word);
node *get_last_node_in_list(node *cur_node);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_code = hash(word);

    node *n = table[hash_code];
    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }

        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int code = 0;

    if (word[0] != '\0') // first letter
    {
        code += tolower(word[0]) - 97; // -97 to get index
    }

    if (word[1] != '\0') // second letter
    {
        code += tolower(word[1]) - 97; // -97 to get index
    }

    if (word[2] != '\0') // third letter
    {
        code += tolower(word[2]) - 97; // -97 to get index
    }

    if (code > (N - 1)) // overflow
    {
        code = code % N;
    }

    if (code < 0) // clamp
    {
        code = 0;
    }

    s++;
    return code;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node* n = insert_node(word);
        if (n == NULL)
        {
            return false;
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return s;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        free_list_recursively(n);
    }
    return true;
}

node *insert_node(const char* val)
{
    int hash_code = hash(val);

    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    strcpy(n->word, val);
    n->next = NULL;

    if (table[hash_code] == NULL) // if no node in hashtable
    {
        table[hash_code] = n;
    }
    else
    {
        n->next = table[hash_code]; // point at head node

        table[hash_code] = n; // set this to be head node
    }

    return n;
}

void free_list_recursively(node *n)
{
    if (n == NULL)
    {
        return;
    }

    free_list_recursively(n->next);

    free(n);
}

node *append_node(const char* val)
{
    int hash_code = hash(val);

    node *n = get_last_node_in_list(table[hash_code]); // get last linked node in hashtable

    if (n == NULL) // hashtable root node is NULL
    {
        n = malloc(sizeof(node));

        n->next = NULL;
        strcpy(n->word, val);
    }
    else // if node exists
    {
        n->next = malloc(sizeof(node)); // allocate the next node and asign previous node to point to it
        if (n == NULL) // allocation failed
        {
            return NULL;
        }

        n = n->next; // set n to next [current] node

        n->next = NULL;
        strcpy(n->word, val); // set the node's value
    }

    return n;
}

node *get_last_node_in_list(node *cur_node)
{
    if (cur_node == NULL)
    {
        return cur_node;
    }
    else if (cur_node->next == NULL)
    {
        return cur_node;
    }

    return get_last_node_in_list(cur_node->next);
}