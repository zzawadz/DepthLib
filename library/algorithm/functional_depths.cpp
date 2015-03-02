/*
 * 	mb_depth.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: zzawadz
 */

#include "../functional_depths.hpp"


namespace Depth
{

////////////////// ModifiedBandDepth /////////////////
  ModifiedBandDepth::ModifiedBandDepth() {};
  arma::vec ModifiedBandDepth::calculate_depth(const arma::mat& x, const arma::mat& y)
  {
      return MBD::mb_depth(x, y);
  }

  /// Utils functions for MBDepth
  namespace MBD
  {
    arma::vec mb_depth(const arma::mat& x)
    {
	arma::vec depth(x.n_rows); depth.zeros();

	size_t d = x.n_cols;
	for(size_t i = 0; i < d; i++)
	{
	  depth += mbd_col(x.col(i));
	}

	depth = depth / (d * choose(x.n_rows, 2));

	return depth;
    }

    arma::vec mb_depth(const arma::mat& x, const arma::mat& y)
    {
      arma::vec depth(x.n_rows); depth.zeros();

      size_t d = x.n_cols;
      for(size_t i = 0; i < d; i++)
      {
	depth += mbd_col_ref(x.col(i), y.col(i));
      }

      depth = depth / (d * choose(y.n_rows, 2));

      return depth;
    }
    
    
    
    



    arma::vec mbd_col(arma::vec x)
    {
      arma::uvec idx = sort_index( x );
      arma::vec sorted = x(idx);
      size_t n = idx.n_elem;
      arma::uvec equal(n); equal.ones();
      arma::uvec lowidx(n);

      size_t pos;
      size_t ti;
      size_t eq;


      for(size_t i = 0; i < n; i++)
      {
	pos = idx[i];
	lowidx[pos] = i;
	  eq = 0;

	  if(i > 0)
	  {
	    ti = i - 1;

	    while((sorted[i] == sorted[ti]))
	    {
	      lowidx[pos] = lowidx[pos] - 1;
	      eq++;
	      if(ti == 0) break;
	      ti--;
	    }
	  }

	  ti = i + 1;
	  while((sorted[i] == sorted[ti]) && ti < n)
	  {
	      equal[pos] = equal[pos] + 1;
	      ti++;
	  }
	  equal[pos] = equal[pos] + eq;

      }

      equal = equal + lowidx;
      arma::vec depth(n);

      for(size_t i = 0; i < n; i++)
      {
	double multiplicity = equal[i] - lowidx[i];
	depth[i] = lowidx[i] * (n - (equal[i])) + multiplicity * (n - equal[i] + lowidx[i]);
	depth[i] = depth[i] + choose(multiplicity, 2);
      }

      return depth;
    }

    ///////////////////////////

    arma::vec mbd_col_ref(arma::vec x,arma::vec y)
    {
      size_t n = x.n_elem;
      size_t n0 = y.n_elem;
      arma::vec depth(n);

      y = arma::sort(y);

      double index1;
      double index2;
      double tval;
      size_t j;

      for(size_t i = 0; i < n; i++)
      {
	      index1 = 0;
	      index2 = 0;
	      tval = x[i];
	      j = 0;
	      while(j < n0 && tval >= y[j])
	      {
		index2++;
		if(tval > y[j]) index1++;
		j++;
	      }

	      double multiplicity = index2 - index1;
	      depth[i] =  (index1 + multiplicity) * (n0 - index1 - multiplicity) +
	      multiplicity * (index1 + (multiplicity - 1)/2);
      }

	return depth;
    }
  
    double choose(double n, double k)
    {
		  double res = lgamma(n + 1) - lgamma(k + 1) - lgamma(n - k + 1);
		  return exp(res);
    }
    
  }

}