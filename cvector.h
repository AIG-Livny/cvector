#ifndef CVECOR_H
#define CVECOR_H

typedef void (*cvector_errorcb)(int code);
void cvector_set_error_callback(cvector_errorcb cb);

typedef struct cvector cvector;

#define CVECTOR_ERR_OK 0
#define CVECTOR_ERR_NOT_ENOUGH_MEMORY 1
#define CVECTOR_ERR_REALLOC_FAILS 2
#define CVECTOR_ERR_OUT_OF_RANGE 3

inline cvector* cvector_create(unsigned int init_len, unsigned int elem_size);
inline void cvector_free(cvector* cvect);
inline void cvector_reserve(cvector* cvect, unsigned int target_size);
inline cvector* cvector_copy(cvector* cvect);
inline void cvector_shrink(cvector* cvect);
inline void* cvector_get(cvector* cvect, unsigned int index);
inline void* cvector_data(cvector* cvect);
inline unsigned int cvector_capacity(cvector* cvect);
inline unsigned int cvector_size(cvector* cvect);
inline void* cvector_back(cvector* cvect);
inline void* cvector_push_back(cvector* cvect, void* elem);
inline void* cvector_pop(cvector* cvect);
inline void cvector_clear(cvector* cvect);
inline void* cvector_insert(cvector* cvect, void* elem, unsigned int index);
inline void cvector_remove(cvector* cvect, unsigned int index);
inline void cvector_remove_fast(cvector* cvect, unsigned int index);
inline cvector* cvector_extend(cvector* dst, cvector* src);
inline void* cvector_find(cvector* cvect, void* pvalue);

#define cvector_iterator(_t) _t*

#define cvector_foreach(it, vec) \
    for(it = (typeof(it))cvector_data(vec); it < (typeof(it))cvector_end(vec); it++)

#endif