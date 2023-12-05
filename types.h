#include <stdio.h>
#include <string.h>

#define MAX_STR 100

typedef struct
{
    int key;
    int id;
    char *title; 
    char *editorial;     
    long int offset;
    size_t size;     
} Book;