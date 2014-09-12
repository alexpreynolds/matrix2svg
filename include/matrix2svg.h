#ifndef _M2S_H
#define _M2S_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <getopt.h>
#include <errno.h>

#include "matrix2svg_data.h"
#include "matrix2svg_types.h"
#include "matrix2svg_print.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    extern const char *m2s_name;
    extern const char *m2s_version;
    extern const char *m2s_authors;
    extern const char *m2s_usage;
    
    typedef struct m2s_globals m2s_globals_t;
    struct m2s_globals_t {
	char **filenames;
	int num_filenames;
	boolean winsorize_rows_flag;
	unsigned short winsorize_rows_perc;
	boolean winsorize_cols_flag;
	unsigned short winsorize_cols_perc;
    } m2s_globals;
    
    const char *m2s_opt_string;
    
    void initialize_globals();
    void parse_command_line_options(int argc, char **argv);
    void print_usage(FILE *stream);

#ifdef __cplusplus
};
#endif

#endif /* _M2S_H */
