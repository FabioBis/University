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
#include <float.h>
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

void getDataSize(int &size_out)
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
}

void getData(Point3D* Out, int size)
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
	
	size_in = atoi(input_string);
	
	int i;
	for (i = 0; i < size; i++)
	{
		if (i < size_in)
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
		else
		{
			Out[i].x = -FLT_MAX;
			Out[i].y = -FLT_MAX;
			Out[i].z = -FLT_MAX;
		}
	}
	
	free(input_string);
	fclose(f);
	return;
}

int main( int argc, char* argv[] )
{
	int my_rank, comm_sz, input_size, partition_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	int active_proc = comm_sz; 
	
	if (my_rank == 0)
	{
		getDataSize(input_size);
	}
	MPI_Bcast(input_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	int actual_size, part_tag = 0;
	if (input_size % comm_sz == 0)
	{
		partition_size = input_size / comm_sz;
		actual_size = input_size;
	}
	else
	{
		partition_size = input_size / comm_sz + 1;
		if (partition_size * (comm_sz + 1) == input_size)
		{
			part_tag = 1;
			active_proc -=1;
		}
		else
		{
			part_tag = 2;
		}
		actual_size = partition_size * comm_sz;
	}
	
	Point3D partition_set[partition_size];
	
	MPI_Datatype Point3Dstruct, Point3Dtype;
	MPI_Datatype type[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE};
	int blocklen[3] = {1, 1, 1};
	MPI_Aint disp[3];
	MPI_Aint base, lb, sizeofentry;
	MPI_Get_address(partition_set, disp);
	MPI_Get_address(partition_set[0].x, disp+1);
	MPI_Get_address(partition_set[0].z, disp+2);
	base = disp[0];
	for (i=0; i < 3; i++) disp[i] = MPI_Aint_diff(disp[i], base);
	
	MPI_Type_create_struct(3, blocklen, disp, type, &Point3Dstruct);
	
	MPI_Get_address(partition_set+1, &sizeofentry);
	sizeofentry = MPI_Aint_diff(sizeofentry, base);
	MPI_Type_create_resized(Point3Dstruct, 0, sizeofentry, &Point3Dtype);
	MPI_Type_commit(&Point3Dtype);
	
	Point3D actual_set[actual_size];
	if ((my_rank == 0)
	{
		getData(actual_set, actual_size);
	}	
	MPI_Scatter(
		actual_set, actual_size, Point3Dtype,
		partition_set, partition_size, Point3Dtype,
		0, MPI_COMM_WORLD);
	
	/* DBG */
	printf("Process %d:\n", my_rank);	
	for (int i = 0; i < partition_size; i++)
	{
		printf("P[%d]= <%f, %f, %f>\n", i, partition_set[i].x,
			partition_set[i].y, partition_set[i].z);		
	}
	/* DBG */
	
	MPI_Finalize();

    return 0;
}