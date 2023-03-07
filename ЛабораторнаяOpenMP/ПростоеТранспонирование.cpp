#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <chrono>
#include "Заголовки.h"
using namespace std;

void transpose_matrix(double** matrix, double** tr_matrix, int n) {
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
#pragma omp simd
        for (int j = 0; j < n; j++)
        {
            tr_matrix[i][j] = matrix[j][i];
        }
    }

}

void print_matrix(double** tr_matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << tr_matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void sequential_transpose(double** matrix, double** tr_matrix, int n) {
    auto start = chrono::high_resolution_clock::now();
    transpose_matrix(matrix, tr_matrix, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time for sequential transpose: " << elapsed.count() << " s" << endl;
    //print_matrix(tr_matrix, n);
}

void parallel_transpose(double** matrix, double** tr_matrix, int n, int num_threads) {
    omp_set_num_threads(num_threads);
    auto start = chrono::high_resolution_clock::now();
    transpose_matrix(matrix, tr_matrix, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time for parallel transpose with " << num_threads << " threads: " << elapsed.count() << " s" << endl;
    //print_matrix(tr_matrix, n);
}

void task_eleven() {
    cout << "Normal transposition" << endl;
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

    sequential_transpose(matrix, tr_matrix, n);

    int num_threads[3] = { 2, 4, 8 };
    for (int i = 0; i < 3; i++) {
        parallel_transpose(matrix, tr_matrix, n, num_threads[i]);
    }


    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
        delete[] tr_matrix[i];
    }
    delete[] matrix;
    delete[] tr_matrix;

    cout << "\n" << endl;
}