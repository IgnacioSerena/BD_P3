#ifndef INDEX_H
#define INDEX_H

#include "types.h"

// Función para inicializar un nuevo índice en memoria
Index *initIndex(size_t capacity);

// Función para liberar la memoria utilizada por el índice
void freeIndex(Index *index);

// Función para insertar una entrada en el índice
int insertEntry(Index *index, int key, long int offset, size_t size);

// Función para realizar una búsqueda binaria en el índice
int binarySearch(const Index *index, int key);

// Función para expandir el índice
int expandIndex(Index *index);

// Función para imprimir el índice
void printIndex(Index *index, FILE *f);

// Función para inicializar un nuevo índice en memoria
IndexDeleted *initIndexDeleted(size_t capacity);

// Función para liberar la memoria utilizada por el índice
void freeIndexDeleted(IndexDeleted *index);

// Función para insertar una entrada en el índice
int insertEntryDeleted(IndexDeleted *index, int key, long int offset, size_t size);

// Función para expandir el índice
int expandIndexDeleted(IndexDeleted *index);

// Función para imprimir el índice
void printIndexDeleted(IndexDeleted *index, FILE *f);

#endif // INDEX_H