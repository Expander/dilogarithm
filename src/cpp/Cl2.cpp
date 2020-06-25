// ====================================================================
// This file is part of Polylogarithm.
//
// Polylogarithm is licenced under the GNU Lesser General Public
// License (GNU LGPL) version 3.
// ====================================================================

#include "Cl2.hpp"
#include "Li2.hpp"
#include <limits>

namespace polylogarithm {

/**
 * @brief Clausen function \f$\mathrm{Cl}_2(\theta) = \mathrm{Im}(\mathrm{Li}_2(e^{i\theta}))\f$
 * @param x real angle
 * @return \f$\mathrm{Cl}_2(\theta)\f$
 */
double Cl2(double x) noexcept
{
   const double PI = 3.141592653589793;
   const std::complex<double> i(0.0, 1.0);

   while (x >= 2*PI) {
      x -= 2*PI;
   }

   while (x < 0.0) {
      x += 2*PI;
   }

   if (std::abs(x) < std::numeric_limits<double>::epsilon() ||
       std::abs(x - PI) < std::numeric_limits<double>::epsilon() ||
       std::abs(x - 2*PI) < std::numeric_limits<double>::epsilon()) {
      return 0.0;
   }

   return std::imag(Li2(std::exp(i*x)));
}

/**
 * @brief Clausen function \f$\mathrm{Cl}_2(\theta) = \mathrm{Im}(\mathrm{Li}_2(e^{i\theta}))\f$ with long double precision
 * @param x real angle
 * @return \f$\mathrm{Cl}_2(\theta)\f$
 */
long double Cl2(long double x) noexcept
{
   const long double PI = 3.14159265358979323846264338327950288L;
   const std::complex<long double> i(0.0L, 1.0L);

   while (x >= 2*PI) {
      x -= 2*PI;
   }

   while (x < 0.0L) {
      x += 2*PI;
   }

   if (std::abs(x) < std::numeric_limits<long double>::epsilon() ||
       std::abs(x - PI) < std::numeric_limits<long double>::epsilon() ||
       std::abs(x - 2*PI) < std::numeric_limits<long double>::epsilon()) {
      return 0.0L;
   }

   return std::imag(Li2(std::exp(i*x)));
}

} // namespace polylogarithm