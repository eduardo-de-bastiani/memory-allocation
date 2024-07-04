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

    // cria uma alocação inicial vazia apenas para o first fit funcionar
    allocation_t *initial_alloc = malloc(sizeof(allocation_t));
    if (initial_alloc == NULL){
        free(m->pool);
        free(m);
        return NULL;
    }
    initial_alloc->size = size;
    m->head = initial_alloc;

    return m;
}

//implementacao com First Fit (procura um espaço disponivel antes de alocar outro espaço na memoria)
void *mymemory_alloc(mymemory_t *m, size_t size){
    allocation_t *current = m->head;
    allocation_t *prev = NULL;

    while (current != NULL) {
        //verificacao para First Fit
        if (current->start == NULL && current->size >= size) {
            //(void*) Converte para ponteiro generico // Aloca o bloco depois da estrutura de controle
            current->start = (void *)(current + 1); 
            
            //verificacao se a nova alocacao nao cobre todo o espaco
            if(current->size > size + sizeof(allocation_t)){
                allocation_t *new_alloc = (allocation_t *)((char *)current + sizeof(allocation_t) + size);
                new_alloc->start = NULL;
                new_alloc->size = current->size - size;
                new_alloc->next = current->next;
                current->size = size;
                current->next = new_alloc;
            }
            
            return current->start;
        }

        prev = current;
        current = current->next;    //vai para o proximo
    }
    
    return NULL;
}

// Libera uma alocacao de memoria especifica
void mymemory_free(mymemory_t *m, void *ptr) {
    allocation_t *current = m-> head;

    while (current != NULL){
        //se o start for o ponteiro da memoria que quermos liberar
        if(current->start == ptr){
            current->start = NULL;
            return;
        }
        current = current->next;    //vai para o proximo
    }
}

//alocacoes atuais do pool
void mymemory_display(mymemory_t *m) {
    printf("\n## Memory Display ##\n");

    if(m->pool == NULL){
        printf("Memory pool is empty.\n");
    }

    allocation_t *current = m->head;
    while (current != NULL) {
        if(current->start != NULL){
        //'zu' especificador para size_t
        printf("Allocation: %p\n size: %zu\n", current, current->size);  
        }
        current = current->next;
    }
}

//status do pool
void mymemory_stats(mymemory_t *m) {
    //inicializamos total_free e largest_free como tamanho do pool para ser decrementado/substituido
    size_t total_free = m->total_size; 
    size_t largest_free = m->total_size;
    size_t total_alloc = 0;
    size_t num_allocs = 0;
    size_t num_frag = 0;
    allocation_t *current = m-> head;

    printf("\n## Memory Status ##\n");

    if(m->pool == NULL){
        printf("Memory pool is empty.\n");
        return;
    }

    while (current != NULL) {
        if (current->start != NULL) {
            total_alloc += current->size;
            num_allocs++;
        } 
        else{
            total_free += current->size;
            num_frag++;

            //atualiza o maior espaco de fragmentacao
            if(current->size > largest_free){
                largest_free = current->size;
            }
        }
        current = current->next;
    }

    printf("Number of allocations: %zu\n", num_allocs);
    printf("Total of allocated memory: %zu bytes\n", total_alloc);
    printf("Amout of free memory: %zu bytes\n", total_free);
    printf("Largest free memory block: %zu bytes\n", largest_free);
    printf("Number of fragmentations: %zu\n", num_frag);   
}


void mymemory_cleanup(mymemory_t *m) {
    // Libera a memoria do pool e a memoria do gerenciamento das estruturas
    free(m->pool);
    free(m);

    m->pool = NULL;
    m->head = NULL;
    m->total_size = 0;
}