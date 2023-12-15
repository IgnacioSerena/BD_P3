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
    index->capacity = capacity;

    return index;
}

// Función para liberar la memoria del índice
void freeIndex(Index *index)
{
    free(index->entries);
    free(index);
}

// Función para buscar la posición de un ISBN en el índice (búsqueda binaria)
int binarySearch(const Index *index, int key)
{
    int low = 0;
    int high = index->size - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (index->entries[mid].key == key)
        {
            return mid; // Se encontró el id
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

    return -1; // No se encontró el id
}

// Función para insertar una entrada en el índice
int insertEntry(Index *index, int key, long int offset, size_t size)
{
    int i, pos = 0;

    // Asegurarse de tener espacio suficiente
    if (index->size == index->capacity)
    {
        if (expandIndex(index) == ERR)
            return ERR; // Error al expandir el índice
    }

    while (pos < index->size && index->entries[pos].key < key)
        pos++;

    // Desplaza las entradas para abrir espacio para la nueva entrada
    i = index->size - 1;
    while (i >= pos)
    {
        index->entries[i + 1] = index->entries[i];
        i--;
    }

    index->entries[pos].size = size;
    index->entries[pos].key = key;
    index->entries[pos].offset = offset;

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
void printIndex(Index *index, FILE *f, FILE *f1)
{
    for (size_t i = 0; i < index->size; i++)
    {
        fprintf(f, "Entry #%zu\n", i);
        fprintf(f, "    key: #%d\n", index->entries[i].key);
        fprintf(f, "    offset: #%ld\n", index->entries[i].offset);
        fprintf(f, "    size: #%zu\n", index->entries[i].size);

        fwrite(&index->entries[i].key, sizeof(int), 1, f1);
        fwrite(&index->entries[i].offset, sizeof(size_t), 1, f1);
        fwrite(&index->entries[i].size, sizeof(size_t), 1, f1);
    }
}


Index *reload(char *filename)
{
    FILE *file = NULL;
    IndexEntry *index = NULL;
    Index *index_array = NULL;

    if(!filename)
        return ERR;

    index_array = initIndex(100);
    if (!index)
        return ERR;

    index = (IndexEntry*)malloc(sizeof(IndexEntry));
    if(!index){
        printf("ERRRRRROOOOOOR");
        return NULL;
    }
    file = fopen(filename, "r+b");
    if (!file)
        return ERR;

    while(fread(&index->key, sizeof(int), 1, file) == sizeof(int)){
        fread(&index->offset, sizeof(long int), 1, file);
        fread(&index->size, sizeof(size_t), 1, file);
        insertEntry(index_array, index->key, index->offset, index->size);
    }

    fclose(file);

  return index_array;
}
