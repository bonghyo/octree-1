#include "octree.hpp"
#include <cassert>

Octree::Octree(const Vec3D origin,
               const Vec3D halfdim): origin(origin),
                                     halfdim(halfdim),
                                     mass(0.0),
                                     com(Vec3D()),
                                     com_built(true),
                                     leaf_node(false)
{
    for(int i = 0 ; i < 8 ; i++)
        children[i] = NULL;
}

Octree::~Octree()
{
    for(int i = 0 ; i < 8 ; i++) {
        if( children != NULL )
            delete children[i];
    }
}

inline Vec3D Octree::get_com()
{
    if( com_built ) return com;

    com.zero();
    for(int i = 0 ; i < 8 ; i++) {
        if( children[i] != NULL ) {
            com += children[i]->get_mass() * children[i]->get_com();
        } 
    }
    com /= mass;
    com_built = true;

    return com;
}

void Octree::add(double mass, Vec3D& pos)
{
    com_built = false;

    if( this->mass == 0 ) {
        this->mass = mass;
        this->com = pos;
        com_built = true;
        leaf_node = true;
        return;
    }

    if( is_leaf() ) {
        leaf_node = false;
        int child_index1 = get_child_index(pos);
        int child_index2 = get_child_index(com);

        children[child_index1] = new Octree( get_new_origin(child_index1),
                                             get_new_halfdim() );
        children[child_index1]->add(mass, pos);

        if(child_index1 == child_index2) {
            children[child_index1]->add(this->mass, com);
        } else {
            children[child_index2] = new Octree( get_new_origin(child_index2),
                                                 get_new_halfdim() );
            children[child_index2]->add(this->mass, com);
        }

        this->mass += mass;
        return;
    }

    int child_index = get_child_index(pos);

    if( children[child_index] == NULL ) {
        children[child_index] = new Octree( get_new_origin(child_index),
                                            get_new_halfdim() );
        children[child_index]->add(mass, pos);
    } else {
        children[child_index]->add(mass, pos);
    }

    this->mass += mass;
    return;
}


int Octree::get_child_index(const Vec3D& pos) const
{
    // Indices are made such that we have
    //   x y z
    // 0 + + +
    // 1 + + -
    // 2 + - +
    // 3 + - -
    // 4 - + +
    // 5 - + -
    // 6 - - +
    // 7 - - -

    int index = 0;
    if( pos.x < origin.x ) index += 4;
    if( pos.y < origin.y ) index += 2;
    if( pos.z < origin.z ) index += 1;

    return index;
}

Vec3D Octree::get_new_origin(int index) const
{
    return Vec3D( origin.x + halfdim.x * (index&4 ? -0.5 : 0.5 ),
                  origin.y + halfdim.y * (index&2 ? -0.5 : 0.5 ),
                  origin.z + halfdim.z * (index&1 ? -0.5 : 0.5 ) );
}

Vec3D Octree::calc_acc(const Vec3D& pos)
{
    double node_d = (origin - pos).length();

    if( pos == get_com() ) { return Vec3D(); }

    if( 2. * node_d / halfdim.x > 20.0  || is_leaf() ) { 
    //if( is_leaf() ) {
        Vec3D dp = pos - get_com();
        return -mass * dp / pow(dp.length(), 3.0);
    }

    Vec3D retval = Vec3D();

    for(int i = 0; i < 8 ; i++ ) {
        if( children[i] != NULL ) {
            retval += children[i]->calc_acc(pos);
        }
    }

    return retval;
}
