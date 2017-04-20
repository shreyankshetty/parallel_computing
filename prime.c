# include <stdlib.h>
# include <stdio.h>
# include <omp.h>

int main ( int argc, char *argv[] );
void pns ( int low, int high, int factor );
int primeNumber ( int n );


int main ( int argc, char *argv[] )


{
  int factor;
  int high;
  int low;

  printf ( "\n" );
  printf ( "PRIME_OPENMP\n" );
  printf ( "  C/OpenMP version\n" );

  printf ( "\n" );
  printf ( "  Number of processors available = %d\n", omp_get_num_procs ( ) );
  printf ( "  Number of threads =              %d\n", omp_get_max_threads ( ) );

  low = 1;
  high = 131072;
  factor = 2;

  pns ( low, high, factor );

  low = 5;
  high = 500000;
  factor = 10;

  pns ( low, high, factor );

  printf ( "\n" );
  printf ( "PRIME_OPENMP\n" );
  printf ( "  Normal end of execution.\n" );

  return 0;
}


void pns ( int low, int high, int factor )


{
  int i;
  int n;
  int primes;
  double wtime;

  printf ( "\n" );
  printf ( "TEST01\n" );
  printf ( "  Call primeNumber to count the primes from 1 to N.\n" );
  printf ( "\n" );
  printf ( "         N        Pi          Time\n" );
  printf ( "\n" );

  n = low;

  while ( n <= high )
  {
    wtime = omp_get_wtime ( );

    primes = primeNumber ( n );

    wtime = omp_get_wtime ( ) - wtime;

    printf ( "  %8d  %8d  %14f\n", n, primes, wtime );

    n = n * factor;
  }
 
  return;
}

int primeNumber ( int n )


{
  int i;
  int j;
  int prime;
  int total = 0;

# pragma omp parallel \
  shared ( n ) \
  private ( i, j, prime )
  

# pragma omp for reduction ( + : total )
  for ( i = 2; i <= n; i++ )
  {
    prime = 1;

    for ( j = 2; j < i; j++ )
    {
      if ( i % j == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }

  return total;
}
