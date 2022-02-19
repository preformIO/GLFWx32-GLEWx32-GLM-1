#include <string>
#include <cstring>
#include <fstream>
#include <streambuf>
#include <iostream>

#include <glm/glm.hpp>
#include <vector>

#include "objloader.h"

// author: david allen <d@preform.io>
// based on code from: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

bool lOBJ::loadOBJ(
    // const char * path,
    // std::vector < glm::vec3 > & out_vertices,
    // std::vector < glm::vec2 > & out_uvs,
    // std::vector < glm::vec3 > & out_normals
)
{
  std::cout << "lOBJ::loadOBJ() Executing." << std::endl;

  // // create temporary variables in which to store the contents of the .obj
  // // -------------------
  // std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
  // std::vector< glm::vec3 > temp_vertices;
  // std::vector< glm::vec2 > temp_uvs;
  // std::vector< glm::vec3 > temp_normals;

//   // load file contents
//   // ----------------
//   FILE * file = fopen(path, "r");
//   if( file == NULL ){
//       printf("Impossible to open the file !\n");
//       return false;
//   }

//   // read file until end
//   // ----------------------
//   while( 1 ){
//     char lineHeader[128];
//     // read the first word of the line
//     int res = fscanf(file, "%s", lineHeader);
//     if (res == EOF)
//         break; // EOF = End Of File. Quit the loop.
//     // else : parse lineHeader

//     // deal with vertices
//     if ( strcmp( lineHeader, "v" ) == 0 )
//     {
//       glm::vec3 vertex;
//       fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
//       temp_vertices.push_back(vertex);
//     }
//     else if ( strcmp( lineHeader, "vt" ) == 0 )
//     {
//       glm::vec2 uv;
//       fscanf(file, "%f %f\n", &uv.x, &uv.y );
//       temp_uvs.push_back(uv);
//     }
//     else if ( strcmp( lineHeader, "vn" ) == 0 )
//     {
//       glm::vec3 normal;
//       fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
//       temp_normals.push_back(normal);
//     }
//     else if ( strcmp( lineHeader, "f" ) == 0 )
//     {
//     // deal with faces
//       std::string vertex1, vertex2, vertex3;
//       unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//       int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
//       if (matches != 9){
//           printf("File can't be read by our simple parser : ( Try exporting with other options\n");
//           return false;
//       }
//       vertexIndices.push_back(vertexIndex[0]);
//       vertexIndices.push_back(vertexIndex[1]);
//       vertexIndices.push_back(vertexIndex[2]);
//       uvIndices    .push_back(uvIndex[0]);
//       uvIndices    .push_back(uvIndex[1]);
//       uvIndices    .push_back(uvIndex[2]);
//       normalIndices.push_back(normalIndex[0]);
//       normalIndices.push_back(normalIndex[1]);
//       normalIndices.push_back(normalIndex[2]);
//     }
//   }

//   // Process data
//   // --------------------------
//   // For each vertex of each triangle
//   for( unsigned int i=0; i<vertexIndices.size(); i++ )
//   {
//     unsigned int vertexIndex = vertexIndices[i];
//     glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
//     out_vertices.push_back(vertex);
//   }
//   // For each uv of each triangle
//   for( unsigned int i=0; i<uvIndices.size(); i++ )
//   {
//     unsigned int uvIndex = uvIndices[i];
//     glm::vec2 uv = temp_uvs[ uvIndex-1 ];
//     out_uvs.push_back(uv);
//   }
//   // For each normal of each triangle
//   for( unsigned int i=0; i<normalIndices.size(); i++ )
//   {
//     unsigned int normalIndex = normalIndices[i];
//     glm::vec3 normal = temp_normals[ normalIndex-1 ];
//     out_vertices.push_back(normal);
//   }
    return false;
}
