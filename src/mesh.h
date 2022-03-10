#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define N_MESH_VERTICES 8
#define N_MESH_FACES 12

extern vec3_t mesh_vertices[N_MESH_VERTICES];
extern face_t mesh_faces[N_MESH_FACES];

// defines a struct for dynamic size meshes, with array of vectors and meshes
typedef struct {
    vec3_t* vertices;   // dynamic array of vertices
    face_t* faces;      // dynamic array of faces
    vec3_t rotation;    // rotation with x, y and z
    vec3_t scale;       // scale with x,y,z
    vec3_t translation; // translation with x,y,z
} mesh_t;

extern mesh_t mesh;

#endif