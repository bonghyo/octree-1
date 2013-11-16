#include "octree.hpp"
#include "vec3d.hpp"
#include <vector>
#include <cmath>
#include <random>

#include <iostream>
using namespace std;

Vec3D direct_force(int index, const vector< Vec3D >& pos)
{
    Vec3D dp;
    const Vec3D mypos = pos[index];
    Vec3D retval = Vec3D();

    for(int i = 0 ; i < index ; i++) {
        dp = pos.at(i) - mypos;
        retval += dp / pow(dp.length(), 3.0);
    }

    for(unsigned int i = index + 1 ; i < pos.size() ; i++) {
        dp = pos[i] - mypos;
        retval += dp / pow(dp.length(), 3.0);
    }

    return retval;
}

int main()
{
    vector< Vec3D > positions;

    default_random_engine generator;
    generator.seed(123);
    uniform_real_distribution<double> coord_dist(-10.0,10.0);
    Octree o(Vec3D(), Vec3D(10.0, 10.0, 10.0));

    for(unsigned int i = 0 ; i < 1000000 ; i++) {
        positions.push_back(Vec3D(coord_dist(generator),
                                  coord_dist(generator),
                                  coord_dist(generator)));
        cout << i << endl;
        //cout << positions[i] << endl;
        o.add(1.0, positions[i]);
    }

    cout << direct_force(1, positions) << endl;
    cout << o.calc_acc(positions[1]) << endl;

    return 0;
}
