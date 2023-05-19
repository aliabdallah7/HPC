#include <iostream>
#include <mpi.h>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int vector1[100], vector2[100];
    int recievedVector1[100], recievedVector2[100];
    int localsum = 0;
    int* localsums = new int[size];
    int finalResult = 0;

    for (int i = 0; i < 100; i++)
    {
        vector1[i] = 1;
        vector2[i] = 2;
    }

    MPI_Scatter(&vector1, 100 / size, MPI_INT, &recievedVector1, 100 / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&vector2, 100 / size, MPI_INT, &recievedVector2, 100 / size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int j = 0; j < 100 / size; j++)
    {
        localsum += recievedVector1[j] * recievedVector2[j];
    }

    MPI_Gather(&localsum, 1, MPI_INT, localsums, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int j = 0; j < size; j++)
        {
            finalResult += localsums[j];
        }
        for (int j = (100 / size) * size; j < 100; j++)
        {
            finalResult += vector1[j] * vector2[j];
        }
        printf("Dot Product v1 * v2 = % d", finalResult);
    }

    MPI_Finalize();
    return 0;
}