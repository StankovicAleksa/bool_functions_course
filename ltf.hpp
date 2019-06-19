#ifndef LTF_HPP
#define LTF_HPP

#include <algorithm>

const int maxn=5;
const int maxinput= (1<<(maxn))-1;

/* linear treshold function */
struct LTF
{
  LTF(){for ( int i=0;i<=maxn;i++) w[i]=0;}
  long long w[maxn+1]; // coefficients. w[0] is the constant coefficient.
  bool set_enc();
  long long _enc[maxinput+1]; // encoding of the equivalence class
  long long eval(int input) const
  {
    long long val=w[0];
    for (int bit=0;bit<maxn;bit++)
    {
      // evaluate function 
      val +=  (( (1<<bit) & input ) ==0 ) ? -w[bit+1] : w[bit+1];
    }
    return val;
  }
};

bool operator < ( const LTF& l1, const LTF &l2) 
{ 
  for ( int i=0;i<=maxinput;i++)
  {
    if (l1._enc[i] == l2._enc[i]) 
      continue;
    else
      return l1._enc[i]<l2._enc[i];
  }
  return false;
}


struct ind_val
{
  int index;
  long long val;
};
ind_val ind_val_ar[maxinput+1];


bool operator < ( const ind_val & iv1, const ind_val &iv2)
{
  return iv1.val < iv2.val;
}

bool LTF::set_enc()
{
  // evaluate all, place them in the inputs
  int n=maxn;

  for ( int input=0;input<=maxinput;input++)
  {
    ind_val_ar[input].val=eval(input); 
    ind_val_ar[input].index=input;
  }

  std::sort(ind_val_ar, ind_val_ar+maxinput+1);  

  long long prev_val=0;
  for ( int i=0;i<=maxinput;i++)
  {
    _enc[ind_val_ar[i].index]=i;
    if ( ind_val_ar[i].val == prev_val )
      return false;
    else
      prev_val = ind_val_ar[i].val;
  }

  return true;
}

/** Representation of a function $f:\{-1,1\}^n \rightarrow \{-1,1\}$ as a (binary) table of all its outputs.
 * The size of the table is $2^{2^n}$. Since $n=5$, we can fit the output in 32-bits.
 ***/

struct func_encoding
{
  func_encoding(long long a):outp(a){}
  func_encoding(const LTF&,bool &has_zero);
  long long outp;
};

bool operator < ( const func_encoding& fe1, const func_encoding& fe2) // in order to use it in dictionary
{
  return fe1.outp < fe2.outp;
}


func_encoding::func_encoding(const LTF &ltf,bool& has_zero)
{
  int n=maxn;
  this->outp=0;
  has_zero=false;
  n=maxn;
  
  
  const int inp_sz=(1<<maxn);
  
  for ( int input=0;input<inp_sz;input++)
  {
    long long val=ltf.eval(input);
    if ( val > 0 )
      this->outp |= (1<< input);
    else if (val == 0)
      has_zero=true;
  }
  static bool us=false;
}

#endif
