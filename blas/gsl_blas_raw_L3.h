/* blas/gsl_blas_raw_L3.h
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
/* Prototypes for level 3 BLAS functions.
 * Based on draft BLAST C interface specification  [Jul 7 1998]
 */
#ifndef __GSL_BLAS_RAW_L3_H__
#define __GSL_BLAS_RAW_L3_H__

#include <gsl/gsl_complex.h>
#include <gsl/gsl_blas_types.h>

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS


/* GEMM */

void gsl_blas_raw_sgemm (CBLAS_TRANSPOSE_t TransA,
                         CBLAS_TRANSPOSE_t TransB,
			 size_t M, size_t N, size_t K,
			 float alpha,
			 const float A[], int lda,
			 const float B[], int ldb,
                         float beta,
			 float C[], int ldc);

void gsl_blas_raw_dgemm (CBLAS_TRANSPOSE_t TransA,
                         CBLAS_TRANSPOSE_t TransB,
			 size_t M, size_t N, size_t K,
			 double alpha,
			 const double A[], int lda,
			 const double B[], int ldb,
                         double beta,
			 double C[], int ldc);

void gsl_blas_raw_cgemm (CBLAS_TRANSPOSE_t TransA,
                         CBLAS_TRANSPOSE_t TransB,
			 size_t M, size_t N, size_t K,
			 const gsl_const_complex_packed_float alpha,
			 const gsl_const_complex_packed_array_float A, int lda, 
			 const gsl_const_complex_packed_array_float B, int ldb,
                         const gsl_const_complex_packed_float beta,
			 gsl_complex_packed_array_float C, int ldc);

void gsl_blas_raw_zgemm (CBLAS_TRANSPOSE_t TransA,
                         CBLAS_TRANSPOSE_t TransB,
			 size_t M, size_t N, size_t K,
			 const gsl_const_complex_packed alpha,
			 const gsl_const_complex_packed_array A, int lda,
			 const gsl_const_complex_packed_array B, int ldb,
                         const gsl_const_complex_packed beta,
			 gsl_complex_packed_array C, int ldc);


/* SYMM */

void gsl_blas_raw_ssymm (CBLAS_SIDE_t Side, CBLAS_UPLO_t Uplo,
			 size_t M, size_t N,
                         float alpha,
			 const float A[], int lda,
                         const float B[], int ldb,
			 float beta,
                         float C[], int ldc);

void gsl_blas_raw_dsymm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo,
			 size_t M, size_t N,
                         double alpha,
			 const double A[], int lda,
                         const double B[], int ldb,
			 double beta,
                         double C[], int ldc);

void gsl_blas_raw_csymm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo,
			 size_t M, size_t N,
                         const gsl_const_complex_packed_float alpha,
			 const gsl_const_complex_packed_array_float A, int lda,
                         const gsl_const_complex_packed_array_float B, int ldb,
			 const gsl_const_complex_packed_float beta,
                         gsl_complex_packed_array_float C, int ldc);

void gsl_blas_raw_zsymm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo,
			 size_t M, size_t N,
                         const gsl_const_complex_packed alpha,
			 const gsl_const_complex_packed_array A, int lda,
                         const gsl_const_complex_packed_array B, int ldb,
			 const gsl_const_complex_packed beta,
                         gsl_complex_packed_array C, int ldc);


/* SYRK */

void gsl_blas_raw_ssyrk (CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t Trans,
			 size_t N, size_t K,
                         float alpha,
			 const float A[], int lda,
                         float beta,
			 float C[], int ldc);

void gsl_blas_raw_dsyrk (CBLAS_UPLO_t Uplo,
                         CBLAS_TRANSPOSE_t Trans,
			 size_t N, size_t K,
                         double alpha,
			 const double A[], int lda,
                         double beta,
			 double C[], int ldc);

void gsl_blas_raw_csyrk (CBLAS_UPLO_t Uplo,
                         CBLAS_TRANSPOSE_t Trans,
			 size_t N, size_t K,
                         const gsl_const_complex_packed_float alpha,
			 const gsl_const_complex_packed_array_float A, int lda,
                         const gsl_const_complex_packed_float beta,
			 gsl_complex_packed_array_float C, int ldc);

void gsl_blas_raw_zsyrk (CBLAS_UPLO_t Uplo,
                         CBLAS_TRANSPOSE_t Trans,
			 size_t N, size_t K,
                         const gsl_const_complex_packed alpha,
			 const gsl_const_complex_packed_array A, int lda,
                         const gsl_const_complex_packed beta,
			 gsl_complex_packed_array C, int ldc);


/* SYR2K */

void gsl_blas_raw_ssyr2k (CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t Trans,
			  size_t N, size_t K,
                          float alpha,
			  const float A[], int lda,
                          const float B[], int ldb,
			  float beta,
                          float C[], int ldc);

void gsl_blas_raw_dsyr2k (CBLAS_UPLO_t Uplo,
                          CBLAS_TRANSPOSE_t Trans,
			  size_t N, size_t K,
                          double alpha,
			  const double A[], int lda,
                          const double B[], int ldb,
			  double beta,
                          double C[], int ldc);

void gsl_blas_raw_csyr2k (CBLAS_UPLO_t Uplo,
                          CBLAS_TRANSPOSE_t Trans,
			  size_t N, size_t K,
                          const gsl_const_complex_packed_float alpha,
			  const gsl_const_complex_packed_array_float A, int lda,
                          const gsl_const_complex_packed_array_float B, int ldb,
			  const gsl_const_complex_packed_float beta,
                          gsl_complex_packed_array_float C, int ldc);

void gsl_blas_raw_zsyr2k (CBLAS_UPLO_t Uplo,
                          CBLAS_TRANSPOSE_t Trans,
			  size_t N, size_t K,
                          const gsl_const_complex_packed alpha,
			  const gsl_const_complex_packed_array A, int lda,
                          const gsl_const_complex_packed_array B, int ldb,
			  const gsl_const_complex_packed beta,
                          gsl_complex_packed_array C, int ldc);


/* TRMM */

void gsl_blas_raw_strmm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t TransA,
                         CBLAS_DIAG_t Diag,
			 size_t M, size_t N,
                         float alpha,
			 const float A[], int lda,
                         float B[], int ldb);

void gsl_blas_raw_dtrmm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t TransA,
                         CBLAS_DIAG_t Diag,
			 size_t M, size_t N,
                         double alpha,
			 const double A[], int lda,
                         double B[], int ldb);

void gsl_blas_raw_ctrmm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t TransA,
                         CBLAS_DIAG_t Diag,
			 size_t M, size_t N,
                         const gsl_const_complex_packed_float alpha,
			 const gsl_const_complex_packed_array_float A, int lda,
                         gsl_complex_packed_array_float B, int ldb);

void gsl_blas_raw_ztrmm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t TransA,
                         CBLAS_DIAG_t Diag,
			 size_t M, size_t N,
                         const gsl_const_complex_packed alpha,
			 const gsl_const_complex_packed_array A, int lda,
                         gsl_complex_packed_array B, int ldb);


/* TRSM */

void gsl_blas_raw_strsm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t TransA,
                         CBLAS_DIAG_t Diag,
			 size_t M, size_t N,
                         float alpha,
			 const float A[], int lda,
                         float B[], int ldb);

void gsl_blas_raw_dtrsm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t TransA,
                         CBLAS_DIAG_t Diag,
			 size_t M, size_t N,
                         double alpha,
			 const double A[], int lda,
                         double B[], int ldb);

void gsl_blas_raw_ctrsm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t TransA,
                         CBLAS_DIAG_t Diag,
			 size_t M, size_t N,
                         const gsl_const_complex_packed_float alpha,
			 const gsl_const_complex_packed_array_float A, int lda,
                         gsl_complex_packed_array_float B, int ldb);

void gsl_blas_raw_ztrsm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo, CBLAS_TRANSPOSE_t TransA,
                         CBLAS_DIAG_t Diag,
			 size_t M, size_t N,
                         const gsl_const_complex_packed alpha,
			 const gsl_const_complex_packed_array A, int lda,
                         gsl_complex_packed_array B, int ldb);


/* HEMM */

void gsl_blas_raw_chemm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo,
			 size_t M, size_t N,
                         const gsl_const_complex_packed_float alpha,
			 const gsl_const_complex_packed_array_float A, int lda,
                         const gsl_const_complex_packed_array_float B, int ldb,
			 const gsl_const_complex_packed_float beta,
                         gsl_complex_packed_array_float C, int ldc);

void gsl_blas_raw_zhemm (CBLAS_SIDE_t Side,
                         CBLAS_UPLO_t Uplo,
			 size_t M, size_t N,
                         const gsl_const_complex_packed alpha,
			 const gsl_const_complex_packed_array A, int lda,
                         const gsl_const_complex_packed_array B, int ldb,
			 const gsl_const_complex_packed beta,
                         gsl_complex_packed_array C, int ldc);


/* HERK */

void gsl_blas_raw_cherk (CBLAS_UPLO_t Uplo,
                         CBLAS_TRANSPOSE_t Trans,
			 size_t N, size_t K,
                         float alpha,
			 const gsl_const_complex_packed_array_float A, int lda,
                         float beta,
			 gsl_complex_packed_array_float C, int ldc);

void gsl_blas_raw_zherk (CBLAS_UPLO_t Uplo,
                         CBLAS_TRANSPOSE_t Trans,
			 size_t N, size_t K,
                         double alpha,
			 const gsl_const_complex_packed_array A, int lda,
                         double beta,
			 gsl_complex_packed_array C, int ldc);


/* HER2K */

void gsl_blas_raw_cher2k (CBLAS_UPLO_t Uplo,
                          CBLAS_TRANSPOSE_t Trans,
			  size_t N, size_t K,
                          const gsl_const_complex_packed_float alpha,
			  const gsl_const_complex_packed_array_float A, int lda,
                          const gsl_const_complex_packed_array_float B, int ldb,
			  float beta,
                          gsl_complex_packed_array_float C, int ldc);


void gsl_blas_raw_zher2k (CBLAS_UPLO_t Uplo,
                          CBLAS_TRANSPOSE_t Trans,
			  size_t N, size_t K,
                          const gsl_const_complex_packed alpha,
			  const gsl_const_complex_packed_array A, int lda,
                          const gsl_const_complex_packed_array B, int ldb,
			  double beta,
                          gsl_complex_packed_array C, int ldc);


__END_DECLS

#endif /* __GSL_BLAS_RAW_L3_H__ */
