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
    bool leaf_node;


public:
    Octree(Vec3D origin, Vec3D halfdim);
    ~Octree();
    double get_mass() {return mass;}
    Vec3D get_com();
    void add(double mass, Vec3D& pos);

    Vec3D calc_acc(const Vec3D& pos);

private:
    bool is_in_tree(const Vec3D& pos) const;
    int get_child_index(const Vec3D& pos) const;

    Vec3D get_new_origin(int index) const;
    inline Vec3D get_new_halfdim() { return 0.5*halfdim; }
    inline bool is_leaf() {return leaf_node;}
};

#endif
