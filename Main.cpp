// Author: david aloka <d@preform.io>
// History:
//      - project setup: https://www.wikihow.com/Set-Up-OpenGL-GLFW-GLEW-GLM-on-a-Project-with-Visual-Studio
// 		- initial source code: https://github.com/opengl-tutorials/ogl/blob/master/tutorial01_first_window/tutorial01.cpp
//		- additional source code: https://github.com/vkphillia/opengl-cpp-template
// 		- integrated "helloTriangle.cpp" from https://www.dropbox.com/s/ldzgp57ph9btzxf/helloTriangle.cpp?dl=0

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

// Include Shader and Object Loader
#include "src/shader.h"
#include "src/objloader.h"

// GLFWwindow helper function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
// --------------------------------
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// shader paths
const char* pathVShader = "data/shaderVec.glsl"; // ? relative to final application location?
const char* pathFShader = "data/shaderFrag.glsl"; // ? relative to final application location?
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



	// load vertex data from OBJ file
	// ------------------------------------------------------------------
	// set up variables to receive mesh data
	// // std::vector< glm::vec3 > vertices;
	// std::vector< glm::vec3 > verts;
	// std::vector< glm::vec2 > uvs; // won't be used at the moment either?
	// std::vector< glm::vec3 > normals; // Won't be used at the moment.
	// Read our .obj file
	// // bool res = lOBJ::loadOBJ(pathOBJ, vertices, uvs, normals);
	// bool res = lOBJ::loadOBJ(pathOBJ, verts, uvs, normals);
	lOBJ::loadOBJ();
	// 
	// TEMP: (until loadOBJ is written properly)
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions					//colors

		// triangle 1
	 -0.5f, -0.5f, 0.0f, 		1.0f, 0.0f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, 		0.5f, 0.5f, 0.0f,  // right 
		0.0f,  0.5f, 0.0f, 		0.0f, 1.0f, 0.0f,  // top   

		// triangle 2
	 -0.5f, -0.5f, 0.0f, 		0.0f, 0.5f, 0.5f,  // left  
		0.5f, -0.5f, 0.0f, 		0.0f, 0.0f, 1.0f,  // right 
		0.0f, -1.0f, 0.0f, 		0.5f, 0.0f, 0.5f,   // bottom
	};
	unsigned int numVertices = sizeof(vertices) / 3;
	// 
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	// 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
	// 
	// uncomment this call to draw in wireframe polygons.
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



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
		glClear(GL_COLOR_BUFFER_BIT);

		// select shader to use
		ourShader.use();
		// ourShader.setFloat("someUniform", 1.0f);

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
}