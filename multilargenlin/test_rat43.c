#define rat43_N       15
#define rat43_P       4

#define rat43_NTRIES  1

static double rat43_x0[rat43_P] = { 100.0, 10.0, 1.0, 1.0 };
static double rat43_epsrel = 1.0e-6;

static double rat43_f[rat43_N];
static double rat43_J[rat43_N * rat43_P];

static double rat43_sigma[rat43_P] = {
  1.6302297817E+01, 2.0828735829E+00,
  1.9566123451E-01, 6.8761936385E-01
};

static double rat43_F[rat43_N] = { 16.08, 33.83, 65.80, 97.20, 191.55,
                                   326.20, 386.87, 520.53, 590.03,
                                   651.92, 724.93, 699.56, 689.96,
                                   637.56, 717.41 };

static void
rat43_checksol(const double x[], const double sumsq,
                 const double epsrel, const char *sname,
                 const char *pname)
{
  size_t i;
  const double sumsq_exact = 8.7864049080E+03;
  const double rat43_x[rat43_P] = { 6.9964151270E+02,
                                    5.2771253025E+00,
                                    7.5962938329E-01,
                                    1.2792483859E+00 };

  gsl_test_rel(sumsq, sumsq_exact, epsrel, "%s/%s sumsq",
               sname, pname);

  for (i = 0; i < rat43_P; ++i)
    {
      gsl_test_rel(x[i], rat43_x[i], epsrel, "%s/%s i=%zu",
                   sname, pname, i);
    }
}

static int
rat43_fdf (const gsl_vector * x, gsl_matrix * JTJ,
           gsl_vector * JTf, double * normf, void *params)
{
  double b[rat43_P];
  gsl_matrix_view J = gsl_matrix_view_array(rat43_J, rat43_N, rat43_P);
  gsl_vector_view f = gsl_vector_view_array(rat43_f, rat43_N);
  size_t i;

  for (i = 0; i < rat43_P; i++)
    {
      b[i] = gsl_vector_get(x, i);
    }

  for (i = 0; i < rat43_N; i++)
    {
      double xi = i + 1.0;
      double e = exp(b[1] - b[2]*xi);
      double term1 = 1.0 + e;
      double term2 = pow(term1, -1.0 / b[3]);
      double yi = b[0] * term2;

      gsl_vector_set (&f.vector, i, yi - rat43_F[i]);

      if (JTJ)
        {
          gsl_matrix_set (&J.matrix, i, 0, term2);
          gsl_matrix_set (&J.matrix, i, 1, -b[0] / b[3] * e * term2 / term1);
          gsl_matrix_set (&J.matrix, i, 2, b[0] / b[3] * xi * e * term2 / term1);
          gsl_matrix_set (&J.matrix, i, 3, b[0] / b[3] / b[3] * log(term1) * term2);
        }
    }

  *normf = gsl_blas_dnrm2(&f.vector);

  if (JTJ)
    {
      gsl_blas_dsyrk(CblasLower, CblasTrans, 1.0, &J.matrix, 0.0, JTJ);
      gsl_blas_dgemv(CblasTrans, 1.0, &J.matrix, &f.vector, 0.0, JTf);
    }

  return GSL_SUCCESS;
}

static gsl_multilarge_function_fdf rat43_func =
{
  &rat43_fdf,
  rat43_P,
  NULL
};

static test_fdf_problem rat43_problem =
{
  "nist-rat43",
  rat43_x0,
  rat43_sigma,
  &rat43_epsrel,
  rat43_NTRIES,
  &rat43_checksol,
  &rat43_func
};
