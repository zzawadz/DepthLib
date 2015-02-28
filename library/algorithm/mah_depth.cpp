#include "../mah_depth.hpp"

namespace Depth
{

arma::vec mah_depth(const arma::mat& x)
{
  return(mah_depth(x,x));
}

arma::vec mah_depth(const arma::mat& x, const arma::rowvec& mean)
{
    return(mah_depth(x,x,mean));
}

arma::vec mah_depth(const arma::mat& x, const arma::mat& y)
{
  arma::mat cov = arma::cov(y);
  arma::rowvec mean = arma::mean(y);
            
  return(mah_depth(x,y,cov,mean));
  
}

arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::mat& cov)
{
  arma::rowvec mean = arma::mean(y);
  return(mah_depth(x,y,cov,mean));
}
  
arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::rowvec& mean)
{
  arma::mat cov = arma::cov(y);
  return(mah_depth(x,y,cov,mean));
}
  
arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::mat& cov, const arma::rowvec& mean)
{
  size_t n = x.n_rows;
  arma::vec depth(n);
  arma::mat covy = cov.i();
      
  arma::rowvec tmpx;
  double dist;
  for(size_t i = 0; i < n; i++)
  {
    tmpx = x.row(i) - mean;
    tmpx = tmpx * covy *tmpx.t();
    dist = 1.0/(1.0 + tmpx(0));
    depth(i) = dist;
  }
  return(depth);
}


} // end namespace depth