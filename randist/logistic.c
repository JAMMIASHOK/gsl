/* randist/logistic.c
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 James Theiler, Brian Gough
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

#include <config.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/* The logistic distribution has the form,

   p(x) dx = (1/mu) exp(-x/mu) / (1 + exp(-x/mu))^2 dx

   for -infty < x < infty */

double
gsl_ran_logistic (const gsl_rng * r, const double mu)
{
  double x, z;

  do
    {
      x = gsl_rng_uniform_pos (r);
    }
  while (x == 1);

  z = log (x / (1 - x));

  return mu * z;
}

double
gsl_ran_logistic_pdf (const double x, const double mu)
{
  double u = exp (-fabs(x)/mu);
  double p = u / (fabs(mu) * (1 + u) * (1 + u));
  return p;
}
