#ifndef _OCTREE_HPP
#define _OCTREE_HPP

#include "vec3d.hpp"

class Octree
{
    Octree *children[8];
    Vec3D origin;
    Vec3D halfdim;
    double mass;
    Vec3D com;
    bool com_built;

public:
    Octree(Vec3D origin, Vec3D halfdim);
    ~Octree();
    double get_mass() {return mass;}
    Vec3D get_com();
    void add(double mass, Vec3D pos);

    void print_children();

private:
    bool is_in_tree(const Vec3D& pos);
    int get_child_index(const Vec3D& pos);

    Vec3D get_new_origin(int index);
    Vec3D get_new_halfdim();
    bool is_leaf();
};

#endif
