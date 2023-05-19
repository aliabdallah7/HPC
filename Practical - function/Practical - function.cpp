#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

double calculateMean(double* array, int size)
{
    double sum = 0;

    for (int i = 0; i < size; i++)
        sum += array[i];

    return sum / size;
}

double calculateLocalSum(double* array, int size, double mean)
{
    double localSum = 0;

    for (int i = 0; i < size; i++)
        localSum += (array[i] - mean) * (array[i] - mean);

    return localSum;
}

int main()
{
    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double N = 150;
    double* X = nullptr;
    double mean = 0;
    double localSum = 0;
    double globalSum = 0;
    double standardDeviation = 0;

    if (rank == 0) {
        // Only the root process initializes the array
        X = new double[N];
        for (int i = 0; i < N; i++) {
            X[i] = i + 1;
            mean += X[i];
        }
        mean /= N;
    }

    // Broadcast the mean to all processes
    MPI_Bcast(&mean, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Calculate the local sum of squared differences from the mean
    int localSize = N / size;
    double* localX = new double[localSize];
    MPI_Scatter(X, localSize, MPI_DOUBLE, localX, localSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    localSum = calculateLocalSum(localX, localSize, mean);
    delete[] localX;

    // Reduce the local sums to the root process
    MPI_Reduce(&localSum, &globalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        // Perform the final calculations on the root process
        for (int i = size * localSize; i < N; i++)
            globalSum += (X[i] - mean) * (X[i] - mean);

        // Calculate the standard deviation
        standardDeviation = sqrt(globalSum / (N - 1));

        // Print the result
        cout << "Standard Deviation: " << standardDeviation << endl;

        // Deallocate memory
        delete[] X;
    }

    MPI_Finalize();
    return 0;
}
