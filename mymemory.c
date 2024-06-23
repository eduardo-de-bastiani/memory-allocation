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



//implementacao com First Fit (procura um espaço disponivel antes de alocar outro espaço na memoria)
void *mymemory_alloc(mymemory_t *m, size_t size){
    allocation_t *current = m->head;
    allocation_t *prev = NULL;

    while (current != NULL) {
        //verificacao para First Fit
        if (current->start == NULL && current->size >= size) {
            //(void*) Converte para ponteiro generico // Aloca o bloco depois da estrutura de controle
            current->start = (void *)(current + 1); 

            //m->total_free -= size;
            
            
            //tenho que colocar algum código aqui que faça: espaço total do bloco(200) - espaco ocupado do bloco(50) e some com o total_free(x + 150). Tem que pegar o resultado da subtracao(150) e subtrair do total_alloc(y - 150) PODE NÃO SER EXATAMENTE AQUI
            // não sei se o problema está na alocação de fato ou no stats

            return current->start;
        }

        prev = current;
        current = current->next;    //vai para o proximo
    }

    //O seguinte metodo foi feito usando IA
    //se um espaço livre nao for encontrado, alocamos mais memoria no final do pool
    //verificacao se o pool eh maior que a alocacao + o que ja foi alocado
    if(m-> total_size >= size + sizeof(allocation_t)){
        allocation_t *new_alloc = (allocation_t *)((char *)m->pool + (m->total_size - size - sizeof(allocation_t)));
        new_alloc->start = (void *)((char *)new_alloc + sizeof(allocation_t));
        new_alloc->size = size;
        new_alloc->next = m->head;
        m->head = new_alloc;
        m->total_size -= size + sizeof(allocation_t);
        return new_alloc->start;
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

    while (current != NULL) {
        if (current->start != NULL) {
            total_alloc += current->size;
            
            num_allocs++;
        } 
        else{

            total_free += current->size;

            
            //tenho que colocar algum código aqui que faça: espaço total do bloco(200) - espaco ocupado do bloco(50) e some com o total_free(x + 150). Tem que pegar o resultado da subtracao(150) e subtrair do total_alloc(y - 150)

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

// Libera todas as alocações de memória, incluindo o pool
void mymemory_cleanup(mymemory_t *m) {
    // Libere todas as alocações individuais, se necessário, e então libere o pool de memória
    free(m->pool);
    free(m);
}


