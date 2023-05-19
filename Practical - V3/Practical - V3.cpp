#include <iostream>
#include <stdio.h>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr[1000];
    int localarr[250];
    int loaclsum = 0;
    int sum = 0;


    if (rank == 0)
        for (int i = 0; i < 1000; i++)
            arr[i] = i + 1;

    //On 4 processors
    MPI_Scatter(&arr, 250, MPI_INT, &localarr, 250, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < 250; i++)
    {
        if (localarr[i] % 2 == 0)
            loaclsum += localarr[i] + 2;
        else
            loaclsum += localarr[i] - 1;
    }


    MPI_Reduce(&loaclsum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("%d\n", sum);


    MPI_Finalize();
    return 0;
}