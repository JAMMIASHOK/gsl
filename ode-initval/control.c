/* ode-initval/control.c
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Gerard Jungman
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Author:  G. Jungman
 * RCS:     $Id$
 */
#include <config.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include "gsl_odeiv.h"



static void
data_free(void * data)
{
  if(data != 0) free(data);
}


static int
hadjust(void * data, size_t dim, unsigned int ord, const double y[], const double yerr[], const double yp[], double * h)
{
  const double * d = (double *) data;
  const double eps_abs = d[0];
  const double eps_rel = d[1];
  const double a_y     = d[2];
  const double a_dydt  = d[3];
  const double S = 0.9;
  const double h_old = fabs(*h);
  double rmax = DBL_MIN;
  size_t i;

  for(i=0; i<dim; i++) {
    const double D0 = eps_rel * (a_y * fabs(y[i]) + a_dydt * h_old * fabs(yp[i])) + eps_abs;
    const double r  = fabs(yerr[i])/(fabs(D0) + 2.0*DBL_MIN);
    rmax = GSL_MAX_DBL(r, rmax);
  }

  if(rmax > 1.1) {
    /* decrease step, no more than factor of 5 */
    *h = h_old * S / pow(rmax, 1.0/ord);
    *h = GSL_MAX_DBL(0.2 * h_old, *h);
    return GSL_ODEIV_HADJ_DEC;
  }
  else if(rmax < 0.9) {
    /* increase step, no more than factor of 5 */
    *h = h_old / S / pow(rmax, 1.0/(ord+1.0));
    *h = GSL_MIN_DBL(5.0 * h_old, *h);
    return GSL_ODEIV_HADJ_INC;
  }
  else {
    /* no change */
    return GSL_ODEIV_HADJ_NIL;
  }
}


gsl_odeiv_evolve_control *
gsl_odeiv_evolve_control_standard_new(
  double eps_rel,
  double eps_abs,
  double a_y,
  double a_dydt)
{
  gsl_odeiv_evolve_control * c = (gsl_odeiv_evolve_control *) malloc(sizeof(gsl_odeiv_evolve_control));
  if(c != 0) {
    double * d;
    c->_data_size = 4 * sizeof(double);
    c->_data = malloc(c->_data_size);
    if(c->_data == 0) {
      free(c);
      return 0;
    }
    d = (double *) c->_data;
    d[0] = eps_abs;
    d[1] = eps_rel;
    d[2] = a_y;
    d[3] = a_dydt;
    c->_free = data_free;
    c->_hadjust = hadjust;
  }  
  return c;
}


gsl_odeiv_evolve_control *
gsl_odeiv_evolve_control_y_new(double eps_rel, double eps_abs)
{
  return gsl_odeiv_evolve_control_standard_new(eps_rel, eps_abs, 1.0, 0.0);
}


gsl_odeiv_evolve_control *
gsl_odeiv_evolve_control_yp_new(double eps_rel, double eps_abs)
{
  return gsl_odeiv_evolve_control_standard_new(eps_rel, eps_abs, 0.0, 1.0);

}


void
gsl_odeiv_evolve_control_free(gsl_odeiv_evolve_control * c)
{
  if(c != 0) {
    if(c->_free != 0) c->_free(c->_data);
    free(c);
  }
}
