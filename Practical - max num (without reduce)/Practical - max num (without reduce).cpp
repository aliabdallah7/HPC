#include <iostream>
#include <mpi.h>

using namespace std;

int main()
{
    //On 4 processors 
    MPI_Init(NULL, NULL);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    int arr[200], recvarr[50], processors[4];

    if (rank == 0)
        for (int i = 0; i < 200; i++)
            arr[i] = i + 1;

    MPI_Scatter(arr, 50, MPI_INT, recvarr, 50, MPI_INT, 0, MPI_COMM_WORLD);

    int max = 0;

    for (int i = 0; i < 50; i++)
        if (recvarr[i] > max)
            max = recvarr[i];


    MPI_Gather(&max, 1, MPI_INT, processors, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int final_max = 0;

    if (rank == 0)
    {
        for (int i = 0; i < 4; i++)
            if (processors[i] > final_max)
                final_max = processors[i];

        cout << "Max number in the array is : " << final_max << endl;
    }

    MPI_Finalize();
    return 0;
}
