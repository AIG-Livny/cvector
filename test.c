#include <stdio.h>
#include "cvector.h"

int main(int argc, char* argv[]){
    cvector* g = cvector_create(10,1);
    int ii = 10;
    cvector_push_back(g, &ii);
    printf("Hello size=%d \n", cvector_size(g));
    return 0;
}