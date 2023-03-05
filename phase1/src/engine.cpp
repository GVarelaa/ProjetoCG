#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "../include/point.h"
#include "../include/world.h"
#include "../include/tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;


World world;


void drawModel(Model model){
	printf("aqui\n");
	vector<Point> vertices = model.getVertices();
	vector<Triangle> triangles = model.getTriangles();

	glBegin(GL_TRIANGLES);
		for(int i = 0; i < triangles.size(); i++){
			Point p1 = vertices[triangles[i].getIndP1()];
			Point p2 = vertices[triangles[i].getIndP2()];
			Point p3 = vertices[triangles[i].getIndP3()];

			glVertex3f(p1.getX(), p1.getY(), p1.getZ());
			glVertex3f(p2.getX(), p2.getY(), p2.getZ());
			glVertex3f(p3.getX(), p3.getY(), p3.getZ());
		}
	glEnd();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
			0.0,0.0,0.0,
			0.0f,1.0f,0.0f);
	
	glPolygonMode(GL_FRONT, GL_LINE);

	// put axis drawing in here
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		
		// Y axis in green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		
		// Z axis in blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);

        glColor3f(255.0f, 255.0f, 255.0f);
		
	glEnd();

	// put the geometric transformations here


	// put drawing instructions here
	Group group = world.get_group();
	vector<Model> models = group.models;
	for(int i = 0; i < models.size(); i++){
		drawModel(models[i]);
	}

	//  End of frame
	glutSwapBuffers();
}


int main(int argc, char **argv) {
	world = World(argv[1]);

	

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	//glutKeyboardFunc(keyboardFunc);
	//glutSpecialFunc(keyboardFunc2);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
