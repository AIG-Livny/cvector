#include "cvector.h"

#include <assert.h>
#include <iso646.h>
#include <string.h>
#include <stdlib.h>

int error_code = 0;
static cvector_errorcb error_callback = NULL;

void throw(int code){
    error_code = code;
    if ( error_callback ) {
        error_callback(code);
    }
}

void cvector_set_error_callback(cvector_errorcb cb){
    error_callback = cb;
}

struct cvector {
    unsigned int elem_size;
    unsigned int size;
    unsigned int alloc_size;
    void* memory;
};

struct cvector* cvector_create(unsigned int init_size, unsigned int elem_size) {
    assert(elem_size);

    struct cvector* newvect = malloc(sizeof(struct cvector));

    if ( not newvect ) {
        throw(CVECTOR_ERR_NOT_ENOUGH_MEMORY);
        return NULL;
    }

    newvect->alloc_size = init_size * elem_size;
    newvect->size = 0;
    newvect->elem_size = elem_size;

    if ( init_size == 0 ){
        newvect->memory = NULL;
    } else {
        cvector_reserve(newvect, init_size);
    }
    return newvect;
}

void cvector_free(struct cvector* cvect) {
    assert(cvect);

    free(cvect->memory);
    free(cvect);
}

void* cvector_data(struct cvector* cvect) {
    assert(cvect);

    return cvect->memory;
}

unsigned int cvector_capacity(struct cvector* cvect) {
    assert(cvect);

    return cvect->alloc_size / cvect->elem_size;
}

unsigned int cvector_size(struct cvector* cvect) {
    assert(cvect);

    return cvect->size;
}

void* cvector_get(struct cvector* cvect, unsigned int index) {
    assert(cvect);

    if ( index >= cvector_size(cvect) ) {
        throw(CVECTOR_ERR_OUT_OF_RANGE);
        return NULL;
    }

    return &cvect->memory[ cvect->elem_size *  index ];
}

void* cvector_back(struct cvector* cvect) {
    return cvector_get(cvect, cvect->size - 1);
}

void* cvector_end(struct cvector* cvect) {
    assert(cvect);

    return &cvect->memory[ cvect->elem_size * cvect->size ];
}

void cvector_resize(struct cvector* cvect, unsigned int new_size) {
    assert(cvect);

    unsigned int new_alloc_size = new_size * cvect->elem_size;
    if ( new_alloc_size == cvect->alloc_size ) {
        return;
    }

    cvect->alloc_size = new_alloc_size;
    cvect->memory = realloc(cvect->memory, cvect->alloc_size);

    if ( not cvect->memory ) {
        throw(CVECTOR_ERR_REALLOC_FAILS);
    }

    assert(cvect->memory);
}

void cvector_grow(struct cvector* cvect) {
    if ( cvector_capacity(cvect) <= cvector_size(cvect) + 1 ) {
        if ( cvector_capacity(cvect) == 0 ) {
            cvector_resize(cvect, 1);
        } else {
            cvector_resize(cvect, cvector_capacity(cvect) * 2);
        }
    }
}

void cvector_reserve(struct cvector* cvect, unsigned int target_size) {
    if ( cvect->alloc_size >= target_size * cvect->elem_size ) {
        return;
    }

    cvector_resize(cvect, target_size);
}

void cvector_shrink(struct cvector* cvect) {
    cvector_resize(cvect,cvector_size(cvect));
}

struct cvector* cvector_copy(struct cvector* cvect) {
    assert(cvect);

    struct cvector* newvect = cvector_create(cvector_size(cvect), cvect->elem_size);
    if ( cvect->memory ) {
        memcpy(newvect->memory, cvect->memory, newvect->alloc_size);
    }

    return newvect;
}

void* cvector_push_back(struct cvector* cvect, void* elem) {
    assert(elem);

    cvector_grow(cvect);
    memcpy(cvector_end(cvect), elem, cvect->elem_size);
    cvect->size += 1;

    return elem;
}

void* cvector_pop(struct cvector* cvect) {
    void* result = cvector_back(cvect);
    if ( result ) {
        cvect->size -= 1;
    }
    return result;
}

void cvector_clear(struct cvector* cvect) {
    assert(cvect);
    cvect->size = 0;
}

void* cvector_insert(struct cvector* cvect, void* elem, unsigned int index) {
    cvector_grow(cvect);

    memmove(
        cvector_get(cvect, index + 1),
        cvector_get(cvect, index),
        (cvect->size - index) * cvect->elem_size);
    memcpy(
        cvector_get(cvect, index),
        elem, cvect->elem_size);
    cvect->size += 1;
    return elem;
}

void cvector_remove(struct cvector* cvect, unsigned int index) {
    assert(cvect);

    if ( cvector_size(cvect) == 1 ) {
        cvect->size = 0;
        return;
    }

    memmove(
        cvector_get(cvect, index),
        &cvect->memory[cvect->elem_size * (index + 1)],
        (cvect->size - index) * cvect->elem_size);
    cvect->size -= 1;
}

void cvector_remove_fast(struct cvector* cvect, unsigned int index) {
    assert(cvect);

    if ( cvector_size(cvect) == 1 ) {
        cvect->size = 0;
        return;
    }

    memcpy(cvector_get(cvect, index), cvector_back(cvect), cvect->elem_size);
}

struct cvector* cvector_extend(struct cvector* dst, struct cvector* src) {
    assert(src);

    if ( cvector_size(src) == 0 ) {
        return dst;
    }

    cvector_reserve(dst, cvector_size(dst) + cvector_size(src));
    memcpy(
        &dst->memory[dst->elem_size*  dst->size],
        src->memory,
        src->size*  src->elem_size);
    dst->size += src->size;
    return dst;
}

struct mys{
    int i;
};

#define cvector_iterator(_t) _t*

#define cvector_foreach(it, vec) \
    for(it = (typeof(it))cvector_data(vec); it < (typeof(it))cvector_end(vec); it++)

void* cvector_find(struct cvector* cvect, void* pvalue) {
    assert(cvect);

    cvector_iterator(struct mys) it;
    cvector_foreach(it, cvect){
        if ( memcmp(it, pvalue, cvector_size(cvect)) == 0 ) {
            return it;
        }
    }

    return NULL;
}
