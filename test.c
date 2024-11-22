#include <stdio.h>
#include <assert.h>
#include "cvector.h"

int main(int argc, char* argv[]){
    cvector* g = cvector_create(10,1);
    int num = 12;
    cvector_push_back(g, &num);
    assert(cvector_size(g) == 1);
    assert(*(int*)cvector_back(g) == 12);
    for ( int i = 0; i < 9; i++ ){
        cvector_push_back(g, &num);
    }
    assert(cvector_capacity(g) == 20);
    cvector_free(g);
    printf("test done\n");
    return 0;
}