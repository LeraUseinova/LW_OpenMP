#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <chrono>
#include "Заголовки.h"

using namespace std;

////////////////////////////////////////// Task 1 //////////////////////////////////////////
void task_one(int nthreads) {
	omp_set_num_threads(nthreads);

#pragma omp parallel 
	{
		int id = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
		printf("Thread id: %d\t Threads: %d\t Hello World\n", id, num_threads);
	}

	cout << '\n' << endl;

	// the output changes on every run because the execution order of the threads is not defined
}



////////////////////////////////////////// Task 3 //////////////////////////////////////////
void task_three(int nthreads) {
	omp_set_num_threads(nthreads);

	// Option 1
	/*#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
		#pragma omp for ordered
		for (int i = 0; i < num_threads; i++)
		{
			#pragma omp ordered
			printf("Thread id: %d\t Threads: %d\t Hello World\n", num_threads - id - 1, num_threads);
		}
	}*/

	// Option 2
	/*#pragma omp parallel
	{
		#pragma omp single
		{
			int num_threads = omp_get_num_threads();
			for (int i = num_threads - 1; i >= 0; i--)
			{
				printf("Thread id: %d\t Threads: %d\t Hello World\n", i, num_threads);
			}
		}
	}*/

	// Option 3
#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int num_threads = omp_get_num_threads();

		for (int i = num_threads - 1; i >= 0; i--)
		{
#pragma omp barrier
			{
				if (i == id)
				{
#pragma omp critical
					printf("Thread id: %d\t Threads: %d\t Hello World\n", i, num_threads);
				}
			}
		}
	}

	cout << '\n' << endl;
}



////////////////////////////////////////// Task 4 //////////////////////////////////////////
const int N = 1000;


void multiply_matrix_seq(double** a, double** b, double** c) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << "Sequential version: " << elapsed.count() << " s" << endl;
}


void multiply_matrix_par(double** a, double** b, double** c, int num_threads) {
	omp_set_num_threads(num_threads);
	auto start = chrono::high_resolution_clock::now();
#pragma omp parallel for collapse(2)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << "Parallel version with " << num_threads << " threads: " << elapsed.count() << " s" << endl;
}

void task_four() {
	double** a, ** b, ** c_seq, ** c_par;
	a = new double* [N];
	b = new double* [N];
	c_seq = new double* [N];
	c_par = new double* [N];
	for (int i = 0; i < N; i++) {
		a[i] = new double[N];
		b[i] = new double[N];
		c_seq[i] = new double[N];
		c_par[i] = new double[N];
	}

	srand(0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i][j] = (double)rand() / RAND_MAX;
			b[i][j] = (double)rand() / RAND_MAX;
			c_seq[i][j] = 0.0;
			c_par[i][j] = 0.0;
		}
	}

	multiply_matrix_seq(a, b, c_seq);
	multiply_matrix_par(a, b, c_par, 2);
	multiply_matrix_par(a, b, c_par, 4);
	multiply_matrix_par(a, b, c_par, 8);


	for (int i = 0; i < N; i++) {
		delete[] a[i];
		delete[] b[i];
		delete[] c_seq[i];
		delete[] c_par[i];
	}
	delete[] a;
	delete[] b;
	delete[] c_seq;
	delete[] c_par;

	/*Sequential version: 19.5207 s
	  Parallel version with 2 threads: 7.86739 s
	  Parallel version with 4 threads: 4.76395 s
	  Parallel version with 8 threads: 3.2466 s*/

	cout << '\n' << endl;
}