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

    int data = 1;
    if (rank == 0)
    {
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Status stat;
        MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &stat);

        printf("Pong");
    }
    else if (rank == 1)
    {
        MPI_Status stat;
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);

        printf("Ping");

        MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
