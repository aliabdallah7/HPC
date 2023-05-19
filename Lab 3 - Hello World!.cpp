#include <iostream>
#include <stdio.h>
#include <mpi.h>

using namespace std;
int main(int argc, char** argv)
{
	MPI_Init(NULL, NULL);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	char name[MPI_MAX_PROCESSOR_NAME];
	int nameLength;
	MPI_Get_processor_name(name, &nameLength);

	printf("Hello world from processor %s, rank %d out of %d processors\n",
		name, rank, size);

	MPI_Finalize();
	return 0;
}