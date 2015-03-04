/*
 * standard_depths.hpp
 *
 *  Created on: Sep 12, 2014
 *      Author: zzawadz
 */

#ifndef STANDARD_DEPTHS_HPP_
#define STANDARD_DEPTHS_HPP_

#include "depth.hpp"
#include "DepthLib_include.hpp"

namespace Depth
{
  
  class ProjectionDepth : public Depth::DepthFunction
  {
     public:
	ProjectionDepth();
	ProjectionDepth(size_t nproj);
	virtual arma::vec calculate_depth(const arma::mat& x, const arma::mat& y) const;
	
      private:
	 size_t nproj;
	
  };
 namespace Projection
 {
   arma::vec projection_depth(const arma::mat& x, const arma::mat& y, size_t nproj);
 }

/////////////////// Tukey's depth

class TukeyDepth : public Depth::DepthFunction
  {
     public:
	TukeyDepth(bool exact);
	TukeyDepth(size_t nproj);
	TukeyDepth(size_t nproj, bool exact);
	virtual arma::vec calculate_depth(const arma::mat& x, const arma::mat& y) const;
	
      private:
	 size_t nproj;
	 bool exact;
	
  };

namespace TukeyUtils
{
  arma::vec tukey_depth(const arma::mat& x, const arma::mat& y, size_t nproj);
  arma::vec tukey_depth1d(const arma::colvec& x, arma::colvec y);
  double get_depths1(double m,const double j);
  double get_HDEP(size_t NT, size_t N, double NUMH);
  arma::vec get_ALPHA(const arma::vec& X, const arma::vec& Y,const double& U,const double& V, const double& P, const double& P2,const double& EPS);
  double tukey_depth2d_exact_single_val(double U, double V,const arma::mat& m);  
  arma::vec tukey_depth2d_exact(const arma::mat& x, const arma::mat& y);
}

namespace StandardDepthUtils
{
  arma::mat runifsphere(size_t n, size_t p);
  arma::vec seq(const double& x, const double& y, const size_t& length);
}

}

#endif /* STANDARD_DEPTHS_HPP_ */