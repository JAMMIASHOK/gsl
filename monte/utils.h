/* monte/utils.h
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Michael Booth
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


double *gsl_monte_vector_alloc(const size_t n);
double *gsl_monte_vector_calloc(const size_t n);
int gsl_monte_vector_free(double * v);

int *gsl_monte_vector_int_alloc(const size_t n);
int *gsl_monte_vector_int_calloc(const size_t n);
int gsl_monte_vector_int_free(int *v);

