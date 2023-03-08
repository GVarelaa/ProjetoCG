#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
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
float alpha_camera = 0, beta_camera = 0, radius_camera = 10;
bool explore_mode = false;


void drawModel(Model model){
	vector<Point> vertices = model.vertices;
	vector<Triangle> triangles = model.triangles;

	glBegin(GL_TRIANGLES);
		for(int i = 0; i < triangles.size(); i++){
			Point p1 = vertices[triangles[i].indP1];
			Point p2 = vertices[triangles[i].indP2];
			Point p3 = vertices[triangles[i].indP3];

			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
			glVertex3f(p3.x, p3.y, p3.z);
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
	Projection projection = world.camera.projection;

	gluPerspective(projection.fov ,ratio, projection.near , projection.far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	Camera camera = world.camera;
	glLoadIdentity();

	// Modo explorador desativado
	if(explore_mode == false){
		gluLookAt(camera.position.x,camera.position.y,camera.position.z , 
	        camera.lookAt.x,camera.lookAt.y,camera.lookAt.z,
	        camera.up.x,camera.up.y,camera.up.z);
	}
	else{
		float px = radius_camera * cos (beta_camera) * sin (alpha_camera);
		float py = radius_camera * sin (beta_camera);
		float pz = radius_camera * cos (beta_camera) * cos (alpha_camera);

		gluLookAt(px, py, pz, 
	        camera.lookAt.x,camera.lookAt.y,camera.lookAt.z,
	        camera.up.x,camera.up.y,camera.up.z);
	}

	

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
	Group group = world.group;
	vector<Model> models = group.models;
	for(int i = 0; i < models.size(); i++){
		models[i].draw();
	}

	//  End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int x, int y){
	if(explore_mode == true){
		if(c == 'c'){
			explore_mode = false;
		}
		else if (c == '+'){
			radius_camera += 1;
		}
		else if (c == '-'){
			radius_camera -= 1;
		}
	}
	else{
		if(c == 'c'){
			explore_mode = true;
		}
	}

	glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y){	
	if (explore_mode == true){
		if (key == GLUT_KEY_LEFT){
			alpha_camera -= M_PI / 20;
		}
		else if (key == GLUT_KEY_RIGHT){
			alpha_camera += M_PI / 20;
		}
		else if (key == GLUT_KEY_UP){
			beta_camera += M_PI / 20;

			if (beta_camera > M_PI / 2) beta_camera = M_PI / 2;
		}
		else if (key == GLUT_KEY_DOWN){
			beta_camera -= M_PI / 20;

			if (beta_camera < -M_PI / 2) beta_camera = -M_PI / 2;
		}

		glutPostRedisplay();
	}
}



int main(int argc, char **argv) {
// init GLUT and the window
	world = World(argv[1]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(world.window.width, world.window.height); // trocar
    glutCreateWindow("CG@DI-UM");
        
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

// init GLEW
#ifndef __APPLE__
    glewInit();
#endif

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);

	world.loadGroup();
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
