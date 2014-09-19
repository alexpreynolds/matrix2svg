#include "matrix2svg_heap.h"
#include "matrix2svg_types.h"

m2s_heap_t * new_heap(uint32_t element_count)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> new_heap()\n");
#endif

    m2s_heap_t *heap = NULL;
    uint32_t element_idx = 0;

    heap = malloc(sizeof(m2s_heap_t));
    if (!heap) {
	fprintf(stderr, "Error: Could not instantiate new heap structure\n");
	exit(EXIT_FAILURE);
    }
    heap->capacity = element_count;
    heap->size = 0;

    heap->data_values = NULL;
    heap->data_values = malloc(sizeof(m2s_data_t) * (element_count + 1));
    if (!heap->data_values) {
	fprintf(stderr, "Error: Could not instantiate heap structure data storage\n");
	exit(EXIT_FAILURE);
    }
    for (element_idx = 0; element_idx < element_count; ++element_idx) {
	heap->data_values[element_idx] = M2S_DEFAULT_HEAP_VALUE;
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> new_heap()\n");
#endif

    return heap;
}

void delete_heap(m2s_heap_t **heap)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> delete_heap()\n");
#endif

    if (!(*heap))
	return;

    (*heap)->capacity = 0;
    (*heap)->size = 0;

    free((*heap)->data_values);
    (*heap)->data_values = NULL;

    free(*heap);
    *heap = NULL;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> delete_heap()\n");
#endif
}

void insert_heap_value(m2s_heap_t *heap, m2s_data_t value)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> insert_heap_value()\n");
#endif

    m2s_data_t *temporary_data_values = NULL;

    if (!heap)
	return;

    /* if heap is full, double its capacity */
    if (heap->size == heap->capacity) {
	heap->capacity *= 2;
	temporary_data_values = malloc(sizeof(m2s_data_t) * (heap->capacity + 1));
	if (!temporary_data_values) {
	    fprintf(stderr, "Error: Could not allocate space for temporary heap value array\n");
	    exit(EXIT_FAILURE);
	}
	/* copy over data; note that we start at index [1] */
	memcpy(temporary_data_values + 1, heap->data_values + 1, sizeof(m2s_data_t) * (heap->capacity + 1));
	free(heap->data_values);
	heap->data_values = temporary_data_values;
    }
    heap->size++;
    heap->data_values[heap->size] = value;
    percolate_heap_value_upwards(heap, heap->size);

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> insert_heap_value()\n");
#endif
}

void percolate_heap_value_upwards(m2s_heap_t *heap, uint32_t index)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> percolate_heap_value_upwards()\n");
#endif

    if (index > 1) {
	if (heap->data_values[index/2] > heap->data_values[index]) {
	    swap_heap_value(heap, index, index/2);
	    percolate_heap_value_upwards(heap, index/2);
	}
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> percolate_heap_value_upwards()\n");
#endif
}

void swap_heap_value(m2s_heap_t *heap, uint32_t first_index, uint32_t second_index)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> swap_heap_value()\n");
#endif
    
    m2s_data_t temporary_value = heap->data_values[first_index];
    heap->data_values[first_index] = heap->data_values[second_index];
    heap->data_values[second_index] = temporary_value;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> swap_heap_value()\n");
#endif
}

void print_heap(m2s_heap_t *heap) 
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_heap()\n");
#endif

    uint32_t idx;
    
    for (idx = 1; idx <= heap->size; ++idx) {
        fprintf(stderr, "%f ", heap->size[idx]);
    }
    fprintf(stderr, "\n");

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_heap()\n");
#endif
}
