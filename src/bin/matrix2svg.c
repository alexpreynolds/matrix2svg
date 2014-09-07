#include "matrix2svg.h"

const char *m2s_name = "matrix2svg";
const char *m2s_version = M2S_VERSION;
const char *m2s_authors = "Alex Reynolds";
const char *m2s_usage = "\n" \
    "Usage: matrix2svg <input-file>\n" \
    "\n" \
    "  Converts textual matrix to a vector-based SVG figure\n\n" \
    "  The <input-file> may be a regular file or standard output from another application (use '-' to denote stdin)\n\n" \
    "  Process Flags:\n\n" \
    "  --help                        | -h      Show this usage message\n";

static struct option m2s_long_options[] = {
    { "help",				no_argument,		NULL,	'h' },
    { NULL,				no_argument,		NULL,	 0  }
}; 

const char *m2s_opt_string = "h?";

int main(int argc, char **argv)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> main()\n");
#endif

    m2s_matrix_t *mtx_ptr = NULL;
    char *in_filename = NULL;
    FILE *in_file_ptr = NULL;

    parse_command_line_options(argc, argv);

    mtx_ptr = new_mtx_ptr(0U, 0U);

    in_filename = m2s_globals.filenames[0];
    in_file_ptr = new_file_ptr(in_filename);
    read_in_data(in_file_ptr, &mtx_ptr);
    delete_file_ptr(&in_file_ptr);

#ifdef DEBUG
    print_col_labels(stderr, mtx_ptr);
    print_row_labels(stderr, mtx_ptr);
    print_rows(stderr, mtx_ptr);
    print_row_stats(stderr, mtx_ptr);
    print_cols(stderr, mtx_ptr);
    print_col_stats(stderr, mtx_ptr);
#endif

    delete_mtx_ptr(&mtx_ptr);

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> main()\n");
#endif

    return EXIT_SUCCESS;
}

void initialize_globals()
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> initialize_globals()\n");
#endif

    m2s_globals.filenames = NULL;
    m2s_globals.num_filenames = 0;

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> initialize_globals()\n");
#endif
}

void parse_command_line_options(int argc, char **argv)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> parse_command_line_options()\n");
#endif

    int client_long_index;
    int client_opt = getopt_long(argc, 
                                 argv, 
                                 m2s_opt_string, 
                                 m2s_long_options, 
                                 &client_long_index);

    opterr = 0; /* disable error reporting by GNU getopt */
    initialize_globals();

    while (client_opt != -1) 
        {
            switch (client_opt) 
                {
                case 'h':
                    print_usage(stdout);
                    exit(EXIT_SUCCESS);
                case '?':
                    print_usage(stdout);
                    exit(EXIT_SUCCESS);
                default:
                    break;
                }
            client_opt = getopt_long(argc, 
                                     argv, 
                                     m2s_opt_string, 
                                     m2s_long_options, 
                                     &client_long_index);
        }

    m2s_globals.filenames = argv + optind;
    m2s_globals.num_filenames = argc - optind;    

    if (m2s_globals.num_filenames != 1) {
        fprintf(stderr, "Error: Please specify an input file (either a regular file or '-' for stdin)\n");
        print_usage(stderr);
        exit(EXIT_FAILURE);
    }

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> parse_command_line_options()\n");
#endif
}

void print_usage(FILE *stream)
{
#ifdef DEBUG
    fprintf(stderr, "Debug: Entering --> print_usage()\n");
#endif

    fprintf(stream, 
            "%s\n" \
            "  version: %s\n" \
            "  author:  %s\n" \
            "%s\n", 
            m2s_name, 
            m2s_version,
            m2s_authors,
            m2s_usage);

#ifdef DEBUG
    fprintf(stderr, "Debug: Leaving  --> print_usage()\n");
#endif
}
