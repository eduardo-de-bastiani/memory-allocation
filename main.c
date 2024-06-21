#include <stdio.h>
#include "mymemory.h"

int main(){

    mymemory_t *m = mymemory_init(sizeof(int) * 10000);

    //mymemory_stats(m);
}