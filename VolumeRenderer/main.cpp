#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "glut.h"
#include <string>

#include "BinaryFileReader.h"
#include "TextureManager.h"
#include "Shader.h"
#include "UserInput.h"
#include "Mat4x4.h"
#include "Vector4.h"
#include "ShaderBucky.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

Shader *shader;
UserInput *g_input;
Mat4x4 * viewPosMatrix;;

float viewPos[] = {0.f, 0.f, 50.0f};
float viewPosDist = -1.0f;
int width, height;

#define RATIO 10

static const GLfloat g_vertices[] =
{
	-1.0f * RATIO, -1.0f * RATIO,  1.0f * RATIO,
	1.0f * RATIO, -1.0f * RATIO,  1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,

	-1.0f * RATIO, -1.0f * RATIO,  1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,
	-1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,

	-1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	-1.0f * RATIO,  1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO, -1.0f * RATIO,

	-1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,

	-1.0f * RATIO,  1.0f * RATIO, -1.0f * RATIO,
	-1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,

	-1.0f * RATIO,  1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO, -1.0f * RATIO,

	-1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO, -1.0f * RATIO,  1.0f * RATIO,

	-1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO, -1.0f * RATIO,  1.0f * RATIO,
	-1.0f * RATIO, -1.0f * RATIO,  1.0f * RATIO,

	1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,

	1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,
	1.0f * RATIO, -1.0f * RATIO,  1.0f * RATIO,

	-1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	-1.0f * RATIO, -1.0f * RATIO,  1.0f * RATIO,
	-1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,

	-1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	-1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,
	-1.0f * RATIO,  1.0f * RATIO, -1.0f * RATIO
};

const GLfloat g_UV[] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	1.0f, 0.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	1.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,

	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	1.0f, 0.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
};

static const GLfloat g_vertices2[] = {
	-1.0f * RATIO, -1.0f * RATIO, -1.0f * RATIO,
	-1.0f * RATIO,  1.0f * RATIO,  1.0f * RATIO,
	-1.0f * RATIO,  1.0f * RATIO, -1.0f * RATIO
};

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{
	//
	// Returns 1 if an OpenGL error occurred, 0 otherwise.
	//
	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
		retCode = 1;
		glErr = glGetError();
	}
	return retCode;
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	width = w; height = h;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	glm::mat4 perMat = glm::perspective(45.0f, (float)w / (float)h, 0.01f, 100.f);
	if(dynamic_cast<ShaderBucky *>(shader) != NULL) {
		ShaderBucky * buckyShader = (ShaderBucky *) shader;
		buckyShader->UpdateUniformMat4("projection", glm::value_ptr(perMat));
	}

	glMatrixMode(GL_MODELVIEW);

}

GLuint uvBuffer = -1;
GLuint vbo = -1;

void renderScene(void) {
	printOpenGLError();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*Vector4 transformedViewPosv;
	if(viewPosMatrix != NULL && g_input != NULL) {
		g_input->UpdateGlobalRotation();
		viewPosMatrix ->RotateX( g_input->GetAngleX() );
		viewPosMatrix ->RotateY( g_input->GetAngleY() );
		viewPosMatrix ->RotateZ( g_input->GetAngleZ() );
		transformedViewPosv = (*viewPosMatrix) * viewPosv;
		viewPosMatrix ->SetIdentity();
		transformedViewPosv = transformedViewPosv * (g_input ->GetViewDistance() / viewPosDist);
	}*/
	// Check angleX,y,z.
	// Also check why transformedViewPosv doesn't change.
	//gluLookAt(transformedViewPosv.p[0], transformedViewPosv.p[1], transformedViewPosv.p[2], 0.0,0.0,0.0, 0.0f,1.0f,0.0f);
	
	if(dynamic_cast<ShaderBucky *>(shader) != NULL) {

		ShaderBucky * buckyShader = (ShaderBucky *) shader;
		glm::mat4 modelViewMat = glm::lookAt(glm::vec3(viewPos[0] + 5.0, viewPos[1], viewPos[2]), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

		g_input->UpdateGlobalRotation();
		modelViewMat = glm::rotate(modelViewMat, (float) g_input->GetAngleX(), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelViewMat = glm::rotate(modelViewMat, (float) -g_input->GetAngleY(), glm::vec3(0.0f, 1.0f, 0.0f));
		buckyShader->UpdateUniformMat4("modelview", glm::value_ptr(modelViewMat));

		glm::mat4 perMat = glm::perspective(45.0f, (float)width / (float)height, 0.01f, 100.f);
		if(dynamic_cast<ShaderBucky *>(shader) != NULL) {
			ShaderBucky * buckyShader = (ShaderBucky *) shader;
			buckyShader->UpdateUniformMat4("projection", glm::value_ptr(perMat));
		}
	}
	

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*float ratio = 10.0f;
	glBegin(GL_QUADS);
	// Front Face
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);glVertex3f(-1.0f * ratio, -1.0f * ratio,  1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);glVertex3f( 1.0f * ratio, -1.0f * ratio,  1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);glVertex3f( 1.0f * ratio,  1.0f * ratio,  1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);glVertex3f(-1.0f * ratio,  1.0f * ratio,  1.0f * ratio);
		// Back Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);glVertex3f(-1.0f * ratio, -1.0f * ratio, -1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);glVertex3f(-1.0f * ratio,  1.0f * ratio, -1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);glVertex3f( 1.0f * ratio,  1.0f * ratio, -1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);glVertex3f( 1.0f * ratio, -1.0f * ratio, -1.0f * ratio);
		// Top Face
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);glVertex3f(-1.0f * ratio,  1.0f * ratio, -1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);glVertex3f(-1.0f * ratio,  1.0f * ratio,  1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);glVertex3f( 1.0f * ratio,  1.0f * ratio,  1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);glVertex3f( 1.0f * ratio,  1.0f * ratio, -1.0f * ratio);
		// Bottom Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);glVertex3f(-1.0f * ratio, -1.0f * ratio, -1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);glVertex3f( 1.0f * ratio, -1.0f * ratio, -1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);glVertex3f( 1.0f * ratio, -1.0f * ratio,  1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);glVertex3f(-1.0f * ratio, -1.0f * ratio,  1.0f * ratio);
		// Right face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);glVertex3f( 1.0f * ratio, -1.0f * ratio, -1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);glVertex3f( 1.0f * ratio,  1.0f * ratio, -1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);glVertex3f( 1.0f * ratio,  1.0f * ratio,  1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);glVertex3f( 1.0f * ratio, -1.0f * ratio,  1.0f * ratio);
		// Left Face
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);glVertex3f(-1.0f * ratio, -1.0f * ratio, -1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);glVertex3f(-1.0f * ratio, -1.0f * ratio,  1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);glVertex3f(-1.0f * ratio,  1.0f * ratio,  1.0f * ratio);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);glVertex3f(-1.0f * ratio,  1.0f * ratio, -1.0f * ratio);
	glEnd();*/

	glutSwapBuffers();
	glutPostRedisplay();
	shader ->ShaderFileChangeWatcher();
}


void processNormalKeys(unsigned char key, int x, int y) {
	if(g_input) {
		g_input ->Keyboard(key, x, y);
	}
}

void mouseDown(int button, int state, int x, int y) {
	if(g_input) {
		g_input ->Mouse(button, state, x, y);
	}
}

void mouseMotion(int x, int y) {
	if(g_input) {
		g_input->MouseMotion(x, y);
	}
}



void InitGL()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Volume Raycasting 3D");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(mouseDown);
	glutMotionFunc(mouseMotion);
	glewInit();

	glDisable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_3D);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0., 0., 0., 1.);

	// Create Matrix for view point manipulation.
	if(viewPosMatrix == NULL) {
		viewPosMatrix = new Mat4x4();
	}
	viewPosDist = viewPos[0] * viewPos[0] + viewPos[1] * viewPos[1] + viewPos[2] * viewPos[2];
	viewPosDist = sqrt(viewPosDist);


}

void EndGL() 
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	InitGL();
	if (glewIsSupported("GL_VERSION_3_3"))
		printf("Ready for OpenGL 3.3\n");
	else {
		printf("OpenGL 3.3 not supported\n");
		exit(1);
	}

	g_input = new UserInput(viewPos);
	shader = new ShaderBucky();
	//shader ->setShaders("./GLSL/textureSimple.vert", "./GLSL/textureSimple.frag");
	shader ->setShaders("./GLSL/test.vert", "./GLSL/test.frag");

	GLuint UVposition = 1;
	GLuint vertexPosition = 0;

	glEnableVertexAttribArray(UVposition);
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_UV), g_UV, GL_STREAM_DRAW);
	glVertexAttribPointer(UVposition, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	glEnableVertexAttribArray(vertexPosition);
	glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	

	glutMainLoop();

	EndGL();

	return 0;
}

/*

glBegin(GL_QUADS);
// Front Face
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,.0f * ratio, .0f* ratio,  1.0f* ratio);		glVertex3f(-1.0f, -1.0f,  1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f* ratio,  1.0f* ratio);		glVertex3f( 1.0f, -1.0f,  1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio,  1.0f* ratio);	glVertex3f( 1.0f,  1.0f,  1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f* ratio,  1.0f* ratio,  1.0f* ratio);		glVertex3f(-1.0f,  1.0f,  1.0f);
// Back Face
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f* ratio, 0.0f* ratio, 0.0f* ratio);		glVertex3f(-1.0f, -1.0f, -1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f* ratio,  1.0f* ratio, 0.0f* ratio);		glVertex3f(-1.0f,  1.0f, -1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio, 0.0f* ratio);		glVertex3f( 1.0f,  1.0f, -1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f* ratio, 0.0f* ratio);		glVertex3f( 1.0f, -1.0f, -1.0f);
// Top Face
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f* ratio,  1.0f* ratio, 0.0f);				glVertex3f(-1.0f,  1.0f, -1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f* ratio,  1.0f* ratio);			glVertex3f(-1.0f,  1.0f,  1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio,  1.0f* ratio);	glVertex3f( 1.0f,  1.0f,  1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio, 0.0f);			glVertex3f( 1.0f,  1.0f, -1.0f);
// Bottom Face
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f, 0.0f);							glVertex3f(-1.0f, -1.0f, -1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f, 0.0f);					glVertex3f( 1.0f, -1.0f, -1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f,  1.0f* ratio);			glVertex3f( 1.0f, -1.0f,  1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f,  1.0f* ratio);					glVertex3f(-1.0f, -1.0f,  1.0f);
// Right face
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f, 0.0f);					glVertex3f( 1.0f, -1.0f, -1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio, 0.0f);			glVertex3f( 1.0f,  1.0f, -1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio,  1.0f* ratio);	glVertex3f( 1.0f,  1.0f,  1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f,  1.0f* ratio);			glVertex3f( 1.0f, -1.0f,  1.0f);
// Left Face
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f, 0.0f);							glVertex3f(-1.0f, -1.0f, -1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f,  1.0f* ratio);					glVertex3f(-1.0f, -1.0f,  1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f* ratio,  1.0f* ratio);			glVertex3f(-1.0f,  1.0f,  1.0f);
glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f* ratio, 0.0f);					glVertex3f(-1.0f,  1.0f, -1.0f);
glEnd();

*/