#pragma once

void task_one(int nthreads);
void task_three(int nthreads);
void multiply_matrix_seq(double** a, double** b, double** c);
void multiply_matrix_par(double** a, double** b, double** c, int num_threads);
void task_four();
void transpose_matrix(double** matrix, double** tr_matrix, int n);
void sequential_transpose(double** matrix, double** tr_matrix, int n);
void print_matrix(double** tr_matrix, int n);
void parallel_transpose(double** matrix, double** tr_matrix, int n, int num_threads);
void task_eleven();
void transpose_tile(double** matrix, double** tr_matrix, int n, int block_size);
void sequential_transpose_tt(double** matrix, double** tr_matrix, int n);
void parallel_transpose_tt(double** matrix, double** tr_matrix, int n, int num_threads, int block_size);
void task_eleven_tt();
void print_matrix_tt(double** tr_matrix, int n);

