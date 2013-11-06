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

    inline double length()
    {
        return sqrt( x*x + y*y + z*z );
    }

    inline void zero()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    inline bool operator==(const Vec3D &rhs)
    {
        return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
    }

    //Vectors add component wise
    inline Vec3D operator+=(const Vec3D& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    Vec3D operator+(const Vec3D& rhs)
    {
        return Vec3D( x + rhs.x, y + rhs.y, z + rhs.z);
    }

    //Vectors subtract component wise
    inline Vec3D operator-=(const Vec3D& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }

    Vec3D operator-(const Vec3D& rhs)
    {
        return Vec3D( x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vec3D operator-()
    {
        return Vec3D( -x, -y, -z);
    }

    inline Vec3D operator*=(const double fact)
    {
        this->x *= fact;
        this->y *= fact;
        this->z *= fact;
        return *this;
    }

    inline Vec3D operator/=(const double fact)
    {
        this->x /= fact;
        this->y /= fact;
        this->z /= fact;
        return *this;
    }

    //Dot Product
    inline double operator*(const Vec3D& rhs)
    {
        return (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z);
    }

    //Vector product
    inline Vec3D operator^(const Vec3D& rhs)
    {
        return Vec3D( this->y*rhs.z - this->z*rhs.y,
                      this->z*rhs.x - this->x*rhs.z,
                      this->x*rhs.y - this->y*rhs.x);
    }

    //Pretty Print vectors.
    friend std::ostream& operator<< (std::ostream& os,const Vec3D& obj)
    {
        os << "[ " << obj.x << " " << obj.y << " " << obj.z << " ]";
        return os;
    }

};

inline Vec3D operator*(const double fact, const Vec3D& rhs)
{
    return Vec3D( fact*rhs.x, fact*rhs.y, fact*rhs.z );
}

inline Vec3D operator*(const Vec3D& lhs, const double fact)
{
    return Vec3D( fact*lhs.x, fact*lhs.y, fact*lhs.z );
}

inline Vec3D operator/(const Vec3D& lhs, const double fact)
{
    return Vec3D(lhs.x / fact, lhs.y / fact, lhs.z / fact);
}



#endif
