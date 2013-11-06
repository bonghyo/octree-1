#include "octree.hpp"

Octree::Octree(const Vec3D origin,
               const Vec3D halfdim): origin(origin),
                                     halfdim(halfdim),
                                     mass(0.0),
                                     com(Vec3D()),
                                     com_built(true)
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

Vec3D Octree::get_com()
{
    if( com_built )
        return com;

    com.zero();
    for(int i = 0 ; i < 8 ; i++) {
        if( children[i] != NULL ) {
            com += children[i]->get_mass() * children[i]->get_com();
        } 
    }
    com /= mass;

    return com;
}

void Octree::add(double mass, Vec3D pos)
{
    com_built = false;

    if( this->mass == 0 ) {
        this->mass = mass;
        this->com = pos;
        com_built = true;
        return;
    }

    if( is_leaf() ) {
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


int Octree::get_child_index(const Vec3D& pos)
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

bool Octree::is_leaf()
{
    for(int i = 0 ; i < 8 ; i++) {
        if( children[i] != NULL ) 
            return false;
    }
    return true;
}

Vec3D Octree::get_new_origin(int index)
{
    return Vec3D( origin.x += halfdim.x * (index&4 ? -0.5 : 0.5 ),
                  origin.y += halfdim.y * (index&2 ? -0.5 : 0.5 ),
                  origin.z += halfdim.z * (index&1 ? -0.5 : 0.5 ) );
}

Vec3D Octree::get_new_halfdim()
{
    return 0.5*halfdim;
}

void Octree::print_children()
{
    for(int i = 0 ; i < 8 ; i++) {
        std::cout << children[i] << " ";
    }
    std::cout << std::endl;
}
