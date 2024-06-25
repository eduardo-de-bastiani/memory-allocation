#include <stdio.h>

//definicao da lista encadeada de alocacoes 
typedef struct allocation{
    void *start;
    size_t size;
    struct allocation *next; // referencia para a proxima alocacao
} allocation_t;

typedef struct{
    void *pool;         // bloco de memoria total (ponteiro aponta para seu inicio)
    size_t total_size;  // tamanho total do bloco de memoria
    allocation_t *head; // posicao atual da memoria
} mymemory_t;

// alocacao do bloco de memoria total, vai retornar o ponteiro do pool
mymemory_t *mymemory_init(size_t size);

//alocao de memoria
void *mymemory_alloc(mymemory_t *m, size_t size);

//liberacao de memoria de alocacao especifica
void mymemory_free(mymemory_t *m, void *ptr);

//exibicao das alocacoes atuais do pool (inicio e tamanho de cada alocacao)
void mymemory_display(mymemory_t *m);

//estatisticas gerais do pool
void mymemory_stats(mymemory_t *m);

//libera todas as alocacoes de memoria, incluindo o pool (fica inutilizavel até inicializar um novo pool)
void mymemory_cleanup(mymemory_t *m);