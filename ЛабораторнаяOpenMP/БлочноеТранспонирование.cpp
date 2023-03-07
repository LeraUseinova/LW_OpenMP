#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <chrono>
#include "Заголовки.h"
using namespace std;

const int BLOCK_SIZE[] = { 8, 16, 32, 64 };

void transpose_tile(double** matrix, double** tr_matrix, int n, int block_size) {
    int i, j, ii, jj;
#pragma omp parallel for private(i, j, ii, jj)
    for (i = 0; i < n; i += block_size) {
        for (j = 0; j < n; j += block_size) {
            for (ii = i; ii < i + block_size && ii < n; ii++) {
                for (jj = j; jj < j + block_size && jj < n; jj++) {
                    tr_matrix[jj][ii] = matrix[ii][jj];
                }
            }
        }
    }
}


void print_matrix_tt(double** tr_matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << tr_matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void sequential_transpose_tt(double** matrix, double** tr_matrix, int n) {
    auto start = chrono::high_resolution_clock::now();
    transpose_tile(matrix, tr_matrix, n, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time for sequential transpose: " << elapsed.count() << " s" << endl;
    //print_matrix_tt(tr_matrix, n);
}

void parallel_transpose_tt(double** matrix, double** tr_matrix, int n, int num_threads, int block_size) {
    omp_set_num_threads(num_threads);
    auto start = chrono::high_resolution_clock::now();
    transpose_tile(matrix, tr_matrix, n, block_size);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time for parallel transpose with " << num_threads << " threads: " << elapsed.count() << " s and block size:" << block_size << endl;
    //print_matrix_tt(tr_matrix, n);
}

void task_eleven_tt() {
    cout << "Tile transposition" << endl;
    int n = 1000;
    double** matrix = new double* [n];
    double** tr_matrix = new double* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];
        tr_matrix[i] = new double[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10;
            //cout << matrix[i][j] << "\t";
        }
        //cout << endl;
    }

    sequential_transpose_tt(matrix, tr_matrix, n);

    int num_threads[3] = { 2, 4, 8 };
    for (int i = 0; i < 4; i++) {
        int block_size = BLOCK_SIZE[i];
        for (int j = 0; j < 3; j++) {
            parallel_transpose_tt(matrix, tr_matrix, n, num_threads[j], block_size);
        }
    }


    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
        delete[] tr_matrix[i];
    }
    delete[] matrix;
    delete[] tr_matrix;

    cout << "\n" << endl;
}