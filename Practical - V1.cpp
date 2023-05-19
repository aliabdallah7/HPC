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

	int arr[150];
	if (rank == 0)
	{
		for (int i = 0; i < 150; i++)
		{
			arr[i] = i + 1;
		}
	}


	int processors[3] = { 0,0,0 };
	int localCount = 0;
	int local_arr[50];
	int generalCount = 0;

	MPI_Scatter(&arr, 50, MPI_INT, &local_arr, 50, MPI_INT, 0, MPI_COMM_WORLD);

	for (int j = 0; j < 50; j++)
	{
		if (local_arr[j] % 7 == 0)
			localCount++;
	}

	//MPI_Gather(&localCount, 1, MPI_INT, processors, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Reduce(&localCount, &generalCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		/*for (int j = 0; j < 3; j++)
			generalCount += processors[j];*/

		printf("The count of numbers divided by 7 is : %d", generalCount);

	}


	MPI_Finalize();
	return 0;
}