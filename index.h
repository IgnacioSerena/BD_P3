#ifndef INDEX_H
#define INDEX_H

#include "types.h"

// Función para inicializar un nuevo índice en memoria
Index *initializeIndex(size_t initialCapacity);

// Función para liberar la memoria utilizada por el índice
void freeIndex(Index *index);

// Función para insertar una entrada en el índice
void insertEntry(Index *index, int key, long int offset, size_t size);

// Función para realizar una búsqueda binaria en el índice
int binarySearch(const Index *index, int key);

// Función para expandir el índice
void expandIndex(Index *index);

#endif // INDEX_H