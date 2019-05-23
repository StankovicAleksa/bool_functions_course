#include <cstdio>
#include <cmath>
const int k=10;
const int n=2*k+1;
const long long pow_n= (1<<n);
double coefficients[n+1];

long long pascal[n+1][n+1];

long long val=0;
int count_1_bits(int bitmask)
{
  return __builtin_popcount(bitmask);
}
void build_pascal()
{
  pascal[0][0]=1;
  for ( int i=0;i<=n;i++)
  {
    for ( int j=0;j<=i;j++)
    {
      pascal[i+1][j]+=pascal[i][j];
      pascal[i+1][j+1]+=pascal[i][j];
    }
  }
}
int main()
{

  build_pascal();
  /*** Find coefficients ***/
  for ( int i=0;i<=n;i++)
  {
    int num_mask = (1<<i)-1;
    for ( long long input=0;input<pow_n;input++)
    {
      int f_val = count_1_bits(input) > k? -1 : 1;
      coefficients[i]+= f_val * ( count_1_bits (num_mask & input)%2 ? -1 : 1 );
    }
  }
  for ( int i=0;i<=n;i++)
    coefficients[i] /= pow_n;

  for ( int i=0;i<=n;i++)
    printf("i: %d, coeff: %lf\n",i,coefficients[i]);
 
  /* Check correctness of computations */
  double sm=0;
  for ( int i=0;i<=n;i++)
  {
    int input = (1<<i)-1;
    double result =0;
    for ( long long fourier_coeff_ind=0;fourier_coeff_ind<pow_n;fourier_coeff_ind++)
    {
      int no_bits = count_1_bits(fourier_coeff_ind);
      double fourier_coefficient = coefficients[no_bits];
      result+= fourier_coefficient * ( count_1_bits (input & fourier_coeff_ind)%2 ?  -1 : 1 );
      sm+= fourier_coefficient*fourier_coefficient;
    }
    printf("Check %d : %lf\n",i,result);
  }
  // L^2 distance
  
  printf("\nL^2 distances: \n\n");
  for ( int d=0;d<=n;d++)
  {
    double L2=0;
    for ( int i=d;i<=n;i++)
    {
      //L2 += pascal[n][d] * coefficients[i]*coefficients[i];
      L2 += pascal[n][i]* coefficients[i]*coefficients[i];
    }

    L2 = sqrt(L2);
    printf("%d %lf\n",d,L2);
  }
  
  printf("\n\n");
  
  /* Check correctness of computations */
  for ( int dd=0;dd<=2*k+1;dd++)
  {
    if ( dd %2 == 0 ) 
      continue;

    double local_max=0;
    for ( int i=0;i<=n;i++)
    {
      int input = (1<<i)-1;
      double result =0;
      for ( long long fourier_coeff_ind=0;fourier_coeff_ind<pow_n;fourier_coeff_ind++)
      {
        int no_bits = count_1_bits(fourier_coeff_ind);

        if ( no_bits >= dd )
          continue;
        double fourier_coefficient = coefficients[no_bits];
        result+= fourier_coefficient * ( count_1_bits (input & fourier_coeff_ind)%2 ?  -1 : 1 );
      }
      // printf("Check %d : %lf\n",i,result);
      if ( result > local_max) 
        local_max= result;
    }
    printf("%d %lf\n",dd,local_max);
  }

  return 0;
}
