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
    int localSize = 1000 / size;
    int loaclsum = 0;
    auto* localarr = new int[localSize];
    int sum = 0;


    if (rank == 0)
        for (int i = 0; i < 1000; i++)
            arr[i] = i + 1;


    MPI_Scatter(arr, localSize, MPI_INT, localarr, localSize, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < localSize; i++)
    {
        if (localarr[i] % 2 == 0)
            loaclsum += localarr[i] + 2;
        else
            loaclsum += localarr[i] - 1;
    }


    MPI_Reduce(&loaclsum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = localSize * size; i < 1000; i++)
        {
            if (arr[i] % 2 == 0)
            {
                arr[i] += 2;
            }
            else
            {
                arr[i] -= 1;
            }
            
            sum += arr[i];
        }

        printf("%d\n", sum);
    }


    MPI_Finalize();
    return 0;
}