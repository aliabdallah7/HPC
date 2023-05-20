#include <iostream>
#include <stdio.h>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        int data[10] = { 1,2,3,4,5,6,7,8,9,10 };
        MPI_Send(&data, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1)
    {
        int data[10];
        
        MPI_Status x_status;
        MPI_Recv(&data, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, &x_status);
        
        cout << "Process 1 Recieve Array: " << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << data[i] << endl;
        }
    }
    MPI_Finalize();
    return 0;
}