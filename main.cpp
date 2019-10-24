#include "stdafx.h"

#define PI 3.14159265

struct Coord3d {
	Coord3d() {
		x = 0;
		y = 0;
		z = 0;
	}
	GLdouble x;
	GLdouble y;
	GLdouble z;
};

// Coord3d color;
std::vector<std::array<double, 3>> v1, v2, v3, n; // Holds geometry data in numerical form

void load_suzanne() {
	std::string filename = "Suzanne.json";

	nlohmann::json geometry_json; // Holds geometry data in json form

	int triangle_count;

	int counter = 0;

	std::ifstream file(filename.data());

	geometry_json = nlohmann::json::parse(file);

	triangle_count = geometry_json["geometry"]["v1"].size();
	v1.resize(triangle_count);
	v2.resize(triangle_count);
	v3.resize(triangle_count);
	n.resize(triangle_count);

	counter = 0;
	for (nlohmann::json::iterator i = geometry_json["geometry"]["v1"].begin(); i != geometry_json["geometry"]["v1"].end(); i++) {
		for (int j = 0; j < 3; j++) {
			v1[counter][j] = (*i)[j];
		}
		counter++;
	}
	counter = 0;
	for (nlohmann::json::iterator i = geometry_json["geometry"]["v2"].begin(); i != geometry_json["geometry"]["v2"].end(); i++) {
		for (int j = 0; j < 3; j++) {
			v2[counter][j] = (*i)[j];
		}
		counter++;
	}
	counter = 0;
	for (nlohmann::json::iterator i = geometry_json["geometry"]["v3"].begin(); i != geometry_json["geometry"]["v3"].end(); i++) {
		for (int j = 0; j < 3; j++) {
			v3[counter][j] = (*i)[j];
		}
		counter++;
	}
	counter = 0;
	for (nlohmann::json::iterator i = geometry_json["normals"].begin(); i != geometry_json["normals"].end(); i++) {
		for (int j = 0; j < 3; j++) {
			n[counter][j] = (*i)[j];
		}
		counter++;
	}

	// If you ever add a color field to the json file one can uncomment these lines 
	//color.x = geometry_json["color"][0];
	//color.y = geometry_json["color"][1];
	//color.z = geometry_json["color"][2];
}

void draw_suzanne() {
	// glColor3f(color.x, color.y, color.z);
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < v1.size(); i++) {
		glNormal3d(n[i][0], n[i][1], n[i][2]);
		glVertex3d(v1[i][0], v1[i][1], v1[i][2]);
		glVertex3d(v2[i][0], v2[i][1], v2[i][2]);
		glVertex3d(v3[i][0], v3[i][1], v3[i][2]);
	}
	glEnd();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  // reset the current matrix to identity matrix

	float eye[] = { 0, 0, 8 };
	float center[] = { 0, 0, 0 };
	// create a viewing matrix defined by an eye point and a reference point
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);  // define the position of the light
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);  // specify the ambient RGBA intensity of the light
	glEnable(GL_LIGHT0);

	glViewport(0, 0, 480, 480);  // define a viewport and display in this viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1, 1.0, 20.0);  // specify a viewing frustum
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -5.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);  // define a viewing matrix

	draw_suzanne();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);  // initialize the library
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);  // define size of the window
	glutInitWindowPosition(0, 0);  // define position of the window
	glutCreateWindow("Hello Suzanne");
	load_suzanne();
	glutDisplayFunc(draw);  // display callback
	glutMainLoop();  // enter event processing loop

	return 0;
}