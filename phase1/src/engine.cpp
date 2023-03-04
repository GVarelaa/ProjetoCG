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

vector<Point*> points_global;

vector<Point*> read_model(char* path){
    vector<Point*> points;
    ifstream file(path);

    if (file.is_open()){
        string line;

        while (getline(file, line)){
            stringstream ss(line);
            string x, y, z;
            ss >> x >> y >> z;
            Point* p = new Point(stof(x), stof(y), stof(z));
            points.push_back(p);
        }

        file.close();
    }
    else{
        cout << "File not found!" << endl;
    }

    return points;
}


void draw_model(vector<Point*> points){
    glBegin(GL_TRIANGLES);

    for (int i=0; i < points.size(); i++){
        glVertex3f(points[i]->getX(), points[i]->getY(), points[i]->getZ());
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
	gluLookAt(-5.0,5.0,-5.0, 
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
    draw_model(points_global);

	//  End of frame
	glutSwapBuffers();
}


int main(int argc, char **argv) {
	/*XMLDocument xml_doc;
	XMLError result = xml_doc.LoadFile(argv[1]);

	XMLNode *root = xml_doc.FirstChild();
	if(root){
		XMLElement *camera = root->FirstChildElement("camera");
		if(camera){
			XMLElement *position = camera->FirstChildElement();
			printf("aqui\n");
			printf("%s\n", position->Attribute("x"));	
	
		}
	}
	*/


	Point p = Point(0.0f, 0.0f, 0.0f);
	Projection pr = Projection(1.0f, 1.0f, 1.0f);
	Camera c = Camera(p, p , p , pr);

	printf("%f\n", c.get_projection().get_fov());
    //points_global = read_model(argv[1]);

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
