#include "index.h"

// Función para inicializar el índice
Index *initIndex(size_t capacity)
{
    Index *index = (Index *)malloc(sizeof(Index));
    if (index == NULL)
    {
        // Manejar el error de asignación de memoria
        exit(EXIT_FAILURE);
    }

    index->entries = (IndexEntry *)malloc(capacity * sizeof(IndexEntry));
    if (index->entries == NULL)
    {
        // Manejar el error de asignación de memoria
        free(index);
        exit(EXIT_FAILURE);
    }

    index->size = 0;
    index->entries[0].size = 0;
    index->entries[0].offset = 0;
    index->capacity = capacity;

    return index;
}

// Función para liberar la memoria del índice
void freeIndex(Index *index)
{
    for(int i = 0; i < index->size; i++)
        free(index->entries[i].key);


    free(index->entries);
    free(index);
}

// Función para buscar la posición de un ISBN en el índice (búsqueda binaria)
int binarySearch(const Index *index, char *key)
{
    int low = 0;
    int high = index->size - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (strcmp(index->entries[mid].key, key) == 0)
        {
            return mid; // Se encontró el ISBN
        }
        else if (index->entries[mid].key < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1; // No se encontró el ISBN
}

// Función para insertar una entrada en el índice
int insertEntry(Index *index, char *key, long int offset, size_t size)
{
    // Inserta la nueva entrada
    index->entries[index->size].size = size;
    index->entries[index->size].key = key;
    index->entries[index->size].offset = offset;

    // Asegurarse de tener espacio suficiente
    if (index->entries[index->size].size == index->capacity)
    {
        if (expandIndex(index) == ERR)
            return ERR; // Error al expandir el índice
    }
    
    // Incrementa el tamaño del índice
    index->size++;

    return OK;
}

int expandIndex(Index *index)
{
    // Duplica la capacidad del índice
    index->capacity *= 2;

    // Realiza la realocación del array de entradas
    index->entries = realloc(index->entries, index->capacity * sizeof(IndexEntry));

    // Verifica si la realocación fue exitosa
    if (index->entries == NULL)
    {
        // Manejar el error según sea necesario
        fprintf(stderr, "Error: could not expand the index.\n");
        return ERR;
    }

    return OK;
}

// Función para imprimir el índice
void printIndex(Index *index)
{
    for (size_t i = 0; i < index->size; i++)
    {
        printf("Entry #%zu\n", i);
        printf("  key: #%s\n", index->entries[i].key);
        printf("  offset: #%ld\n", index->entries[i].offset);
        printf("  size: #%zu\n", index->entries[i].size);
    }
}
