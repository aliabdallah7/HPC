#include <iostream>
#include <stdio.h>
#include <cmath>
#include "math.h"
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //On 4 processors

    float B = 0;
    float arr[16] = { 1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4 };
    float recv_arr[4];

    if (rank == 0)
    {
        cout << "Please enter the number" << endl;
        cin >> B;
    }

    MPI_Bcast(&B, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, 4, MPI_FLOAT, recv_arr, 4, MPI_FLOAT, 0, MPI_COMM_WORLD);


    for (int i = 0; i < 4; i++)
    {
        if (rank == 0)
            recv_arr[i] += B;
        else if (rank == 1)
            recv_arr[i] *= B;
        else if (rank == 2)
            recv_arr[i] -= B;
        else if (rank == 3)
            recv_arr[i] /= B;
    }

    float final_result[16];
    MPI_Gather(recv_arr, 4, MPI_FLOAT, final_result, 4, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << "The matrix result is : \n";

        for (int i = 0; i < 16; i++)
        {
            cout << final_result[i] << endl;
        }
    }

    MPI_Finalize();
    return 0;
}