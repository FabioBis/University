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
int dominates(float x_a, float y_a, float z_a, float x_b, float y_b, float z_b)
{
  return
	(
     x_a >= x_b &&
     y_a >= y_b &&
     z_a >= z_b
     )
    &&
	(
     x_a > x_b ||
     y_a > y_b ||
     z_a > z_b
     );
}

void skyline(float *x_in, float *y_in,float *z_in, int size_in,
             int *out, int *skyline_size)
{
  /*
    Initialize support array s. It contains each position of skyline
    elements inside input array In. If s[i] == 1, In[i] represent a skyline
    point of array In.
  */
  int i;
  for (i = 0 ; i < size_in; i++)
  {
    out[i] = 1;
  }

  /* Compute skyline. */
  int j, k;
  for (j = 0; j < size_in; j++)
  {
    for (k = 0; k < size_in; k++)
    {
      if (k != j)
      {
        if (dominates(x_in[j], y_in[j], z_in[j], x_in[k], y_in[k], z_in[k]))
          {
            out[k] = 0;
          }
      }
    }
  }
  *skyline_size = 0;
  int l;
  for (l = 0; l < size_in; l++)
  {
    *skyline_size += out[l]; /* Counting skyline elements. */
  }
  return;
}

void getDataSize(int *size_out)
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
  input_string = (char *) malloc (bytes + 1);
  getline(&input_string, &bytes, f);

  *size_out = atoi(input_string);
  free(input_string);
  fclose(f);
  return;
}

void getData(float *x_out, float *y_out, float *z_out, int size)
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
  input_string = (char *) malloc (bytes + 1);
  getline(&input_string, &bytes, f);

  int size_in = atoi(input_string);

  int i;
  for (i = 0; i < size; i++)
  {
    if (i < size_in)
    {
      getline(&input_string, &bytes, f);
      char str[50], *s = str, *t = NULL;
      strcpy(str, input_string);

      float coordinates[3];
      int j;
      for (j = 0; j < 3; j++)
      {
        t = strtok(s, " ");
        s = NULL;
        coordinates[j] = atof(t);
      }
      x_out[i] = coordinates[0];
      y_out[i] = coordinates[1];
      z_out[i] = coordinates[2];
    }
    else
    {
      x_out[i] = -FLT_MAX;
      y_out[i] = -FLT_MAX;
      z_out[i] = -FLT_MAX;
    }
  }

  free(input_string);
  fclose(f);
  return;
}

int main( int argc, char* argv[] )
{
  int my_rank, comm_sz, input_size, partition_size;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  int active_proc = comm_sz;

  MPI_Barrier(MPI_COMM_WORLD);

  if (my_rank == 0)
  {
    getDataSize(&input_size);
  }
  MPI_Bcast(&input_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

  printf("Process %d:\n", my_rank);  /* DBG */
  printf("Input size: %d.\n", input_size);  /* DBG */

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

  float x[actual_size];
  float y[actual_size];
  float z[actual_size];

  float local_x[partition_size];
  float local_y[partition_size];
  float local_z[partition_size];

  if (my_rank == 0)
  {
    getData(x, y, z, actual_size);
  }
  MPI_Scatter(x, partition_size, MPI_FLOAT, local_x, partition_size, MPI_FLOAT,
              0, MPI_COMM_WORLD);
  MPI_Scatter(y, partition_size, MPI_FLOAT, local_y, partition_size, MPI_FLOAT,
              0, MPI_COMM_WORLD);
  MPI_Scatter(z, partition_size, MPI_FLOAT, local_z, partition_size, MPI_FLOAT,
              0, MPI_COMM_WORLD);

  /* DBG */
  printf("Process %d:\n", my_rank);
  int i;
  for (i = 0; i < partition_size; i++)
  {
    printf("P%d[%d] = <%f, %f, %f>\n", my_rank, i, local_x[i], local_y[i],
           local_z[i]);
  }
  /* DBG */

  MPI_Finalize();

  return 0;
}
