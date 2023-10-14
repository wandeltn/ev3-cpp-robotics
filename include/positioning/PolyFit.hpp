#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>
#include <iomanip>

class PolyFit {
    public:
        PolyFit();
        static double getRegressionStrechfactor(std::vector<double> values);

    private:
        static double incbeta(double a, double b, double x);
        static double invincbeta(double y, double alpha, double beta);
        static double CalculateTValueStudent(const double nu, const double alpha);
        static double cdfStudent(const double nu, const double t);
        static double cdfFisher(const double df1, const double df2, const double x);
        static double **Make2DArray(const size_t rows, const size_t cols);
        static double **MatTrans(double **array, const size_t rows, const size_t cols);
        static double **MatMul(const size_t m1, const size_t m2, const size_t m3, double **A, double **B);
        static void MatVectMul(const size_t m1, const size_t m2, double **A, double *v, double *Av);
        static double determinant(double **a, const size_t k);
        static void transpose(double **num, double **fac, double **inverse, const size_t r);
        static void cofactor(double **num, double **inverse, const size_t f);
        static void displayMat(double **A, const size_t n, const size_t m);
        static double CalculateRSS(const double *x, const double *y, const double *a, double **Weights, const bool fixed, const size_t N, const size_t n);
        static double CalculateTSS(const double *x, const double *y, const double *a, double **Weights, const bool fixed, const size_t N, const size_t n);
        static double CalculateR2COD(const double *x, const double *y, const double *a, double **Weights, const bool fixed, const size_t N, const size_t n);
        static double CalculateR2Adj(const double *x, const double *y, const double *a, double **Weights, const bool fixed,const size_t N, const size_t n);
        static void Fit(const double *x, double *y, const size_t n, const size_t k, const bool fixedinter, const double fixedinterval, double *beta, double **Weights, double **XTWXInv);
        static double calculatePoly(const double x, const double *a, const size_t n);
        static void WriteCIBands(std::string filename, const double *x, const double *coefbeta, double **XTXInv, const double tstudentval, const double SE, const size_t n, const size_t k);
        static void CalculateWeights(const double *erry, double **Weights, const size_t n, const int type);
        static void CalculateSERRBeta(const bool fixedinter, const double SE, size_t k, double *serbeta, double **XTWXInv);
        static void DisplayPolynomial(const size_t k);
        static void DisplayANOVA(const size_t nstar, const size_t k, const double TSS, const double RSS);
        static void DisplayCoefs(const size_t k, const size_t nstar, const double tstudentval, const double *coefbeta, const double *serbeta);
        static void DisplayStatistics(const size_t n, const size_t nstar, const size_t k, const double RSS, const double R2, const double R2Adj, const double SE);
        static void DisplayCovCorrMatrix(const size_t k, const double sigma, const bool fixed, double **XTWXInv);

};