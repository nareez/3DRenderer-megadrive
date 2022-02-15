#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define N_MESH_VERTICES 102
#define N_MESH_FACES 200

extern vec3_t mesh_vertices[N_MESH_VERTICES];
extern face_t mesh_faces[N_MESH_FACES];

#endif