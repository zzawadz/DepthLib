/*
 * euclid_depth.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: zzawadz
 */

#include "../distance_depths.hpp"

namespace Depth
{ 
 //////////////////////////// LP depth ///////////////////////////////
  
  
 LpDepth::LpDepth(double p, double a, double b) : p(p), a(a), b(b) {};
 arma::vec LpDepth::calculate_depth(const arma::mat& x, const arma::mat& y) const
 {
    return LP::lp_depth(x, y, this->p, this->a, this->b);
 }
  
 namespace LP
 {
    arma::vec lp_depth(const arma::mat& x, const arma::mat& y, const double &p, const double& a, const double& b)
    {
	size_t d = y.n_cols;
	size_t n_y = y.n_rows;
	size_t n_x = x.n_rows;

	arma::vec depth(n_x);
	size_t k,i;
    
    	for(k = 0; k< n_x; k++)
	{
	  arma::rowvec tmp = arma::zeros<arma::rowvec>(d);
  	  double sum_res = 0;
	  double tmp_sum;
	  
	  for(size_t i = 0; i < n_y; i++)
	  {
	    tmp = x.row(k) - y.row(i);
	    tmp = arma::abs(tmp);
	    tmp = arma::pow(tmp, p);
	    tmp_sum = arma::sum(tmp);
	    tmp_sum = a*tmp_sum + b;
	    sum_res = sum_res + tmp_sum;
	  }
	  depth(k) = 1/(1 + sum_res/static_cast<double>(n_y));
	 }
		return depth;
    }
 }
  
  
  
 //////////////////// Euclidean depth /////////////
  // constructors
   EuclidDepth::EuclidDepth() {}
   EuclidDepth::EuclidDepth(arma::rowvec center) : center(center) {}
    
   arma::vec EuclidDepth::calculate_depth(const arma::mat& x, const arma::mat& y) const
   {
     if(this->center.is_empty()) 
     {
	return Euclid::euclid_depth(x, y);
     } else
     {
	return Euclid::euclid_depth(x, this->center);
     }
   }
  
  namespace Euclid {
    
    
    arma::vec euclid_depth(const arma::mat& x, const arma::rowvec& center)
    {
	    arma::vec depth(x.n_rows);
	    
	    size_t n = x.n_rows;
	    arma::rowvec tmp;
	    
	    for(size_t i = 0; i < n; i++)
	    {
	      tmp = x.row(i) - center;
	      depth(i) = sqrt(sum(tmp % tmp));
	    }
	    
	    depth = 1/(depth + 1);

	    return depth;
    }
    

    arma::vec euclid_depth(const arma::mat& x)
    {
	    arma::rowvec center = arma::mean(x, 0);
	    return euclid_depth(x, center);
    }

    arma::vec euclid_depth(const arma::mat& x, const arma::mat& y)
    {
	    arma::rowvec center = arma::mean(y, 0);
	    return euclid_depth(x, center);
    }
  }
  
  //////// Mahalanobis ////////
  MahalanobisDepth::MahalanobisDepth() {}
  MahalanobisDepth::MahalanobisDepth(arma::mat cov) : cov(cov) {}
  MahalanobisDepth::MahalanobisDepth(arma::rowvec center) : center(center) {}
  MahalanobisDepth::MahalanobisDepth(arma::rowvec center, arma::mat cov) : center(center), cov(cov) {}
  
  arma::vec  MahalanobisDepth::calculate_depth(const arma::mat& x, const arma::mat& y) const
  {
   if(this->center.is_empty() && this->cov.is_empty())
   {
      return Mahalanobis::mah_depth(x, y);
   }
   if(this->center.is_empty())
   {
      return Mahalanobis::mah_depth(x, y, this->cov);
   }
   if(this->cov.is_empty())
   {
      return Mahalanobis::mah_depth(x, y, this->center);
   }
   return Mahalanobis::mah_depth(x, y, this->center, this->cov);
   
  }
  
  
  namespace Mahalanobis
  {
      arma::vec mah_depth(const arma::mat& x)
      {
	return(mah_depth(x,x));
      }

      arma::vec mah_depth(const arma::mat& x, const arma::rowvec& center)
      {
	  return(mah_depth(x, x, center));
      }

      arma::vec mah_depth(const arma::mat& x, const arma::mat& y)
      {
	arma::mat cov = arma::cov(y);
	arma::rowvec center = arma::mean(y);
	
	return(mah_depth(x, y, center, cov));
	
      }

      arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::mat& cov)
      {
	arma::rowvec center = arma::mean(y);
	return(mah_depth(x, y, center, cov));
      }
	
      arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::rowvec& center)
      {
	arma::mat cov = arma::cov(y);
	return(mah_depth(x, y, center, cov));
      }
	
      arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::rowvec& center, const arma::mat& cov)
      {
	size_t n = x.n_rows;
	arma::vec depth(n);
	arma::mat covy = cov.i();
	
	arma::rowvec tmpx;
	double dist;
	for(size_t i = 0; i < n; i++)
	{
	  tmpx = x.row(i) - center;
	  tmpx = tmpx * covy *tmpx.t();
	  dist = 1.0/(1.0 + tmpx(0));
	  depth(i) = dist;
	}
	return(depth);
      }
    
  }

}
