#include <iostream>
#include <stdio.h>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
    //Run on number of the processors that divide the value of N only

    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N, B;

    if (rank == 0)
    {
        cout << "Please enter N : " << endl;
        cin >> N;

        cout << "Please enter B : " << endl;
        cin >> B;
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int* arr = new int[N];
    int* recv_arr = new int[N / size];

    if (rank == 0)
        for (int i = 0; i < N; i++)
            arr[i] = i + 1;


    MPI_Scatter(arr, (N / size), MPI_INT, recv_arr, (N / size), MPI_INT, 0, MPI_COMM_WORLD);


    for (int i = 0; i < N / size; i++)
    {
        recv_arr[i] += B;
    }

    int* final_result = new int[N];

    MPI_Gather(recv_arr, (N / size), MPI_INT, final_result, (N / size), MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << "The matrix result is : \n";

        for (int i = 0; i < N; i++)
        {
            cout << final_result[i] << endl;
        }
    }

    MPI_Finalize();
    return 0;
}