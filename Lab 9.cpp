#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    int N;
    if (rank == 0)
    {
        printf("Please Enter the N value : \n");
        cin >> N;
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int* arr = new int[N];
    int* local_arr = new int[N / size];

    if (rank == 0)
        for (int i = 0; i < N; i++)
            arr[i] = i;


    MPI_Scatter(arr, N / size, MPI_INT, local_arr, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    double local_sum = 0;
    for (int i = 0; i < N / size; i++)
    {
        double x = (local_arr[i] - 0.5) / N;
        local_sum += 1 / (1 + x * x);
    }

    double final_result = 0;
    MPI_Reduce(&local_sum, &final_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        final_result = (4 * final_result) / N;
        cout << "Pi = " << final_result;
    }

    MPI_Finalize();
    return 0;
}
