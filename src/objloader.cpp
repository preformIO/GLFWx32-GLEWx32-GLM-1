// author: david allen <d@preform.io>
// based on code from: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#include <format>
#include <string>
#include <cstring>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <vector>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "objloader.h"

bool lOBJ::loadOBJ(
    const char * path,
    vector < float > & out_vertices,
    vector < vec2 > & out_uvs,
    vector < vec3 > & out_normals
)
{
    cout << "lOBJ::loadOBJ() Executing." << endl;

    // create temporary variables in which to store the contents of the .obj
    // -------------------
    vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    vector< vector< float >> temp_vertices;
    vector< vec2 > temp_uvs;
    vector< vec3 > temp_normals;

    // load file contents
    // ----------------
    FILE* file;
    errno_t err;
    // Open for read (will fail if file "crt_fopen_s.c" doesn't exist)
    err = fopen_s(&file, path, "r");
    if (err == 0)
    {
        printf("The file '%s' was opened\n", path);
    }
    else
    {
        printf("The file '%s' was not opened\n", path);
        return false;
    }

    // read file until end
    // ----------------------
    while( 1 ){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf_s(file, "%s", lineHeader, _countof(lineHeader));
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        // else : parse lineHeader

        // deal with vertices
        if ( strcmp( lineHeader, "v" ) == 0 )
        {
            vector< float > vertex; 
            vertex.resize(6); // three position args, three color args
            fscanf_s(file, "%f %f %f %f %f %f\n", &vertex[0], &vertex[1], &vertex[2], &vertex[3], &vertex[4], &vertex[5]);

            temp_vertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 )
        {
            vec2 uv;
            fscanf_s(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 )
        {
            vec3 normal;
            fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
        // deal with faces
            //string vertex1, vertex2, vertex3; // TODO: delete this line?
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf_s(file, " %i/%i/%i %i/%i/%i %i/%i/%i\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    // Process data
    // --------------------------
    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ )
    {
        unsigned int vertexIndex = vertexIndices[i];
        vector< float > vertex = temp_vertices[vertexIndex - 1];
        for (float f : vertex)
            out_vertices.push_back(f);
    }
    // For each uv of each triangle
    for( unsigned int i=0; i<uvIndices.size(); i++ )
    {
        unsigned int uvIndex = uvIndices[i];
        vec2 uv = temp_uvs[ uvIndex-1 ];
        out_uvs.push_back(uv);
    }
    // For each normal of each triangle
    for( unsigned int i=0; i<normalIndices.size(); i++ )
    {
        unsigned int normalIndex = normalIndices[i];
        vec3 normal = temp_normals[ normalIndex-1 ];
        out_normals.push_back(normal);
    }

    return true;
}

