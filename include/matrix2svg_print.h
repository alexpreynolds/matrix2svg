#ifndef M2S_PRINT_H
#define M2S_PRINT_H

#include "matrix2svg.h"

void print_rows(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_row_stats(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_row_labels(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_row_cells(FILE *stream, const m2s_matrix_t *mtx_ptr, const uint32_t row_idx);
void print_cols(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_col_stats(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_col_labels(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_col_cells(FILE *stream, const m2s_matrix_t *mtx_ptr, const uint32_t col_idx);

#endif
