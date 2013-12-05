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

Vec3D find_max_frac_error(vector<Vec3D> f1, vector<Vec3D> f2)
{
    vector<Vec3D> frac_errors(f1.size());

    for(int i = 0 ; i < f1.size() ; i++) {
        frac_errors[i] = (f2[i] - f1[i] ) / f1[i];
    }

    double maxx = 0.0, maxy = 0.0, maxz = 0.0;

    for(int i = 0 ; i < f1.size() ; i++) {
        if( abs(frac_errors[i].x) > maxx ) maxx = frac_errors[i].x;
        if( abs(frac_errors[i].y) > maxy ) maxy = frac_errors[i].y;
        if( abs(frac_errors[i].z) > maxz ) maxz = frac_errors[i].z;
    }

    return Vec3D(maxx, maxy, maxz);
}

int main()
{
    vector< Vec3D > positions;

    const int Nparts = 100000;

    default_random_engine generator;
    generator.seed(123);
    uniform_real_distribution<double> coord_dist(-10.0,10.0);
    Octree o(Vec3D(), Vec3D(10.0, 10.0, 10.0));

    for(unsigned int i = 0 ; i < Nparts ; i++) {
        positions.push_back(Vec3D(coord_dist(generator),
                                  coord_dist(generator),
                                  coord_dist(generator)));
        //cout << positions[i] << endl;
        o.add(1.0, positions[i]);
    }

    vector< Vec3D > tforces;
    vector< Vec3D > dforces;


    for(int i = 0 ; i < Nparts ; i++) {
        cout << i << endl;
        tforces.push_back( o.calc_acc( positions[i] ) );
        //dforces.push_back(  direct_force(i, positions) );

        cout <<  tforces[i] << endl;

        //cout << (tforces[i] - dforces[i]) / dforces[i] <<  endl;
    }



    return 0;
}
