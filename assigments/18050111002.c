/*
Matrix-vector multiplication is implemented using parallel programming in this program. 
The mpi.h library of OpenMPI is used for the implementation

The author of this program is Ertuğrul Çınar, and the student ID is 18050111002.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MASTER_RANK 0

// Function to print the matrix
void print_matrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to print the vector
void print_vector(double *vector, int size) {
    for (int i = 0; i < size; i++) {
        printf("%lf ", vector[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Initialize MPI
    int num_procs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Check if all arguments are passed
    if (argc != 4) {
        if (rank == MASTER_RANK) {
            printf("Usage: mpirun -n <num_procs> %s rows cols output_file_name\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    char *output_file_name = argv[3];

    // Set the seed for random number generation
    srand(18050111002);

    // Create a large matrix
    int large_size = rank % 10000;
    double **large_matrix = (double **)malloc(large_size * sizeof(double *));
    for (int i = 0; i < large_size; i++) {
        large_matrix[i] = (double *)calloc(large_size, sizeof(double));
    }

    // Fill the large matrix with random values
    for (int i = 0; i < large_size; i++) {
        for (int j = 0; j < large_size; j++) {
            large_matrix[i][j] = (double)(rand() % 10000 + 1) / 100.0; // random value between [1.0 - 100.0]
        }
    }

    // Create a small matrix
    int small_size = 100 + (rank % 100);
    double **small_matrix = (double **)malloc(small_size * sizeof(double *));
    for (int i = 0; i < small_size; i++) {
        small_matrix[i] = (double *)calloc(small_size, sizeof(double));
    }

    // Fill the small matrix with random values
    for (int i = 0; i < small_size; i++) {
        for (int j = 0; j < small_size; j++) {
            small_matrix[i][j] = (double)(rand() % 10000 + 1) / 100.0; // random value between [1.0 - 100.0]
        }
    }

    // Create a random vector
    double *vector = (double *)malloc(cols * sizeof(double));
    for (int i = 0; i < cols; i++) {
        vector[i] = (double)(rand() % 10000 + 1) / 100.0; // random value between [1.0 - 100.0]
    }

    // Perform matrix-vector multiplication using the large matrix
    double *large_result = (double *)calloc(large_size, sizeof(double));
    double large_start_time = MPI_W

// Perform matrix-vector multiplication
    double *result = (double *)calloc(rows, sizeof(double));
    double *local_result = (double *)calloc(local_rows, sizeof(double));
    for (int i = 0; i < local_rows; i++) {
        for (int j = 0; j < cols; j++) {
            local_result[i] += local_matrix[i][j] * vector[j];
        }
    }

    // Gather the results to the root process
    MPI_Gather(local_result, local_rows, MPI_DOUBLE, result, local_rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Write the result to the output file
    if (rank == 0) {
        FILE *fp = fopen(output_file_name, "w");
        if (fp == NULL) {
            printf("Failed to open file for writing.\n");
            return 1;
        }
        for (int i = 0; i < rows; i++) {
            fprintf(fp, "%lf\n", result[i]);
        }
        fclose(fp);
    }

    // Free memory
    for (int i = 0; i < local_rows; i++) {
        free(local_matrix[i]);
    }
    free(local_matrix);
    free(local_result);
    free(vector);
    free(result);

    MPI_Finalize();

    return 0;
}
