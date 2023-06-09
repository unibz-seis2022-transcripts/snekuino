#include "canvas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <gl/GLU.h>


#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

static bool quit = false;

static GLuint textureID = ~0x00;
static unsigned char* texData = NULL;
static int texWidth = 0;
static int texHeight = 0;
static int resX = 0;
static int resY = 0;

static GLFWwindow* window = NULL;
static int windowWidth = 0;
static int windowHeight = 0;

static float u0 = 0;
static float v0 = 0;
static float u1 = 1;
static float v1 = 1;

static bool dirty = false;

int nextPo2(int n)
{
	int i = 1;
	while (i < n)
	{
		i *= 2;
	}

	return i;
}


static void onError(int error, const char* desc)
{
	printf("<error> GLFW err #%d: \"%s\"\n", error, desc);
}

static void onKey(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		aPressed = true;

	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		aPressed = false;

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		sPressed = true;

	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		sPressed = false;

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		dPressed = true;

	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		dPressed = false;

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		wPressed = true;

	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		wPressed = false;
	
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		qPressed = true;

	if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
		qPressed = false;

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		enterPressed = true;

	if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		enterPressed = false;
}

static void onChar(GLFWwindow* window, unsigned int c)
{
}

static void onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
}

int canvasInit(int x, int y, int width, int height, int resolutionX, int resolutionY)
{
	if (resolutionX <= 0 || resolutionY <= 0)
		return -1;

	if (width <= 0 || height <= 0)
		return -1;

	glfwSetErrorCallback(onError);

	if (glfwInit() == GLFW_FALSE)
	{
		printf("failed to init glfw\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	window = glfwCreateWindow(width, height, "Snek", NULL, NULL);
	if (!window)
	{
		printf("failed to init glfw\n");
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);				// enable vsync

	glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);

	glfwSetWindowPos(window, x, y);
	glfwSetWindowSize(window, width, height);

	windowWidth = width;
	windowHeight = height;

	glfwSetKeyCallback(window, onKey);
	glfwSetCharCallback(window, onChar);
	glfwSetMouseButtonCallback(window, onMouseButton);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize OpenGL loader!\n");
		return -1;
	}

	//printf("Your OpenGL version: %s\n Enjoy your graphics performance\n", glGetString(GL_VERSION));

	glPointSize(4);
	glLineWidth(1);

	glColor3f(1, 1, 1);
	glClearColor(0, 0, 0, 1);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glGenTextures(1, &textureID);

	if (texData)
	{
		free(texData);
		texData = NULL;
	}

	resX = resolutionX;
	resY = resolutionY;

	texWidth = nextPo2(resX);
	texHeight = nextPo2(resY);
	texData = (unsigned char*)malloc(texWidth * texHeight * 3 * sizeof(unsigned char));

	u0 = 0;
	v0 = 0;

	u1 = (float)resX / texWidth;
	v1 = (float)resY / texHeight;

	memset(texData, 0, texWidth * texHeight * 3 * sizeof(unsigned char));

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return 0;
}

void canvasClose()
{
	if (texData)
	{
		free(texData);
		texData = NULL;
	}

	if (textureID == ~0x00)
	{
		glDeleteTextures(1, &textureID);
		textureID = ~0x00;
	}

	if (window)
	{
		glfwDestroyWindow(window);
		window = NULL;

		glfwTerminate();
	}
}

void repaint()
{
	if (!window)
		return;

	if (dirty)
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texWidth, texHeight, GL_RGB, GL_UNSIGNED_BYTE, texData);
		dirty = false;
	}

	glViewport(0, 0, windowWidth, windowHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(u0, v0);
		glVertex2f(-1, -1);

		glTexCoord2f(u1, v0);
		glVertex2f(1, -1);

		glTexCoord2f(u1, v1);
		glVertex2f(1, 1);

		glTexCoord2f(u0, v1);
		glVertex2f(-1, 1);
	}
	glEnd();

	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);

}

int canvasUpdate()
{
	if (!window)
		return -1;

	if (quit || glfwWindowShouldClose(window))
		return -1;

	glfwPollEvents();

	return 0;
}

void canvasSetPixel(int x, int y, float value)
{
	if (!window)
		return;

	if (textureID == ~0x00)
		return;

	x = max(0, min(x, resX - 1));
	y = max(0, min(y, resY - 1));

	unsigned char c = (unsigned char)(max(0, min(value * 255, 255)));
	int idx = x * 3 + (y * (texWidth * 3));

	texData[idx + 0] = 0;
	texData[idx + 1] = c;
	texData[idx + 2] = 0;

	dirty = true;
}

void canvasSetPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{
	if (!window)
		return;

	if (textureID == ~0x00)
		return;

	x = max(0, min(x, resX - 1));
	y = max(0, min(y, resY - 1));

	int idx = x * 3 + (y * (texWidth * 3));

	texData[idx + 0] = red;
	texData[idx + 1] = green;
	texData[idx + 2] = blue;

	dirty = true;
}
