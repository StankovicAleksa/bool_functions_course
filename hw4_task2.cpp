#include <iostream>
#include <cmath>
#include <map>
#include <algorithm>
#include <set>
#include "ltf.hpp"

std::set <LTF> ltfs[maxn+1];

void find_lowest_int_coefficients();

int main()
{

  // try out all possible coefficients!
  //old_main(); 
  find_lowest_int_coefficients(); 

 // find_lowest_influence();

  return 0;
}


std::map < func_encoding, LTF> int_ltfs;

long long w[maxn+1];

const int max_coeff=5;

long long max_inf_w[maxn+1];
long long max_total_inf=0;
long long best_outp;
bool has_zero;

void rec(int d, bool positive)
{
  if ( d > maxn)
  {
     // check
    LTF ltf; 
    for ( int i=0;i<d;i++)
      ltf.w[i]=w[i];

    func_encoding fe(ltf,has_zero);
    if (!has_zero && int_ltfs.count(fe) ==0 ) 
    {
      int_ltfs[fe]=ltf;
      // calculate influence 
      long long inf=0;
      long long outp=fe.outp;
      for (  int input=0;input<=maxinput;input++)
      {
        for ( int i=0;i<maxn;i++)
        {
          int op= (input ^ (1<<i) ); 
          if ( ( (outp & (1<<input)) ==0 ) != (( outp & (1<<op) ) ==0  ) )
            inf++;
        }
      }
      if ( inf > max_total_inf)
      {
        max_total_inf = inf;
        for ( int i=0;i<=maxn;i++)
          max_inf_w[i]=w[i];
        best_outp=outp;
      }
    } 
    return ;
  }
  else
  {
    if ( d > 0 )
    {
      int low = -max_coeff;
      if ( positive) 
        low =0;
      for ( int i=low;i<=max_coeff;i++)
      {
        w[d]=i;
        rec(d+1,positive);
      }

    }
    else
    {
      for ( int i=-max_coeff;i<=max_coeff;i++)
      {
        w[d]=i;
        rec(d+1,positive);
      }
    }
  }
}


void find_lowest_int_coefficients()
{
  rec(0,false);


  std::cout << "final ltf size "  << int_ltfs.size() << std::endl;
  std::cout << "Final max_inf output: " << max_total_inf << "/32"<< std::endl;
  for ( int i=0;i<=maxn;i++)
    std::cout << max_inf_w[i] << " ";
  std::cout << std::endl;

  
  w[0]=0;
  w[1]=w[2]=w[3]=w[4]=w[5]=1;
  LTF ltf; 
  for ( int i=0;i<=maxn;i++)
    ltf.w[i]=w[i];
  bool is_zero=false;
  func_encoding fe(ltf,is_zero);
  long long outp=fe.outp;
  // calculate influence 
  long long inf=0;
  for (  int input=0;input<=maxinput;input++)
  {
    for ( int i=0;i<maxn;i++)
    {
      int op= (input ^ (1<<i) ); 
      if ( ( (outp & (1<<input)) ==0 ) != (( outp & (1<<op) ) ==0  ) )
        inf++;
    }
  }
  std::cout << "Influence of majority is: " << inf << "/32" << std::endl;
  return ;
  /* output all LTFs */
}
