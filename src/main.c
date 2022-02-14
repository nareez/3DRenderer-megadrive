//TODO fix div/0 on drawline
#include <genesis.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"

#define COLOR 0xff

int how_much_triangles_to_render = 0;
triangle_t triangles_to_render[N_MESH_FACES];

vec3_t camera_position = { .x = FIX16(0), .y = FIX16(0), .z = FIX16(0) };
vec3_t cube_rotation = { .x = FIX16(0), .y = FIX16(0), .z = FIX16(0) };

fix16 fov_factor = FIX16(5);

void setup(void){
    // reduce DMA buffer size to avoid running out of memory (we don't need it)
    DMA_setBufferSize(2048);
    MEM_pack();

    // init BMP mode
    initialize_window();
}

// Function that receives a 3D vector and returns a projected 2D points
vec2_t project(vec3_t point){
    vec2_t projected_point = {
        .x = fix16Div(fix16Mul(fov_factor, point.x), point.z),
        .y = fix16Div(fix16Mul(fov_factor, point.y), point.z)
    };
    return projected_point;
}

void update(void){
    //prevent overflow subtracting when value is greater than 31.78
    cube_rotation.x += cube_rotation.x >= FIX16(31.78) ? FIX16(-31.78) : FIX16(0.1);
    cube_rotation.y += cube_rotation.y >= FIX16(31.78) ? FIX16(-31.78) : FIX16(0.1);
    cube_rotation.z += cube_rotation.z >= FIX16(31.78) ? FIX16(-31.78) : FIX16(0.1);
    // draw_fix16(cube_rotation.x);
    // draw_fix16(cube_rotation.y);
    // draw_fix16(cube_rotation.z);
    // draw_fix16_reset();
    how_much_triangles_to_render = 0;
    
    for (int i = 0; i < N_MESH_FACES; i++) {
        face_t mesh_face = mesh_faces[i];
        vec3_t face_vertices[3];
        face_vertices[0] = mesh_vertices[mesh_face.a - 1];
        face_vertices[1] = mesh_vertices[mesh_face.b - 1];
        face_vertices[2] = mesh_vertices[mesh_face.c - 1];

        vec3_t transformed_vertices[3];

        for (int j = 0; j < 3; j++) {
            vec3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

            // translate away from the camera
            transformed_vertex.z += FIX16(15);

            // Save transformed vertex in the array of transformed vertices
            transformed_vertices[j] = transformed_vertex;
        }

        // check backface culling
        vec3_t vector_a = transformed_vertices[0]; /*    A   */
        vec3_t vector_b = transformed_vertices[1]; /*  /  \  */
        vec3_t vector_c = transformed_vertices[2]; /* B---C  */

        // get vector subtraction of B-A and C-A
        vec3_t vector_ab = vec3_sub(vector_b, vector_a);
        vec3_t vector_ac = vec3_sub(vector_c, vector_a);

        // Normalize
        vec3_normalize(&vector_ab);
        vec3_normalize(&vector_ac);

        // Compute the face normal (using cross product to find perpendicular)
        vec3_t normal = vec3_cross(vector_ab, vector_ac);

        // Normalize the face normal vector
        vec3_normalize(&normal);

        // find the vector ray between camera position and a point in triangle
        vec3_t camera_ray = vec3_sub(camera_position, vector_a);

        // Calculate how aligned the camera ray is with the face normal (using dot product)
        fix16 dot_normal_camera = vec3_dot(normal, camera_ray);
        // bypass the triangles that are looking away from camera
        if (dot_normal_camera < FIX16(0)) continue;

        // loop all tree vertices to perform projection
        triangle_t projected_triangle;
        for (int j = 0; j < 3; j++) {
            // project current vertex
            vec2_t projected_point = project(transformed_vertices[j]);

            // scale and translate to the middle of the screen
            projected_point.x += FIX16(128+2);
            projected_point.y += FIX16(80+1);

            projected_triangle.points[j] = projected_point;
            
        }
        //save triangle in array to render
        triangles_to_render[how_much_triangles_to_render] = projected_triangle;
        how_much_triangles_to_render++;
    }
}

void render(void){
    BMP_waitWhileFlipRequestPending();
    BMP_clear();

    //loop all triangles and render
    for (int i = 0; i < how_much_triangles_to_render; i++){
        // triangle_t triangle = triangles_to_render[i];

        draw_triangle(triangles_to_render[i].points[0].x, triangles_to_render[i].points[0].y
                     ,triangles_to_render[i].points[1].x, triangles_to_render[i].points[1].y
                     ,triangles_to_render[i].points[2].x, triangles_to_render[i].points[2].y
                     ,COLOR, cube_rotation);

    }
    BMP_showFPS(1);
    BMP_flip(1);    
}

int main()
{
    setup();
    while (1){
        update();
        render();
    }
}