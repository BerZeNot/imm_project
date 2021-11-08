
typedef struct TMat2D TMat2D; 

// OK
TMat2D *mat2D_create(int nrows, int ncolumns);

// OK
int mat2D_free(TMat2D *mat);

// OK
int mat2D_set_value(TMat2D *mat, int i, int j, double val);

// OK
int mat2D_get_value(TMat2D *mat, int i, int j, double *val);

// OK
int mat2D_fill_with_random(TMat2D *mat, double minValue, double maxValue);

// MISSING IMPLEMENTATION
int mat2D_sum_two_matrixes(TMat2D *mat1, TMat2D *mat2, TMat2D *matResult);

// MISSING IMPLEMENTATION
int mat2D_multiply_two_matrixes(TMat2D *mat1, TMat2D *mat2, TMat2D *matResult);

// OK
int mat2D_multiply_mat_scalar(TMat2D *mat1, TMat2D *matResult, double scalar);

// OK
int mat2D_calculate_trace(TMat2D *mat1, double *result);

// OK
int mat2D_sum_lines(TMat2D *mat, double *vector);

// OK
int mat2D_get_number_of_rows(TMat2D *mat, int *result);

// OK
int mat2D_get_number_of_columns(TMat2D *mat, int *result);

// OK
int mat2D_print_matrix(TMat2D *mat);

int mat2d_increase_size(TMat2D *mat, int nrows, int ncols);