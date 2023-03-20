#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // Check if all arguments are passed
    if (argc != 4) {
        printf("Usage: ./program rows cols output_file_name\n");
        return 1;
    }
    
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    char *output_file_name = argv[3];

    // Set the seed for random number generation
    srand(18050111002);

    // Allocate memory for matrix
    double **matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double *)calloc(cols, sizeof(double));
    }

    // Fill the matrix with random values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (double)(rand() % 10000 + 1) / 100.0; // random value between [1.0 - 100.0]
        }
    }

    // Create a random vector
    double *vector = (double *)malloc(cols * sizeof(double));
    for (int i = 0; i < cols; i++) {
        vector[i] = (double)(rand() % 10000 + 1) / 100.0; // random value between [1.0 - 100.0]
    }

    // Perform matrix-vector multiplication
    double *result = (double *)calloc(rows, sizeof(double));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    // Write the result to the output file
    FILE *fp = fopen(output_file_name, "w");
    if (fp == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        fprintf(fp, "%lf\n", result[i]);
    }
    fclose(fp);

    // Free memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    return 0;
}
