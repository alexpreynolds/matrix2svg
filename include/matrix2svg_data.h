#ifndef _M2S_DATA_H
#define _M2S_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <getopt.h>
#include <errno.h>

#include "matrix2svg_types.h"

#ifdef __cplusplus
extern "C" {
#endif

    void read_in_data(FILE *in_file_ptr, m2s_matrix_t **mtx_ptr);
    FILE * new_file_ptr(const char *in_fn);
    void delete_file_ptr(FILE **file_ptr);
    m2s_stats_t * new_stats_ptr(const uint32_t length);
    m2s_matrix_t * new_mtx_ptr(const uint32_t rows, const uint32_t cols);
    void add_mtx_col_stats(m2s_matrix_t **mtx_ptr);
    void add_mtx_col_label(m2s_matrix_t **mtx_ptr, const char *label);
    void add_mtx_row_stats(m2s_matrix_t **mtx_ptr);
    void add_mtx_row_label(m2s_matrix_t **mtx_ptr, const char *label);
    void add_mtx_row_data(m2s_matrix_t **mtx_ptr);
    void add_mtx_row_missing(m2s_matrix_t **mtx_ptr);
    void update_mtx_data_value(m2s_matrix_t **mtx_ptr, const char *value, const uint32_t row_idx, const uint32_t col_idx);
    void update_mtx_missing_value(m2s_matrix_t **mtx_ptr, const boolean value, const uint32_t row_idx, const uint32_t col_idx);
    void update_mtx_stats(m2s_matrix_t **mtx_ptr, const double value, const uint32_t row_idx, const uint32_t col_idx);
    void reset_mtx_stats_ptr(m2s_stats_t **stats_ptr, uint32_t length);
    void transform_log_mtx(m2s_matrix_t **mtx_ptr);
    void delete_stats_ptr(m2s_matrix_t **mtx_ptr);
    void delete_mtx_ptr(m2s_matrix_t **mtx_ptr);
    char * strtok_single(char *str, const char *delims);
    
#ifdef __cplusplus
};
#endif

#endif /* _M2S_H */
