#include "Vector.hpp"

Vector::Vector(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector Vector::operator+(const Vector& summand)
{
    return Vector{x + summand.x, y + summand.y};
}

Vector Vector::operator-(const Vector& subtrahend)
{
    return Vector{x - subtrahend.x, y - subtrahend.y};   
}

Vector Vector::operator/(const double divisor)
{
    return Vector{x / divisor, y / divisor};
}

Vector Vector::operator*(const double factor)
{
    return Vector{x * factor, y * factor};
}

double Vector::operator^(const Vector& multiplicand)
{
    return (x * multiplicand.x) + (y * multiplicand.y); 
}