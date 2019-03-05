#include <cstdio>
#include <cmath>
const int k=10;
const int n=2*k+1;
const long long max_val = (1<<n);
double coefficients[n+1];

long long val=0;
int count_1_bits(int bitmask)
{
  return __builtin_popcount(bitmask);
}

int main()
{
  /*** Find coefficients ***/
  for ( int i=0;i<=n;i++)
  {
    int num_mask = (1<<i)-1;
    for ( long long val=0;val<max_val;val++)
    {
      int f_val = count_1_bits(val) > k? -1 : 1;
      coefficients[i]+= f_val * ( count_1_bits (num_mask & val )%2 ? -1 : 1 );
    }
  }
  for ( int i=0;i<=n;i++)
  {
    coefficients[i] /= max_val;
  }
  for ( int i=0;i<=n;i++)
    printf("i: %d, coeff: %lf\n",i,coefficients[i]);
 

  /* Check correctness of computations */
  for ( int i=0;i<=n;i++)
  {
    int num_mask = (1<<i)-1;
    double result =0;
    for ( long long val=0;val<max_val;val++)
    {
      int no_bits = count_1_bits(val);
      result+= coefficients[no_bits] * ( count_1_bits (num_mask & val )%2 ? -1 : 1 );
    }
    printf("Check %d : %lf\n",i,result);
  }

  // L^2 distance
  printf("\nL^2 distances: \n\n");
  for ( int d=0;d<=n;d++)
  {
    double L2=0;
    for ( int i=d+1;i<=k;i++)
      L2 += coefficients[i]*coefficients[i];
    L2 = sqrt(L2);
    printf("%d %lf\n",d,L2);
  }
  
  printf("\n\n");
  
  /* Check correctness of computations */
  for ( int dd=0;dd<=2*k+1;dd++)
  {
    double local_max=0;
    for ( int i=0;i<=n;i++)
    {
      int num_mask = (1<<i)-1;
      double result =0;
      for ( long long val=0;val<max_val;val++)
      {
        int no_bits = count_1_bits(val);
        if ( no_bits > dd )
          continue;
        result+= coefficients[no_bits] * ( count_1_bits (num_mask & val )%2 ? -1 : 1 );
      }
      // printf("Check %d : %lf\n",i,result);
      if ( result > local_max) local_max= result;
    }
    printf("%d %lf\n",dd,local_max);
  }

  return 0;
}
