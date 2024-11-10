#ifndef VEC_H
# define VEC_H

#include <stdbool.h>

typedef void (*cvector_errorcb)(int code);
void cvector_set_error_callback(cvector_errorcb cb);

#define CVECTOR_ERR_OK 0
#define CVECTOR_ERR_NOT_ENOUGH_MEMORY 1
#define CVECTOR_ERR_REALLOC_FAILS 2
#define CVECTOR_ERR_OUT_OF_RANGE 3

inline struct cvector* cvector_create(unsigned int init_len, unsigned int elem_size);
inline void cvector_free(struct cvector* cvect);
inline void cvector_reserve(struct cvector* cvect, unsigned int target_size);
inline struct cvector* cvector_copy(struct cvector* cvect);
inline void cvector_shrink(struct cvector* cvect);
inline void* cvector_get(struct cvector* cvect, unsigned int index);
inline void* cvector_data(struct cvector* cvect);
inline unsigned int cvector_capacity(struct cvector* cvect);
inline unsigned int cvector_size(struct cvector* cvect);
inline void* cvector_back(struct cvector* cvect);
inline void* cvector_push_back(struct cvector* cvect, void* elem);
inline void* cvector_pop(struct cvector* cvect);
inline void cvector_clear(struct cvector* cvect);
inline void* cvector_insert(struct cvector* cvect, void* elem, unsigned int index);
inline void cvector_remove(struct cvector* cvect, unsigned int index);
inline void cvector_remove_fast(struct cvector* cvect, unsigned int index);
inline struct cvector* cvector_extend(struct cvector* dst, struct cvector* src);
inline void* cvector_find(struct cvector* cvect, void* pvalue);

#define cvector_iterator(_t) _t*

#define cvector_foreach(it, vec) \
    for(it = (typeof(it))cvector_data(vec); it < (typeof(it))cvector_end(vec); it++)

#endif