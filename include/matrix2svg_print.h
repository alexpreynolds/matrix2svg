#ifndef _M2S_PRINT_H
#define _M2S_PRINT_H

#include "matrix2svg.h"

#ifdef __cplusplus
extern "C" {
#endif

void print_rows(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_row_stats(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_row_labels(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_row_cells(FILE *stream, const m2s_matrix_t *mtx_ptr, const uint32_t row_idx);
void print_cols(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_col_stats(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_col_labels(FILE *stream, const m2s_matrix_t *mtx_ptr);
void print_col_cells(FILE *stream, const m2s_matrix_t *mtx_ptr, const uint32_t col_idx);

#ifdef __cplusplus
};
#endif

#endif /* _M2S_PRINT_H */
