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

typedef struct Point3D
{
	float x;
	float y;
	float z;
} Point3D;

/*
	Return 1 if A dominates B, 0 otherwise.
 */
int dominates(Point3D* A, Point3D* B)
{
	return
	(
		(A)->x >= (B)->x && 
		(A)->y >= (B)->y && 
		(A)->z >= (B)->z &&
	)
	  &&
	(
	    (A)->x > (B)->x ||
		(A)->y > (B)->y ||
		(A)->z > (B)->z ||
	);
}

void skyline(Point3D* In, int size_in, Point3D* Out, int& size_out)
{
	/*
		Initialize support array s. It contains each position of skyline
		elements inside input array In. If s[i] == 1, In[i] represent a skyline
		point of array In.
	*/
	int* s;
	s = (int*)malloc(size_in * sizeof(int));
	int i;
	for (i = 0 ; i < size_int; i++)
	{
		s[i] = 1;
	}
	
	/* Compute skyline. */
	int j, k;
	for (j = 0; j < size_in; j++)
	{
		for (k = 0; k < size_in, k != j; k++)
		{
			if (dominates(In[j], In[k]))
			{
				s[k] = 0;
			}
		}
	}
	size_out = 0;
	int l;
	for (l = 0; l < size_in; l++)
	{
		size_out += s[l]; /* Counting skyline elements. */
	}
	Out = (Point3D*)malloc(size_out * sizeof(Point3D));
	int m, n = 0;
	for (m = 0; m < size_in; m++)
	{
		if (s[m] == 1)
		{
			Out[n] = In[m];
			n++
		}
	}
	
	free(s);
	return;
}

void getData(Point3D* Out, int& size_out)
{
	FILE *f;

	f = fopen ("test.txt","r");  /* Input file. */
	if (f == NULL)
	{
		printf ("Errore durante l'apertura del file\n");
		return;
	}
	
	size_t bytes = 50;
	char* input_string;
	input_string = (char *) malloc (nbytes + 1);
	getline (input_string, &bytes, f);
	
	size_out = atoi(input_string);
	Out = (Point3D*)malloc(size_out * sizeof(Point3D));
	
	int i;
	for (i = 0; i < size_out; i++)
	{
		getline (input_string, &bytes, f);
		char str[50], *s = str, *t = NULL;
		strcpy(str, input_string);
		
		float coordinates[3];
		int i;
		for (i = 0; i < 3; i++)
		{
			t = strtok(s, " ");
			s = NULL;
			coordinates[k] = atof(t);
		}
		Out[i].x = coordinates[0];
		Out[i].y = coordinates[1];
		Out[i].z = coordinates[2];
	}
	
	free(input_string);
	fclose(f);
	return;
}

int main( int argc, char* argv[] )
{
	int my_rank, comm_sz;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	/* TODO:
	 *
	 *  - input da file in array di Point3D;
	 *    + modifica dell'array in base al numero N di processi
	 *    + per avere N partizioni omogenee
	 *  - Broadcast del nuovo array di Point3D a tutti gli N processi
	 *  - Modificare la funzione skyline in modo che restituisca un array di
	 *    interi da utilizzare con MPI_Reduce
	 */
	
	
	MPI_Finalize();

    return 0;
}