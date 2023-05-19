#include <iostream>
#include <stdio.h>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
    //On 3 processors
    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        int data[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
        MPI_Send(&data[5], 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&data[10], 5, MPI_INT, 2, 0, MPI_COMM_WORLD);
        int localsum = 0;
        for (int i = 0; i < 5; i++) {
            localsum += data[i];
        }
        MPI_Status x_status;
        int sum1, sum2;
        MPI_Recv(&sum1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &x_status);
        MPI_Recv(&sum2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &x_status);
        cout << "localsum : " << localsum << endl;
        cout << "sum1 : " << sum1 << endl;
        cout << "sum2 : " << sum2 << endl;
        cout << "Process 0 Total sum Array:" << localsum + sum1 + sum2 << endl;
    }
    else if (rank == 1 || rank == 2)
    {
        int data[5];
        MPI_Status x_status;
        MPI_Recv(&data, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, &x_status);
        int localsum = 0;
        for (int i = 0; i < 5; i++)
        {
            localsum += data[i];
        }
        MPI_Send(&localsum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }
    MPI_Finalize();
    return 0;
}