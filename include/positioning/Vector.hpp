#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>
#include <iostream>

class Vector {
    public:
        Vector(double x = 0, double y = 0);

        double getDistanceTo(Vector point);
        
        Vector operator+(const Vector& summand);
        Vector operator-(const Vector& subtrahend);
        Vector operator/(const double divisor);
        Vector operator*(const double factor);
        double operator^(const Vector& multiplicand);
        bool   operator==(const Vector& comparison);
        friend std::ostream& operator<<(std::ostream& os, const Vector& vector);
        
        double x;
        double y;

    private:
};

#endif // __VECTOR_H__