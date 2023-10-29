
// ********************************************************************
// * Code PolyFit                                                     *
// * Written by Ianik Plante                                          *
// *                                                                  *
// * KBR                                                              *
// * 2400 NASA Parkway, Houston, TX 77058                             *
// * Ianik.Plante-1@nasa.gov                                          *
// *                                                                  *
// * This code is used to fit a series of n points with a polynomial  *
// * of degree k, and calculation of error bars on the coefficients.  *
// * If error is provided on the y values, it is possible to use a    *
// * weighted fit as an option. Another option provided is to fix the *
// * intercept value, i.e. the first parameter.                       *
// *                                                                  *
// * This code has been written partially using data from publicly    *
// * available sources.                                               *
// *                                                                  *  
// * The code works to the best of the author's knowledge, but some   *   
// * bugs may be present. This code is provided as-is, with no        *
// * warranty of any kind. By using this code you agree that the      * 
// * author, the company KBR or NASA are not responsible for possible *
// * problems related to the usage of this code.                      * 
// *                                                                  *   
// * The program has been reviewed and approved by export control for * 
// * public release. However some export restriction exists. Please   *    
// * respect applicable laws.                                         *
// *                                                                  *   
// ********************************************************************

#include "PolyFit.hpp"

#define MAXIT 1
#define EPS 3.0e-7
#define FPMIN 1.0e-30
#define NODEBUG



/*
 * zlib License
 *
 * Regularized Incomplete Beta Function
 *
 * Copyright (c) 2016, 2017 Lewis Van Winkle
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#define STOP 1.0e-8
#define TINY 1.0e-30

PolyFit::PolyFit()
{

}

double PolyFit::getRegressionStrechfactor(std::vector<double> values)
{
    std::cout << "Polynomial fit!" << std::endl;
    
    // Input values
    // **************************************************************
    size_t k = 2;                                    // Polynomial order
    bool fixedinter = false;                         // Fixed the intercept (coefficient A0)
    int wtype = 0;                                   // Weight: 0 = none (default), 1 = sigma, 2 = 1/sigma^2
    double fixedinterval = 0.;                       // The fixed intercept value (if applicable)
    // double alphaval = 0.05;                          // Critical apha value

    double x[values.size()] = {};
    double y[values.size()];

    std::copy(values.begin(), values.end(), y);
    for (uint i = 0; i < values.size(); i++) {
        x[i] = i;
    }

#ifndef NODEBUG
    for (uint i = 0; i < sizeof(x) / sizeof(double); i++) {
        std::cout << "x" << i << ": " << x[i] << "\n";
        std::cout << "y" << i << ": " << y[i] << "\n";
    }
#endif
    double erry[0];       // Data points (err on y) (if applicable)

    // Definition of other variables
    // **************************************************************
    size_t n = 0;                                    // Number of data points (adjusted later)
    size_t nstar = 0;                                // equal to n (fixed intercept) or (n-1) not fixed
    double coefbeta[k+1];                            // Coefficients of the polynomial
    // double serbeta[k+1];                             // Standard error on coefficients
    // double tstudentval = 0.;                         // Student t value
    // double SE = 0.;                                  // Standard error
    
    double **XTWXInv;                                // Matrix XTWX Inverse [k+1,k+1]
    double **Weights;                                // Matrix Weights [n,n]


    // Initialize values
    // **************************************************************
    n = sizeof(x)/sizeof(double);
    nstar = n-1;
    if (fixedinter) nstar = n;

#ifndef NODEBUG
    std::cout << "Number of points: " << n << std::endl;
    std::cout << "Polynomial order: " << k << std::endl;
    if (fixedinter) {
        std::cout << "A0 is fixed!" << std::endl;
    } else {
        std::cout << "A0 is adjustable!" << std::endl;
    }
#endif

    if (k>nstar) {
        std::cout << "The polynomial order is too high. Max should be " << n << " for adjustable A0 ";
        std::cout << "and " << n-1 << " for fixed A0. ";  
        std::cout << "Program stopped" << std::endl;
        return -1;
    }

#ifndef NODEBUG
    if (k==nstar) {
        std::cout << "The degree of freedom is equal to the number of points. ";
        std::cout << "The fit will be exact." << std::endl;  
    }
#endif

    XTWXInv = Make2DArray(k+1,k+1);
    Weights = Make2DArray(n,n);

    // Build the weight matrix
    // **************************************************************
    CalculateWeights(erry, Weights, n, wtype);

#ifndef NODEBUG
    std::cout << "Weights" << std::endl;
    displayMat(Weights,n,n);
#endif

    if (determinant(Weights,n)==0.) {
        std::cout << "One or more points have 0 error. Review the errors on points or use no weighting. ";
        std::cout << "Program stopped" << std::endl;
        return -1;
    } 

#ifndef NODEBUG
    std::cout << "Calculate the coefficients of the fit" << "\n";
#endif
    // **************************************************************
    Fit(x,y,n,k,fixedinter,fixedinterval,coefbeta,Weights,XTWXInv);

#ifndef NODEBUG
    std::cout << "Calculate related values" << "\n";
    // **************************************************************
    double RSS = CalculateRSS(x,y,coefbeta,Weights,fixedinter,n,k+1);
    double TSS = CalculateTSS(x,y,coefbeta,Weights,fixedinter,n,k+1);
    double R2 = CalculateR2COD(x,y,coefbeta,Weights,fixedinter,n,k+1);
    double R2Adj = CalculateR2Adj(x,y,coefbeta,Weights,fixedinter,n,k+1);

    if ((nstar-k)>0) {
        SE = sqrt(RSS/(nstar-k)); 
        tstudentval = fabs(CalculateTValueStudent(nstar-k, 1.-0.5*alphaval)); 
    }
    std::cout << "t-student value: " << tstudentval << std::endl << std::endl;
    // Calculate the standard errors on the coefficients
    // **************************************************************
    CalculateSERRBeta(fixedinter,SE,k,serbeta,XTWXInv);

    // Display polynomial
    // **************************************************************
    DisplayPolynomial(k);

    // Display polynomial coefficients
    // **************************************************************
    DisplayCoefs(k, nstar, tstudentval, coefbeta, serbeta);

    // Display statistics
    // **************************************************************
    DisplayStatistics(n,nstar,k,RSS,R2,R2Adj,SE);
  
    // Display ANOVA table
    // **************************************************************
    DisplayANOVA(nstar, k, TSS, RSS);

    // Write the prediction and confidence intervals
    // **************************************************************
    WriteCIBands("CIBands2.dat",x,coefbeta,XTWXInv,tstudentval,SE,n,k);

    // Display the covariance and correlation matrix
    // **************************************************************
    DisplayCovCorrMatrix(k, SE, fixedinter, XTWXInv);
#endif
    return coefbeta[1]; //return the second coefficient of the poly
}

// Adapted from https://github.com/codeplea/incbeta
double PolyFit::incbeta(double a, double b, double x) {
    if (x < 0.0 || x > 1.0) return 1.0/0.0;

    if (a<=0.) {
        std::cout << "Warning: a should be >0";
        return 0.;
    }

    if (b<=0.) {
        std::cout << "Warning: b should be >0";
        return 0.;
    }


    /*The continued fraction converges nicely for x < (a+1)/(a+b+2)*/
    if (x > (a+1.0)/(a+b+2.0)) {
        return (1.0-incbeta(b,a,1.0-x)); /*Use the fact that beta is symmetrical.*/
    }

    /*Find the first part before the continued fraction.*/
    const double lbeta_ab = lgamma(a)+lgamma(b)-lgamma(a+b);
    const double front = exp(log(x)*a+log(1.0-x)*b-lbeta_ab) / a;

    /*Use Lentz's algorithm to evaluate the continued fraction.*/
    double f = 1.0, c = 1.0, d = 0.0;

    int i, m;
    for (i = 0; i <= 200; ++i) {
        m = i/2;

        double numerator;
        if (i == 0) {
            numerator = 1.0; /*First numerator is 1.0.*/
        } else if (i % 2 == 0) {
            numerator = (m*(b-m)*x)/((a+2.0*m-1.0)*(a+2.0*m)); /*Even term.*/
        } else {
            numerator = -((a+m)*(a+b+m)*x)/((a+2.0*m)*(a+2.0*m+1)); /*Odd term.*/
        }

        /*Do an iteration of Lentz's algorithm.*/
        d = 1.0 + numerator * d;
        if (fabs(d) < TINY) d = TINY;
        d = 1.0 / d;

        c = 1.0 + numerator / c;
        if (fabs(c) < TINY) c = TINY;

        const double cd = c*d;
        f *= cd;

        /*Check for stop.*/
        if (fabs(1.0-cd) < STOP) {
            return front * (f-1.0);
        }
    }

    return 1.0/0.0; /*Needed more loops, did not converge.*/
}

double PolyFit::invincbeta(double y,double alpha, double beta) {

    if (y <= 0.) return 0.;
    else if (y >= 1.) return 1.;
    if (alpha<=0.) {
        std::cout << "Warning: alpha should be >0";
        return 0.;
    }

    if (beta<=0.) {
        std::cout << "Warning: beta should be >0";
        return 0.;
    }


    double x = 0.5;
    double a = 0;
    double b = 1;
    double precision = 1.e-8; 
    double binit = y; 
    double bcur = incbeta(alpha,beta,x);
    
    while (fabs(bcur-binit)>precision) {
        
        if ((bcur-binit)<0) {
            a = x;
        }
        else {
            b = x;
        }
        x = (a+b)*0.5;
        bcur = incbeta(alpha,beta,x);

        //std::cout << x << "\t" << bcur << "\n";
   

    }

    return x;


}



// Calculate the t value for a Student distribution
// Adapted from http://www.cplusplus.com/forum/beginner/216098/
// **************************************************************
double PolyFit::CalculateTValueStudent(const double nu, const double alpha) {

    // double precision = 1.e-5;

    if (alpha<=0. || alpha >= 1.) return 0.;

    double x = invincbeta(2.*std::min(alpha,1.-alpha), 0.5*nu, 0.5);
    x = sqrt(nu*(1.-x)/x);
    return (alpha >= 0.5? x : -x);
    

}

// Cumulative distribution for Student-t
// **************************************************************
double PolyFit::cdfStudent(const double nu, const double t)
{
    double x = nu/(t*t+nu); 
   
    return 1.-incbeta(0.5*nu,0.5,x);
}

// Cumulative distribution for Fisher F
// **************************************************************
double PolyFit::cdfFisher(const double df1, const double df2, const double x) {
    double y = df1*x/(df1*x+df2);
    return incbeta(0.5*df1,0.5*df2,y);
}

// Initialize a 2D array
// **************************************************************
double **PolyFit::Make2DArray(const size_t rows, const size_t cols) {

    double **array;

    array = new double*[rows];
    for(size_t i = 0; i < rows; i++) {
        array[i] = new double[cols];
    }

    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < cols; j++) {
            array[i][j] = 0.;
        }
    }
    
    return array;

}

// Transpose a 2D array
// **************************************************************
double **PolyFit::MatTrans(double **array, const size_t rows, const size_t cols) {

    double **arrayT = Make2DArray(cols,rows);

    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < cols; j++) {
            arrayT[j][i] = array[i][j];
        }
    }
    
    return arrayT;

}

// Perform the multiplication of matrix A[m1,m2] by B[m2,m3]
// **************************************************************
double **PolyFit::MatMul(const size_t m1, const size_t m2, const size_t m3, double **A, double **B) {

    double **array = Make2DArray(m1,m3);

    for (size_t i=0; i<m1; i++) {          
        for (size_t j=0; j<m3; j++) {      
            array[i][j]=0.; 
            for (size_t m=0; m<m2; m++) {
                array[i][j]+=A[i][m]*B[m][j];
            } 
        }       
    }
    return array;

}

// Perform the multiplication of matrix A[m1,m2] by vector v[m2,1]
// **************************************************************
void PolyFit::MatVectMul(const size_t m1, const size_t m2, double **A, double *v, double *Av) {

    
    for (size_t i=0; i<m1; i++) {   
        Av[i]=0.;
        for (size_t j=0; j<m2; j++) {
            Av[i]+=A[i][j]*v[j];    
        } 
    }
   

}


// Calculates the determinant of a matrix 
// **************************************************************
double PolyFit::determinant(double **a, const size_t k) {

    double s = 1;
    double det = 0.;
    double **b = Make2DArray(k,k);
    size_t m;
    size_t n;

    if (k == 1) return (a[0][0]);

    for (size_t c=0; c<k; c++) {

        m = 0;
        n = 0;

        for (size_t i = 0; i < k; i++) {

            for (size_t j = 0; j < k; j++) {
                // std::cout << "inside determinant loop" << "\n";
                // std::cout << "c: " << c << "\n";
                // std::cout << "k: " << k << "\n";
                // std::cout << "i: " << i << "\n";
                // std::cout << "j: " << j << "\n";

                b[i][j] = 0;

                if (i != 0 && j != c) {

                    b[m][n] = a[i][j];
                    if (n < (k - 2)) {
                        n++;
                    }
                    else
                    {
                        n = 0;
                        m++;
                    }
                }
            }
        }

        det = det + s * (a[0][c] * determinant(b, k - 1));
        s = -1 * s;

    }
   
    return (det);

}


// Perform the 
// **************************************************************
void PolyFit::transpose(double **num, double **fac, double **inverse, const size_t r) {

    double **b = Make2DArray(r,r);
    double deter;

    for (size_t i=0; i<r; i++) {
        for (size_t j=0; j<r; j++) {
            b[i][j] = fac[j][i];
        }
    }

    deter = determinant(num, r);

    for (size_t i=0; i<r; i++) {
        for (size_t j=0; j<r; j++) {
            inverse[i][j] = b[i][j] / deter;
        }
    }

}

// Calculates the cofactors 
// **************************************************************
void PolyFit::cofactor(double **num, double **inverse, const size_t f)
{

    double **b = Make2DArray(f,f);
    double **fac = Make2DArray(f,f);
   
    size_t m;
    size_t n;

    for (size_t q=0; q<f; q++) {

        for (size_t p=0; p<f; p++) {

            m = 0;
            n = 0;

            for (size_t i=0; i<f; i++) {

                for (size_t j=0; j<f; j++) {

                    if (i != q && j != p) {

                        b[m][n] = num[i][j];

                        if (n < (f - 2)) {
                            n++;
                        }
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }

    transpose(num, fac, inverse, f);

}


// Display a matrix 
// **************************************************************
void PolyFit::displayMat(double **A, const size_t n, const size_t m)  {
 
    std::cout << "Matrix " << n << " x " << m << std::endl;
    for (size_t i=0; i<n; i++) { 
        for (size_t j=0; j<m; j++) 
            std::cout << A[i][j] << "\t"; 
        std::cout << std::endl; 
    } 
    std::cout << std::endl;

} 

// Calculate the residual sum of squares (RSS)
// **************************************************************
double PolyFit::CalculateRSS(const double *x, const double *y, const double *a, double **Weights,
const bool fixed, const size_t N, const size_t n) {

    double r2 = 0.;
    double ri = 0.;
    for (size_t i=0; i<N; i++) {
        ri = y[i];
        for (size_t j=0; j<n; j++) {
            ri -= a[j]*pow(x[i],j);
        }
        r2 += ri*ri*Weights[i][i];
    }

    return r2;

}

// Calculate the total sum of squares (TSS) 
// **************************************************************
double PolyFit::CalculateTSS(const double *x, const double *y, const double *a, double **Weights, 
const bool fixed, const size_t N, const size_t n) {

    double r2 = 0.;
    double ri = 0.;
    double sumwy = 0.;
    double sumweights = 0.;
    size_t begin = 0;
    if (fixed) {
        for (size_t i=begin; i<N; i++) {    
            r2+= y[i]*y[i]*Weights[i][i];
        }
    } else {


        for (size_t i=begin; i<N; i++) {    
            sumwy += y[i]*Weights[i][i];
            sumweights += Weights[i][i];
        }
 
        for (size_t i=begin; i<N; i++) {  
            ri = y[i]-sumwy/sumweights;
            r2 += ri*ri*Weights[i][i];
        }
    }

    return r2;

}

// Calculate coefficient R2 - COD
// **************************************************************
double PolyFit::CalculateR2COD(const double *x, const double *y, const double *a, double **Weights,
const bool fixed, const size_t N, const size_t n) {

    double RSS = CalculateRSS(x,y,a,Weights,fixed,N,n);
    double TSS = CalculateTSS(x,y,a,Weights,fixed,N,n);
    double R2 = 1.-RSS/TSS;

    return R2;

}

// Calculate the coefficient R2 - adjusted
// **************************************************************
double PolyFit::CalculateR2Adj(const double *x, const double *y, const double *a, double **Weights,
const bool fixed,const size_t N, const size_t n) {

    double RSS = CalculateRSS(x,y,a,Weights,fixed,N,n);
    double TSS = CalculateTSS(x,y,a,Weights,fixed,N,n);

    double dferr = N-n;
    double dftot = N-1;

    if (fixed) {
        dferr += 1.;
        dftot += 1.;
    }
    
    double R2Adj = 1.-(dftot)/(dferr)*RSS/TSS;

    return R2Adj;

}

// Perform the fit of data n data points (x,y) with a polynomial of order k
// **************************************************************
void PolyFit::Fit(const double *x, double *y, const size_t n, const size_t k, const bool fixedinter,
const double fixedinterval, double *beta, double **Weights, double **XTWXInv) { 
  
    // Definition of variables
    // **************************************************************
    double **X = Make2DArray(n,k+1);           // [n,k+1]
    double **XT;                               // [k+1,n]
    double **XTW;                              // [k+1,n]
    double **XTWX;                             // [k+1,k+1]

    double *XTWY = new double[k+1];
    double *Y = new double[n];

    size_t begin = 0;
    if (fixedinter) begin = 1;

    // Initialize X
    // **************************************************************
    for (size_t i=0; i<n; i++) { 
        for (size_t j=begin; j<(k+1); j++) {  // begin
          X[i][j]=pow(x[i],j);  
        }       
    } 

    // Matrix calculations
    // **************************************************************
    XT = MatTrans(X, n, k+1);                 // Calculate XT
    XTW = MatMul(k+1,n,n,XT,Weights);         // Calculate XT*W
    XTWX = MatMul(k+1,n,k+1,XTW,X);           // Calculate (XTW)*X

    if (fixedinter) XTWX[0][0] = 1.;  
    
    cofactor(XTWX, XTWXInv, k+1);             // Calculate (XTWX)^-1

    for (size_t m=0; m<n; m++) {
        if (fixedinter) {
            Y[m]= y[m]-fixedinterval;
        } 
        else {
            Y[m] = y[m];
        }
    } 
    MatVectMul(k+1,n,XTW,Y,XTWY);             // Calculate (XTW)*Y
    MatVectMul(k+1,k+1,XTWXInv,XTWY,beta);    // Calculate beta = (XTWXInv)*XTWY

    if (fixedinter) beta[0] = fixedinterval;

#ifndef NODEBUG
    std::cout << "Matrix X" << std::endl;
    displayMat(X,n,k+1);

    std::cout << "Matrix XT" << std::endl;
    displayMat(XT,k+1,n);

    std::cout << "Matrix XTW" << std::endl;
    displayMat(XTW,k+1,n);

    std::cout << "Matrix XTWXInv" << std::endl;
    displayMat(XTWXInv,k+1,k+1);
#endif

}

// Calculate the polynomial at a given x value
// **************************************************************
double PolyFit::calculatePoly(const double x, const double *a, const size_t n) {

    double poly = 0.;

    for (size_t i=0; i<n; i++) {
        poly += a[i]*pow(x,i);
    }

    return poly;

}

// Calculate and write the confidence bands in a file
// **************************************************************
void PolyFit::WriteCIBands(std::string filename, const double *x, const double *coefbeta, double **XTXInv, 
const double tstudentval, const double SE, const size_t n, const size_t k) {

   
    double interval = (x[n-1]-x[0]);
    double x1,y0,y1,y2,y3,y4;
    double xstar[k+1];
    double xprod = 0.;

    std::ofstream output;
    output.open(filename.c_str());
    
    for (int i=0; i<101; i++) {
        x1 = x[0]+interval/100.*i;
        for (size_t j=0; j<k+1; j++) {
            xstar[j] = pow(x1,j); 
        }
        
        xprod = 0.;
        for (size_t j=0; j<(k+1); j++) {
            for (size_t m=0; m<(k+1); m++) {
                xprod += xstar[m]*xstar[j]*XTXInv[j][m];   
            }   
        }

        y0 = calculatePoly(x1, coefbeta,k+1);
        y1 = y0 - tstudentval*SE*sqrt(xprod);
        y2 = y0 + tstudentval*SE*sqrt(xprod);
        y3 = y0 - tstudentval*SE*sqrt(1+xprod);
        y4 = y0 + tstudentval*SE*sqrt(1+xprod);

        output << x1 << "\t" << y0 << "\t" << y1 << "\t" << y2 << "\t";
        output << y3 << "\t" << y4 << std::endl;

    }


    output.close();


}

// Calculate the weights matrix
// **************************************************************
void PolyFit::CalculateWeights(const double *erry, double **Weights, const size_t n,
const int type) {


    for(size_t i = 0; i < n; i++) {

        switch (type) {
            case 0:
                Weights[i][i] = 1.;
            break;
            case 1:
                Weights[i][i] = erry[i];
            break;
            case 2:
                if (erry[i]>0.) {
                    Weights[i][i] = 1./(erry[i]*erry[i]);
                } 
                else {
                    Weights[i][i] = 0.;
                }
            break;
        }
                
    }

}

// Calculate the standard error on the beta coefficients
// **************************************************************
void PolyFit::CalculateSERRBeta(const bool fixedinter, const double SE, size_t k, double *serbeta, double **XTWXInv) {

    size_t begin = 0;
    if (fixedinter) begin = 1;

    serbeta[0] = 0.;  
    for (size_t i=begin; i<(k+1); i++) {   
        serbeta[i] = SE*sqrt(XTWXInv[i][i]);
    }

}

// Display the polynomial
// **************************************************************
void PolyFit::DisplayPolynomial(const size_t k) {

    std::cout << "y = ";
    for (size_t i=0; i<(k+1); i++) { 
        std::cout << "A" << i;
        if (i>0) std::cout << "X";
        if (i>1) std::cout << "^" << i;
        if (i<k) std::cout << " + ";
    }
    std::cout << std::endl << std::endl;

}

// Display the ANOVA test result
// **************************************************************
void PolyFit::DisplayANOVA(const size_t nstar, const size_t k, const double TSS, const double RSS) {

    double MSReg = (TSS-RSS)/(k);
    double MSE = RSS/(nstar-k); 
    double FVal = MSReg/MSE; 
    double pFVal = 1.-cdfFisher(k,nstar-k, FVal);

    std::cout << "ANOVA" << std::endl;
    std::cout << "\tDF\tSum squares\tMean square\tF value\tProb>F" << std::endl;
    std::cout << "Model\t" << k << "\t" << (TSS-RSS) << "\t" << (TSS-RSS)/k << "\t" << FVal << "\t" << pFVal << std::endl;
    std::cout << "Error\t" << nstar-k << "\t" << RSS << "\t" << RSS/(nstar-k) << std::endl;  
    std::cout << "Total\t" << nstar << "\t" << TSS << std::endl << std::endl;  

}


// Display the coefficients of the polynomial
// **************************************************************
void PolyFit::DisplayCoefs(const size_t k, const size_t nstar, const double tstudentval, const double *coefbeta, const double *serbeta) {

    double lcibeta;    // Low confidence interval coefficients
    double hcibeta;    // High confidence interval coefficients

    std::cout << "Polynomial coefficients" << std::endl;
    std::cout << "Coeff\tValue\tStdErr\tLowCI\tHighCI\tStudent-t\tProb>|t|" << std::endl;

    for (size_t i=0; i<(k+1); i++) { 
        lcibeta = coefbeta[i]-tstudentval*serbeta[i];
        hcibeta = coefbeta[i]+tstudentval*serbeta[i];
        std::cout << "A" << i << "\t"; 
        std::cout << coefbeta[i] << "\t";
        std::cout << serbeta[i] << "\t";
        std::cout << lcibeta << "\t";
        std::cout << hcibeta << "\t";

        if (serbeta[i]>0) {
            std::cout << coefbeta[i]/serbeta[i] << "\t";
            std::cout << 1.-cdfStudent(nstar-k, coefbeta[i]/serbeta[i]);  
        } else {
            std::cout << "-\t-";
        }

        std::cout << std::endl;
    }

}

// Display some statistics values
// **************************************************************
void PolyFit::DisplayStatistics(const size_t n, const size_t nstar, const size_t k, const double RSS, const double R2,
const double R2Adj, const double SE) {

  
    std::cout << std::endl;
    std::cout << "Statistics" << std::endl;
    std::cout << "Number of points: " << n << std::endl;
    std::cout << "Degrees of freedom: " << nstar-k << std::endl; 
    std::cout << "Residual sum of squares: " << RSS << std::endl;
    std::cout << "R-square (COD): " << R2 << std::endl;
    std::cout << "Adj R-square: " << R2Adj << std::endl;
    std::cout << "RMSE: " << SE << std::endl << std::endl;


}


// Display the covariance and correlation matrix
// **************************************************************
void PolyFit::DisplayCovCorrMatrix(const size_t k, const double sigma, const bool fixed, double **XTWXInv) {

    
    double **CovMatrix = Make2DArray(k+1,k+1);
    double **CorrMatrix = Make2DArray(k+1,k+1);

    for (size_t i=0; i<k+1; i++) {
        for (size_t j=0; j<k+1; j++) { 
            CovMatrix[i][j] = sigma*sigma*XTWXInv[i][j];
        }
    }

    if (fixed) CovMatrix[0][0] = 1.;

    for (size_t i=0; i<k+1; i++) {
        for (size_t j=0; j<k+1; j++) { 
            CorrMatrix[i][j] = CovMatrix[i][j]/(sqrt(CovMatrix[i][i])*sqrt(CovMatrix[j][j])); 
        }
    }


    std::cout << "Covariance matrix" << std::endl;
    displayMat(CovMatrix,k+1,k+1);

    std::cout << "Correlation matrix" << std::endl;
    displayMat(CorrMatrix,k+1,k+1);


}
