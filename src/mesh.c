#include <stdio.h>
#include <string.h>
#include "mesh.h"
#include "array.h"

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {0,0,0}
};

vec3_t cube_vertices[N_CUBE_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 },
    { .x = -1, .y =  1, .z = -1 },
    { .x =  1, .y =  1, .z = -1 },
    { .x =  1, .y = -1, .z = -1 },
    { .x =  1, .y =  1, .z =  1 },
    { .x =  1, .y = -1, .z =  1 },
    { .x = -1, .y =  1, .z =  1 },
    { .x = -1, .y = -1, .z =  1 }
};

face_t cube_faces[N_CUBE_FACES] = {
    { .a = 1, .b = 2, .c = 3, .color = 0xffff0000},
    { .a = 1, .b = 3, .c = 4, .color = 0xffff0000},

    { .a = 4, .b = 3, .c = 5, .color = 0xff00ff00},
    { .a = 4, .b = 5, .c = 6, .color = 0xff00ff00},

    { .a = 6, .b = 5, .c = 7, .color = 0xff0000ff},
    { .a = 6, .b = 7, .c = 8, .color = 0xff0000ff},

    { .a = 8, .b = 7, .c = 2, .color = 0xffff00ff},
    { .a = 8, .b = 2, .c = 1, .color = 0xffff00ff},

    { .a = 2, .b = 7, .c = 5, .color = 0xffffff00},
    { .a = 2, .b = 5, .c = 3, .color = 0xffffff00},

    { .a = 6, .b = 8, .c = 1, .color = 0xff00ffff},
    { .a = 6, .b = 1, .c = 4, .color = 0xff00ffff},
};

void load_cube_mesh_data(void) {
    for (int i = 0; i < N_CUBE_VERTICES; i++) {
        vec3_t cube_vertex = cube_vertices[i];
        array_push(mesh.vertices, cube_vertex);
    }
    for (int i = 0; i < N_CUBE_FACES; i++) {
        face_t cube_face = cube_faces[i];
        array_push(mesh.faces, cube_face);
    }
}

void load_obj_file_data(char *filename) {
    FILE *file;
    file = fopen(filename, "r");

    char line[512];

    while (fgets(line, 512, file)) {
        //printf("LINE=%s", line);
        //vertex
        if (strncmp(line, "v ", 2) == 0) {
            vec3_t vertex;
            sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            array_push(mesh.vertices, vertex);
        }
        //faces
        if (strncmp(line, "f ", 2) == 0) {
            int vertex_indices[3];
            int texture_indices[3];
            int normal_indices[3];
            sscanf(
                line, "f %d/%d/%d %d/%d/%d %d/%d/%d", 
                &vertex_indices[0], &texture_indices[0], &normal_indices[0],
                &vertex_indices[1], &texture_indices[1], &normal_indices[1],
                &vertex_indices[2], &texture_indices[2], &normal_indices[2]
            );
            face_t face = {
                .a = vertex_indices[0],
                .b = vertex_indices[1],
                .c = vertex_indices[2]
            };
            array_push(mesh.faces, face);
        }
    }
}