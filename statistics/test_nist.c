/* statistics/test_nist.c
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Jim Davies, Brian Gough
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

/* These tests are based on the NIST Statistical Reference Datasets
   See http://www.nist.gov/itl/div898/strd/index.html for more
   information. */

#include <config.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_test.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_ieee_utils.h>

int
main (void)
{
  size_t i ;

  const size_t nlew = 200 ; 

  const double lew[200] = { 
    -213, -564,  -35,  -15,  141,  115, -420, -360,  203, -338, -431,  194,
    -220, -513,  154, -125, -559,   92,  -21, -579,  -52,   99, -543, -175,
     162, -457, -346,  204, -300, -474,  164, -107, -572,   -8,   83, -541,
    -224,  180, -420, -374,  201, -236, -531,   83,   27, -564, -112,  131,
    -507, -254,  199, -311, -495,  143,  -46, -579,  -90,  136, -472, -338,
     202, -287, -477,  169, -124, -568,   17,   48, -568, -135,  162, -430,
    -422,  172,  -74, -577,  -13,   92, -534, -243,  194, -355, -465,  156,
     -81, -578,  -64,  139, -449, -384,  193, -198, -538,  110,  -44, -577,
      -6,   66, -552, -164,  161, -460, -344,  205, -281, -504,  134,  -28,
    -576, -118,  156, -437, -381,  200, -220, -540,   83,   11, -568, -160,
     172, -414, -408,  188, -125, -572,  -32,  139, -492, -321,  205, -262,
    -504,  142,  -83, -574,    0,   48, -571, -106,  137, -501, -266,  190,
    -391, -406,  194, -186, -553,   83,  -13, -577,  -49,  103, -515, -280,
     201,  300, -506,  131,  -45, -578,  -80,  138, -462, -361,  201, -211,
    -554,   32,   74, -533, -235,  187, -372, -442,  182, -147, -566,   25,
      68, -535, -244,  194, -351, -463,  174, -125, -570,   15,   72, -550,
    -190,  172, -424, -385,  198, -218, -536,   96 } ;

  const size_t nlottery = 218 ;

  const double lottery[218] = { 
    162, 671, 933, 414, 788, 730, 817, 33, 536, 875, 670, 236, 473, 167,
    877, 980, 316, 950, 456, 92, 517, 557, 956, 954, 104, 178, 794, 278,
    147, 773, 437, 435, 502, 610, 582, 780, 689, 562, 964, 791, 28, 97,
    848, 281, 858, 538, 660, 972, 671, 613, 867, 448, 738, 966, 139, 636,
    847, 659, 754, 243, 122, 455, 195, 968, 793, 59, 730, 361, 574, 522,
    97, 762, 431, 158, 429, 414, 22, 629, 788, 999, 187, 215, 810, 782,
    47, 34, 108, 986, 25, 644, 829, 630, 315, 567, 919, 331, 207, 412,
    242, 607, 668, 944, 749, 168, 864, 442, 533, 805, 372, 63, 458, 777,
    416, 340, 436, 140, 919, 350, 510, 572, 905, 900, 85, 389, 473, 758,
    444, 169, 625, 692, 140, 897, 672, 288, 312, 860, 724, 226, 884, 508,
    976, 741, 476, 417, 831, 15, 318, 432, 241, 114, 799, 955, 833, 358,
    935, 146, 630, 830, 440, 642, 356, 373, 271, 715, 367, 393, 190, 669,
    8, 861, 108, 795, 269, 590, 326, 866, 64, 523, 862, 840, 219, 382,
    998, 4, 628, 305, 747, 247, 34, 747, 729, 645, 856, 974, 24, 568, 24,
    694, 608, 480, 410, 729, 947, 293, 53, 930, 223, 203, 677, 227, 62,
    455, 387, 318, 562, 242, 428, 968 } ;

  const size_t nmavro = 50 ;

  const double mavro[50] = { 
    2.00180, 2.00170, 2.00180, 2.00190, 2.00180, 2.00170, 2.00150,
    2.00140, 2.00150, 2.00150, 2.00170, 2.00180, 2.00180, 2.00190,
    2.00190, 2.00210, 2.00200, 2.00160, 2.00140, 2.00130, 2.00130,
    2.00150, 2.00150, 2.00160, 2.00150, 2.00140, 2.00130, 2.00140,
    2.00150, 2.00140, 2.00150, 2.00160, 2.00150, 2.00160, 2.00190,
    2.00200, 2.00200, 2.00210, 2.00220, 2.00230, 2.00240, 2.00250,
    2.00270, 2.00260, 2.00260, 2.00260, 2.00270, 2.00260, 2.00250, 
    2.00240 } ;

  const size_t nmichelson = 100 ;

  const double michelson [100] = { 
    299.85, 299.74, 299.90, 300.07, 299.93, 299.85, 299.95, 299.98,
    299.98, 299.88, 300.00, 299.98, 299.93, 299.65, 299.76, 299.81,
    300.00, 300.00, 299.96, 299.96, 299.96, 299.94, 299.96, 299.94,
    299.88, 299.80, 299.85, 299.88, 299.90, 299.84, 299.83, 299.79,
    299.81, 299.88, 299.88, 299.83, 299.80, 299.79, 299.76, 299.80,
    299.88, 299.88, 299.88, 299.86, 299.72, 299.72, 299.62, 299.86,
    299.97, 299.95, 299.88, 299.91, 299.85, 299.87, 299.84, 299.84,
    299.85, 299.84, 299.84, 299.84, 299.89, 299.81, 299.81, 299.82,
    299.80, 299.77, 299.76, 299.74, 299.75, 299.76, 299.91, 299.92,
    299.89, 299.86, 299.88, 299.72, 299.84, 299.85, 299.85, 299.78,
    299.89, 299.84, 299.78, 299.81, 299.76, 299.81, 299.79, 299.81,
    299.82, 299.85, 299.87, 299.87, 299.81, 299.74, 299.81, 299.94,
    299.95, 299.80, 299.81, 299.87 } ;

  const size_t npidigits = 5000 ;
  const double pidigits [5000] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8,
    9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2,
    8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 5, 1, 0, 5, 8, 2, 0, 9,
    7, 4, 9, 4, 4, 5, 9, 2, 3, 0, 7, 8, 1, 6, 4, 0, 6, 2, 8, 6, 2, 0,
    8, 9, 9, 8, 6, 2, 8, 0, 3, 4, 8, 2, 5, 3, 4, 2, 1, 1, 7, 0, 6, 7,
    9, 8, 2, 1, 4, 8, 0, 8, 6, 5, 1, 3, 2, 8, 2, 3, 0, 6, 6, 4, 7, 0,
    9, 3, 8, 4, 4, 6, 0, 9, 5, 5, 0, 5, 8, 2, 2, 3, 1, 7, 2, 5, 3, 5,
    9, 4, 0, 8, 1, 2, 8, 4, 8, 1, 1, 1, 7, 4, 5, 0, 2, 8, 4, 1, 0, 2,
    7, 0, 1, 9, 3, 8, 5, 2, 1, 1, 0, 5, 5, 5, 9, 6, 4, 4, 6, 2, 2, 9,
    4, 8, 9, 5, 4, 9, 3, 0, 3, 8, 1, 9, 6, 4, 4, 2, 8, 8, 1, 0, 9, 7,
    5, 6, 6, 5, 9, 3, 3, 4, 4, 6, 1, 2, 8, 4, 7, 5, 6, 4, 8, 2, 3, 3,
    7, 8, 6, 7, 8, 3, 1, 6, 5, 2, 7, 1, 2, 0, 1, 9, 0, 9, 1, 4, 5, 6,
    4, 8, 5, 6, 6, 9, 2, 3, 4, 6, 0, 3, 4, 8, 6, 1, 0, 4, 5, 4, 3, 2,
    6, 6, 4, 8, 2, 1, 3, 3, 9, 3, 6, 0, 7, 2, 6, 0, 2, 4, 9, 1, 4, 1,
    2, 7, 3, 7, 2, 4, 5, 8, 7, 0, 0, 6, 6, 0, 6, 3, 1, 5, 5, 8, 8, 1,
    7, 4, 8, 8, 1, 5, 2, 0, 9, 2, 0, 9, 6, 2, 8, 2, 9, 2, 5, 4, 0, 9,
    1, 7, 1, 5, 3, 6, 4, 3, 6, 7, 8, 9, 2, 5, 9, 0, 3, 6, 0, 0, 1, 1,
    3, 3, 0, 5, 3, 0, 5, 4, 8, 8, 2, 0, 4, 6, 6, 5, 2, 1, 3, 8, 4, 1,
    4, 6, 9, 5, 1, 9, 4, 1, 5, 1, 1, 6, 0, 9, 4, 3, 3, 0, 5, 7, 2, 7,
    0, 3, 6, 5, 7, 5, 9, 5, 9, 1, 9, 5, 3, 0, 9, 2, 1, 8, 6, 1, 1, 7,
    3, 8, 1, 9, 3, 2, 6, 1, 1, 7, 9, 3, 1, 0, 5, 1, 1, 8, 5, 4, 8, 0,
    7, 4, 4, 6, 2, 3, 7, 9, 9, 6, 2, 7, 4, 9, 5, 6, 7, 3, 5, 1, 8, 8,
    5, 7, 5, 2, 7, 2, 4, 8, 9, 1, 2, 2, 7, 9, 3, 8, 1, 8, 3, 0, 1, 1,
    9, 4, 9, 1, 2, 9, 8, 3, 3, 6, 7, 3, 3, 6, 2, 4, 4, 0, 6, 5, 6, 6,
    4, 3, 0, 8, 6, 0, 2, 1, 3, 9, 4, 9, 4, 6, 3, 9, 5, 2, 2, 4, 7, 3,
    7, 1, 9, 0, 7, 0, 2, 1, 7, 9, 8, 6, 0, 9, 4, 3, 7, 0, 2, 7, 7, 0,
    5, 3, 9, 2, 1, 7, 1, 7, 6, 2, 9, 3, 1, 7, 6, 7, 5, 2, 3, 8, 4, 6,
    7, 4, 8, 1, 8, 4, 6, 7, 6, 6, 9, 4, 0, 5, 1, 3, 2, 0, 0, 0, 5, 6,
    8, 1, 2, 7, 1, 4, 5, 2, 6, 3, 5, 6, 0, 8, 2, 7, 7, 8, 5, 7, 7, 1,
    3, 4, 2, 7, 5, 7, 7, 8, 9, 6, 0, 9, 1, 7, 3, 6, 3, 7, 1, 7, 8, 7,
    2, 1, 4, 6, 8, 4, 4, 0, 9, 0, 1, 2, 2, 4, 9, 5, 3, 4, 3, 0, 1, 4,
    6, 5, 4, 9, 5, 8, 5, 3, 7, 1, 0, 5, 0, 7, 9, 2, 2, 7, 9, 6, 8, 9,
    2, 5, 8, 9, 2, 3, 5, 4, 2, 0, 1, 9, 9, 5, 6, 1, 1, 2, 1, 2, 9, 0,
    2, 1, 9, 6, 0, 8, 6, 4, 0, 3, 4, 4, 1, 8, 1, 5, 9, 8, 1, 3, 6, 2,
    9, 7, 7, 4, 7, 7, 1, 3, 0, 9, 9, 6, 0, 5, 1, 8, 7, 0, 7, 2, 1, 1,
    3, 4, 9, 9, 9, 9, 9, 9, 8, 3, 7, 2, 9, 7, 8, 0, 4, 9, 9, 5, 1, 0,
    5, 9, 7, 3, 1, 7, 3, 2, 8, 1, 6, 0, 9, 6, 3, 1, 8, 5, 9, 5, 0, 2,
    4, 4, 5, 9, 4, 5, 5, 3, 4, 6, 9, 0, 8, 3, 0, 2, 6, 4, 2, 5, 2, 2,
    3, 0, 8, 2, 5, 3, 3, 4, 4, 6, 8, 5, 0, 3, 5, 2, 6, 1, 9, 3, 1, 1,
    8, 8, 1, 7, 1, 0, 1, 0, 0, 0, 3, 1, 3, 7, 8, 3, 8, 7, 5, 2, 8, 8,
    6, 5, 8, 7, 5, 3, 3, 2, 0, 8, 3, 8, 1, 4, 2, 0, 6, 1, 7, 1, 7, 7,
    6, 6, 9, 1, 4, 7, 3, 0, 3, 5, 9, 8, 2, 5, 3, 4, 9, 0, 4, 2, 8, 7,
    5, 5, 4, 6, 8, 7, 3, 1, 1, 5, 9, 5, 6, 2, 8, 6, 3, 8, 8, 2, 3, 5,
    3, 7, 8, 7, 5, 9, 3, 7, 5, 1, 9, 5, 7, 7, 8, 1, 8, 5, 7, 7, 3, 0,
    5, 3, 2, 1, 7, 1, 2, 2, 6, 8, 0, 6, 6, 1, 3, 0, 0, 1, 9, 2, 7, 8,
    7, 6, 6, 1, 1, 1, 9, 5, 9, 0, 9, 2, 1, 6, 4, 2, 0, 1, 9, 8, 9, 3,
    8, 0, 9, 5, 2, 5, 7, 2, 0, 1, 0, 6, 5, 4, 8, 5, 8, 6, 3, 2, 7, 8,
    8, 6, 5, 9, 3, 6, 1, 5, 3, 3, 8, 1, 8, 2, 7, 9, 6, 8, 2, 3, 0, 3,
    0, 1, 9, 5, 2, 0, 3, 5, 3, 0, 1, 8, 5, 2, 9, 6, 8, 9, 9, 5, 7, 7,
    3, 6, 2, 2, 5, 9, 9, 4, 1, 3, 8, 9, 1, 2, 4, 9, 7, 2, 1, 7, 7, 5,
    2, 8, 3, 4, 7, 9, 1, 3, 1, 5, 1, 5, 5, 7, 4, 8, 5, 7, 2, 4, 2, 4,
    5, 4, 1, 5, 0, 6, 9, 5, 9, 5, 0, 8, 2, 9, 5, 3, 3, 1, 1, 6, 8, 6,
    1, 7, 2, 7, 8, 5, 5, 8, 8, 9, 0, 7, 5, 0, 9, 8, 3, 8, 1, 7, 5, 4,
    6, 3, 7, 4, 6, 4, 9, 3, 9, 3, 1, 9, 2, 5, 5, 0, 6, 0, 4, 0, 0, 9,
    2, 7, 7, 0, 1, 6, 7, 1, 1, 3, 9, 0, 0, 9, 8, 4, 8, 8, 2, 4, 0, 1,
    2, 8, 5, 8, 3, 6, 1, 6, 0, 3, 5, 6, 3, 7, 0, 7, 6, 6, 0, 1, 0, 4,
    7, 1, 0, 1, 8, 1, 9, 4, 2, 9, 5, 5, 5, 9, 6, 1, 9, 8, 9, 4, 6, 7,
    6, 7, 8, 3, 7, 4, 4, 9, 4, 4, 8, 2, 5, 5, 3, 7, 9, 7, 7, 4, 7, 2,
    6, 8, 4, 7, 1, 0, 4, 0, 4, 7, 5, 3, 4, 6, 4, 6, 2, 0, 8, 0, 4, 6,
    6, 8, 4, 2, 5, 9, 0, 6, 9, 4, 9, 1, 2, 9, 3, 3, 1, 3, 6, 7, 7, 0,
    2, 8, 9, 8, 9, 1, 5, 2, 1, 0, 4, 7, 5, 2, 1, 6, 2, 0, 5, 6, 9, 6,
    6, 0, 2, 4, 0, 5, 8, 0, 3, 8, 1, 5, 0, 1, 9, 3, 5, 1, 1, 2, 5, 3,
    3, 8, 2, 4, 3, 0, 0, 3, 5, 5, 8, 7, 6, 4, 0, 2, 4, 7, 4, 9, 6, 4,
    7, 3, 2, 6, 3, 9, 1, 4, 1, 9, 9, 2, 7, 2, 6, 0, 4, 2, 6, 9, 9, 2,
    2, 7, 9, 6, 7, 8, 2, 3, 5, 4, 7, 8, 1, 6, 3, 6, 0, 0, 9, 3, 4, 1,
    7, 2, 1, 6, 4, 1, 2, 1, 9, 9, 2, 4, 5, 8, 6, 3, 1, 5, 0, 3, 0, 2,
    8, 6, 1, 8, 2, 9, 7, 4, 5, 5, 5, 7, 0, 6, 7, 4, 9, 8, 3, 8, 5, 0,
    5, 4, 9, 4, 5, 8, 8, 5, 8, 6, 9, 2, 6, 9, 9, 5, 6, 9, 0, 9, 2, 7,
    2, 1, 0, 7, 9, 7, 5, 0, 9, 3, 0, 2, 9, 5, 5, 3, 2, 1, 1, 6, 5, 3,
    4, 4, 9, 8, 7, 2, 0, 2, 7, 5, 5, 9, 6, 0, 2, 3, 6, 4, 8, 0, 6, 6,
    5, 4, 9, 9, 1, 1, 9, 8, 8, 1, 8, 3, 4, 7, 9, 7, 7, 5, 3, 5, 6, 6,
    3, 6, 9, 8, 0, 7, 4, 2, 6, 5, 4, 2, 5, 2, 7, 8, 6, 2, 5, 5, 1, 8,
    1, 8, 4, 1, 7, 5, 7, 4, 6, 7, 2, 8, 9, 0, 9, 7, 7, 7, 7, 2, 7, 9,
    3, 8, 0, 0, 0, 8, 1, 6, 4, 7, 0, 6, 0, 0, 1, 6, 1, 4, 5, 2, 4, 9,
    1, 9, 2, 1, 7, 3, 2, 1, 7, 2, 1, 4, 7, 7, 2, 3, 5, 0, 1, 4, 1, 4,
    4, 1, 9, 7, 3, 5, 6, 8, 5, 4, 8, 1, 6, 1, 3, 6, 1, 1, 5, 7, 3, 5,
    2, 5, 5, 2, 1, 3, 3, 4, 7, 5, 7, 4, 1, 8, 4, 9, 4, 6, 8, 4, 3, 8,
    5, 2, 3, 3, 2, 3, 9, 0, 7, 3, 9, 4, 1, 4, 3, 3, 3, 4, 5, 4, 7, 7,
    6, 2, 4, 1, 6, 8, 6, 2, 5, 1, 8, 9, 8, 3, 5, 6, 9, 4, 8, 5, 5, 6,
    2, 0, 9, 9, 2, 1, 9, 2, 2, 2, 1, 8, 4, 2, 7, 2, 5, 5, 0, 2, 5, 4,
    2, 5, 6, 8, 8, 7, 6, 7, 1, 7, 9, 0, 4, 9, 4, 6, 0, 1, 6, 5, 3, 4,
    6, 6, 8, 0, 4, 9, 8, 8, 6, 2, 7, 2, 3, 2, 7, 9, 1, 7, 8, 6, 0, 8,
    5, 7, 8, 4, 3, 8, 3, 8, 2, 7, 9, 6, 7, 9, 7, 6, 6, 8, 1, 4, 5, 4,
    1, 0, 0, 9, 5, 3, 8, 8, 3, 7, 8, 6, 3, 6, 0, 9, 5, 0, 6, 8, 0, 0,
    6, 4, 2, 2, 5, 1, 2, 5, 2, 0, 5, 1, 1, 7, 3, 9, 2, 9, 8, 4, 8, 9,
    6, 0, 8, 4, 1, 2, 8, 4, 8, 8, 6, 2, 6, 9, 4, 5, 6, 0, 4, 2, 4, 1,
    9, 6, 5, 2, 8, 5, 0, 2, 2, 2, 1, 0, 6, 6, 1, 1, 8, 6, 3, 0, 6, 7,
    4, 4, 2, 7, 8, 6, 2, 2, 0, 3, 9, 1, 9, 4, 9, 4, 5, 0, 4, 7, 1, 2,
    3, 7, 1, 3, 7, 8, 6, 9, 6, 0, 9, 5, 6, 3, 6, 4, 3, 7, 1, 9, 1, 7,
    2, 8, 7, 4, 6, 7, 7, 6, 4, 6, 5, 7, 5, 7, 3, 9, 6, 2, 4, 1, 3, 8,
    9, 0, 8, 6, 5, 8, 3, 2, 6, 4, 5, 9, 9, 5, 8, 1, 3, 3, 9, 0, 4, 7,
    8, 0, 2, 7, 5, 9, 0, 0, 9, 9, 4, 6, 5, 7, 6, 4, 0, 7, 8, 9, 5, 1,
    2, 6, 9, 4, 6, 8, 3, 9, 8, 3, 5, 2, 5, 9, 5, 7, 0, 9, 8, 2, 5, 8,
    2, 2, 6, 2, 0, 5, 2, 2, 4, 8, 9, 4, 0, 7, 7, 2, 6, 7, 1, 9, 4, 7,
    8, 2, 6, 8, 4, 8, 2, 6, 0, 1, 4, 7, 6, 9, 9, 0, 9, 0, 2, 6, 4, 0,
    1, 3, 6, 3, 9, 4, 4, 3, 7, 4, 5, 5, 3, 0, 5, 0, 6, 8, 2, 0, 3, 4,
    9, 6, 2, 5, 2, 4, 5, 1, 7, 4, 9, 3, 9, 9, 6, 5, 1, 4, 3, 1, 4, 2,
    9, 8, 0, 9, 1, 9, 0, 6, 5, 9, 2, 5, 0, 9, 3, 7, 2, 2, 1, 6, 9, 6,
    4, 6, 1, 5, 1, 5, 7, 0, 9, 8, 5, 8, 3, 8, 7, 4, 1, 0, 5, 9, 7, 8,
    8, 5, 9, 5, 9, 7, 7, 2, 9, 7, 5, 4, 9, 8, 9, 3, 0, 1, 6, 1, 7, 5,
    3, 9, 2, 8, 4, 6, 8, 1, 3, 8, 2, 6, 8, 6, 8, 3, 8, 6, 8, 9, 4, 2,
    7, 7, 4, 1, 5, 5, 9, 9, 1, 8, 5, 5, 9, 2, 5, 2, 4, 5, 9, 5, 3, 9,
    5, 9, 4, 3, 1, 0, 4, 9, 9, 7, 2, 5, 2, 4, 6, 8, 0, 8, 4, 5, 9, 8,
    7, 2, 7, 3, 6, 4, 4, 6, 9, 5, 8, 4, 8, 6, 5, 3, 8, 3, 6, 7, 3, 6,
    2, 2, 2, 6, 2, 6, 0, 9, 9, 1, 2, 4, 6, 0, 8, 0, 5, 1, 2, 4, 3, 8,
    8, 4, 3, 9, 0, 4, 5, 1, 2, 4, 4, 1, 3, 6, 5, 4, 9, 7, 6, 2, 7, 8,
    0, 7, 9, 7, 7, 1, 5, 6, 9, 1, 4, 3, 5, 9, 9, 7, 7, 0, 0, 1, 2, 9,
    6, 1, 6, 0, 8, 9, 4, 4, 1, 6, 9, 4, 8, 6, 8, 5, 5, 5, 8, 4, 8, 4,
    0, 6, 3, 5, 3, 4, 2, 2, 0, 7, 2, 2, 2, 5, 8, 2, 8, 4, 8, 8, 6, 4,
    8, 1, 5, 8, 4, 5, 6, 0, 2, 8, 5, 0, 6, 0, 1, 6, 8, 4, 2, 7, 3, 9,
    4, 5, 2, 2, 6, 7, 4, 6, 7, 6, 7, 8, 8, 9, 5, 2, 5, 2, 1, 3, 8, 5,
    2, 2, 5, 4, 9, 9, 5, 4, 6, 6, 6, 7, 2, 7, 8, 2, 3, 9, 8, 6, 4, 5,
    6, 5, 9, 6, 1, 1, 6, 3, 5, 4, 8, 8, 6, 2, 3, 0, 5, 7, 7, 4, 5, 6,
    4, 9, 8, 0, 3, 5, 5, 9, 3, 6, 3, 4, 5, 6, 8, 1, 7, 4, 3, 2, 4, 1,
    1, 2, 5, 1, 5, 0, 7, 6, 0, 6, 9, 4, 7, 9, 4, 5, 1, 0, 9, 6, 5, 9,
    6, 0, 9, 4, 0, 2, 5, 2, 2, 8, 8, 7, 9, 7, 1, 0, 8, 9, 3, 1, 4, 5,
    6, 6, 9, 1, 3, 6, 8, 6, 7, 2, 2, 8, 7, 4, 8, 9, 4, 0, 5, 6, 0, 1,
    0, 1, 5, 0, 3, 3, 0, 8, 6, 1, 7, 9, 2, 8, 6, 8, 0, 9, 2, 0, 8, 7,
    4, 7, 6, 0, 9, 1, 7, 8, 2, 4, 9, 3, 8, 5, 8, 9, 0, 0, 9, 7, 1, 4,
    9, 0, 9, 6, 7, 5, 9, 8, 5, 2, 6, 1, 3, 6, 5, 5, 4, 9, 7, 8, 1, 8,
    9, 3, 1, 2, 9, 7, 8, 4, 8, 2, 1, 6, 8, 2, 9, 9, 8, 9, 4, 8, 7, 2,
    2, 6, 5, 8, 8, 0, 4, 8, 5, 7, 5, 6, 4, 0, 1, 4, 2, 7, 0, 4, 7, 7,
    5, 5, 5, 1, 3, 2, 3, 7, 9, 6, 4, 1, 4, 5, 1, 5, 2, 3, 7, 4, 6, 2,
    3, 4, 3, 6, 4, 5, 4, 2, 8, 5, 8, 4, 4, 4, 7, 9, 5, 2, 6, 5, 8, 6,
    7, 8, 2, 1, 0, 5, 1, 1, 4, 1, 3, 5, 4, 7, 3, 5, 7, 3, 9, 5, 2, 3,
    1, 1, 3, 4, 2, 7, 1, 6, 6, 1, 0, 2, 1, 3, 5, 9, 6, 9, 5, 3, 6, 2,
    3, 1, 4, 4, 2, 9, 5, 2, 4, 8, 4, 9, 3, 7, 1, 8, 7, 1, 1, 0, 1, 4,
    5, 7, 6, 5, 4, 0, 3, 5, 9, 0, 2, 7, 9, 9, 3, 4, 4, 0, 3, 7, 4, 2,
    0, 0, 7, 3, 1, 0, 5, 7, 8, 5, 3, 9, 0, 6, 2, 1, 9, 8, 3, 8, 7, 4,
    4, 7, 8, 0, 8, 4, 7, 8, 4, 8, 9, 6, 8, 3, 3, 2, 1, 4, 4, 5, 7, 1,
    3, 8, 6, 8, 7, 5, 1, 9, 4, 3, 5, 0, 6, 4, 3, 0, 2, 1, 8, 4, 5, 3,
    1, 9, 1, 0, 4, 8, 4, 8, 1, 0, 0, 5, 3, 7, 0, 6, 1, 4, 6, 8, 0, 6,
    7, 4, 9, 1, 9, 2, 7, 8, 1, 9, 1, 1, 9, 7, 9, 3, 9, 9, 5, 2, 0, 6,
    1, 4, 1, 9, 6, 6, 3, 4, 2, 8, 7, 5, 4, 4, 4, 0, 6, 4, 3, 7, 4, 5,
    1, 2, 3, 7, 1, 8, 1, 9, 2, 1, 7, 9, 9, 9, 8, 3, 9, 1, 0, 1, 5, 9,
    1, 9, 5, 6, 1, 8, 1, 4, 6, 7, 5, 1, 4, 2, 6, 9, 1, 2, 3, 9, 7, 4,
    8, 9, 4, 0, 9, 0, 7, 1, 8, 6, 4, 9, 4, 2, 3, 1, 9, 6, 1, 5, 6, 7,
    9, 4, 5, 2, 0, 8, 0, 9, 5, 1, 4, 6, 5, 5, 0, 2, 2, 5, 2, 3, 1, 6,
    0, 3, 8, 8, 1, 9, 3, 0, 1, 4, 2, 0, 9, 3, 7, 6, 2, 1, 3, 7, 8, 5,
    5, 9, 5, 6, 6, 3, 8, 9, 3, 7, 7, 8, 7, 0, 8, 3, 0, 3, 9, 0, 6, 9,
    7, 9, 2, 0, 7, 7, 3, 4, 6, 7, 2, 2, 1, 8, 2, 5, 6, 2, 5, 9, 9, 6,
    6, 1, 5, 0, 1, 4, 2, 1, 5, 0, 3, 0, 6, 8, 0, 3, 8, 4, 4, 7, 7, 3,
    4, 5, 4, 9, 2, 0, 2, 6, 0, 5, 4, 1, 4, 6, 6, 5, 9, 2, 5, 2, 0, 1,
    4, 9, 7, 4, 4, 2, 8, 5, 0, 7, 3, 2, 5, 1, 8, 6, 6, 6, 0, 0, 2, 1,
    3, 2, 4, 3, 4, 0, 8, 8, 1, 9, 0, 7, 1, 0, 4, 8, 6, 3, 3, 1, 7, 3,
    4, 6, 4, 9, 6, 5, 1, 4, 5, 3, 9, 0, 5, 7, 9, 6, 2, 6, 8, 5, 6, 1,
    0, 0, 5, 5, 0, 8, 1, 0, 6, 6, 5, 8, 7, 9, 6, 9, 9, 8, 1, 6, 3, 5,
    7, 4, 7, 3, 6, 3, 8, 4, 0, 5, 2, 5, 7, 1, 4, 5, 9, 1, 0, 2, 8, 9,
    7, 0, 6, 4, 1, 4, 0, 1, 1, 0, 9, 7, 1, 2, 0, 6, 2, 8, 0, 4, 3, 9,
    0, 3, 9, 7, 5, 9, 5, 1, 5, 6, 7, 7, 1, 5, 7, 7, 0, 0, 4, 2, 0, 3,
    3, 7, 8, 6, 9, 9, 3, 6, 0, 0, 7, 2, 3, 0, 5, 5, 8, 7, 6, 3, 1, 7,
    6, 3, 5, 9, 4, 2, 1, 8, 7, 3, 1, 2, 5, 1, 4, 7, 1, 2, 0, 5, 3, 2,
    9, 2, 8, 1, 9, 1, 8, 2, 6, 1, 8, 6, 1, 2, 5, 8, 6, 7, 3, 2, 1, 5,
    7, 9, 1, 9, 8, 4, 1, 4, 8, 4, 8, 8, 2, 9, 1, 6, 4, 4, 7, 0, 6, 0,
    9, 5, 7, 5, 2, 7, 0, 6, 9, 5, 7, 2, 2, 0, 9, 1, 7, 5, 6, 7, 1, 1,
    6, 7, 2, 2, 9, 1, 0, 9, 8, 1, 6, 9, 0, 9, 1, 5, 2, 8, 0, 1, 7, 3,
    5, 0, 6, 7, 1, 2, 7, 4, 8, 5, 8, 3, 2, 2, 2, 8, 7, 1, 8, 3, 5, 2,
    0, 9, 3, 5, 3, 9, 6, 5, 7, 2, 5, 1, 2, 1, 0, 8, 3, 5, 7, 9, 1, 5,
    1, 3, 6, 9, 8, 8, 2, 0, 9, 1, 4, 4, 4, 2, 1, 0, 0, 6, 7, 5, 1, 0,
    3, 3, 4, 6, 7, 1, 1, 0, 3, 1, 4, 1, 2, 6, 7, 1, 1, 1, 3, 6, 9, 9,
    0, 8, 6, 5, 8, 5, 1, 6, 3, 9, 8, 3, 1, 5, 0, 1, 9, 7, 0, 1, 6, 5,
    1, 5, 1, 1, 6, 8, 5, 1, 7, 1, 4, 3, 7, 6, 5, 7, 6, 1, 8, 3, 5, 1,
    5, 5, 6, 5, 0, 8, 8, 4, 9, 0, 9, 9, 8, 9, 8, 5, 9, 9, 8, 2, 3, 8,
    7, 3, 4, 5, 5, 2, 8, 3, 3, 1, 6, 3, 5, 5, 0, 7, 6, 4, 7, 9, 1, 8,
    5, 3, 5, 8, 9, 3, 2, 2, 6, 1, 8, 5, 4, 8, 9, 6, 3, 2, 1, 3, 2, 9,
    3, 3, 0, 8, 9, 8, 5, 7, 0, 6, 4, 2, 0, 4, 6, 7, 5, 2, 5, 9, 0, 7,
    0, 9, 1, 5, 4, 8, 1, 4, 1, 6, 5, 4, 9, 8, 5, 9, 4, 6, 1, 6, 3, 7,
    1, 8, 0, 2, 7, 0, 9, 8, 1, 9, 9, 4, 3, 0, 9, 9, 2, 4, 4, 8, 8, 9,
    5, 7, 5, 7, 1, 2, 8, 2, 8, 9, 0, 5, 9, 2, 3, 2, 3, 3, 2, 6, 0, 9,
    7, 2, 9, 9, 7, 1, 2, 0, 8, 4, 4, 3, 3, 5, 7, 3, 2, 6, 5, 4, 8, 9,
    3, 8, 2, 3, 9, 1, 1, 9, 3, 2, 5, 9, 7, 4, 6, 3, 6, 6, 7, 3, 0, 5,
    8, 3, 6, 0, 4, 1, 4, 2, 8, 1, 3, 8, 8, 3, 0, 3, 2, 0, 3, 8, 2, 4,
    9, 0, 3, 7, 5, 8, 9, 8, 5, 2, 4, 3, 7, 4, 4, 1, 7, 0, 2, 9, 1, 3,
    2, 7, 6, 5, 6, 1, 8, 0, 9, 3, 7, 7, 3, 4, 4, 4, 0, 3, 0, 7, 0, 7,
    4, 6, 9, 2, 1, 1, 2, 0, 1, 9, 1, 3, 0, 2, 0, 3, 3, 0, 3, 8, 0, 1,
    9, 7, 6, 2, 1, 1, 0, 1, 1, 0, 0, 4, 4, 9, 2, 9, 3, 2, 1, 5, 1, 6,
    0, 8, 4, 2, 4, 4, 4, 8, 5, 9, 6, 3, 7, 6, 6, 9, 8, 3, 8, 9, 5, 2,
    2, 8, 6, 8, 4, 7, 8, 3, 1, 2, 3, 5, 5, 2, 6, 5, 8, 2, 1, 3, 1, 4,
    4, 9, 5, 7, 6, 8, 5, 7, 2, 6, 2, 4, 3, 3, 4, 4, 1, 8, 9, 3, 0, 3,
    9, 6, 8, 6, 4, 2, 6, 2, 4, 3, 4, 1, 0, 7, 7, 3, 2, 2, 6, 9, 7, 8,
    0, 2, 8, 0, 7, 3, 1, 8, 9, 1, 5, 4, 4, 1, 1, 0, 1, 0, 4, 4, 6, 8,
    2, 3, 2, 5, 2, 7, 1, 6, 2, 0, 1, 0, 5, 2, 6, 5, 2, 2, 7, 2, 1, 1,
    1, 6, 6, 0, 3, 9, 6, 6, 6, 5, 5, 7, 3, 0, 9, 2, 5, 4, 7, 1, 1, 0,
    5, 5, 7, 8, 5, 3, 7, 6, 3, 4, 6, 6, 8, 2, 0, 6, 5, 3, 1, 0, 9, 8,
    9, 6, 5, 2, 6, 9, 1, 8, 6, 2, 0, 5, 6, 4, 7, 6, 9, 3, 1, 2, 5, 7,
    0, 5, 8, 6, 3, 5, 6, 6, 2, 0, 1, 8, 5, 5, 8, 1, 0, 0, 7, 2, 9, 3,
    6, 0, 6, 5, 9, 8, 7, 6, 4, 8, 6, 1, 1, 7, 9, 1, 0, 4, 5, 3, 3, 4,
    8, 8, 5, 0, 3, 4, 6, 1, 1, 3, 6, 5, 7, 6, 8, 6, 7, 5, 3, 2, 4, 9,
    4, 4, 1, 6, 6, 8, 0, 3, 9, 6, 2, 6, 5, 7, 9, 7, 8, 7, 7, 1, 8, 5,
    5, 6, 0, 8, 4, 5, 5, 2, 9, 6, 5, 4, 1, 2, 6, 6, 5, 4, 0, 8, 5, 3,
    0, 6, 1, 4, 3, 4, 4, 4, 3, 1, 8, 5, 8, 6, 7, 6, 9, 7, 5, 1, 4, 5,
    6, 6, 1, 4, 0, 6, 8, 0, 0, 7, 0, 0, 2, 3, 7, 8, 7, 7, 6, 5, 9, 1,
    3, 4, 4, 0, 1, 7, 1, 2, 7, 4, 9, 4, 7, 0, 4, 2, 0, 5, 6, 2, 2, 3,
    0, 5, 3, 8, 9, 9, 4, 5, 6, 1, 3, 1, 4, 0, 7, 1, 1, 2, 7, 0, 0, 0,
    4, 0, 7, 8, 5, 4, 7, 3, 3, 2, 6, 9, 9, 3, 9, 0, 8, 1, 4, 5, 4, 6,
    6, 4, 6, 4, 5, 8, 8, 0, 7, 9, 7, 2, 7, 0, 8, 2, 6, 6, 8, 3, 0, 6,
    3, 4, 3, 2, 8, 5, 8, 7, 8, 5, 6, 9, 8, 3, 0, 5, 2, 3, 5, 8, 0, 8,
    9, 3, 3, 0, 6, 5, 7, 5, 7, 4, 0, 6, 7, 9, 5, 4, 5, 7, 1, 6, 3, 7,
    7, 5, 2, 5, 4, 2, 0, 2, 1, 1, 4, 9, 5, 5, 7, 6, 1, 5, 8, 1, 4, 0,
    0, 2, 5, 0, 1, 2, 6, 2, 2, 8, 5, 9, 4, 1, 3, 0, 2, 1, 6, 4, 7, 1,
    5, 5, 0, 9, 7, 9, 2, 5, 9, 2, 3, 0, 9, 9, 0, 7, 9, 6, 5, 4, 7, 3,
    7, 6, 1, 2, 5, 5, 1, 7, 6, 5, 6, 7, 5, 1, 3, 5, 7, 5, 1, 7, 8, 2,
    9, 6, 6, 6, 4, 5, 4, 7, 7, 9, 1, 7, 4, 5, 0, 1, 1, 2, 9, 9, 6, 1,
    4, 8, 9, 0, 3, 0, 4, 6, 3, 9, 9, 4, 7, 1, 3, 2, 9, 6, 2, 1, 0, 7,
    3, 4, 0, 4, 3, 7, 5, 1, 8, 9, 5, 7, 3, 5, 9, 6, 1, 4, 5, 8, 9, 0,
    1, 9, 3, 8, 9, 7, 1, 3, 1, 1, 1, 7, 9, 0, 4, 2, 9, 7, 8, 2, 8, 5,
    6, 4, 7, 5, 0, 3, 2, 0, 3, 1, 9, 8, 6, 9, 1, 5, 1, 4, 0, 2, 8, 7,
    0, 8, 0, 8, 5, 9, 9, 0, 4, 8, 0, 1, 0, 9, 4, 1, 2, 1, 4, 7, 2, 2,
    1, 3, 1, 7, 9, 4, 7, 6, 4, 7, 7, 7, 2, 6, 2, 2, 4, 1, 4, 2, 5, 4,
    8, 5, 4, 5, 4, 0, 3, 3, 2, 1, 5, 7, 1, 8, 5, 3, 0, 6, 1, 4, 2, 2,
    8, 8, 1, 3, 7, 5, 8, 5, 0, 4, 3, 0, 6, 3, 3, 2, 1, 7, 5, 1, 8, 2,
    9, 7, 9, 8, 6, 6, 2, 2, 3, 7, 1, 7, 2, 1, 5, 9, 1, 6, 0, 7, 7, 1,
    6, 6, 9, 2, 5, 4, 7, 4, 8, 7, 3, 8, 9, 8, 6, 6, 5, 4, 9, 4, 9, 4,
    5, 0, 1, 1, 4, 6, 5, 4, 0, 6, 2, 8, 4, 3, 3, 6, 6, 3, 9, 3, 7, 9,
    0, 0, 3, 9, 7, 6, 9, 2, 6, 5, 6, 7, 2, 1, 4, 6, 3, 8, 5, 3, 0, 6,
    7, 3, 6, 0, 9, 6, 5, 7, 1, 2, 0, 9, 1, 8, 0, 7, 6, 3, 8, 3, 2, 7,
    1, 6, 6, 4, 1, 6, 2, 7, 4, 8, 8, 8, 8, 0, 0, 7, 8, 6, 9, 2, 5, 6,
    0, 2, 9, 0, 2, 2, 8, 4, 7, 2, 1, 0, 4, 0, 3, 1, 7, 2, 1, 1, 8, 6,
    0, 8, 2, 0, 4, 1, 9, 0, 0, 0, 4, 2, 2, 9, 6, 6, 1, 7, 1, 1, 9, 6,
    3, 7, 7, 9, 2, 1, 3, 3, 7, 5, 7, 5, 1, 1, 4, 9, 5, 9, 5, 0, 1, 5,
    6, 6, 0, 4, 9, 6, 3, 1, 8, 6, 2, 9, 4, 7, 2, 6, 5, 4, 7, 3, 6, 4,
    2, 5, 2, 3, 0, 8, 1, 7, 7, 0, 3, 6, 7, 5, 1, 5, 9, 0, 6, 7, 3, 5,
    0, 2, 3, 5, 0, 7, 2, 8, 3, 5, 4, 0, 5, 6, 7, 0, 4, 0, 3, 8, 6, 7,
    4, 3, 5, 1, 3, 6, 2, 2, 2, 2, 4, 7, 7, 1, 5, 8, 9, 1, 5, 0, 4, 9,
    5, 3, 0, 9, 8, 4, 4, 4, 8, 9, 3, 3, 3, 0, 9, 6, 3, 4, 0, 8, 7, 8,
    0, 7, 6, 9, 3, 2, 5, 9, 9, 3, 9, 7, 8, 0, 5, 4, 1, 9, 3, 4, 1, 4,
    4, 7, 3, 7, 7, 4, 4, 1, 8, 4, 2, 6, 3, 1, 2, 9, 8, 6, 0, 8, 0, 9,
    9, 8, 8, 8, 6, 8, 7, 4, 1, 3, 2, 6, 0, 4, 7, 2 } ;


  const size_t nacc1 = 3 ;
  const double numacc1[3] = { 10000001, 10000003, 10000002 } ;

  const size_t nacc2 = 1001 ;
  double numacc2[1001] ;

  const size_t nacc3 = 1001 ;
  double numacc3[1001] ;

  const size_t nacc4 = 1001 ;
  double numacc4[1001] ;

  numacc2[0] = 1.2 ;
  numacc3[0] = 1000000.2 ; 
  numacc4[0] = 10000000.2 ; 
 
  for (i = 1 ; i < 1000  ; i += 2) 
    {
      numacc2[i] = 1.1 ;
      numacc2[i+1] = 1.3 ;
      numacc3[i] = 1000000.1 ;
      numacc3[i+1] = 1000000.3 ;
      numacc4[i] = 10000000.1 ;
      numacc4[i+1] = 10000000.3 ;
    }

  gsl_ieee_env_setup ();

  {
    double mean = gsl_stats_mean (lew, 1, nlew);
    double sd = gsl_stats_sd (lew, 1, nlew);
    double lag1 = gsl_stats_lag1_autocorrelation (lew, 1, nlew);

    double expected_mean = -177.435000000000;
    double expected_sd = 277.332168044316;
    double expected_lag1 = -0.307304800605679;

    gsl_test_rel (mean, expected_mean, 1e-15, "lew gsl_stats_mean") ;
    gsl_test_rel (sd, expected_sd, 1e-15, "lew gsl_stats_sd") ;
    gsl_test_rel (lag1, expected_lag1, 1e-14, "lew autocorrelation") ;
  }


  {
    double mean = gsl_stats_mean (lottery, 1, nlottery);
    double sd = gsl_stats_sd (lottery, 1, nlottery);
    double lag1 = gsl_stats_lag1_autocorrelation (lottery, 1, nlottery);

    double expected_mean = 518.958715596330;
    double expected_sd = 291.699727470969;
    double expected_lag1 = -0.120948622967393;

    gsl_test_rel (mean, expected_mean, 1e-15, "lottery gsl_stats_mean") ;
    gsl_test_rel (sd, expected_sd, 1e-15, "lottery gsl_stats_sd") ;
    gsl_test_rel (lag1, expected_lag1, 1e-14, "lottery autocorrelation") ;
  }

  {
    double mean = gsl_stats_mean (mavro, 1, nmavro);
    double sd = gsl_stats_sd (mavro, 1, nmavro);
    double lag1 = gsl_stats_lag1_autocorrelation (mavro, 1, nmavro);

    double expected_mean = 2.00185600000000;
    double expected_sd = 0.000429123454003053;
    double expected_lag1 = 0.937989183438248;

    gsl_test_rel (mean, expected_mean, 1e-15, "mavro gsl_stats_mean") ;
    gsl_test_rel (sd, expected_sd, 1e-13, "mavro gsl_stats_sd") ;
    gsl_test_rel (lag1, expected_lag1, 1e-13, "mavro autocorrelation") ;
  }


  {
    double mean = gsl_stats_mean (michelson, 1, nmichelson);
    double sd = gsl_stats_sd (michelson, 1, nmichelson);
    double lag1 = gsl_stats_lag1_autocorrelation (michelson, 1, nmichelson);

    double expected_mean = 299.852400000000;
    double expected_sd = 0.0790105478190518;
    double expected_lag1 = 0.535199668621283;

    gsl_test_rel (mean, expected_mean, 1e-15, "michelson gsl_stats_mean") ;
    gsl_test_rel (sd, expected_sd, 1e-13, "michelson gsl_stats_sd") ;
    gsl_test_rel (lag1, expected_lag1, 1e-13, "michelson autocorrelation") ;
  }

  {
    double mean = gsl_stats_mean (pidigits, 1, npidigits);
    double sd = gsl_stats_sd (pidigits, 1, npidigits);
    double lag1 = gsl_stats_lag1_autocorrelation (pidigits, 1, npidigits);

    double expected_mean = 4.53480000000000;
    double expected_sd = 2.86733906028871;
    double expected_lag1 = -0.00355099287237972;

    gsl_test_rel (mean, expected_mean, 1e-14, "pidigits gsl_stats_mean") ;
    gsl_test_rel (sd, expected_sd, 1e-15, "pidigits gsl_stats_sd") ;
    gsl_test_rel (lag1, expected_lag1, 1e-14, "pidigits autocorrelation") ;
  }
    
  {
    double mean = gsl_stats_mean (numacc1, 1, nacc1);
    double sd = gsl_stats_sd (numacc1, 1, nacc1);
    double lag1 = gsl_stats_lag1_autocorrelation (numacc1, 1, nacc1);

    double expected_mean = 10000002;
    double expected_sd = 1;
    double expected_lag1 = -0.5;

    gsl_test_rel (mean, expected_mean, 1e-15, "acc1 gsl_stats_mean") ;
    gsl_test_rel (sd, expected_sd, 1e-15, "acc1 gsl_stats_sd") ;
    gsl_test_rel (lag1, expected_lag1, 1e-15, "acc1 autocorrelation") ;
  }

  {
    double mean = gsl_stats_mean (numacc2, 1, nacc2);
    double sd = gsl_stats_sd (numacc2, 1, nacc2);
    double lag1 = gsl_stats_lag1_autocorrelation (numacc2, 1, nacc2);

    double expected_mean = 1.2;
    double expected_sd = 0.1;
    double expected_lag1 = -0.999;

    gsl_test_rel (mean, expected_mean, 1e-15, "acc2 gsl_stats_mean") ;
    gsl_test_rel (sd, expected_sd, 1e-15, "acc2 gsl_stats_sd") ;
    gsl_test_rel (lag1, expected_lag1, 1e-10, "acc2 autocorrelation") ;
  }

  {
    double mean = gsl_stats_mean (numacc3, 1, nacc3);
    double sd = gsl_stats_sd (numacc3, 1, nacc3);
    double lag1 = gsl_stats_lag1_autocorrelation (numacc3, 1, nacc3);

    double expected_mean = 1000000.2;
    double expected_sd = 0.1;
    double expected_lag1 = -0.999;

    gsl_test_rel (mean, expected_mean, 1e-15, "acc3 gsl_stats_mean") ;
    gsl_test_rel (sd, expected_sd, 1e-9, "acc3 gsl_stats_sd") ;
    gsl_test_rel (lag1, expected_lag1, 1e-10, "acc3 autocorrelation") ;
  }


  {
    double mean = gsl_stats_mean (numacc4, 1, nacc4);
    double sd = gsl_stats_sd (numacc4, 1, nacc4);
    double lag1 = gsl_stats_lag1_autocorrelation (numacc4, 1, nacc4);

    double expected_mean = 10000000.2;
    double expected_sd = 0.1;
    double expected_lag1 = -0.999;

    gsl_test_rel (mean, expected_mean, 1e-15, "acc4 gsl_stats_mean") ;
    gsl_test_rel (sd, expected_sd, 1e-7, "acc4 gsl_stats_sd") ;
    gsl_test_rel (lag1, expected_lag1, 1e-10, "acc4 autocorrelation") ;
  }


  return gsl_test_summary ();
}







