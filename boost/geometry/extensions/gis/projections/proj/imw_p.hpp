#ifndef BOOST_GEOMETRY_PROJECTIONS_IMW_P_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMW_P_HPP

// Boost.Geometry - extensions-gis-projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright (c) 2008-2011 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels (Geodan, Amsterdam)

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/extensions/gis/projections/impl/base_static.hpp>
#include <boost/geometry/extensions/gis/projections/impl/base_dynamic.hpp>
#include <boost/geometry/extensions/gis/projections/impl/projects.hpp>
#include <boost/geometry/extensions/gis/projections/impl/factory_entry.hpp>
#include <boost/geometry/extensions/gis/projections/impl/pj_mlfn.hpp>

namespace boost { namespace geometry { namespace projection
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace imw_p{
            static const double TOL = 1e-10;
            static const double EPS = 1e-10;

            struct PXY { double x, y; }; // x/y projection specific

            struct par_imw_p
            {
                double    P, Pp, Q, Qp, R_1, R_2, sphi_1, sphi_2, C2;
                double    phi_1, phi_2, lam_1;
                double    en[EN_SIZE];
                int    mode; /* = 0, phi_1 and phi_2 != 0, = 1, phi_1 = 0, = -1 phi_2 = 0 */
            };
            template <typename Parameters>
                inline int
            phi12(Parameters& par, par_imw_p& proj_parm, double *del, double *sig) {
                int err = 0;

                if (!pj_param(par.params, "tlat_1").i ||
                    !pj_param(par.params, "tlat_2").i) {
                    err = -41;
                } else {
                    proj_parm.phi_1 = pj_param(par.params, "rlat_1").f;
                    proj_parm.phi_2 = pj_param(par.params, "rlat_2").f;
                    *del = 0.5 * (proj_parm.phi_2 - proj_parm.phi_1);
                    *sig = 0.5 * (proj_parm.phi_2 + proj_parm.phi_1);
                    err = (fabs(*del) < EPS || fabs(*sig) < EPS) ? -42 : 0;
                }
                return err;
            }
            template <typename Parameters>
                inline PXY
            loc_for(double const& lp_lam, double const& lp_phi, const Parameters& par, par_imw_p const& proj_parm, double *yc) {
                PXY xy;

                if (! lp_phi) {
                    xy.x = lp_lam;
                    xy.y = 0.;
                } else {
                    double xa, ya, xb, yb, xc, D, B, m, sp, t, R, C;

                    sp = sin(lp_phi);
                    m = pj_mlfn(lp_phi, sp, cos(lp_phi), proj_parm.en);
                    xa = proj_parm.Pp + proj_parm.Qp * m;
                    ya = proj_parm.P + proj_parm.Q * m;
                    R = 1. / (tan(lp_phi) * sqrt(1. - par.es * sp * sp));
                    C = sqrt(R * R - xa * xa);
                    if (lp_phi < 0.) C = - C;
                    C += ya - R;
                    if (proj_parm.mode < 0) {
                        xb = lp_lam;
                        yb = proj_parm.C2;
                    } else {
                        t = lp_lam * proj_parm.sphi_2;
                        xb = proj_parm.R_2 * sin(t);
                        yb = proj_parm.C2 + proj_parm.R_2 * (1. - cos(t));
                    }
                    if (proj_parm.mode > 0) {
                        xc = lp_lam;
                        *yc = 0.;
                    } else {
                        t = lp_lam * proj_parm.sphi_1;
                        xc = proj_parm.R_1 * sin(t);
                        *yc = proj_parm.R_1 * (1. - cos(t));
                    }
                    D = (xb - xc)/(yb - *yc);
                    B = xc + D * (C + R - *yc);
                    xy.x = D * sqrt(R * R * (1 + D * D) - B * B);
                    if (lp_phi > 0)
                        xy.x = - xy.x;
                    xy.x = (B + xy.x) / (1. + D * D);
                    xy.y = sqrt(R * R - xy.x * xy.x);
                    if (lp_phi > 0)
                        xy.y = - xy.y;
                    xy.y += C + R;
                }
                return (xy);
            }

            template <typename Parameters>
            inline void
            xy(Parameters& par, par_imw_p& proj_parm, double phi, double *x, double *y, double *sp, double *R) {
                double F;

                *sp = sin(phi);
                *R = 1./(tan(phi) * sqrt(1. - par.es * *sp * *sp ));
                F = proj_parm.lam_1 * *sp;
                *y = *R * (1 - cos(F));
                *x = *R * sin(F);
            }


            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_imw_p_ellipsoid : public base_t_fi<base_imw_p_ellipsoid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_imw_p m_proj_parm;

                inline base_imw_p_ellipsoid(const Parameters& par)
                    : base_t_fi<base_imw_p_ellipsoid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    double yc = 0;
                    PXY xy = loc_for(lp_lon, lp_lat, this->m_par, m_proj_parm, &yc);
                    xy_x = xy.x; xy_y = xy.y;
                }

                inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
                {
                    PXY t;
                    double yc = 0;

                    lp_lat = this->m_proj_parm.phi_2;
                    lp_lon = xy_x / cos(lp_lat);
                    do {
                        t = loc_for(lp_lon, lp_lat, this->m_par, m_proj_parm, &yc);
                        lp_lat = ((lp_lat - this->m_proj_parm.phi_1) * (xy_y - yc) / (t.y - yc)) + this->m_proj_parm.phi_1;
                        lp_lon = lp_lon * xy_x / t.x;
                    } while (fabs(t.x - xy_x) > TOL || fabs(t.y - xy_y) > TOL);
                }
            };

            // International Map of the World Polyconic
            template <typename Parameters>
            void setup_imw_p(Parameters& par, par_imw_p& proj_parm)
            {
                double del, sig, s, t, x1, x2, T2, y1, m1, m2, y2;
                int i;
                    pj_enfn(par.es, proj_parm.en);
                if( (i = phi12(par, proj_parm, &del, &sig)) != 0)
                    throw proj_exception(i);
                if (proj_parm.phi_2 < proj_parm.phi_1) { /* make sure proj_parm.phi_1 most southerly */
                    del = proj_parm.phi_1;
                    proj_parm.phi_1 = proj_parm.phi_2;
                    proj_parm.phi_2 = del;
                }
                if (pj_param(par.params, "tlon_1").i)
                    proj_parm.lam_1 = pj_param(par.params, "rlon_1").f;
                else { /* use predefined based upon latitude */
                    sig = fabs(sig * RAD_TO_DEG);
                    if (sig <= 60)        sig = 2.;
                    else if (sig <= 76) sig = 4.;
                    else                sig = 8.;
                    proj_parm.lam_1 = sig * DEG_TO_RAD;
                }
                proj_parm.mode = 0;
                if (proj_parm.phi_1) xy(par, proj_parm, proj_parm.phi_1, &x1, &y1, &proj_parm.sphi_1, &proj_parm.R_1);
                else {
                    proj_parm.mode = 1;
                    y1 = 0.;
                    x1 = proj_parm.lam_1;
                }
                if (proj_parm.phi_2) xy(par, proj_parm, proj_parm.phi_2, &x2, &T2, &proj_parm.sphi_2, &proj_parm.R_2);
                else {
                    proj_parm.mode = -1;
                    T2 = 0.;
                    x2 = proj_parm.lam_1;
                }
                m1 = pj_mlfn(proj_parm.phi_1, proj_parm.sphi_1, cos(proj_parm.phi_1), proj_parm.en);
                m2 = pj_mlfn(proj_parm.phi_2, proj_parm.sphi_2, cos(proj_parm.phi_2), proj_parm.en);
                t = m2 - m1;
                s = x2 - x1;
                y2 = sqrt(t * t - s * s) + y1;
                proj_parm.C2 = y2 - T2;
                t = 1. / t;
                proj_parm.P = (m2 * y1 - m1 * y2) * t;
                proj_parm.Q = (y2 - y1) * t;
                proj_parm.Pp = (m2 * x1 - m1 * x2) * t;
                proj_parm.Qp = (x2 - x1) * t;
                // par.fwd = e_forward;
                // par.inv = e_inverse;
            }

        }} // namespace detail::imw_p
    #endif // doxygen

    /*!
        \brief International Map of the World Polyconic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Mod Polyconic
         - Ellipsoid
         - lat_1= and lat_2= [lon_1=]
        \par Example
        \image html ex_imw_p.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct imw_p_ellipsoid : public detail::imw_p::base_imw_p_ellipsoid<Geographic, Cartesian, Parameters>
    {
        inline imw_p_ellipsoid(const Parameters& par) : detail::imw_p::base_imw_p_ellipsoid<Geographic, Cartesian, Parameters>(par)
        {
            detail::imw_p::setup_imw_p(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class imw_p_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<imw_p_ellipsoid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void imw_p_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("imw_p", new imw_p_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

}}} // namespace boost::geometry::projection

#endif // BOOST_GEOMETRY_PROJECTIONS_IMW_P_HPP

