#include "octree.hpp"
#include "vec3d.hpp"

#include <iostream>
using namespace std;

int main()
{
    Octree o = Octree(Vec3D(), Vec3D(10, 10, 10));

    o.add(1.2, Vec3D(2,3,4));

    o.add(0.4, Vec3D(-2,-3,-4));
    o.add(0.4, Vec3D(2.2, 3.4, 3.4));

    cout << o.get_com() << endl;

    return 0;
}
