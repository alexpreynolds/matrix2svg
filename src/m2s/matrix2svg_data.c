#include "matrix2svg_data.h"
#include "matrix2svg_types.h"

void read_in_data(FILE *in_file_ptr, m2s_matrix_t **mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> read_in_data()\n");
#endif

    char in_line[M2S_MAX_LINE_LENGTH + 1];
    char *tok = NULL;
    uint32_t line_idx = 0U;
    int32_t col_idx = -1;

    in_line[M2S_MAX_LINE_LENGTH] = '1';

    /* read in column labels */
    fgets(in_line, M2S_MAX_LINE_LENGTH + 1, in_file_ptr);
    tok = strtok_single(in_line, "\t\n");
    do {
        if (col_idx >= 0) {
            add_mtx_col_label(mtx_ptr, tok);
            add_mtx_col_stats(mtx_ptr);
        }
        tok = strtok_single(NULL, "\t\n");
        col_idx++;
    } while (tok);

    /* read in row labels and cell values */
    while (fgets(in_line, M2S_MAX_LINE_LENGTH + 1, in_file_ptr)) {
        col_idx = -1;
        tok = strtok_single(in_line, "\t\n");
        add_mtx_row_label(mtx_ptr, tok);
        add_mtx_row_stats(mtx_ptr);
        add_mtx_row_data(mtx_ptr);
        add_mtx_row_missing(mtx_ptr);
        col_idx++;
        do {
            tok = strtok_single(NULL, "\t\n");
            if (tok)
                update_mtx_data_value(mtx_ptr, tok, line_idx, col_idx);
            col_idx++;
        } while(tok);
        line_idx++;
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> read_in_data()\n");
#endif
}

FILE * new_file_ptr(const char *in_fn)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> new_file_ptr()\n");
#endif

    FILE *file_ptr = NULL;
    boolean not_stdin = kTrue;

    not_stdin = strcmp(in_fn, "-");
    file_ptr = (not_stdin) ? fopen(in_fn, "r") : stdin;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> new_file_ptr()\n");
#endif
    
    return file_ptr;
}

void delete_file_ptr(FILE **file_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> delete_file_ptr()\n");
#endif

    fclose(*file_ptr);
    *file_ptr = NULL;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> delete_file_ptr()\n");
#endif
}

m2s_stats_t * new_stats_ptr(const uint32_t length)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> new_stats_ptr()\n");
#endif

    m2s_stats_t *stats_ptr = NULL;

    stats_ptr = malloc(sizeof(m2s_stats_t));
    if (!stats_ptr) {
        fprintf(stderr, "Error: new stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    stats_ptr->means = NULL;
    stats_ptr->means = malloc(length * sizeof(double));
    if (!stats_ptr->means) {
        fprintf(stderr, "Error: blank stats means pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    stats_ptr->svars = NULL;
    stats_ptr->svars = malloc(length * sizeof(double));
    if (!stats_ptr->svars) {
        fprintf(stderr, "Error: blank stats svars pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    stats_ptr->stdevs = NULL;
    stats_ptr->stdevs = malloc(length * sizeof(double));
    if (!stats_ptr->stdevs) {
        fprintf(stderr, "Error: blank stats stdevs pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    stats_ptr->mins = NULL;
    stats_ptr->mins = malloc(length * sizeof(double));
    if (!stats_ptr->mins) {
        fprintf(stderr, "Error: blank stats mins pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    stats_ptr->maxs = NULL;
    stats_ptr->maxs = malloc(length * sizeof(double));
    if (!stats_ptr->maxs) {
        fprintf(stderr, "Error: blank stats maxs pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    return stats_ptr;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> new_stats_ptr()\n");
#endif
}

m2s_matrix_t * new_mtx_ptr(const uint32_t rows, const uint32_t cols)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> new_mtx_ptr()\n");
#endif

    m2s_matrix_t *mtx_ptr = NULL;
    mtx_ptr = malloc(sizeof(m2s_matrix_t));
    if (!mtx_ptr) {
        fprintf(stderr, "Error: matrix pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    
    mtx_ptr->row_labels = NULL;
    if (rows > 0) {
        mtx_ptr->row_labels = malloc(rows * sizeof(char *));
        if (!mtx_ptr->row_labels) {
            fprintf(stderr, "Error: row label pointer is NULL\n");
            exit(EXIT_FAILURE);
        }
    }
    mtx_ptr->row_count = rows;

    mtx_ptr->col_labels = NULL;
    if (cols > 0) {
        mtx_ptr->col_labels = malloc(cols * sizeof(char *));
        if (!mtx_ptr->col_labels) {
            fprintf(stderr, "Error: column label pointer is NULL\n");
            exit(EXIT_FAILURE);
        }
    }
    mtx_ptr->col_count = cols;
    
    mtx_ptr->data_values = NULL;
    if ((rows > 0) && (cols > 0)) {
        mtx_ptr->data_values = malloc((uint64_t)rows * (uint64_t)cols * sizeof(double));
        if (!mtx_ptr->data_values) {
            fprintf(stderr, "Error: data values pointer is NULL\n");
            exit(EXIT_FAILURE);
        }
    }

    mtx_ptr->missing_values = NULL;
    if ((rows > 0) && (cols > 0)) {
        mtx_ptr->missing_values = malloc((uint64_t)rows * (uint64_t)cols * sizeof(boolean));
        if (!mtx_ptr->missing_values) {
            fprintf(stderr, "Error: missing values pointer is NULL\n");
            exit(EXIT_FAILURE);
        }
    }

    mtx_ptr->row_stats = NULL;
    mtx_ptr->col_stats = NULL;
    if ((rows > 0) && (cols > 0)) {
        mtx_ptr->row_stats = new_stats_ptr(rows);
        mtx_ptr->col_stats = new_stats_ptr(cols);
        if ((!mtx_ptr->row_stats) || (!mtx_ptr->col_stats)) {
            fprintf(stderr, "Error: new row or col stats pointer is NULL\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        mtx_ptr->row_stats = malloc(sizeof(m2s_stats_t));
        mtx_ptr->col_stats = malloc(sizeof(m2s_stats_t));
        if ((!mtx_ptr->row_stats) || (!mtx_ptr->col_stats)) {
            fprintf(stderr, "Error: malloc'ed row or col stats pointer is NULL\n");
            exit(EXIT_FAILURE);
        }
        mtx_ptr->row_stats->means = NULL;
        mtx_ptr->row_stats->svars = NULL;
        mtx_ptr->row_stats->stdevs = NULL;
        mtx_ptr->row_stats->mins = NULL;
        mtx_ptr->row_stats->maxs = NULL;
        mtx_ptr->col_stats->means = NULL;
        mtx_ptr->col_stats->svars = NULL;
        mtx_ptr->col_stats->stdevs = NULL;
        mtx_ptr->col_stats->mins = NULL;
        mtx_ptr->col_stats->maxs = NULL;
    }

    mtx_ptr->color_values = NULL;
    if ((rows > 0) && (cols > 0)) {
        mtx_ptr->color_values = malloc(rows * cols * sizeof(m2s_color_t));
        if (!mtx_ptr->color_values) {
            fprintf(stderr, "Error: color values pointer is NULL\n");
            exit(EXIT_FAILURE);
        }
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> new_mtx_ptr()\n");
#endif

    return mtx_ptr;
}

void add_mtx_col_stats(m2s_matrix_t **mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> add_mtx_col_stats()\n");
#endif

    m2s_stats_t *col_stats_ptr = (*mtx_ptr)->col_stats;
    uint32_t old_col_count = (*mtx_ptr)->col_count - 1;
    uint32_t new_col_count = old_col_count + 1;
    double *old_col_means = col_stats_ptr->means;
    double *old_col_svars = col_stats_ptr->svars;
    double *old_col_stdevs = col_stats_ptr->stdevs;
    double *old_col_mins = col_stats_ptr->mins;
    double *old_col_maxs = col_stats_ptr->maxs;
    double *new_col_means = NULL;
    double *new_col_svars = NULL;
    double *new_col_stdevs = NULL;
    double *new_col_mins = NULL;
    double *new_col_maxs = NULL;

    new_col_means = realloc(old_col_means, new_col_count * sizeof(double));
    if (!new_col_means) {
        fprintf(stderr, "Error: new matrix column means stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_col_means[new_col_count - 1] = 0.0f;
    col_stats_ptr->means = new_col_means;

    new_col_svars = realloc(old_col_svars, new_col_count * sizeof(double));
    if (!new_col_svars) {
        fprintf(stderr, "Error: new matrix column svars stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_col_svars[new_col_count - 1] = 0.0f;
    col_stats_ptr->svars = new_col_svars;

    new_col_stdevs = realloc(old_col_stdevs, new_col_count * sizeof(double));
    if (!new_col_stdevs) {
        fprintf(stderr, "Error: new matrix column stdevs stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_col_stdevs[new_col_count - 1] = 0.0f;
    col_stats_ptr->stdevs = new_col_stdevs;

    new_col_mins = realloc(old_col_mins, new_col_count * sizeof(double));
    if (!new_col_mins) {
        fprintf(stderr, "Error: new matrix column mins stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_col_mins[new_col_count - 1] = DBL_MAX;
    col_stats_ptr->mins = new_col_mins;

    new_col_maxs = realloc(old_col_maxs, new_col_count * sizeof(double));
    if (!new_col_maxs) {
        fprintf(stderr, "Error: new matrix column maxs stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_col_maxs[new_col_count - 1] = -DBL_MAX;
    col_stats_ptr->maxs = new_col_maxs;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> add_mtx_col_stats()\n");
#endif
}

void add_mtx_col_label(m2s_matrix_t **mtx_ptr, const char *label)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> add_mtx_col_label()\n");
#endif

    char **old_col_labels = (*mtx_ptr)->col_labels;
    char **new_col_labels = NULL;
    uint32_t old_col_count = (*mtx_ptr)->col_count;
    uint32_t new_col_count = old_col_count + 1;

    new_col_labels = realloc(old_col_labels, new_col_count * sizeof(char *));
    if (!new_col_labels) {
        fprintf(stderr, "Error: new matrix column labels pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    (*mtx_ptr)->col_labels = new_col_labels;
    (*mtx_ptr)->col_labels[new_col_count - 1] = NULL;
    (*mtx_ptr)->col_labels[new_col_count - 1] = malloc(sizeof(char) * (strlen(label) + 1));
    if (!(*mtx_ptr)->col_labels[new_col_count - 1]) {
        fprintf(stderr, "Error: new column label pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    strcpy((*mtx_ptr)->col_labels[new_col_count - 1], label);
    (*mtx_ptr)->col_count++;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> add_mtx_col_label()\n");
#endif
}

void add_mtx_row_stats(m2s_matrix_t **mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> add_mtx_row_stats()\n");
#endif

    m2s_stats_t *row_stats_ptr = (*mtx_ptr)->row_stats;
    uint32_t old_row_count = (*mtx_ptr)->row_count - 1;
    uint32_t new_row_count = old_row_count + 1;
    double *old_row_means = row_stats_ptr->means;
    double *old_row_svars = row_stats_ptr->svars;
    double *old_row_stdevs = row_stats_ptr->stdevs;
    double *old_row_mins = row_stats_ptr->mins;
    double *old_row_maxs = row_stats_ptr->maxs;
    double *new_row_means = NULL;
    double *new_row_svars = NULL;
    double *new_row_stdevs = NULL;
    double *new_row_mins = NULL;
    double *new_row_maxs = NULL;

    new_row_means = realloc(old_row_means, new_row_count * sizeof(double));
    if (!new_row_means) {
        fprintf(stderr, "Error: new matrix row means stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_row_means[new_row_count - 1] = 0.0f;
    row_stats_ptr->means = new_row_means;

    new_row_svars = realloc(old_row_svars, new_row_count * sizeof(double));
    if (!new_row_svars) {
        fprintf(stderr, "Error: new matrix row svars stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_row_svars[new_row_count - 1] = 0.0f;
    row_stats_ptr->svars = new_row_svars;

    new_row_stdevs = realloc(old_row_stdevs, new_row_count * sizeof(double));
    if (!new_row_stdevs) {
        fprintf(stderr, "Error: new matrix row stdevs stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_row_stdevs[new_row_count - 1] = 0.0f;
    row_stats_ptr->stdevs = new_row_stdevs;

    new_row_mins = realloc(old_row_mins, new_row_count * sizeof(double));
    if (!new_row_mins) {
        fprintf(stderr, "Error: new matrix row mins stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_row_mins[new_row_count - 1] = DBL_MAX;
    row_stats_ptr->mins = new_row_mins;

    new_row_maxs = realloc(old_row_maxs, new_row_count * sizeof(double));
    if (!new_row_maxs) {
        fprintf(stderr, "Error: new matrix row maxs stats pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    new_row_maxs[new_row_count - 1] = -DBL_MAX;
    row_stats_ptr->maxs = new_row_maxs;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> add_mtx_row_stats()\n");
#endif
}


void add_mtx_row_label(m2s_matrix_t **mtx_ptr, const char *label)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> add_mtx_row_label()\n");
#endif

    char **old_row_labels = (*mtx_ptr)->row_labels;
    char **new_row_labels = NULL;
    uint32_t old_row_count = (*mtx_ptr)->row_count;
    uint32_t new_row_count = old_row_count + 1;

    new_row_labels = realloc(old_row_labels, new_row_count * sizeof(char *));
    if (!new_row_labels) {
        fprintf(stderr, "Error: new matrix row labels pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    (*mtx_ptr)->row_labels = new_row_labels;
    (*mtx_ptr)->row_labels[new_row_count - 1] = NULL;
    (*mtx_ptr)->row_labels[new_row_count - 1] = malloc(sizeof(char) * (strlen(label) + 1));
    if (!(*mtx_ptr)->row_labels[new_row_count - 1]) {
        fprintf(stderr, "Error: new row label pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    strcpy((*mtx_ptr)->row_labels[new_row_count - 1], label);    
    (*mtx_ptr)->row_count++;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> add_mtx_row_label()\n");
#endif
}

void add_mtx_row_data(m2s_matrix_t **mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> add_mtx_row_data()\n");
#endif
    
    m2s_data_t *new_data_values = NULL;
    uint32_t old_row_count = (*mtx_ptr)->row_count - 1;
    uint32_t new_row_count = old_row_count + 1;
    uint32_t col_count = (*mtx_ptr)->col_count;
    uint64_t cell_idx, start_idx, end_idx;

    new_data_values = realloc((*mtx_ptr)->data_values, (uint64_t)new_row_count * (uint64_t)col_count * sizeof(m2s_data_t));
    if (!new_data_values) {
        fprintf(stderr, "Error: new matrix row cells pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    (*mtx_ptr)->data_values = new_data_values;

    start_idx = (uint64_t)old_row_count * (uint64_t)col_count;
    end_idx = (uint64_t)new_row_count * (uint64_t)col_count;
    for (cell_idx = start_idx; cell_idx < end_idx; ++cell_idx) {
        (*mtx_ptr)->data_values[cell_idx] = 0.0f;
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> add_mtx_row_data()\n");
#endif
}

void add_mtx_row_missing(m2s_matrix_t **mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> add_mtx_row_missing()\n");
#endif
    
    boolean *new_missing_values = NULL;
    uint32_t old_row_count = (*mtx_ptr)->row_count - 1;
    uint32_t new_row_count = old_row_count + 1;
    uint32_t col_count = (*mtx_ptr)->col_count;
    uint64_t cell_idx, start_idx, end_idx;
    
    new_missing_values = realloc((*mtx_ptr)->missing_values, (uint64_t)new_row_count * (uint64_t)col_count * sizeof(boolean));
    if (!new_missing_values) {
        fprintf(stderr, "Error: new matrix row cells pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    (*mtx_ptr)->missing_values = new_missing_values;

    start_idx = (uint64_t)old_row_count * (uint64_t)col_count;
    end_idx = (uint64_t)new_row_count * (uint64_t)col_count;
    for (cell_idx = start_idx; cell_idx < end_idx; ++cell_idx) {
        (*mtx_ptr)->missing_values[cell_idx] = kFalse;
    }    
    
#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> add_mtx_row_missing()\n");
#endif
}

void update_mtx_data_value(m2s_matrix_t **mtx_ptr, const char *value, const uint32_t row_idx, const uint32_t col_idx)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> update_mtx_data_value()\n");
#endif

    char *comp = NULL;
    uint32_t current_col_count = (*mtx_ptr)->col_count;
    uint64_t cell_idx = ((uint64_t)row_idx * (uint64_t)current_col_count) + col_idx;

#ifdef DEBUG
    fprintf(stderr, "Debug: Setting  --> [%s] at [%05llu]\n", value, (long long unsigned int) cell_idx);
#endif

    if (strlen(value) > 0) {
        (*mtx_ptr)->data_values[cell_idx] = strtod(value, &comp);
        update_mtx_stats(mtx_ptr, (*mtx_ptr)->data_values[cell_idx], row_idx, col_idx);
    }
    else {
        update_mtx_missing_value(mtx_ptr, kTrue, row_idx, col_idx);
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> update_mtx_data_value()\n");
#endif
}

void update_mtx_missing_value(m2s_matrix_t **mtx_ptr, const boolean value, const uint32_t row_idx, const uint32_t col_idx)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> update_mtx_missing_value()\n");
#endif

    uint32_t current_col_count = (*mtx_ptr)->col_count;
    uint64_t cell_idx = ((uint64_t)row_idx * (uint64_t)current_col_count) + col_idx;

#ifdef DEBUG
    fprintf(stderr, "Debug: Setting  --> [%c] at [%05llu]\n", (value == kFalse ? 'F' : 'T'), (long long unsigned int) cell_idx);
#endif

    (*mtx_ptr)->missing_values[cell_idx] = value;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> update_mtx_missing_value()\n");
#endif
}

void update_mtx_stats(m2s_matrix_t **mtx_ptr, const double value, const uint32_t row_idx, const uint32_t col_idx)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> update_mtx_stats()\n");
#endif
    
    m2s_stats_t *row_stats_ptr = (*mtx_ptr)->row_stats;
    double *row_means = row_stats_ptr->means;
    double *row_svars = row_stats_ptr->svars;
    double *row_stdevs = row_stats_ptr->stdevs;
    double *row_mins = row_stats_ptr->mins;
    double *row_maxs = row_stats_ptr->maxs;
    double old_row_mean = row_means[row_idx];
    double old_row_svar = row_svars[row_idx];

    m2s_stats_t *col_stats_ptr = (*mtx_ptr)->col_stats;
    double *col_means = col_stats_ptr->means;
    double *col_svars = col_stats_ptr->svars;
    double *col_stdevs = col_stats_ptr->stdevs;
    double *col_mins = col_stats_ptr->mins;
    double *col_maxs = col_stats_ptr->maxs;
    double old_col_mean = col_means[col_idx];
    double old_col_svar = col_svars[col_idx];

    /* Welford's method: cf. http://www.johndcook.com/standard_deviation.html */
    row_means[row_idx] = old_row_mean + (value - old_row_mean) / (col_idx + 1);
    row_svars[row_idx] = old_row_svar + (value - old_row_mean) * (value - row_means[row_idx]);
    row_stdevs[row_idx] = sqrt( row_svars[row_idx] / ((*mtx_ptr)->col_count - 1) );
    if (row_mins[row_idx] > value) row_mins[row_idx] = value;
    if (row_maxs[row_idx] < value) row_maxs[row_idx] = value;

    col_means[col_idx] = old_col_mean + (value - old_col_mean) / (row_idx + 1);
    col_svars[col_idx] = old_col_svar + (value - old_col_mean) * (value - col_means[col_idx]);
    col_stdevs[col_idx] = sqrt( col_svars[col_idx] / ((*mtx_ptr)->row_count - 1) );
    if (col_mins[col_idx] > value) col_mins[col_idx] = value;
    if (col_maxs[col_idx] < value) col_maxs[col_idx] = value;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> update_mtx_stats()\n");
#endif
}

void reset_mtx_stats_ptr(m2s_stats_t **stats_ptr, uint32_t length)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> reset_mtx_stats_ptr()\n");
#endif

    uint32_t elem_idx;
    double *means = (*stats_ptr)->means;
    double *svars = (*stats_ptr)->svars;
    double *stdevs = (*stats_ptr)->stdevs;
    double *mins = (*stats_ptr)->mins;
    double *maxs = (*stats_ptr)->maxs;

    for (elem_idx = 0; elem_idx < length; ++elem_idx) {
        means[elem_idx] = 0.0f;
        svars[elem_idx] = 0.0f;
        stdevs[elem_idx] = 0.0f;
        mins[elem_idx] = DBL_MAX;
        maxs[elem_idx] = -DBL_MAX;
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> reset_mtx_stats_ptr()\n");
#endif
}

void transform_log_mtx(m2s_matrix_t **mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> transform_log_mtx()\n");
#endif

    uint32_t row_count = (*mtx_ptr)->row_count;
    uint32_t col_count = (*mtx_ptr)->col_count;
    m2s_data_t *data_values = (*mtx_ptr)->data_values;
    boolean *missing_values = (*mtx_ptr)->missing_values;
    m2s_stats_t *row_stats = (*mtx_ptr)->row_stats;
    m2s_stats_t *col_stats = (*mtx_ptr)->col_stats;
    uint64_t row_idx, col_idx, cell_idx;

    if ((!data_values) || (!missing_values) || (row_count == 0) || (col_count == 0))
        return;
    
    /* reset statistics values */
    reset_mtx_stats_ptr(&row_stats, row_count);
    reset_mtx_stats_ptr(&col_stats, col_count);

    /* as we transform data values with natural log, we update the statistics */
    for (row_idx = 0; row_idx < row_count; ++row_idx) {
        for (col_idx = 0; col_idx < col_count; ++col_idx) {
            cell_idx = row_idx * col_count + col_idx;
            if ((data_values[cell_idx] > 0) && (missing_values[cell_idx] == kFalse)) {
                data_values[cell_idx] = log(data_values[cell_idx]);
                update_mtx_stats(mtx_ptr, data_values[cell_idx], row_idx, col_idx);
            }
            else if ((data_values[cell_idx] <= 0) && (missing_values[cell_idx] == kFalse)) {
                fprintf(stderr, "Error: Cannot take logarithm of illegal value [%f] at [row, col] = [%llu, %llu]\n", data_values[cell_idx], (long long unsigned int) row_idx, (long long unsigned int) col_idx);
                exit(EXIT_FAILURE);
            }
        }
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> transform_log_mtx()\n");
#endif
}

void delete_stats_ptr(m2s_matrix_t **mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> delete_stats_ptr()\n");
#endif

    m2s_stats_t *row_stats_ptr = (*mtx_ptr)->row_stats;
    m2s_stats_t *col_stats_ptr = (*mtx_ptr)->col_stats;
    
    if ((!row_stats_ptr) || (!col_stats_ptr))
        return;

    free(row_stats_ptr->means);   row_stats_ptr->means   = NULL;
    free(row_stats_ptr->svars);   row_stats_ptr->svars   = NULL;
    free(row_stats_ptr->stdevs);  row_stats_ptr->stdevs  = NULL;
    free(row_stats_ptr->mins);    row_stats_ptr->mins    = NULL;
    free(row_stats_ptr->maxs);    row_stats_ptr->maxs    = NULL;

    free(col_stats_ptr->means);   col_stats_ptr->means   = NULL;
    free(col_stats_ptr->svars);   col_stats_ptr->svars   = NULL;
    free(col_stats_ptr->stdevs);  col_stats_ptr->stdevs  = NULL;
    free(col_stats_ptr->mins);    col_stats_ptr->mins    = NULL;
    free(col_stats_ptr->maxs);    col_stats_ptr->maxs    = NULL;

    free((*mtx_ptr)->row_stats);  (*mtx_ptr)->row_stats  = NULL;
    free((*mtx_ptr)->col_stats);  (*mtx_ptr)->col_stats  = NULL;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> delete_stats_ptr()\n");
#endif
}

void delete_mtx_ptr(m2s_matrix_t **mtx_ptr)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> delete_mtx_ptr()\n");
#endif

    m2s_matrix_t **mtx = (m2s_matrix_t **) mtx_ptr;
    uint32_t row_idx, col_idx;

    for (row_idx = 0; row_idx < (*mtx)->row_count; ++row_idx) {
        free((*mtx)->row_labels[row_idx]); (*mtx)->row_labels[row_idx] = NULL;
    }
    free((*mtx)->row_labels); (*mtx)->row_labels = NULL;
    for (col_idx = 0; col_idx < (*mtx)->col_count; ++col_idx) {
        free((*mtx)->col_labels[col_idx]); (*mtx)->col_labels[col_idx] = NULL;
    }
    free((*mtx)->col_labels); (*mtx)->col_labels = NULL;
    free((*mtx)->data_values); (*mtx)->data_values = NULL;
    free((*mtx)->missing_values); (*mtx)->missing_values = NULL;
    delete_stats_ptr(mtx_ptr);
    free((*mtx)->color_values); (*mtx)->color_values = NULL;
    free(*mtx); *mtx = NULL;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> delete_mtx_ptr()\n");
#endif
}

char * strtok_single(char *str, const char *delims)
{
    /* cf. http://stackoverflow.com/a/8706031/19410 */
    static char *src = NULL;
    char *p, *ret = NULL;

    if (str)
        src = str;

    if (!src)
        return NULL;

    if ((p = strpbrk(src, delims)) != NULL) {
        *p = 0;
        ret = src;
        src = ++p;
    }

    return ret;
}

