// Author: david aloka <d@preform.io>
// History:
//      - project setup https://www.wikihow.com/Set-Up-OpenGL-GLFW-GLEW-GLM-on-a-Project-with-Visual-Studio
// 		- initial source code https://github.com/opengl-tutorials/ogl/blob/master/tutorial01_first_window/tutorial01.cpp
//		- additional source code https://github.com/vkphillia/opengl-cpp-template
// 		- integrated "helloTriangle.cpp" https://www.dropbox.com/s/ldzgp57ph9btzxf/helloTriangle.cpp?dl=0
//		- perspective projection camera https://learnopengl.com/Getting-started/Coordinate-Systems

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// Include Shader and Object Loader
#include "src/shader.h"
#include "src/objloader.h"
using namespace lOBJ;

// GLFWwindow helper function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
// --------------------------------
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
// shader paths
const char* pathVShader = "data/shaderVec.hlsl"; // ? relative to final application location?
const char* pathFShader = "data/shaderFrag.hlsl"; // ? relative to final application location?
// obj file path
const char* pathOBJ = "data/objs/cube_tris.obj"; // ? relative to final application location?



int main(void)
{
	// glfw: initialize and configure
	// ------------------------------
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif

	// glfw window creation -- Open a window and create its OpenGL context
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLEW: initialize -- load all OpenGL function pointers
	// ---------------------------------------
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}



	// build and compile our shader program
	// ------------------------------------
	Shader ourShader(pathVShader, pathFShader);



	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// load vertex data from OBJ file
	// --
	// set up variables to receive mesh data
	vector< float > vertices;
	vector< vec2 > uvs; // Won't be used at the moment either?
	vector< vec3 > normals; // Won't be used at the moment.
	// Read our .obj file
	bool res = loadOBJ(pathOBJ, vertices, uvs, normals);
	unsigned int numVertices = vertices.size() / 6;
	//
	// vertex buffer(s) vertex attributes
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	// 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	// set up vertex attribute pointers
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	
	// Render settings
	// uncomment this call to draw in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// uncomment this call for front-face rendering
	//glPolygonMode(GL_FRONT, GL_FILL);
	// uncomment this call for inverted normals rendering
	//glPolygonMode(GL_BACK, GL_FILL);
	// enable depth testing so fragments render at proper depth
	glEnable(GL_DEPTH_TEST);


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// select shader to use
		ourShader.use();
		// ourShader.setFloat("someUniform", 1.0f);


		// create transformations
		mat4 model = mat4(1.0f); // make sure to initialize matrix to identity matrix first
		mat4 view = mat4(1.0f);
		mat4 projection = mat4(1.0f);
		view = translate(view, vec3(0.0f, 0.0f, -3.0f));
		view = rotate(view, radians(30.0f), vec3(1.0f, 0.0f, 0.0f));
		view = rotate(view, radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
		projection = perspective(radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		// pass tranformations to appropriate shader uniforms
		ourShader.setMat4("model", model);
		ourShader.setMat4("view", view);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		ourShader.setMat4("projection", projection);


		// draw our triangles
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		// glBindVertexArray(0); // unbind our VA no need to unbind it every time 

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	ourShader.del();

	// glfw: clsose OpenGL window and terminate GLFW, clearing all allocated resources.
	//---------------------------------------------------------------
	glfwTerminate();

	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}