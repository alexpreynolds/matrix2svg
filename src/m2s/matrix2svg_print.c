#include "matrix2svg_print.h"
#include "matrix2svg.h"

void print_ops()
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_ops()\n");
#endif

    int idx;
    int m2s_operations_count = sizeof(m2s_operations) / sizeof(*m2s_operations);

    for (idx = 0; idx < m2s_operations_count; ++idx) {
	fprintf(stderr, "[%d] %s\n", m2s_operations[idx], M2S_OPERATION_STRING[m2s_operations[idx]]);
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_ops()\n");
#endif
}

void print_rows(FILE *stream, const m2s_matrix_t *mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_rows()\n");
#endif

    uint32_t row_idx;
    
    for (row_idx = 0U; row_idx < mtx_ptr->row_count; row_idx++) {
        fprintf(stream, "\trow [%05u] [%s]\n", row_idx, mtx_ptr->row_labels[row_idx]);
        print_row_cells(stream, mtx_ptr, row_idx);
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_rows()\n");
#endif
}

void print_row_stats(FILE *stream, const m2s_matrix_t *mtx_ptr) 
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_row_stats()\n");
#endif

    uint32_t row_idx;

    for (row_idx = 0U; row_idx < mtx_ptr->row_count; row_idx++) {
        fprintf(stream, "\trow [%05u] \t mean [%f] \t var [%f] \t sd [%f] \t min [%f] \t max [%f]\n", 
                row_idx, 
                mtx_ptr->row_stats->means[row_idx], 
                mtx_ptr->row_stats->svars[row_idx] / (mtx_ptr->col_count - 1), 
                mtx_ptr->row_stats->stdevs[row_idx],
                mtx_ptr->row_stats->mins[row_idx], 
                mtx_ptr->row_stats->maxs[row_idx]);
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_row_stats()\n");
#endif
}

void print_row_labels(FILE *stream, const m2s_matrix_t *mtx_ptr) 
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_row_labels()\n");
#endif

    uint32_t row_idx;

    for (row_idx = 0U; row_idx < mtx_ptr->row_count; row_idx++) {
        fprintf(stream, "\trow [%05u] [%s]\n", row_idx, mtx_ptr->row_labels[row_idx]);
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_row_labels()\n");
#endif
}

void print_row_cells(FILE *stream, const m2s_matrix_t *mtx_ptr, const uint32_t row_idx) 
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_row_cells()\n");
#endif

    uint32_t col_count = mtx_ptr->col_count;
    uint64_t cell_idx, start_idx, end_idx;

    start_idx = (uint64_t)row_idx * (uint64_t)col_count;
    end_idx = (row_idx + 1) * (uint64_t)col_count;

    fprintf(stream, "\tdata -> ");
    for (cell_idx = start_idx; cell_idx < end_idx; cell_idx++) {
        fprintf(stream, "%f + ", mtx_ptr->data_values[cell_idx]);
    }
    fprintf(stream, "\n");

    fprintf(stream, "\tmissing -> ");
    for (cell_idx = start_idx; cell_idx < end_idx; cell_idx++) {
        fprintf(stream, "%c + ", (mtx_ptr->missing_values[cell_idx] == kFalse ? 'F' : 'T'));
    }
    fprintf(stream, "\n");

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_row_cells()\n");
#endif
}

void print_cols(FILE *stream, const m2s_matrix_t *mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_cols()\n");
#endif

    uint32_t col_idx;
    
    for (col_idx = 0U; col_idx < mtx_ptr->col_count; col_idx++) {
        fprintf(stream, "\tcol [%05u] [%s]\n", col_idx, mtx_ptr->col_labels[col_idx]);
        print_col_cells(stream, mtx_ptr, col_idx);
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_cols()\n");
#endif
}

void print_col_stats(FILE *stream, const m2s_matrix_t *mtx_ptr) 
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_col_stats()\n");
#endif

    uint32_t col_idx;

    for (col_idx = 0U; col_idx < mtx_ptr->col_count; col_idx++) {
        fprintf(stream, "\tcol [%05u] \t mean [%f] \t var [%f] \t sd [%f] \t min [%f] \t max [%f]\n", 
                col_idx, 
                mtx_ptr->col_stats->means[col_idx], 
                mtx_ptr->col_stats->svars[col_idx] / (mtx_ptr->row_count - 1), 
                mtx_ptr->col_stats->stdevs[col_idx],
                mtx_ptr->col_stats->mins[col_idx], 
                mtx_ptr->col_stats->maxs[col_idx]);
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_col_stats()\n");
#endif
}

void print_col_labels(FILE *stream, const m2s_matrix_t *mtx_ptr) 
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_col_labels()\n");
#endif

    uint32_t col_idx;

    for (col_idx = 0U; col_idx < mtx_ptr->col_count; col_idx++) {
        fprintf(stream, "\tcol [%05u] [%s]\n", col_idx, mtx_ptr->col_labels[col_idx]);
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_col_labels()\n");
#endif
}

void print_col_cells(FILE *stream, const m2s_matrix_t *mtx_ptr, const uint32_t col_idx)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_col_cells()\n");
#endif

    uint32_t row_count = mtx_ptr->row_count;
    uint32_t col_count = mtx_ptr->col_count;
    uint64_t cell_idx, start_idx, end_idx;

    start_idx = col_idx;
    end_idx = col_idx + ((uint64_t)col_count * (uint64_t)row_count);

    fprintf(stream, "\tdata -> ");
    for (cell_idx = start_idx; cell_idx < end_idx; cell_idx += col_count) {
        fprintf(stream, "%f + ", mtx_ptr->data_values[cell_idx]);
    }
    fprintf(stream, "\n");

    fprintf(stream, "\tmissing -> ");
    for (cell_idx = start_idx; cell_idx < end_idx; cell_idx += col_count) {
        fprintf(stream, "%c + ", (mtx_ptr->missing_values[cell_idx] == kFalse ? 'F' : 'T'));
    }
    fprintf(stream, "\n");

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_col_cells()\n");
#endif
}
