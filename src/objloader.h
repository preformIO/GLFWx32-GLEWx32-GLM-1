// author: david allen <d@preform.io>
// based on code from: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#include <vector>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#ifndef H_OBJLOADER
#define H_OBJLOADER

namespace lOBJ {
    bool loadOBJ(
         const char * path,
         vector < float > & out_vertices,
         vector < vec2 > & out_uvs,
         vector < vec3 > & out_normals
    );
}


#endif //!H_OBJLOADER