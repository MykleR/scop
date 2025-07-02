#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <debug.hpp>
#include <utils.hpp>
#include <Pipeline.hpp>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WIN_TITLE "42 SCOP"

#define GL_VERT_SHADER "shaders/vertex.vert"
#define GL_FRAG_SHADER "shaders/fragment.frag"


class OpenglApp
{
FIELD(GLFWwindow*, _window)
FIELD(Pipeline, _shaders)

EXCEPTION(GLFWInitException, "GLFW Initialization failed")
EXCEPTION(WindowInitException, "Window Creation failed")
EXCEPTION(GLEWInitException, "GLEW loading failed")

public:
	OpenglApp();
	~OpenglApp();

	int run();

private:
	void initOpengl();
	void initShader();
	void loop();
};
