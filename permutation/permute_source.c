/* permutation/permute_source.c
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Brian Gough
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

/* In-place Permutations 

   permute:    OUT[i]       = IN[perm[i]]     i = 0 .. N-1
   invpermute: OUT[perm[i]] = IN[i]           i = 0 .. N-1

   PERM is an index map, i.e. a vector which contains a permutation of
   the integers 0 .. N-1.

   From Knuth "Sorting and Searching", Volume 3 (3rd ed), Section 5.2
   Exercise 10 (answers), p 617

   FIXME: these have not been fully tested.
*/

int
TYPE (gsl_permute) (const size_t * p, BASE * data, const size_t stride, const size_t n)
{
  size_t i, k, pk;

  BASE r1, t;
  
  for (i = 0; i < n; i++)
    {
      k = p[i];
      
      while (k > i) 
        k = p[k];
      
      if (k < i)
        continue ;
      
      /* Now have k == i, i.e the least in its cycle */
      
      pk = p[k];
      
      if (pk == i)
        continue ;
      
      /* shuffle the elements of the cycle */
      
      t = data[i*stride];
      
      while (pk != i)
        {
          r1 = data[pk*stride];
          data[k*stride] = r1;
          k = pk;
          pk = p[k];
        };
      
      data[k*stride] = t;
    }

  return GSL_SUCCESS;
}

int
FUNCTION (gsl_permute,inverse) (const size_t * p, BASE * data, const size_t stride, const size_t n)
{
  size_t i, k, pk;

  BASE r1, t;

  for (i = 0; i < n; i++)
    {
      k = p[i];
          
      while (k > i) 
        k = p[k];

      if (k < i)
        continue ;
      
      /* Now have k == i, i.e the least in its cycle */

      pk = p[k];

      if (pk == i)
        continue ;
      
      /* shuffle the elements of the cycle in the inverse direction */
      
      t = data[k*stride];

      while (pk != i)
        {
          r1 = data[pk*stride];
          data[pk*stride] = t;
          k = pk;
          pk = p[k];
          t = r1;
        };
      
      data[pk*stride] = t;
    }

  return GSL_SUCCESS;
}


int
TYPE (gsl_permute_vector) (const gsl_permutation * p, TYPE (gsl_vector) * v)
{
  if (v->size != p->size)
    {
      GSL_ERROR ("vector and permutation must be the same length", GSL_EBADLEN);
    }

  TYPE (gsl_permute) (p->data, v->data, v->stride, v->size) ;

  return GSL_SUCCESS;
}

int
FUNCTION (gsl_permute_vector,inverse) (const gsl_permutation * p, TYPE (gsl_vector) * v)
{
  if (v->size != p->size)
    {
      GSL_ERROR ("vector and permutation must be the same length", GSL_EBADLEN);
    }

  FUNCTION (gsl_permute,inverse) (p->data, v->data, v->stride, v->size) ;

  return GSL_SUCCESS;
}
