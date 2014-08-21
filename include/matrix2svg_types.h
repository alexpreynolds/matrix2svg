#ifndef M2S_TYPES_H
#define M2S_TYPES_H

#include <stdint.h>

typedef int boolean;
extern const boolean kTrue;
extern const boolean kFalse;

typedef double m2s_data_t;
typedef struct m2s_matrix_t m2s_matrix_t;
typedef struct m2s_stats_t m2s_stats_t;
typedef struct m2s_color_t m2s_color_t;

struct m2s_matrix_t {
    uint32_t      row_count;
    uint32_t      col_count;
    char        **col_labels;
    char        **row_labels;
    m2s_data_t   *data_values;
    boolean      *missing_values;
    m2s_stats_t  *row_stats;
    m2s_stats_t  *col_stats;
    m2s_color_t  *color_values;
};

struct m2s_stats_t {
    double *means;
    double *svars;
    double *stdevs;
    double *mins;
    double *maxs;
};

struct m2s_color_t {
    short r;
    short g;
    short b;
    float a;
};

#endif
