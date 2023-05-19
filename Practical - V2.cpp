#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv)
{
    //On 3 processors "-n 3"
    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int arr[150];
    int N;

    if (rank == 0)
    {
        for (int i = 0; i < 150; i++)
            arr[i] = i;

        printf("Enter the N\n");
        cin >> N;
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int recvbuf[50];

    MPI_Scatter(arr, 50, MPI_INT, recvbuf, 50, MPI_INT, 0, MPI_COMM_WORLD);


    int found = 0;
    int The_rank = 0;
    int x = 1;

    for (int i = 0; i < 50; i++)
    {
        if (N == recvbuf[i])
        {
            if (rank == 0)
                x = 0;
            found = rank;
        }
    }

    MPI_Reduce(&found, &The_rank, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        if (The_rank != 0 || x == 0)
            printf("The rank is : %d", The_rank);
        else
            printf("-1");
    }



    MPI_Finalize();
    return 0;
}
