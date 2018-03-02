// ====================================================================
// This file is part of Polylogarithm.
//
// Polylogarithm is licenced under the GNU Lesser General Public
// License (GNU LGPL) version 3.
// ====================================================================

#include "Li2.hpp"
#include <limits>

namespace polylogarithm {

namespace {
   template <typename T>
   T sqr(T x) noexcept { return x*x; }
} // anonymous namespace

/**
 * @brief Clausen function \f$\mathrm{Cl}_2(\theta) = \mathrm{Im}(\mathrm{Li}_2(e^{i\theta}))\f$
 * @param x real angle
 * @return \f$\mathrm{Cl}_2(\theta)\f$
 */
double Cl2(double x)
{
   using std::exp;
   const std::complex<double> i(0.,1.);

   return std::imag(Li2(exp(i*x)));
}

/**
 * @brief Real dilogarithm \f$\mathrm{Li}_2(x)\f$
 * @param x real argument
 * @note Implementation translated by R.Brun from CERNLIB DILOG function C332
 * @return \f$\mathrm{Li}_2(x)\f$
 */
double Li2(double x) {
   using std::log;

   const double PI  = 3.1415926535897932384626433832795;
   const double HF  = 0.5;
   const double PI2 = PI*PI;
   const double PI3 = PI2/3;
   const double PI6 = PI2/6;
   const double PI12 = PI2/12;
   const double C[20] = {0.42996693560813697, 0.40975987533077105,
     -0.01858843665014592, 0.00145751084062268,-0.00014304184442340,
      0.00001588415541880,-0.00000190784959387, 0.00000024195180854,
     -0.00000003193341274, 0.00000000434545063,-0.00000000060578480,
      0.00000000008612098,-0.00000000001244332, 0.00000000000182256,
     -0.00000000000027007, 0.00000000000004042,-0.00000000000000610,
      0.00000000000000093,-0.00000000000000014, 0.00000000000000002};

   double T,H,Y,S,A,ALFA,B1,B2,B0;

   if (x == 1) {
       H = PI6;
   } else if (x == -1) {
       H = -PI12;
   } else {
       T = -x;
       if (T <= -2) {
           Y = -1/(1+T);
           S = 1;
           B1= log(-T);
           B2= log(1+1/T);
           A = -PI3+HF*(B1*B1-B2*B2);
       } else if (T < -1) {
           Y = -1-T;
           S = -1;
           A = log(-T);
           A = -PI6+A*(A+log(1+1/T));
       } else if (T <= -0.5) {
           Y = -(1+T)/T;
           S = 1;
           A = log(-T);
           A = -PI6+A*(-HF*A+log(1+T));
       } else if (T < 0) {
           Y = -T/(1+T);
           S = -1;
           B1= log(1+T);
           A = HF*B1*B1;
       } else if (T <= 1) {
           Y = T;
           S = 1;
           A = 0;
       } else {
           Y = 1/T;
           S = -1;
           B1= log(T);
           A = PI6+HF*B1*B1;
       }
       H    = Y+Y-1;
       ALFA = H+H;
       B1   = 0;
       B2   = 0;
       for (int i=19;i>=0;i--){
          B0 = C[i] + ALFA*B1-B2;
          B2 = B1;
          B1 = B0;
       }
       H = -(S*(B0-H*B2)+A);
    }
    return H;
}

/**
 * @brief Complex dilogarithm \f$\mathrm{Li}_2(z)\f$
 * @param z complex argument
 * @note Implementation translated from SPheno to C++
 * @return \f$\mathrm{Li}_2(z)\f$
 */
std::complex<double> Li2(const std::complex<double>& z)
{
   const double PI = 3.1415926535897932384626433832795;
   static const int N = 20;

   // bf[1..N-1] are the even Bernoulli numbers / (2 n + 1)!
   // generated by: Table[BernoulliB[2 n]/(2 n + 1)!, {n, 1, 19}]
   const double bf[N] = {
      - 1./4.,
      + 1./36.,
      - 1./36.e2,
      + 1./21168.e1,
      - 1./108864.e2,
      + 1./52690176.e1,
      - 4.0647616451442255268059093862919666745470571274397078e-11,
      + 8.9216910204564525552179873167527488515142836130490451e-13,
      - 1.9939295860721075687236443477937897056306947496538801e-14,
      + 4.5189800296199181916504765528555932283968190144666184e-16,
      - 1.0356517612181247014483411542218656665960912381686505e-17,
      + 2.3952186210261867457402837430009803816789490019429743e-19,
      - 5.5817858743250093362830745056254199055670546676443981e-21,
      + 1.3091507554183212858123073991865923017498498387833038e-22,
      - 3.0874198024267402932422797648664624315955652561327457e-24,
      + 7.315975652702203420357905609252148591033401063690875e-26,
      - 1.7408456572340007409890551477597025453408414217542713e-27,
      + 4.1576356446138997196178996207752266734882541595115639e-29,
      - 9.9621484882846221031940067024558388498548600173944888e-31,
      + 2.3940344248961653005211679878937495629342791569329158e-32,
   };

   const double rz = std::real(z);
   const double iz = std::imag(z);
   const double az = std::abs(z);

   // special cases
   if (iz == 0.) {
      if (rz <= 1.)
         return {Li2(rz), 0.};
      if (rz > 1.)
         return {Li2(rz), -PI*std::log(rz)};
   } else if (az < std::numeric_limits<double>::epsilon()) {
      return z;
   }

   std::complex<double> cy, cz;
   int jsgn, ipi12;

   // transformation to |z|<1, Re(z)<=0.5
   if (rz <= 0.5) {
      if (az > 1.) {
         cy = -0.5 * sqr(std::log(-z));
         cz = -std::log(1. - 1. / z);
         jsgn = -1;
         ipi12 = -2;
      } else { // (az <= 1.)
         cy = 0;
         cz = -std::log(1. - z);
         jsgn = 1;
         ipi12 = 0;
      }
   } else { // rz > 0.5
      if (az <= std::sqrt(2*rz)) {
         cz = -std::log(z);
         cy = cz * std::log(1. - z);
         jsgn = -1;
         ipi12 = 2;
      } else { // (az > sqrt(2*rz))
         cy = -0.5 * sqr(std::log(-z));
         cz = -std::log(1. - 1. / z);
         jsgn = -1;
         ipi12 = -2;
      }
   }

   // the dilogarithm
   const std::complex<double> cz2(sqr(cz));
   std::complex<double> sumC;

   for (int i1 = 2; i1 < N; i1++)
      sumC = cz2 * (sumC + bf[N + 1 - i1]);

   // lowest order terms w/ different powers
   sumC = cz + cz2 * (bf[0] + cz * (bf[1] + sumC));

   const std::complex<double> result
      = double(jsgn) * sumC + cy + ipi12 * PI * PI / 12.;

   return result;
}

} // namespace polylogarithm
