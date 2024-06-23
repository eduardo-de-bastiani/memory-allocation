#include <stdio.h>
#include "mymemory.h"

int main(){

    // 24 bytes de cada alocacao estão sendo usados para estruturas de controle 

    mymemory_t *m = mymemory_init(sizeof(int) * 1000);
    mymemory_stats(m);

    printf("\n---[First Allocation]---\n");
    int *ptr1 = mymemory_alloc(m,500);
    mymemory_stats(m);

    printf("\n---[Second Allocation]---\n");
    int *ptr2 = mymemory_alloc(m,200);
    mymemory_stats(m);

    printf("\n---[Third Allocation]---\n");
    int *ptr3 = mymemory_alloc(m,100);
    mymemory_stats(m);

    printf("\n---[Allocation Display]---\n");
    mymemory_display(m);

    printf("\n---[Removing Second Allocation]---\n");
    mymemory_free(m, ptr2);
    mymemory_stats(m);
    printf("\n");
    mymemory_display(m);    

    printf("\n---[Allocating Memory trough First Fit]---\n");
    int *ptr4 = mymemory_alloc(m, 50);
    mymemory_stats(m);
    printf("\n");
    mymemory_display(m);

    //o total_free deve mostrar 3254 bytes
    
}