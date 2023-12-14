#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TYPES_H
#define TYPES_H

#define MAX_STR 100

typedef enum
{
    ERR = 0,
    OK
} STATUS;

// Estructura para representar una entrada en el índice
typedef struct {
    int key;         // ISBN del libro
    long int offset;  // Desplazamiento en el archivo de datos
    size_t size;      // Tamaño del registro del libro
} IndexEntry;

// Estructura para representar el índice en memoria
typedef struct {
    IndexEntry *entries;  // Array de entradas en el índice
    size_t size;          // Número actual de entradas en el índice
    size_t capacity;      // Capacidad actual del índice
} Index;

#endif /* TYPES_H */