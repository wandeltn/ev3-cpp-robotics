#include "Vector.hpp"

Vector::Vector(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Vector::getDistanceTo(Vector point)
{
    Vector distanceBetween = point - *this;
    return (sqrt(pow(distanceBetween.x, 2) + pow(distanceBetween.y, 2)));
}

double Vector::getLength()
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

// double Vector::getAngle()
// {
//     double result = acos(*this^Vector{1, 0} / this->getLength()) * 180 / M_PI;
//     std::cout << "Vector::getAngle(): " << result << "\n";
//     std::cout << "Vector::getLength(): " << this->getLength() << "\n";
//     std::cout << "Vector before acos: " << (*this^Vector{1, 0} / this->getLength()) << "\n";
//     return result;
// }

Vector Vector::operator+(const Vector &summand)
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

Vector Vector::operator*(const Vector& multiplicand)
{
    return (x * multiplicand.x) + (y * multiplicand.y); 
}

double Vector::operator^(const Vector &multiplicand)
{
    return (this->x * multiplicand.x) + (this->y * multiplicand.y);
}

bool Vector::operator==(const Vector& comparison)
{
    if (this->x == comparison.x && this->y == comparison.y) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    os << "x: " << vector.x << " y: " << vector.y;
    return os;
}
