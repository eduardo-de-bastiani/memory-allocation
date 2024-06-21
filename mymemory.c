#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymemory.h"

mymemory_t *mymemory_init(size_t size){
    mymemory_t *m = (mymemory_t *)malloc(sizeof(mymemory_t));
    if (m == NULL){
        return NULL;
    }
    // '->' acesso de atributo de um objeto
    // neste caso, acessamos o pool e inicializamos ele
    m-> pool = malloc(size);
    if(m -> pool == NULL){
        free(m);
        return NULL;
    }

    m -> total_size = size;
    m -> head = NULL;

    return m;
}




void *mymemory_alloc(mymemory_t *m, size_t size){
    allocation_t *current = m->head;
    allocation_t *prev = NULL;

    while (current != NULL) {
        if (current->size >= size) {
            void *start = current->start;
            if (prev == NULL) {
                m->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return start;
        }
        prev = current;
        current = current->next;
    }
}


// Libera uma alocação específica
void mymemory_free(mymemory_t *m, void *ptr) {
    // Implemente a lógica para encontrar e liberar a alocação específica dentro do seu pool
}

// Exibe as alocações atuais do pool
void mymemory_display(mymemory_t *m) {
    allocation_t *current = m->head;
    while (current != NULL) {
        printf("Alocação em %p, tamanho %zu\n", current, *(current->size));
        current = current->next;
    }
}

// Exibe estatísticas gerais do pool
void mymemory_stats(mymemory_t *m) {
    // Implemente a lógica para calcular e exibir estatísticas, como espaço total, espaço alocado, espaço livre, etc.
}

// Libera todas as alocações de memória, incluindo o pool
void mymemory_cleanup(mymemory_t *m) {
    // Libere todas as alocações individuais, se necessário, e então libere o pool de memória
    free(m->pool);
    free(m);
}


