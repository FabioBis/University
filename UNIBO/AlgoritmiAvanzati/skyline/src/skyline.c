/*
 *  Nome: Fabio
 *  Cognome: Biselli
 *	Matricola: 0000734326
 *	e-mail: fabio.biselli@studio.unibo.it
 *	
 *	Compile: mpicc -Wall skyline.c -o skyline
 *	Run: 
 */

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

int main( int argc, char* argv[] )
{
	int my_rank, comm_sz;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	/* TODO */
	
	MPI_Finalize();

    return 0;
}