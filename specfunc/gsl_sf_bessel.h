#ifndef GSL_BESSEL_H_
#define GSL_BESSEL_H_

/* Evaluate regular cylindrical Bessel functions J_0(x), J_1(x). */
double gsl_sf_bessel_J0(double x);
double gsl_sf_bessel_J1(double x);

/* Evaluate regular modified cylindrical Bessel funcions I_0(x), I_1(x). */
double gsl_sf_bessel_I0(double x);
double gsl_sf_bessel_I1(double x);

/* Evaluate scaled regular modified cylindrical Bessel funcions
   exp(-|x|) I_0(x)
   exp(-|x|) I_1(x).
   */
double gsl_sf_bessel_I0_scaled(double x);
double gsl_sf_bessel_I1_scaled(double x);

/* Evaluate regular modified cylindrical Bessel function I_n(x). */
double gsl_sf_bessel_I(int n, double x);

/* Evaluate logarithm of regular modified cylindrical Bessel functions I_n(x).
   This method avoids overflow when calculating for large x.
 */
double gsl_sf_log_bessel_I0(double);
double gsl_sf_log_bessel_I1(double);
double gsl_sf_log_bessel_I(int, double);


/* Evaluate the regular spherical Bessel function j_l(x)
   at a given point x for a set of l values 0,...,lmax.
   Assumes x > 0.
   Uses the Steed/Barnett algorithm.
   See Comp. Phys. Comm. 21, 297 (1981).
 */
void gsl_sf_bessel_j_steed(double x, int lmax, double * jl_x);


/* Regular cylindrical Bessel functions J_nu(x) calculated
   with the Meissel uniform approximation. Assumes x >= 0.
   This approximation is accurate to near 10^{-3} at the boundaries
   between the asymptotic regions; well away from the boundaries
   the accuracy is better than 10^{-5}.
   Asymptotic approximations 8.11.5, 8.12.5, and 8.42.7 from
   G.N.Watson, A Treatise on the Theory of Bessel Functions,
   2nd Edition (Cambridge University Press, 1944).
   Higher terms in expansion for x near l given by
   Airey in Phil. Mag. 31, 520 (1916).
 */
double besselJ_meissel(double nu, double x);


/* Evaluate  d/dx(J_nu(x)) given the value J_nu(x).
   Uses the recursion relation and one extra function evaluation.
   Assumes x > 0.
   This is not very good pointwise (although the other relation,
   written in terms of nu+1 and nu-1, is only slightly better).
   However, it is quite good in the mean, over intervals greater
   than one period.
 */
double besselJprime_meissel(double nu, double x, double J_nu_x);


/* Evaluate Meissel expansion for spherical Bessel functions j_l(x).
 */
double sphbesselj_meissel(double l, double x);


/* Evaluate d/dx(j_l(x)) using the value j_l(x). Use recursion and 
 * one extra function evaluation.
 */
double sphbesseljprime_meissel(double l, double x, double jl_x);


/* Leading large argument behaviour of the regular
   spherical Bessel function j_l(x), using the 
   Meissel approximation.
   Calculates the derivative as well if dflag!=0.
 */
void asymp_sphbesselj_meissel(double l, double x,
				     double *jl, double *jlp,
				     int dflag);






#endif /* !GSL_BESSEL_H_ */
