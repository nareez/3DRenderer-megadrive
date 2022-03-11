#include <genesis.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "matrix.h"

int num_triangles = 0;
triangle_t triangles_to_render[N_MESH_FACES];

vec3_t camera_position = { .x = FIX16(0), .y = FIX16(0), .z = FIX16(0) };

fix16 fov_factor = FIX16(50);

void handleJoyEvent(u16 joy, u16 changed, u16 state);

void setup(void){

    // reduce DMA buffer size to avoid running out of memory
    DMA_setBufferSize(2048);
    MEM_pack();

    //controller checking
    JOY_setSupport(PORT_1, JOY_SUPPORT_6BTN);
    JOY_setSupport(PORT_2, JOY_SUPPORT_OFF);

    JOY_setEventHandler(handleJoyEvent);

    //initialize the render mode
    render_method = RENDER_FILL_TRIANGLE_WIRE;
    cull_method = CULL_BACKFACE;

    // init BMP mode
    initialize_window();
}

void handleJoyEvent(u16 joy, u16 changed, u16 state){
    if (joy == JOY_1){
        if (changed & ~state & BUTTON_A){
            cull_method = 1 - cull_method;
        }
        if (changed & ~state & BUTTON_B){
            render_method = (render_method - 1 + 3) % 3;
        }
    }
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

    JOY_update();

    //prevent overflow subtracting when value is greater than 31.78
    mesh.rotation.x += mesh.rotation.x >= FIX16(31.78) ? FIX16(-31.78) : FIX16(0.1);
    mesh.rotation.y += mesh.rotation.y >= FIX16(31.78) ? FIX16(-31.78) : FIX16(0.1);
    mesh.rotation.z += mesh.rotation.z >= FIX16(31.78) ? FIX16(-31.78) : FIX16(0.1);
    mesh.translation.z = FIX16(3);
    // mesh.scale.x += 0.003;
    // mesh.scale.y += 0.001;
    // mesh.translation.x += 0.01;

    // reset triangles to render
    num_triangles = 0;

    // create a rotation, scale and translation matrix that will be used to multiply the mesh vertices
    // mat4_t scale_matrix = mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
    mat4_t translation_matrix = mat4_make_translation(mesh.translation.x, mesh.translation.y, mesh.translation.z);
    mat4_t rotation_matrix_x = mat4_make_rotation_x(mesh.rotation.x);
    mat4_t rotation_matrix_y = mat4_make_rotation_y(mesh.rotation.y);
    mat4_t rotation_matrix_z = mat4_make_rotation_z(mesh.rotation.z);

    for (int i = 0; i < N_MESH_FACES; i++) {
        face_t mesh_face = mesh_faces[i];
        vec3_t face_vertices[3];
        face_vertices[0] = mesh_vertices[mesh_face.a - 1];
        face_vertices[1] = mesh_vertices[mesh_face.b - 1];
        face_vertices[2] = mesh_vertices[mesh_face.c - 1];

        vec4_t transformed_vertices[3];

        for (int j = 0; j < 3; j++) {

            vec4_t transformed_vertex = vec4_from_vec3(face_vertices[j]);

            // transformed_vertex = mat4_mul_vec4(scale_matrix, transformed_vertex);
            transformed_vertex = mat4_mul_vec4(rotation_matrix_x, transformed_vertex);
            transformed_vertex = mat4_mul_vec4(rotation_matrix_y, transformed_vertex);
            transformed_vertex = mat4_mul_vec4(rotation_matrix_z, transformed_vertex);
            transformed_vertex = mat4_mul_vec4(translation_matrix, transformed_vertex);

            // Save transformed vertex in the array of transformed vertices
            transformed_vertices[j] = transformed_vertex;
        }

        if(cull_method == CULL_BACKFACE){
            // check backface culling
            vec3_t vector_a = vec3_from_vec4(transformed_vertices[0]); /*    A   */
            vec3_t vector_b = vec3_from_vec4(transformed_vertices[1]); /*  /  \  */
            vec3_t vector_c = vec3_from_vec4(transformed_vertices[2]); /* B---C  */

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
        }

        // loop all tree vertices to perform projection
        vec2_t projected_points[3];
        for (int j = 0; j < 3; j++) {
            // project current vertex
            projected_points[j] = project(vec3_from_vec4(transformed_vertices[j]));

            // translate to the middle of the screen
            projected_points[j].x += FIX16(128);
            projected_points[j].y += FIX16(80);
            
        }

        fix16 avg_depth = fix16Div((transformed_vertices[0].z + transformed_vertices[1].z + transformed_vertices[2].z), FIX16(3.0));

        triangle_t projected_triangle = {
            .points = {
                { projected_points[0].x, projected_points[0].y },
                { projected_points[1].x, projected_points[1].y },
                { projected_points[2].x, projected_points[2].y },
            },
            .color = mesh_face.color,
            .avg_depth = avg_depth
        };

        //save triangle in array to render
        triangles_to_render[num_triangles] = projected_triangle;
        num_triangles++;
    }
    // Sort the triangles to render by their avg_depth
    for (int i = 0; i < num_triangles; i++) {
        for (int j = i; j < num_triangles; j++) {
            if (triangles_to_render[i].avg_depth < triangles_to_render[j].avg_depth) {
                // Swap the triangles positions in the array
                triangle_t temp = triangles_to_render[i];
                triangles_to_render[i] = triangles_to_render[j];
                triangles_to_render[j] = temp;
            }
        }
    }
}

void render(void){
    BMP_waitWhileFlipRequestPending();
    BMP_clear();

    // loop all triangles and render
    for (int i = 0; i < num_triangles; i++){
        // se não funcionar chamar diretamente
        triangle_t triangle = triangles_to_render[i];
        
        
        if (render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE){
            draw_filled_triangle(fix16ToRoundedInt(triangle.points[0].x), fix16ToRoundedInt(triangle.points[0].y)
                                ,fix16ToRoundedInt(triangle.points[1].x), fix16ToRoundedInt(triangle.points[1].y)
                                ,fix16ToRoundedInt(triangle.points[2].x), fix16ToRoundedInt(triangle.points[2].y)
                                ,triangle.color);
        }
        if (render_method == RENDER_FILL_TRIANGLE_WIRE || render_method == RENDER_WIRE){
            draw_triangle(fix16ToRoundedInt(triangle.points[0].x), fix16ToRoundedInt(triangle.points[0].y)
                         ,fix16ToRoundedInt(triangle.points[1].x), fix16ToRoundedInt(triangle.points[1].y)
                         ,fix16ToRoundedInt(triangle.points[2].x), fix16ToRoundedInt(triangle.points[2].y)
                         ,0x00ff);
        }
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