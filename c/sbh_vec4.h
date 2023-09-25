/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of schwarzschild_black_holes.                           *
 *                                                                            *
 *  schwarzschild_black_holes is free software: you can redistribute it       *
 *  and/or modify it under the terms of the GNU General Public License as     *
 *  published by the Free Software Foundation, either version 3 of the        *
 *  License, or (at your option) any later version.                           *
 *                                                                            *
 *  schwarzschild_black_holes is distributed in the hope that it will be      *
 *  useful but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with schwarzschild_black_holes.  If not, see                        *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a basic double-precision 4D vector struct.                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/09/25                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef SBH_VEC4
#define SBH_VEC4

#include "sbh_inline.h"
#include <math.h>

/*  Struct for working with four-dimensional points.                          */
struct sbh_vec4 {

    /*  Rather than defining the struct to consist of doubles x, y, z, t, use *
     *  an array of 4 doubles. This allows us to use the same struct for      *
     *  different coordinate systems without the awkwardness of writing       *
     *  something like "x = r" or "y = theta", and so on.                     */
    double dat[4];
};

/******************************************************************************
 *  Function:                                                                 *
 *      sbh_vec4_rect                                                         *
 *  Purpose:                                                                  *
 *      Creates a 4D vector from "rectangular", or Cartesian, coordinates.    *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          The x-component of the vector.                                    *
 *      y (double):                                                           *
 *          The y-component of the vector.                                    *
 *      z (double):                                                           *
 *          The z-component of the vector.                                    *
 *      t (double):                                                           *
 *          The time component of the vector.                                 *
 *  Outputs:                                                                  *
 *      v (struct sbh_vec4):                                                  *
 *          The vector (x, y, z, t).                                          *
 *  Method:                                                                   *
 *      Set the individual components for the struct and return.              *
 ******************************************************************************/
SBH_INLINE struct sbh_vec4
sbh_vec4_rect(double x, double y, double z, double t)
{
    /*  Declare necessary variables.                                          */
    struct sbh_vec4 p;

    /*  Set the components for the vector and return.                         */
    p.dat[0] = x;
    p.dat[1] = y;
    p.dat[2] = z;
    p.dat[3] = t;
    return p;
}
/*  End of sbh_vec4_rect.                                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      sbh_vec4_rect_from_schwarzschild                                      *
 *  Purpose:                                                                  *
 *      Given the Schwarzschild coordinates of a point p, returns the vector  *
 *      in R^4 with the corresponding Cartesian coordinates.                  *
 *  Arguments:                                                                *
 *      r (double):                                                           *
 *          The radial component of the point.                                *
 *      phi (double):                                                         *
 *          The azimuthal part of the vector.                                 *
 *      theta (double):                                                       *
 *          The angle the vector makes with the north pole.                   *
 *      t (double):                                                           *
 *          The time component of the vector.                                 *
 *  Outputs:                                                                  *
 *      v (struct sbh_vec4):                                                  *
 *          The vector (x, y, z, t).                                          *
 *  Method:                                                                   *
 *      Use the spherical coordinate formulas and append the time component.  *
 ******************************************************************************/
SBH_INLINE struct sbh_vec4
sbh_vec4_rect_from_schwarzschild(double r, double phi, double theta, double t)
{
    /*  Declare necessary variables.                                          */
    struct sbh_vec4 p;

    /*  Schwarzschild coordinates are basically spherical coordinate plus     *
     *  time. Use the standard spherical-to-rectangular conversion factors.   */
    const double sin_phi = sin(phi);
    const double cos_phi = cos(phi);
    const double sin_theta = sin(theta);
    const double cos_theta = cos(theta);

    /*  Compute Cartesian coordinates from the spatial part (r, theta, phi).  */
    p.dat[0] = r * sin_theta * cos_phi;
    p.dat[1] = r * sin_theta * sin_phi;
    p.dat[2] = r * cos_theta;

    /*  The time factor is the same in both coordinate systems.               */
    p.dat[3] = t;
    return p;
}
/*  End of sbh_vec4_rect_from_schwarzschild.                                  */

SBH_INLINE struct sbh_vec4
sbh_vec4_schwarzschild_to_rect(const struct sbh_vec4 *q)
{
    /*  The input vector is in Schwarzschild coordinates. Pass them to the    *
     *  rect_from_schwarzschild function and return.                          */
    return sbh_vec4_rect_from_schwarzschild(
        q->dat[0], q->dat[1], q->dat[2], q->dat[3]
    );
}

SBH_INLINE void
sbh_vec4_convert_schwarzschild_to_rect(struct sbh_vec4 *p)
{
    /*  Avoid overwriting data. Save the "r" component of the input.          */
    const double r = p->dat[0];

    /*  Compute the spherical-to-rectangular conversion factors.              */
    const double sin_phi = sin(p->dat[1]);
    const double cos_phi = cos(p->dat[1]);
    const double sin_theta = sin(p->dat[2]);
    const double cos_theta = cos(p->dat[2]);

    /*  Compute Cartesian coordinates from the spatial part (r, theta, phi).  *
     *  The time part is the same in both systems, no need to change.         */
    p->dat[0] = r * sin_theta * cos_phi;
    p->dat[1] = r * sin_theta * sin_phi;
    p->dat[2] = r * cos_theta;
}
/*  End of sbh_vec4_convert_schwarzschild_to_rect.                            */

#endif
/*  End of include guard.                                                     */
