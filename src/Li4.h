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

/** complex polylogarithm with n=4 */
void cli4_(double re, double im, double* res_re, double* res_im);

/** complex polylogarithm with n=4 with long double precision */
void cli4l_(long double re, long double im, long double* res_re, long double* res_im);

#ifdef __cplusplus
}
#endif