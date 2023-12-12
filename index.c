#include "index.h"

// Función para inicializar el índice
Index* initIndex(size_t capacity) {
    Index *index = (Index*)malloc(sizeof(Index));
    if (index == NULL) {
        // Manejar el error de asignación de memoria
        exit(EXIT_FAILURE);
    }

    index->entries = (indexbook*)malloc(capacity * sizeof(indexbook));
    if (index->entries == NULL) {
        // Manejar el error de asignación de memoria
        free(index);
        exit(EXIT_FAILURE);
    }

    index->size = 0;
    index->capacity = capacity;

    return index;
}

// Función para liberar la memoria del índice
void freeIndex(Index *index) {
    free(index->entries);
    free(index);
}

// Función para buscar la posición de un ISBN en el índice (búsqueda binaria)
int binarySearch(Index *index, int key) {
    int low = 0;
    int high = index->size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (index->entries[mid].key == key) {
            return mid; // Se encontró el ISBN
        } else if (index->entries[mid].key < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // No se encontró el ISBN
}

// Función para insertar una entrada en el índice
void insertEntry(Index *index, int key, long int offset, size_t size) {
    // Asegurarse de tener espacio suficiente
    if (index->size == index->capacity) {
        expandIndex(index);
    }

    // Encuentra la posición de inserción
    int position = binarySearch(index, key);

    // Desplaza las entradas para abrir espacio para la nueva entrada
    for (int i = index->size - 1; i >= position; i--) {
        index->entries[i + 1] = index->entries[i];
    }

    // Inserta la nueva entrada
    index->entries[position].key = key;
    index->entries[position].offset = offset;
    index->entries[position].size = size;

    // Incrementa el tamaño del índice
    index->size++;
}


void expandIndex(Index *index) {
    // Duplica la capacidad del índice
    index->capacity *= 2;

    // Realiza la realocación del array de entradas
    index->entries = realloc(index->entries, index->capacity * sizeof(IndexEntry));

    // Verifica si la realocación fue exitosa
    if (index->entries == NULL) {
        // Manejar el error según sea necesario
        fprintf(stderr, "Error: No se pudo expandir el índice.\n");
        exit(EXIT_FAILURE);
    }
}

// Función para imprimir el índice
void printIndex(Index *index) {
    for (size_t i = 0; i < index->size; i++) {
        printf("Entry #%zu\n", i);
        printf("  key: #%d\n", index->entries[i].key);
        printf("  offset: #%ld\n", index->entries[i].offset);
        printf("  size: #%zu\n", index->entries[i].size);
    }
}
