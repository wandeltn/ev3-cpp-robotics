#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector {
    public:
        Vector(double x = 0, double y = 0);

        
        Vector operator+(const Vector& summand);
        Vector operator-(const Vector& subtrahend);
        Vector operator/(const double divisor);
        Vector operator*(const double factor);
        double operator^(const Vector& multiplicand);
        
        double x;
        double y;

    private:
};

#endif // __VECTOR_H__