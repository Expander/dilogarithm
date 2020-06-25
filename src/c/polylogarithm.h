/* ====================================================================
 * This file is part of Polylogarithm.
 *
 * Polylogarithm is licenced under the GNU Lesser General Public
 * License (GNU LGPL) version 3.
 * ==================================================================== */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** real polylogarithm with n=2 (dilogarithm) */
double li2(double x);

/** real polylogarithm with n=2 (dilogarithm) with long double precision */
long double li2l(long double x);

/** complex polylogarithm with n=2 (dilogarithm) */
void cli2_(double re, double im, double* res_re, double* res_im);

/** complex polylogarithm with n=2 (dilogarithm) with long double precision */
void cli2l_(long double re, long double im, long double* res_re, long double* res_im);

/** complex polylogarithm with n=3 (trilogarithm) */
void cli3_(double re, double im, double* res_re, double* res_im);

/** complex polylogarithm with n=3 (trilogarithm) with long double precision */
void cli3l_(long double re, long double im, long double* res_re, long double* res_im);

/** complex polylogarithm with n=4 */
void cli4_(double re, double im, double* res_re, double* res_im);

/** complex polylogarithm with n=4 with long double precision */
void cli4l_(long double re, long double im, long double* res_re, long double* res_im);

/** complex polylogarithm with n=5 */
void cli5_(double re, double im, double* res_re, double* res_im);

/** complex polylogarithm with n=5 with long double precision */
void cli5l_(long double re, long double im, long double* res_re, long double* res_im);

/** complex polylogarithm with n=6 */
void cli6_(double re, double im, double* res_re, double* res_im);

/** complex polylogarithm with n=6 with long double precision */
void cli6l_(long double re, long double im, long double* res_re, long double* res_im);

#ifdef __cplusplus
}
#endif
