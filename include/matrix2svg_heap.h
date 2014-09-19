#ifndef _M2S_HEAP_H
#define _M2S_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix2svg_types.h"

#ifdef __cplusplus
extern "C" {
#endif

    m2s_heap_t * new_heap(uint32_t element_count);
    void delete_heap(m2s_heap_t **heap);
    void insert_heap_value(m2s_heap_t *heap, m2s_data_t value);
    void percolate_heap_value_upwards(m2s_heap_t *heap, uint32_t index);
    void swap_heap_value(m2s_heap_t *heap, uint32_t first_index, uint32_t second_index);
    void print_heap(m2s_heap_t *heap);

#ifdef __cplusplus
};
#endif

#endif /* _M2S_HEAP_H */
