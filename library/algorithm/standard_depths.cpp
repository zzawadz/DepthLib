/*
 * depth.hpp
 *
 *  Created on: Sep 14, 2014
 *      Author: zzawadz
 */

#include "../standard_depths.hpp"

namespace Depth
{
 ///////////////////// Projection depth
 ProjectionDepth::ProjectionDepth() : nproj(1000) {};
 ProjectionDepth::ProjectionDepth(size_t nproj) : nproj(nproj) {};
 arma::vec ProjectionDepth::calculate_depth(const arma::mat& x, const arma::mat& y) const
 {
    return Projection::projection_depth(x, y, this->nproj);
 }
 
 namespace Projection
 {
  arma::vec projection_depth(const arma::mat& x, const arma::mat& y, size_t nproj)
  {  
    size_t nx = x.n_rows;
    size_t ny = y.n_rows;
    size_t d  = y.n_cols;

    arma::mat directions = StandardDepthUtils::runifsphere(nproj, d);
    directions = directions.t();
    
    arma::vec depth(nx);
    arma::vec tmpProj(ny);
    arma::rowvec medians(nproj);
    arma::rowvec mads(nproj);
    size_t i;
    for(i = 0; i < nproj; i++)
    {
      tmpProj = y * directions.col(i);
      medians(i) = arma::median(tmpProj);
      mads(i) = arma::median(arma::abs(tmpProj - medians(i)));
    }

    arma::rowvec tmpX(nproj);
    for(i = 0; i < nx; i++)
    {
      tmpX = x.row(i) * directions;
      tmpX -= medians;
      tmpX /= mads;
      tmpX = arma::abs(tmpX);
      depth(i) = arma::max(tmpX);
    }

    depth = 1/(1+depth);
    return depth;
  }
 }
  
///////////////// Tukey's depths

TukeyDepth::TukeyDepth(bool exact) : nproj(1000), exact(exact) {};
TukeyDepth::TukeyDepth(size_t nproj) : nproj(nproj), exact(false) {};
TukeyDepth::TukeyDepth(size_t nproj, bool exact) : nproj(nproj), exact(exact) {};
  
arma::vec TukeyDepth::calculate_depth(const arma::mat& x, const arma::mat& y) const
{
  if(x.n_cols == 1) return TukeyUtils::tukey_depth1d(x, y);
  if(x.n_cols == 2 && this->exact) return TukeyUtils::tukey_depth2d_exact(x, y);
  TukeyUtils::tukey_depth(x, y, this->nproj);
}

  
  namespace TukeyUtils 
  {
    arma::vec tukey_depth(const arma::mat& x, const arma::mat& y, size_t nproj)
    {  
      size_t nx = x.n_rows;
      size_t ny = y.n_rows;
      size_t d  = y.n_cols;

      arma::mat directions = StandardDepthUtils::runifsphere(nproj, d);
      directions = directions.t();
      
      arma::mat xdir = x * directions;
      arma::mat ydir = y * directions;
      
      arma::mat bigRes(xdir.n_rows, x.n_cols);
      
      for(size_t i = 0; i < nproj; i++)
      {
	bigRes.col(i) = tukey_depth1d(xdir.col(i), ydir.col(i));    
      }
      
      return arma::max(bigRes, 1);
    }
    
    
    arma::vec tukey_depth1d(const arma::colvec& x, arma::colvec y)
    {
      y = arma::sort(y);
      arma::vec result(x.n_elem); result.zeros();
      
      size_t end = x.n_elem;
      double nElem = static_cast<double>(x.n_elem);
      double half = nElem / 2.0;
      double tmp;
      for(size_t i = 0; i < end; i++)
      {
	tmp = static_cast<double>( std::lower_bound(y.begin(), y.end(), x.at(i)) - y.begin());
	if(tmp >= half) tmp = nElem - tmp - 1;
	result[i] = tmp/nElem;
      }
      return result;
    }
    
    
    /// Functions for 2d exact
      double get_depths1(double m,const double j)
      {
	if(m < j) return 0.0;
	if(j==1) return m;
	if(j==2) return (m*(m-1.0))/2.0;
	if(j==3) return (m*(m-1.0)*(m-2.0))/6.0;
	return 0.0;
      }

      double get_HDEP(size_t NT, size_t N, double NUMH)
      {
	  //NUMS = NUMS+depths1(NT,1)*depths1(NN,2)+depths1(NT,2)*depths1(NN,1)+
	  //  depths1(NT,3);
	  //if(N >= 3) SDEP<-(NUMS+0.0)/(depths1(N,3))
	  NUMH = NUMH+NT;
	  double HDEP = NUMH/N;
	  return HDEP;
      }


      arma::vec get_HDEP(const arma::vec& X, const arma::vec& Y,const double& U,const double& V, const double& P, const double& P2,const double& EPS)
      {	
	size_t N = X.n_elem;
	size_t NT = 0;
	
	arma::vec ALPHA(N);
	
	// temporary variables
	double DV;
	double XU;
	double YU;
	
	
	for(size_t i = 0; i < N; i++)
	{
	  DV = sqrt(((X[i]-U)*(X[i]-U)+(Y[i]-V)*(Y[i]-V)));
	  
	  if (DV <= EPS) { NT++; }
	  else
	  {
	    XU = (X[i]-U)/DV;
	    YU = (Y[i]-V)/DV;
	    
	    if (fabs(XU) > fabs(YU))
	    {
	      if (X[i] >= U)
	      {
		ALPHA[i-NT] = asin(YU);
		if(ALPHA[i-NT] < 0.0)
		{
		  ALPHA[i-NT] = P2+ALPHA[i-NT];
		} 
	      }
	      else
	      {
		ALPHA[i-NT] = P-asin(YU);
	      }
	    }
	    else
	    {
	      if (Y[i] >= V)
		ALPHA[i-NT] = acos(XU);
	      else
		ALPHA[i-NT] = P2-acos(XU);
	    }
	    if (ALPHA[i-NT] >= P2-EPS) ALPHA[i-NT] = 0.0;
	  }

	}
	

	ALPHA.resize(N-NT);
	ALPHA = arma::sort(ALPHA);
	return ALPHA;
      }


      double tukey_depth2d_exact_single_val(double U, double V,const arma::mat& m)
      {
	//  Compute the halfspace depth of the point (u,v) for the pairs of points
	//  in the n by 2 matrix m.
	// CONST
	const size_t N   = m.n_rows;
	const double P   = M_PI;
	const double P2  = P*2.0;
	const double EPS = 0.000001;
	
	// Var
	arma::colvec X = m.col(0);
	arma::colvec Y = m.col(1);
	double NUMH = 0.0;

	arma::vec ALPHA = get_HDEP(X,Y,U,V,P,P2,EPS);
	size_t NN = ALPHA.n_rows;
	size_t NT = N - NN;
	

	if(NN<=1) return get_HDEP(NT, N, NUMH);
	
	double ANGLE = ALPHA[0]-ALPHA[NN-1]+P2;
	for(size_t i =1; i < NN; i++)
	{
	  ANGLE = std::max(ANGLE,ALPHA[i]-ALPHA[i-1]);
	}
	/*If NN end */
	if(ANGLE > (P+EPS)) return get_HDEP(NT, N, NUMH);
	
	
	ANGLE = ALPHA[0];
	size_t NU = 0;
	for(size_t i = 0; i < NN; i++)
	{
	  ALPHA[i] = ALPHA[i]-ANGLE;
	  if(ALPHA[i]<(P-EPS)) NU++;
	}
	/*If NN end */
	if(NU >= NN) return get_HDEP(NT, N, NUMH);
	
      
	size_t JA = 1;
	size_t JB = 1;
	double ALPHK = ALPHA[0];
	double BETAK = ALPHA[NU]-P;
	size_t NN2   = NN*2;
	//size_t NBAD  = 0;
	size_t I     = NU;
	size_t NF    = NN;
	
	double ADD;
	arma::vec FV(NN);
	
	for(size_t J = 0; J < NN2; J++)
	{
	  ADD = ALPHK+EPS;
	
	  
	  if (ADD < BETAK)
	  {
	    NF++;

	    
	    if(JA < NN)
	    {
	      JA++;
	      ALPHK = ALPHA[JA-1];
	    }
	    else ALPHK = P2+1.0;
	    
	
	  }
	  else
	  {
	    I++;
	    if(I > NN)
	    {
	      I = 1;
	      NF = NF-NN;
	    }
	    FV[I-1] = NF;

	    if(JB < NN)
	    {
	      JB++;
	      if(JB+NU <= NN)
		BETAK = ALPHA[JB+NU-1]-P;
	      else
		BETAK = ALPHA[JB+NU-NN-1]+P;
	    }
	    else
	      BETAK = P2+1.0;
	  }
	}

	size_t GI = 0;
	size_t KI = 0;
	double AEPS;
	JA = 1;
	
	ANGLE = ALPHA[0];
	size_t dif = NN-FV[0];
	NUMH = (FV[0] < dif)?FV[0] : dif;
	
	
	for(size_t I = 1; I < NN; I++)
	{
	  AEPS = ANGLE+EPS;
	  if(ALPHA[I] <= AEPS)
	  {
	    JA++;
	  }
	  else
	  {
	    GI = GI+JA;
	    JA = 1;
	    ANGLE = ALPHA[I];
	  }
	  KI   = FV[I]-GI;
	  
	  NUMH = (NUMH < FV[I] - GI)? NUMH : FV[I] - GI; 
	  NUMH = (NUMH < NN-KI)? NUMH : NN-KI;
	
	}
	
	return get_HDEP(NT, N, NUMH);
      }
      
    arma::vec tukey_depth2d_exact(const arma::mat& x, const arma::mat& y)
    {
      size_t n = x.n_rows;
      arma::vec depth(n);
      for(size_t i = 0; i < n; i++)
      {
	depth[i] = tukey_depth2d_exact_single_val(x.at(i,0), x.at(i,1), y);
      }
      return depth;
    }
      
  }
  
  namespace StandardDepthUtils
  {
    arma::mat runifsphere(size_t n, size_t p)
    {
      arma::mat X(n, p);
      //NumericVector rx = rnorm(n*p);
      //arma::mat X(rx.begin(), n, p, false);
      X.randn();
      arma::vec norm = arma::sum(X % X, 1);
      norm = arma::sqrt(norm);
      X.each_col() /= norm;
      return X;
    }
  
    ////////////// seq for Armadillo - works as seq in R
    arma::vec seq(const double& x, const double& y, const size_t& length)
    {
      arma::vec result(length);
      double step = (y-x)/static_cast<double>(length-1);
      result(0) = x;
      for(size_t i = 1; i < length; i++) result(i) = result(i-1) + step;
      return(result);
    }
    
  }
  
}