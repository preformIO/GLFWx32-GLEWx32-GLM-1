# GLFWx32-GLEWx32-GLM-1

Basic example OpenGL application for Visual Studio 2022 that loads an OBJ file from pathOBJ and displays it using shaders specified by pathVShader and pathFshader using perspective projection and slow model rotation.

User can press escape to quit the appliction, and re-sizing the window resizes the perspective projection so it diplays without distortion regardless of window size.

## author

david aloka <d@preform.io>, copyright 2022

## history

### 2022.02.19 12:50
 * implemented perspective projection camera including model, view, and projection transformations
	https://learnopengl.com/Getting-started/Coordinate-Systems
 * implemented simple OBJ loader
	http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
 * OBJ data
	https://www.dropbox.com/s/kb2xjpofsquff4k/data.tgz?dl=0
### 2022.02.19 00:25
 * integrated Shader class
	https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
 * integrated "helloTriangle.cpp" 
	https://www.dropbox.com/s/ldzgp57ph9btzxf/helloTriangle.cpp?dl=0
 * integrated additional source code 
	https://github.com/vkphillia/opengl-cpp-template
### 2022.02.19 00:25
 * integrated initial source code 
	https://github.com/opengl-tutorials/ogl/blob/master/tutorial01_first_window/tutorial01.cpp
 * project setup 
	https://www.wikihow.com/Set-Up-OpenGL-GLFW-GLEW-GLM-on-a-Project-with-Visual-Studio