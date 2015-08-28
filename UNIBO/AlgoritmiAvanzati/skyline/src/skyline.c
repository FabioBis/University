/*
 *  Nome: Fabio
 *  Cognome: Biselli
 *	Matricola: 0000734326
 *	e-mail: fabio.biselli@studio.unibo.it
 *
 *  Load mpi (Fedora 18): module load mpi/openmpi-$(uname -i)
 *	Compile: mpicc -Wall skyline.c -o skyline
 *	Run: mpirun -n <N> ./skyline
 */

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <time.h>

/*
 *  Given two points: A(x_a, y_a, z_a) and B(x_b, y_b, z_b), returns 1
 *  iff A dominates B, 0 otherwise.
 */
int dominates(float x_a, float y_a, float z_a, float x_b, float y_b, float z_b)
{
  return (x_a >= x_b && y_a >= y_b && z_a >= z_b)
    && ( x_a > x_b || y_a > y_b || z_a > z_b);
}


void skyline(float *x_in, float *y_in,float *z_in, long int size_in,
             int *out, long int *skyline_size)
{
  long int i;
  for (i = 0 ; i < size_in; i++)
  {
    out[i] = 1;
  }

  /* Compute skyline. */
  long int j, k;
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
  long int l;
  for (l = 0; l < size_in; l++)
  {
    *skyline_size += out[l]; /* Counting skyline elements. */
  }
  return;
}


void getDataSize(long int *size_out)
{
  FILE *f;

  f = fopen ("in.txt","r");  /* Input file. */
  if (f == NULL)
  {
    printf ("Open file error.\n");
    return;
  }

  size_t bytes = 50;
  char* input_string;
  input_string = (char *) malloc (bytes + 1);
  getline(&input_string, &bytes, f);

  *size_out = strtol(input_string, NULL, 10);
  free(input_string);
  fclose(f);
  return;
}


void getData(float *x_out, float *y_out, float *z_out)
{
  FILE *f;

  f = fopen ("in.txt","r");  /* Input file. */
  if (f == NULL)
  {
    printf ("Open file error.\n");
    return;
  }

  size_t bytes = 50;
  char* input_string;
  input_string = (char *) malloc (bytes + 1);
  getline(&input_string, &bytes, f);

  long int size_in = strtol(input_string, NULL, 10);

  long int i;
  for (i = 0; i < size_in; i++)
  {
    getline(&input_string, &bytes, f);
    char str[50], *s = str, *t = NULL;
    strcpy(str, input_string);

    float coordinates[3];
    long int j;
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

  free(input_string);
  fclose(f);
  return;
}


void saveData(float *x_out, float *y_out, float *z_out, long int size)
{
  FILE *f;

  f = fopen ("out.txt","w");  /* Output file. */
  if (f == NULL)
  {
    printf ("Open file error.\n");
    return;
  }

  fprintf(f, "%lu\n", size);
  long int i;
  for (i = 0; i < size; i++)
  {
    fprintf(f, "%f %f %f\n", x_out[i], y_out[i], z_out[i]);
  }

  fclose(f);
  return;
}


/*
 *  Main program.
 */
int main( int argc, char* argv[] )
{
  int my_rank, comm_sz;
  long int input_size, partition_size;
  double time_start0, time_stop0, time_start1, time_stop1,
    time_start2, time_stop2, total_time = 0.0;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

  MPI_Barrier(MPI_COMM_WORLD);

  if (my_rank == 0)
  {
    getDataSize(&input_size);
    time_start0 = MPI_Wtime(); /* T0: broadcast time. */
  }
  /* Broadcast data size to all processes. */
  MPI_Bcast(&input_size, 1, MPI_LONG, 0, MPI_COMM_WORLD);

  partition_size = input_size / comm_sz;

  float x[input_size];
  float y[input_size];
  float z[input_size];

  float local_x[partition_size];
  float local_y[partition_size];
  float local_z[partition_size];

  if (my_rank == 0)
  {
    time_stop0 = MPI_Wtime();
    getData(x, y, z);
  }

  /* Phase 1: qualify tournament. */
  time_start1 = MPI_Wtime(); /* T1: computation time. */

  /* Distribution of partitioned data among processes. */
  MPI_Scatter(x, partition_size, MPI_FLOAT,
              local_x, partition_size, MPI_FLOAT,
              0, MPI_COMM_WORLD);
  MPI_Scatter(y, partition_size, MPI_FLOAT,
              local_y, partition_size, MPI_FLOAT,
              0, MPI_COMM_WORLD);
  MPI_Scatter(z, partition_size, MPI_FLOAT,
              local_z, partition_size, MPI_FLOAT,
              0, MPI_COMM_WORLD);

  /* Computing local skyline support array. */
  int local_skyline[partition_size];
  long int local_skyline_size;
  int *actual_skyline;
  skyline(local_x, local_y, local_z, partition_size,
          local_skyline, &local_skyline_size);

  if (my_rank == 0)
  {
    actual_skyline = (int *)malloc(input_size*sizeof(int));
  }
  /* Gathering the computed data on server process (rank 0). */
  MPI_Gather(local_skyline, partition_size, MPI_INT,
             actual_skyline, partition_size, MPI_INT,
             0, MPI_COMM_WORLD);

  /* Computing the number of  winners. */
  long int actual_skyline_size;
  MPI_Reduce(&local_skyline_size, &actual_skyline_size, 1, MPI_LONG, MPI_SUM,
             0, MPI_COMM_WORLD);


  /* Computing the elapsed time of phase 1. */
  time_stop1 = MPI_Wtime();
  double local_elapse = time_stop1 - time_start1;
  MPI_Reduce(&local_elapse, &total_time, 1, MPI_DOUBLE, MPI_MAX,
             0, MPI_COMM_WORLD);

  if (my_rank == 0)
  {
    /* Phase 2: Final tournament. */
    time_start2 = MPI_Wtime(); /* T2: final round time. */

    actual_skyline_size += input_size % comm_sz;
    float x_tmp[actual_skyline_size];
    float y_tmp[actual_skyline_size];
    float z_tmp[actual_skyline_size];
    long int global_index = input_size - 1;
    long int tmp_index = actual_skyline_size - 1;
    long int limit = partition_size * comm_sz - 1;

    for(; global_index > limit; global_index--)
    {
      /* If we have some remanents points to check, we put them
         at the end the buffers for the 'final round'. */
      actual_skyline[global_index] = 0;
      x_tmp[tmp_index] = x[global_index];
      y_tmp[tmp_index] = y[global_index];
      z_tmp[tmp_index] = z[global_index];
      tmp_index--;
    }
    long int i, tmp_size = 0;
    for (i = 0; i < input_size; i++)
    {
      if (actual_skyline[i] == 1)
      {
        x_tmp[tmp_size] = x[i];
        y_tmp[tmp_size] = y[i];
        z_tmp[tmp_size] = z[i];
        tmp_size++;
      }
    }

    int skyline_tmp[tmp_size];
    long int skyline_size;
    skyline(x_tmp, y_tmp, z_tmp, tmp_size, skyline_tmp, &skyline_size);
    float x_skyline[skyline_size];
    float y_skyline[skyline_size];
    float z_skyline[skyline_size];
    long int j = 0;
    for (i = 0; i < tmp_size; i++)
    {
      if (skyline_tmp[i] == 1)
      {
        x_skyline[j] = x_tmp[i];
        y_skyline[j] = y_tmp[i];
        z_skyline[j] = z_tmp[i];
        j++;
      }
    }
    time_stop2 = MPI_Wtime();

    total_time += time_stop0 - time_start0 + time_stop2 - time_start2;

    /* Saving and Printing results. */
    printf("Time: %f\n", total_time);
    saveData(x_skyline, y_skyline, z_skyline, skyline_size);

    free(actual_skyline);
  }

  MPI_Finalize();

  return 0;
}
