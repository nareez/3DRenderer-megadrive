#!/usr/bin/env python3
import argparse
import os

class Vertex:
    x = None
    y = None
    z = None

class Face:
    vertex_indices = None
    texture_indices = None
    normal_indices = None

def read_obj(filename):
    lines = open(filename).read().split('\n')

    vertices = []
    faces = []

    for line in lines:
        line = line.split(' ')
        if len(line) < 2:
            continue

        key = line[0]
        values = line[1:]

        if key == 'v':
            vertex = Vertex()
            vertex.x = values[0]
            vertex.y = values[1]
            vertex.z = values[2]
            vertices.append(vertex)
        elif key == 'f':
            face = Face()
            splitted = [i.split('/') for i in values]
            face.vertex_indices = [i[0] for i in splitted]
            face.texture_indices = [i[1] for i in splitted]
            face.normal_indices = [i[2] for i in splitted]
            faces.append(face)
        elif key == 'vn':
            continue
        elif key == 'vt':
            continue

    return vertices, faces

def formatVertices(vertices,templateType=0):

    firstLineTemplate = 'vec3_t mesh_vertices[{0}] = {{' + os.linesep
    contentLineTemplate = '    {{ .x = {0}, .y = {1}, .z = {2} }},' + os.linesep
    lastLineTemplate = '};'

    if (templateType == 1):
        firstLineTemplate = 'vec3_t mesh_vertices[{0}] = {{' + os.linesep
        contentLineTemplate = '    {{ .x = FIX16({0}), .y = FIX16({1}), .z = FIX16({2}) }},' + os.linesep
        lastLineTemplate = '};'

    firstLine = firstLineTemplate.format(len(vertices))
    contentLine = ''
    for vertice in vertices:
        contentLine += contentLineTemplate.format(vertice.x, vertice.y, vertice.z)
    contentLine = contentLine[:-2] + os.linesep
    lastLine = lastLineTemplate

    resultMeshesText = firstLine + contentLine + lastLine
    return resultMeshesText

def formatFaces(faces):
    firstLineTemplate = 'face_t mesh_faces[{0}] = {{' + os.linesep
    contentLineTemplate = '    {{ .a = {0}, .b = {1}, .c = {2} }},' + os.linesep
    lastLineTemplate = '};'

    firstLine = firstLineTemplate.format(len(faces))
    contentLine = ''
    for face in faces:
        contentLine += contentLineTemplate.format(face.vertex_indices[0], face.vertex_indices[1], face.vertex_indices[2])
    contentLine = contentLine[:-2] + os.linesep
    lastLine = lastLineTemplate

    resultFacesText = firstLine + contentLine + lastLine
    return resultFacesText


parser = argparse.ArgumentParser(description='Convert OBJ Wavefront to C Arrays vertices and faces')
parser.add_argument('sourcefile', nargs=1, metavar='source file', help='Source OBJ Wavefront file')
parser.add_argument('--type', nargs='?',type=int, choices=[0,1], default=0, help='0: default | 1: SGDK fix16 format')
args = parser.parse_args()

vertices, faces = read_obj(args.sourcefile[0])

verticesText = formatVertices(vertices, args.type)
facesText = formatFaces(faces)

print(verticesText)
print(os.linesep)
print(facesText)
