/*
 *  Nome: Fabio
 *  Cognome: Biselli
 *	Matricola: 0000734326
 *	e-mail: fabio.biselli@studio.unibo.it
 *
 *  Load mpi: module load mpi/openmpi-$(uname -i)
 *	***Compile: gcc -Wall serial_skyline.c -o serial_skyline -lrt
 *	Compile: mpicc -Wall serial_skyline.c -o serial_skyline
 *	Run: mpirun -n <N> ./serial_skyline
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


int dominates(float x_a, float y_a, float z_a, float x_b, float y_b, float z_b)
{
  return (x_a >= x_b && y_a >= y_b && z_a >= z_b)
    && ( x_a > x_b || y_a > y_b || z_a > z_b);
}

void skyline(float *x_in, float *y_in,float *z_in, int size_in,
             int *out, int *skyline_size)
{
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

  f = fopen ("in.txt","r");  /* Input file. */
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

  f = fopen ("in.txt","r");  /* Input file. */
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

void saveData(float *x_out, float *y_out, float *z_out, int size)
{
  FILE *f;

  f = fopen ("out.txt","w");  /* Output file. */
  if (f == NULL)
  {
    printf ("Errore durante l'apertura del file\n");
    return;
  }

  fprintf(f, "%d\n", size);
  int i;
  for (i = 0; i < size; i++)
  {
    fprintf(f, "%f %f %f\n", x_out[i], y_out[i], z_out[i]);
  }

  fclose(f);
  return;
}

int main( int argc, char* argv[] )
{
  int comm_sz, input_size, partition_size;
  struct timespec start, stop;
  int c;

  while ((c = getopt(argc, argv, "n:")) != -1)
  {
    switch(c)
      {
      case 'n':
        comm_sz = atoi(optarg);
        if (comm_sz < 1)
          {
            abort();
          }
        break;
      default:
        abort();
      }
  }

  getDataSize(&input_size);

  partition_size = input_size / comm_sz;

  float x[input_size];
  float y[input_size];
  float z[input_size];
  getData(x, y, z, input_size);

  int actual_skyline[input_size];

  float local_x[comm_sz][partition_size];
  float local_y[comm_sz][partition_size];
  float local_z[comm_sz][partition_size];

  int i, j, index = 0;
  for (i = 0; i < comm_sz; i++)
  {
    for (j = 0; j < partition_size; j++)
    {
      local_x[i][j] = x[index];
      local_y[i][j] = y[index];
      local_z[i][j] = z[index];
      index++;
    }
  }

  for (i = 0; i < input_size; i++)
  {
    actual_skyline[i] = 1;
  }

  if (clock_gettime(CLOCK_REALTIME, &start) == -1)
  {
    perror( "clock gettime" );
    exit( EXIT_FAILURE );
  }

  int k;
  for (i = 1; i <= comm_sz; i++)
  {
    for (j = 1; j <= partition_size; j++)
    {
      for (k = 1; k <= partition_size; k++)
      {
        if (dominates(local_x[i-1][j-1], local_y[i-1][j-1], local_z[i-1][j-1],
                      local_x[i-1][k-1], local_y[i-1][k-1], local_z[i-1][k-1]))
        {
          actual_skyline[(i-1)*partition_size + k - 1] = 0;
        }
      }
    }
  }

  int tmp_skyline_size = 0;
  for (i = 0; i < input_size; i++)
  {
    tmp_skyline_size += actual_skyline[i]; /* Counting skyline elements. */
  }

  float x_tmp[tmp_skyline_size];
  float y_tmp[tmp_skyline_size];
  float z_tmp[tmp_skyline_size];
  int tmp_size = 0;
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
  int skyline_size;
  skyline(x_tmp, y_tmp, z_tmp, tmp_size, skyline_tmp, &skyline_size);
  float x_skyline[skyline_size];
  float y_skyline[skyline_size];
  float z_skyline[skyline_size];
  j = 0;
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

  double total_time;
  if (clock_gettime(CLOCK_REALTIME, &stop) == -1)
  {
    perror( "clock gettime" );
    exit( EXIT_FAILURE );
  }

  total_time = (stop.tv_sec - start.tv_sec)
    + (stop.tv_nsec - start.tv_nsec)
    / 1000000000.0;

  /* Saving and Printing results. */
  printf("Time: %f\n", total_time);
  saveData(x_skyline, y_skyline, z_skyline, skyline_size);

  return 0;
}
