#ifndef INDEX_H
#define INDEX_H

#include "types.h"

// Función para inicializar un nuevo índice en memoria
Index *initIndex(size_t initialCapacity);

// Función para liberar la memoria utilizada por el índice
void freeIndex(Index *index);

// Función para insertar una entrada en el índice
int insertEntry(Index *index, char *key, long int offset, size_t size);

// Función para realizar una búsqueda binaria en el índice
int binarySearch(const Index *index, char *key);

// Función para expandir el índice
int expandIndex(Index *index);

// Función para imprimir el índice
void printIndex(Index *index);

#endif // INDEX_H