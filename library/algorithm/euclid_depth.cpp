/*
 * euclid_depth.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: zzawadz
 */

#include "../euclid_depth.hpp"

namespace Depth
{
  using namespace std::placeholders;
  
  
  /*arma::vec make_euclid_depth()
  {
    
    
  }*/
  
  namespace Euclid {
    
    
    arma::vec EuclidDepth::calculate_depth(const arma::mat& x, const arma::mat& y)
    {
      return euclid_depth(x,y);
    }
    
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

}
