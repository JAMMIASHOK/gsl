/* blas/source_rotg.h
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

/*
 * Author:  G. Jungman
 * RCS:     $Id$
 */

  const BASE_TYPE roe   = ( fabs(*a) > fabs(*b) ? *a : *b );
  const BASE_TYPE scale = fabs(*a) + fabs(*b);
  BASE_TYPE r, z;

  if( scale != 0.0 ) {
    const BASE_TYPE aos = *a/scale;
    const BASE_TYPE bos = *b/scale;
    r = scale * sqrt(aos*aos + bos*bos);
    r = GSL_SIGN(roe) * r;
    *c = *a/r;
    *s = *b/r;
    z = 1.0;
    if( fabs(*a) > fabs(*b) ) z = *s;
    if( fabs(*b) >= fabs(*a) && *c != 0.0 ) z = 1.0/(*c);
  }
  else {
   *c = 1.0;
   *s = 0.0;
   r = 0.0;
   z = 0.0;
  }
  
  *a = r;
  *b = z;
