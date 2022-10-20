// GABRIEL LEITE - 22.219.028-2
#include <mpi.h>
#include <stdio.h>

int myrank, numprocs;

int main(int argc, char **argv) 
{
  int node;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &node);

  printf("Processo %d\n",node);

  float maioral;

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Barrier(MPI_COMM_WORLD);  
  

  if (myrank == 0) 
  {
   	float data[12] = {1,2,3,4,55.3,6,7,8,9,10,11,12};
    float recv[4];
   	
    MPI_Scatter (
      data,
      4,
      MPI_FLOAT,
      recv,
      4,
      MPI_FLOAT,
      0,
      MPI_COMM_WORLD
    );

    int resp = 50;
    float x;
    
    float maiorLocal;

    int i;
		maiorLocal = recv[0];
		for (i = 0; i < 4; ++i)
    {
			if (recv[i] > maiorLocal)
      {
				maiorLocal = recv[i];
      }
		}

		printf ("\nProcesso(%d) > Recebi: ", myrank);
    printf ("%f,", recv[0]);
    printf ("%f,", recv[1]);
    printf ("%f,", recv[2]);
    printf ("%f\n", recv[3]);
    printf ("\nProcesso(%d) > Maior Local: %f", myrank, maiorLocal);

    MPI_Reduce(
    &maiorLocal,	
    &maioral, 
    1,					
    MPI_FLOAT,		
    MPI_MAX,			
    0,						
    MPI_COMM_WORLD);

    printf ("\n\n\n\n O MAIORAL: %f\n\n\n", maioral);
    
  } 
  else
  {
    float recv[4];

    float x;
    
    MPI_Scatter (
      &x,
      4,
      MPI_FLOAT,
      recv,
      4,
      MPI_FLOAT,
      0,
      MPI_COMM_WORLD
    );

    float maiorLocal;
    float maioral;

    int i;
		maiorLocal = recv[0];
		for (i = 0; i < 4; ++i)
    {
			if (recv[i] > maiorLocal)
      {
				maiorLocal = recv[i];
      }
		}

    

		

    printf ("\nProcesso(%d) > Recebi: ", myrank);
    printf ("%f,", recv[0]);
    printf ("%f,", recv[1]);
    printf ("%f,", recv[2]);
    printf ("%f\n", recv[3]);
    printf ("\nProcesso(%d) > Maior Local: %f", myrank, maiorLocal);

    MPI_Reduce(
    &maiorLocal,	
    &maioral, 
    1,						
    MPI_FLOAT,	
    MPI_MAX,			
    0,						
    MPI_COMM_WORLD);
    
  }


  MPI_Finalize();

  return 0;
}
// MPI SCATTER REDUCE - PRONTO FUNCIONA