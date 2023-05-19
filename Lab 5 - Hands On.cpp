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

	int data[15];
	int localsum = 0;
	int localdata[5];
	int sums[3] = { 0,0,0 };
	int sum = 0;

	if (rank == 0)
	{
		for (int i = 0; i < 15; i++)
			data[i] = i + 1;
		cout << "Data Generated.." << endl;
	}

	MPI_Scatter(&data, 5, MPI_INT, &localdata, 5, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < 5; i++)
		localsum += localdata[i];
	cout << "Localsum is : " << localsum << endl;

	MPI_Gather(&localsum, 1, MPI_INT, sums, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		for (int i = 0; i < 3; i++)
			sum += sums[i];
		cout << "Total Sum : " << sum << endl;
	}

	MPI_Finalize();
	return 0;
}