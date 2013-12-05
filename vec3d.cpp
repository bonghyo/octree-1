#include "vec3d.hpp"

Vec3D operator*(const double fact, const Vec3D& rhs)
{
    return Vec3D( fact*rhs.x, fact*rhs.y, fact*rhs.z );
}

Vec3D operator*(const Vec3D& lhs, const double fact)
{
    return Vec3D( fact*lhs.x, fact*lhs.y, fact*lhs.z );
}



