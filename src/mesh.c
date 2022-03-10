#include "mesh.h"

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {FIX16(0), FIX16(0), FIX16(0)},
    .scale = {FIX16(1.0), FIX16(1.0), FIX16(1.0)},
    .translation = {FIX16(0), FIX16(0), FIX16(0)}
};

vec3_t mesh_vertices[N_MESH_VERTICES] = {
    { .x =FIX16(-1), .y =FIX16(-1), .z =FIX16(-1) }, // 1
    { .x =FIX16(-1), .y = FIX16(1), .z =FIX16(-1) }, // 2
    { .x = FIX16(1), .y = FIX16(1), .z =FIX16(-1) }, // 3
    { .x = FIX16(1), .y =FIX16(-1), .z =FIX16(-1) }, // 4
    { .x = FIX16(1), .y = FIX16(1), .z = FIX16(1) }, // 5
    { .x = FIX16(1), .y =FIX16(-1), .z = FIX16(1) }, // 6
    { .x =FIX16(-1), .y = FIX16(1), .z = FIX16(1) }, // 7
    { .x =FIX16(-1), .y =FIX16(-1), .z = FIX16(1) }  // 8
};

face_t mesh_faces[N_MESH_FACES] = {
    // front
    { .a = 1, .b = 2, .c = 3, .color = 0x0044  },
    { .a = 1, .b = 3, .c = 4, .color = 0x0044  },
    // right
    { .a = 4, .b = 3, .c = 5, .color = 0x0066 },
    { .a = 4, .b = 5, .c = 6, .color = 0x0066  },
    // back
    { .a = 6, .b = 5, .c = 7, .color = 0x0088 },
    { .a = 6, .b = 7, .c = 8, .color = 0x0088 },
    // left
    { .a = 8, .b = 7, .c = 2, .color = 0x0022  },
    { .a = 8, .b = 2, .c = 1, .color = 0x0022  },
    // top
    { .a = 2, .b = 7, .c = 5, .color = 0x00aa  },
    { .a = 2, .b = 5, .c = 3, .color = 0x00aa  },
    // bottom
    { .a = 6, .b = 8, .c = 1, .color = 0x00ff },
    { .a = 6, .b = 1, .c = 4, .color = 0x00ff }
};

