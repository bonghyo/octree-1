/****************************************************************************
 *                                Vec3d                                     *
 *                                =====                                     *
 * This is a class which encapulates a 3D vector with overloaded operators  *
 * to give all properties as expected mathematically.                       *
 ***************************************************************************/

#ifndef _VEC3D_HPP
#define _VEC3D_HPP

#include <iostream>
#include <cmath>

class Vec3D {
public:
    double x, y, z;

    Vec3D(double x, double y, double z): x(x), y(y), z(z) {};
    Vec3D(): x(0), y(0), z(0) {};

    double length() const
    {
        return sqrt( x*x + y*y + z*z );
    }

    double lengthsq() const
    {
        return x*x + y*y + z*z;
    }

    void zero()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    bool operator==(const Vec3D &rhs) const
    {
        return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
    }

    //Vectors add component wise
    Vec3D operator+=(const Vec3D& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    Vec3D operator+(const Vec3D& rhs) const
    {
        return Vec3D( x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vec3D operator/(const Vec3D& rhs) const
    {
        return Vec3D( x / rhs.x, y / rhs.y, z / rhs.z );
    }

    //Vectors subtract component wise
    Vec3D operator-=(const Vec3D& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }

    Vec3D operator-(const Vec3D& rhs) const
    {
        return Vec3D(x - rhs.x, y-rhs.y, z-rhs.z);
    }

    Vec3D operator-() const
    {
        return Vec3D( -x, -y, -z);
    }

    Vec3D operator*=(const double fact)
    {
        this->x *= fact;
        this->y *= fact;
        this->z *= fact;
        return *this;
    }

    Vec3D operator/=(const double fact)
    {
        this->x /= fact;
        this->y /= fact;
        this->z /= fact;
        return *this;
    }

    //Dot Product
    double operator*(const Vec3D& rhs) const
    {
        return (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z);
    }

    //Vector product
    Vec3D operator^(const Vec3D& rhs) const
    {
        return Vec3D( this->y*rhs.z - this->z*rhs.y,
                      this->z*rhs.x - this->x*rhs.z,
                      this->x*rhs.y - this->y*rhs.x);
    }

    Vec3D operator/(const double fact) const
    {
        return Vec3D(x / fact, y / fact, z / fact);
    }

    Vec3D operator*(const double fact) const
    {
        return Vec3D( fact*x, fact*y, fact*z );
    }

    //Pretty Print vectors.
    friend std::ostream& operator<< (std::ostream& os,const Vec3D& obj)
    {
        os << "[ " << obj.x << " " << obj.y << " " << obj.z << " ]";
        return os;
    }


};

Vec3D operator*(const double fact, const Vec3D& rhs);


#endif
