#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <string.h>
#include <random>
#include <array>
#include <vector>
#include <time.h>
#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <set>
#include <locale>
#include <Windows.h>
using namespace std;
#define DEG2RAD(a) (a * 0.0174532925)

double newPlayerX = 7.2;
double newPlayerY = 0.1;
double newPlayerZ = 7.5;
double playerX = 0;
double playerY = 0;
double playerZ = 0;
double playerRot = 0;
double tempX = 0;
double tempZ = 0;
float r = 0;
bool front1 = true;
bool back1 = false;
bool left1 = false;
bool right1 = false;
int view = 0;
int WIDTH = 1280;
int HEIGHT = 720;
int playerAngle = 0;
double playerRadius = 0.35;
bool firstPerson = false;
bool thirdPerson = true;
int coinAngle = 0;
bool coin1 = false;
bool coin2 = false;
bool coin3 = false;
bool coin4 = false;
bool coin5 = false;
bool coin6 = false;
bool coin7 = false;
bool coin8 = false;
bool coin9 = false;
bool coin10 = false;
bool coin11 = false;
bool collision = false;
bool coinCollision = false;
bool gameWon = false;
bool gameOver = false;
bool start = true;
int score = 0;
float lightIntensity2 = -1;
int timer = 200;
int level = 1;
bool collision_lvl1 = false;
bool coin1_lvl1 = false;
bool coin2_lvl1 = false;
bool coin3_lvl1 = false;
bool coin4_lvl1 = false;
bool coinCollision_lvl1 = false;
bool gameWon_lvl1 = false;
bool gameOver_lvl1 = false;
bool start_lvl1 = true;
int coinAngle_lvl1 = 0;
int playerAngle_lvl1 = 0;
int view_lvl1 = 0;
double newPlayerX_lvl1 = 7.2;
double newPlayerY_lvl1 = 0.1;
double newPlayerZ_lvl1 = 7.5;
double playerX_lvl1 = 0;
double playerY_lvl1 = 0;
double playerZ_lvl1 = 0;
bool front1_lvl1 = true;
bool back1_lvl1 = false;
bool left1_lvl1 = false;
bool right1_lvl1 = false;





GLuint tex;
char title[] = "Treasure Of Pharaohs";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;


class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};


class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}


	Vector operator+(Vector& v) {
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	Vector operator-(Vector& v) {
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	Vector operator*(float n) {
		return Vector(x * n, y * n, z * n);
	}

	Vector operator/(float n) {
		return Vector(x / n, y / n, z / n);
	}


	Vector cross(Vector v) {
		return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	Vector unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}
};



Vector Eye(newPlayerX, 0.9626, newPlayerZ + 2);
Vector At(newPlayerX, 0.843739, newPlayerZ);
Vector Up(0, 1, 0);

int cameraZoom = 0;


void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(60, 640 / 480, 0.001, 100);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//camera.look();
}










// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_container;
Model_3DS model_player;
Model_3DS model_coin;
Model_3DS model_goal;
Model_3DS model_wall;
Model_3DS model_fence;
Model_3DS model_statue;
// Textures
GLTexture tex_ground;



void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}


void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


}




void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}








void RenderGround()
{
	glDisable(GL_LIGHTING); // Disable lighting

	glColor3f(0.6, 0.6, 0.6); // Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D); // Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]); // Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0); // Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-10, 0, -10);
	glTexCoord2f(5, 0);
	glVertex3f(10, 0, -10);
	glTexCoord2f(5, 5);
	glVertex3f(10, 0, 10);
	glTexCoord2f(0, 5);
	glVertex3f(-10, 0, 10);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1); // Set material back to white instead of grey used for the ground texture.
}

void RenderMaze() {

	//phase 1
	glPushMatrix();
	glTranslatef(7.2, 0.04, 6);
	glScalef(0.015, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.8, 0.04, 0);
	glScalef(0.015, 0.015, 0.058);
	glRotatef(90, 0, 1, 0);
	model_container.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.04, 9.9);
	glScalef(0.057, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.5, 0.04, 6);
	glScalef(0.025, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9.8, 0.04, 0);
	glScalef(0.015, 0.015, 0.058);
	glRotatef(90, 0, 1, 0);
	model_container.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 0.04, 6);
	glScalef(0.008, 0.015, 0.01);
	glRotatef(0, 0, 1, 0);
	model_container.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.04, -9.9);
	glScalef(0.057, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 0.04, -2);
	glScalef(0.015, 0.015, 0.045);
	glRotatef(90, 0, 1, 0);
	model_container.Draw();
	glPopMatrix();

	//phase 2 - wrong
	glPushMatrix();
	glTranslatef(4.2, 0.04, 2.1);
	glScalef(0.015, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();

	//phase 3 - wrong
	glPushMatrix();
	glTranslatef(7.2, 0.04, -1.8);
	glScalef(0.015, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();

	//phase 4 - wrong
	glPushMatrix();
	glTranslatef(4.2, 0.04, -5.7);
	glScalef(0.015, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();

	//phase 2 - right
	glPushMatrix();
	glTranslatef(-1.2, 0.04, 2.1);
	glScalef(0.015, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();

	//phase 3 - right
	glPushMatrix();
	glTranslatef(-7.2, 0.04, -1.8);
	glScalef(0.015, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();

	//phase 4 - right
	glPushMatrix();
	glTranslatef(-1.2, 0.04, -5.7);
	glScalef(0.015, 0.015, 0.015);
	model_container.Draw();
	glPopMatrix();




}

void collisions() {

	if (level == 2) {
		if (newPlayerX < 9.7 + 0.1 && newPlayerX > 9.7 - 0.1) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}

		if (newPlayerX < -9.7 + 0.1 && newPlayerX > -9.7 - 0.1) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}

		if (newPlayerZ < 9.7 + 0.1 && newPlayerZ > 9.7 - 0.1) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}

		if (newPlayerZ < -9.7 + 0.1 && newPlayerZ > -9.7 - 0.1) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

	}

	else {


		if (newPlayerX_lvl1 <= 9.7 + 0.1 && newPlayerX_lvl1 >= 9.7 - 0.1) {
			newPlayerX_lvl1 -= 0.1;
			playerX_lvl1 -= 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerX_lvl1 <= -9.7 + 0.1 && newPlayerX_lvl1 >= -9.7 - 0.1) {
			newPlayerX_lvl1 += 0.1;
			playerX_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= 9.7 + 0.1 && newPlayerZ_lvl1 >= 9.7 - 0.1) {
			newPlayerZ_lvl1 -= 0.1;
			playerZ_lvl1 -= 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= -9.7 + 0.1 && newPlayerZ_lvl1 >= -9.7 - 0.1) {
			newPlayerZ_lvl1 += 0.1;
			playerZ_lvl1 += 0.1;
			collision_lvl1 = true;
		}



	}


}


void RenderPlayer() {

	glPushMatrix();
	glTranslated(playerX, 0, playerZ);
	glTranslatef(7.2, 0.05, 7.5);
	glScalef(0.015, 0.015, 0.015);
	glRotatef(180, 0, 1, 0);
	glRotated(playerAngle, 0, 1, 0);
	model_player.Draw();
	glPopMatrix();




}

void RenderPlayer_lvl1() {

	glPushMatrix();
	glTranslated(playerX_lvl1, 0, playerZ_lvl1);
	glTranslatef(7.2, 0.05, 7.5);
	glScalef(0.015, 0.015, 0.015);
	glRotatef(180, 0, 1, 0);
	glRotated(playerAngle_lvl1, 0, 1, 0);
	model_player.Draw();
	glPopMatrix();




}


void RenderSky() {

	glPushMatrix();
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(-30, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 50, 100, 100);
	gluDeleteQuadric(qobj);
	glPopMatrix();

}

void RenderCoins() {

	if (!coin1) {
		glPushMatrix();
		glTranslatef(4.8, 0.1, 4.8);
		glScalef(0.020, 0.020, 0.020);
		glRotatef(180, 0, 1, 0);
		glRotated(coinAngle, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}
	if (!coin2) {
	glPushMatrix();
	glTranslatef(7.1, 0.1, 1);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}
	if (!coin3) {
	glPushMatrix();
	glTranslatef(3.2, 0.1, -1.5);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}
	if (!coin4) {
	glPushMatrix();
	glTranslatef(7.7, 0.1, -7.4);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}
	if (!coin5) {
	glPushMatrix();
	glTranslatef(3, 0.1, -8.2);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}
	if (!coin6) {
	glPushMatrix();
	glTranslatef(2.7, 0.1, 8.5);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}
	if (!coin7) {
	glPushMatrix();
	glTranslatef(0.5, 0.1, 3.2);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}
	if (!coin8) {
	glPushMatrix();
	glTranslatef(-5.3, 0.1, 3.2);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}
	if (!coin9) {
	glPushMatrix();
	glTranslatef(-5.8, 0.1, -0.3);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}
	if (!coin10) {
	glPushMatrix();
	glTranslatef(-2.1, 0.1, 0.1);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}
	if (!coin11) {
	glPushMatrix();
	glTranslatef(-5.1, 0.1, -7.9);
	glScalef(0.020, 0.020, 0.020);
	glRotatef(180, 0, 1, 0);
	glRotated(coinAngle, 0, 1, 0);
	model_coin.Draw();
	glPopMatrix();
	}

}

void RenderCoins_lvl1() {

	if (!coin1_lvl1) {
		glPushMatrix();
		glTranslatef(8, 0.1, 1.4);
		glScalef(0.020, 0.020, 0.020);
		glRotatef(180, 0, 1, 0);
		glRotated(coinAngle_lvl1, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}
	if (!coin2_lvl1) {
		glPushMatrix();
		glTranslatef(3, 0.1, 1.4);
		glScalef(0.020, 0.020, 0.020);
		glRotatef(180, 0, 1, 0);
		glRotated(coinAngle_lvl1, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}
	if (!coin3_lvl1) {
		glPushMatrix();
		glTranslatef(-2, 0.1, 1.4);
		glScalef(0.020, 0.020, 0.020);
		glRotatef(180, 0, 1, 0);
		glRotated(coinAngle_lvl1, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}
	if (!coin4_lvl1) {
		glPushMatrix();
		glTranslatef(-7, 0.1, 1.4);
		glScalef(0.020, 0.020, 0.020);
		glRotatef(180, 0, 1, 0);
		glRotated(coinAngle_lvl1, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}
	

}

void RenderGoal() {


	glPushMatrix();
	
	glTranslatef(0.6, 0.4, -6.5);
	glScalef(0.01, 0.01, 0.01);
	glRotatef(270, 0, 1, 0);
	model_goal.Draw();
	glPopMatrix();


}

void RenderGoal_lvl1() {


	glPushMatrix();

	glTranslatef(-2.4, 0.4, -7.8);
	glScalef(0.01, 0.01, 0.01);
	glRotatef(0, 0, 1, 0);
	model_statue.Draw();
	glPopMatrix();


}

void RenderMaze_lvl1() {


	//phase 1
	glPushMatrix();
	glTranslatef(9.9, 0.04, 9.9);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 7.2);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 4.5);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 1.7);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -1);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -3.7);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -6.4);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -9.1);
	glScalef(0.00005, 0.00004, 0.00001);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19.8, 0, 0);
	glPushMatrix();
	glTranslatef(9.9, 0.04, 9.9);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 7.2);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 4.5);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 1.7);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -1);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -3.7);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -6.4);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -9.1);
	glScalef(0.00005, 0.00004, 0.00001);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glTranslatef(9.9, 0.04, 9.9);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 7.2);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 4.5);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 1.7);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -1);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -3.7);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -6.4);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -9.1);
	glScalef(0.00005, 0.00004, 0.00001);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glPushMatrix();
	glTranslatef(9.9, 0.04, 9.9);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 7.2);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 4.5);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, 1.7);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -1);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -3.7);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -6.4);
	glScalef(0.00005, 0.00004, 0.00004);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.9, 0.04, -9.1);
	glScalef(0.00005, 0.00004, 0.00001);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(5, 0.04, -1);
	glScalef(0.015, 0.015, 0.06);
	glRotatef(0, 0, 1, 0);
	model_fence.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.04, -1);
	glScalef(0.015, 0.015, 0.06);
	glRotatef(0, 0, 1, 0);
	model_fence.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 0.04, -1);
	glScalef(0.015, 0.015, 0.06);
	glRotatef(0, 0, 1, 0);
	model_fence.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.5, 0.04, -7);
	glScalef(0.008, 0.015, 0.015);
	glRotatef(-90, 0, 1, 0);
	model_fence.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 0.04, -7);
	glScalef(0.008, 0.015, 0.015);
	glRotatef(-90, 0, 1, 0);
	model_fence.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, 0.04, -7);
	glScalef(0.008, 0.015, 0.015);
	glRotatef(-90, 0, 1, 0);
	model_fence.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.5, 0.04, -7);
	glScalef(0.008, 0.015, 0.015);
	glRotatef(-90, 0, 1, 0);
	model_fence.Draw();
	glPopMatrix();
}

void displayText2D(char* text, int posX, int posY) {
	
	int len;
	len = (int)strlen(text);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3d(1, 0, 0);
	glRasterPos2i(posX, posY);

	void* font = GLUT_BITMAP_TIMES_ROMAN_24;
	for (int i = 0; i < len; i++) {
		char c = text[i];
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void myDisplay(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//cout << "playerX: ";
	//cout << newPlayerX_lvl1;
	//cout << " " << " ---- ";
	//cout << "playerY: ";
	//cout << newPlayerY_lvl1;
	//cout << " " << " ---- ";
	//cout << "playerZ: ";
	//cout << newPlayerZ_lvl1;
	//cout << endl;

	//cout << endl;
	//cout << endl;
	//cout << endl;
	//cout << endl;

	if (level == 2) {
		if (gameOver || gameWon) {
			lightIntensity2 = 1;
		}
		GLfloat lightIntensity[] = { lightIntensity2, lightIntensity2, lightIntensity2, 1.0f };
		GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

		if (start) {
			PlaySound(TEXT("sounds/laugh.wav"), NULL, SND_ASYNC | SND_FILENAME);
			start = false;

			//Vector Eye(newPlayerX, 0.9626, newPlayerZ + 2);
			//Vector At(newPlayerX, 0.843739, newPlayerZ);
			//Vector Up(0, 1, 0);
			Eye.x = newPlayerX;
			Eye.y = 0.9626;
			Eye.z = newPlayerZ + 2;
			At.x = newPlayerX;
			At.y = 0.843739;
			At.z = newPlayerZ;
			Up.x = 0;
			Up.y = 1;
			Up.z = 0;
			glLoadIdentity();
			gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
			firstPerson = false;
			thirdPerson = true;
		}

		if (gameWon) {

			PlaySound(TEXT("sounds/gamewon.wav"), NULL, SND_ASYNC | SND_FILENAME);
			GLfloat lightIntensity1[] = { 1.0, 1.0, 1.0, 0.1f };
			GLfloat lightPosition1[] = { 0.0, 5.0, 0.0, 0.0f };
			glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
			glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			displayText2D("You've won!", 600, 360);
			char* p5s[20];
			sprintf((char*)p5s, "score: %d", score);
			displayText2D((char*)p5s, 600, 330);
			glutSwapBuffers();
			return;
		}

		if (gameOver) {

			PlaySound(TEXT("sounds/gameover.wav"), NULL, SND_ASYNC | SND_FILENAME);
			GLfloat lightIntensity1[] = { 1.0, 1.0, 1.0, 0.1f };
			GLfloat lightPosition1[] = { 0.0, 5.0, 0.0, 0.0f };
			glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
			glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity1);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			displayText2D("Game Over", 600, 360);
			char* p5s[20];
			sprintf((char*)p5s, "score: %d", score);
			displayText2D((char*)p5s, 600, 330);
			glutSwapBuffers();

			return;
		}




		glPushMatrix();
		RenderGround();
		glPopMatrix();

		glPushMatrix();
		RenderSky();
		glPopMatrix();

		glPushMatrix();
		RenderMaze();
		glPopMatrix();

		glPushMatrix();
		RenderPlayer();
		glPopMatrix();

		glPushMatrix();
		RenderCoins();
		glPopMatrix();

		glPushMatrix();
		RenderGoal();
		glPopMatrix();

		displayText2D("You Need To Find Cleopatra & Anubis!", 450, 700);

		char* text[20];
		sprintf((char*)text, "Score: %d", score);
		displayText2D((char*)text, 10, 700);

		char* text1[20];
		sprintf((char*)text1, "Time: %d", timer);
		displayText2D((char*)text1, 1180, 700);

		if (collision) {


			PlaySound(TEXT("sounds/impact.wav"), NULL, SND_ASYNC | SND_FILENAME);

			collision = false;

		}


		if (coinCollision) {

			if (lightIntensity2 + 0.3 < 0.7)
				lightIntensity2 = lightIntensity2 + 0.3;
			PlaySound(TEXT("sounds/coin_sound.wav"), NULL, SND_ASYNC | SND_FILENAME);

			coinCollision = false;

		}

	}

	else {

		
	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);


	if (start_lvl1) {
		PlaySound(TEXT("sounds/treasure.wav"), NULL, SND_ASYNC | SND_FILENAME);
		start_lvl1 = false;
	}

	if (gameWon_lvl1) {

		level = 2;
	}

	if (gameOver_lvl1) {

		PlaySound(TEXT("sounds/gameover.wav"), NULL, SND_ASYNC | SND_FILENAME);
		GLfloat lightIntensity1[] = { 1.0, 1.0, 1.0, 0.1f };
		GLfloat lightPosition1[] = { 0.0, 5.0, 0.0, 0.0f };
		glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity1);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		displayText2D("Game Over", 600, 360);
		char* p5s[20];
		sprintf((char*)p5s, "score: %d", score);
		displayText2D((char*)p5s, 600, 330);
		glutSwapBuffers();

		return;
	}



	glPushMatrix();
	RenderGround();
	glPopMatrix();

	glPushMatrix();
	RenderSky();
	glPopMatrix();

	glPushMatrix();
	RenderMaze_lvl1();
	glPopMatrix();

	glPushMatrix();
	RenderPlayer_lvl1();
	glPopMatrix();

	glPushMatrix();
	RenderCoins_lvl1();
	glPopMatrix();

	glPushMatrix();
	RenderGoal_lvl1();
	glPopMatrix();

	char* text[20];
	sprintf((char*)text, "Score: %d", score);
	displayText2D((char*)text, 10, 700);

	char* text1[20];
	sprintf((char*)text1, "Time: %d", timer);
	displayText2D((char*)text1, 1180, 700);

	displayText2D("You Need To Find Cleopatra & Anubis!", 450, 700);

	if (collision_lvl1) {


		PlaySound(TEXT("sounds/impact.wav"), NULL, SND_ASYNC | SND_FILENAME);

		collision_lvl1 = false;

	}

	if (coinCollision_lvl1) {

		PlaySound(TEXT("sounds/coin_sound.wav"), NULL, SND_ASYNC | SND_FILENAME);

		coinCollision_lvl1 = false;

	}



}



	glutSwapBuffers();
}


void movePlayerLeft() {
	if (level == 2) {
		if (gameOver || gameWon)
			return;
		if (true) {
			playerAngle += 90;
			playerAngle = playerAngle % 360;
		}
		glutPostRedisplay();
	}

	else {

		if (gameOver_lvl1 || gameWon_lvl1)
			return;
		if (true) {
			playerAngle_lvl1 += 90;
			playerAngle_lvl1 = playerAngle_lvl1 % 360;
		}
		glutPostRedisplay();


	}
}

void movePlayerRight() {
	if (level == 2) {
		if (gameOver || gameWon)
			return;
		if (true) {
			if (playerAngle == 0)
				playerAngle = 270;
			else
				playerAngle -= 90;
		}
		glutPostRedisplay();
	}

	else {

		if (gameOver_lvl1 || gameWon_lvl1)
			return;
		if (true) {
			if (playerAngle_lvl1 == 0)
				playerAngle_lvl1 = 270;
			else
				playerAngle_lvl1 -= 90;
		}
		glutPostRedisplay();

	}

	
}

void movePlayerUp() {

	if (level == 2) {
		if (gameOver || gameWon)
			return;
		/*int z = (int)(playerZ)-1;
		int rz = (int)(playerZ + playerRadius) - 1;
		int lz = (int)(playerZ - playerRadius) - 1;
		int x = (int)(playerX - playerRadius - 0.1);
		x -= 1;*/
		if (playerAngle == 0) {
			/*playerZ -= 0.05;*/
			playerZ -= 0.1;
			/*playerX -= 0.1;*/
			newPlayerZ -= 0.1;


		}

		else if (playerAngle == 90) {
			/*playerZ -= 0.05;*/
			playerX -= 0.1;
			/*playerX -= 0.1;*/
			newPlayerX -= 0.1;


		}


		else if (playerAngle == 180) {
			/*playerZ -= 0.05;*/
			playerZ += 0.1;
			/*playerX -= 0.1;*/
			newPlayerZ += 0.1;


		}


		else if (playerAngle == 270) {
			/*playerZ -= 0.05;*/
			playerX += 0.1;
			/*playerX -= 0.1;*/
			newPlayerX += 0.1;


		}

		//phase 1
		//block1
		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 0 && newPlayerX >= 4.7) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 180 && newPlayerX >= 4.7) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 270 && newPlayerX >= 4.7) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}



		//block2
		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 0 && newPlayerX >= 0.1 && newPlayerX <= 2.9) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 180 && newPlayerX >= 0.1 && newPlayerX <= 2.9) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 90 && newPlayerX >= 0.1 && newPlayerX <= 2.9) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 270 && newPlayerX >= 0.1 && newPlayerX <= 2.9) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}

		//block3
		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 0 && newPlayerX <= -1.2) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 180 && newPlayerX <= -1.2) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 90 && newPlayerX <= -1.2) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}


		//phase 2
		//block1
		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 0 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 180 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 90 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}

		//block2
		if (newPlayerX <= 1.6 + 0.1 && newPlayerX >= 1.6 - 0.1 && playerAngle == 90 && newPlayerZ <= 5.8 + 0.1) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}

		if (newPlayerX <= 1.6 + 0.1 && newPlayerX >= 1.6 - 0.1 && playerAngle == 270 && newPlayerZ <= 5.8 + 0.1) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}

		//block3
		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 0 && newPlayerX >= 4.7) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 180 && newPlayerX >= 4.7) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 270 && newPlayerX >= 4.7) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}

		//block4
		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 0 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 180 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 90 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}


		//phase 3
		//block1
		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 0 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7 + 0.1) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 180 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7 + 0.1) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 270 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7 + 0.1) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}


		//block2
		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 0 && newPlayerX <= -4.5) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 180 && newPlayerX <= -4.5) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 90 && newPlayerX <= -4.5) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}

		//block3
		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 0 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 180 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 270 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}


		//coin1
		if (newPlayerX <= 4.8 + 0.2 && newPlayerX >= 4.8 - 0.2 && newPlayerZ <= 4.8 + 0.2 && newPlayerZ >= 4.8 - 0.2) {

			if (!coin1) {
				score = score + 5;
				coinCollision = true;
			}
			coin1 = true;


		}

		//coin2
		if (newPlayerX <= 7.1 + 0.2 && newPlayerX >= 7.1 - 0.2 && newPlayerZ <= 1 + 0.2 && newPlayerZ >= 1 - 0.2) {

			if (!coin2) {
				score = score + 5;
				coinCollision = true;
			}
			coin2 = true;

		}

		//coin3
		if (newPlayerX <= 3.2 + 0.2 && newPlayerX >= 3.2 - 0.2 && newPlayerZ <= -1.5 + 0.2 && newPlayerZ >= -1.5 - 0.2) {

			if (!coin3) {
				score = score + 5;
				coinCollision = true;
			}
			coin3 = true;

		}

		//coin4
		if (newPlayerX <= 7.7 + 0.2 && newPlayerX >= 7.7 - 0.2 && newPlayerZ <= -7.4 + 0.2 && newPlayerZ >= -7.4 - 0.2) {

			if (!coin4) {
				score = score + 5;
				coinCollision = true;
			}
			coin4 = true;

		}

		//coin5
		if (newPlayerX <= 3 + 0.2 && newPlayerX >= 3 - 0.2 && newPlayerZ <= -8.2 + 0.2 && newPlayerZ >= -8.2 - 0.2) {

			if (!coin5) {
				score = score + 5;
				coinCollision = true;
			}
			coin5 = true;

		}

		//coin6
		if (newPlayerX <= 2.7 + 0.2 && newPlayerX >= 2.7 - 0.2 && newPlayerZ <= 8.5 + 0.2 && newPlayerZ >= 8.5 - 0.2) {

			if (!coin6) {
				score = score + 5;
				coinCollision = true;
			}
			coin6 = true;

		}

		//coin7
		if (newPlayerX <= 0.5 + 0.2 && newPlayerX >= 0.5 - 0.2 && newPlayerZ <= 3.2 + 0.2 && newPlayerZ >= 3.2 - 0.2) {

			if (!coin7) {
				score = score + 5;
				coinCollision = true;
			}
			coin7 = true;

		}

		//coin8
		if (newPlayerX <= -5.3 + 0.2 && newPlayerX >= -5.3 - 0.2 && newPlayerZ <= 3.2 + 0.2 && newPlayerZ >= 3.2 - 0.2) {

			if (!coin8) {
				score = score + 5;
				coinCollision = true;
			}
			coin8 = true;

		}

		//coin9
		if (newPlayerX <= -5.8 + 0.2 && newPlayerX >= -5.8 - 0.2 && newPlayerZ <= -0.3 + 0.2 && newPlayerZ >= -0.3 - 0.2) {

			if (!coin9) {
				score = score + 5;
				coinCollision = true;
			}
			coin9 = true;

		}

		//coin10
		if (newPlayerX <= -2.1 + 0.2 && newPlayerX >= -2.1 - 0.2 && newPlayerZ <= 0.1 + 0.2 && newPlayerZ >= 0.1 - 0.2) {

			if (!coin10) {
				score = score + 5;
				coinCollision = true;
			}
			coin10 = true;

		}

		//coin11
		if (newPlayerX <= -5.1 + 0.2 && newPlayerX >= -5.1 - 0.2 && newPlayerZ <= -7.9 + 0.2 && newPlayerZ >= -7.9 - 0.2) {

			if (!coin11) {
				score = score + 5;
				coinCollision = true;
			}
			coin11 = true;

		}


		//GOAL
		if (newPlayerX <= 0.6 + 0.2 && newPlayerX >= 0.6 - 0.2 && newPlayerZ <= -6.5 + 0.2 && newPlayerZ >= -6.5 - 0.2) {

			if (!gameWon) {

				gameWon = true;
			}


		}

		glutPostRedisplay();
	}

	else {

	if (gameOver_lvl1 || gameWon_lvl1)
		return;

	if (playerAngle_lvl1 == 0) {
		/*playerZ -= 0.05;*/
		playerZ_lvl1 -= 0.1;
		/*playerX -= 0.1;*/
		newPlayerZ_lvl1 -= 0.1;


	}

	else if (playerAngle_lvl1 == 90) {
		/*playerZ -= 0.05;*/
		playerX_lvl1 -= 0.1;
		/*playerX -= 0.1;*/
		newPlayerX_lvl1 -= 0.1;


	}


	else if (playerAngle_lvl1 == 180) {
		/*playerZ -= 0.05;*/
		playerZ_lvl1 += 0.1;
		/*playerX -= 0.1;*/
		newPlayerZ_lvl1 += 0.1;


	}


	else if (playerAngle_lvl1 == 270) {
		/*playerZ -= 0.05;*/
		playerX_lvl1 += 0.1;
		/*playerX -= 0.1;*/
		newPlayerX_lvl1 += 0.1;


	}

	if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 90 && newPlayerX_lvl1 <= 5.2 + 0.1 && newPlayerX_lvl1 >= 5.2 - 0.1) {
		newPlayerX_lvl1 += 0.1;
		playerX_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 270 && newPlayerX_lvl1 <= 4.8 + 0.1 && newPlayerX_lvl1 >= 4.8 - 0.1) {
		newPlayerX_lvl1 -= 0.1;
		playerX_lvl1 -= 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= 5 + 0.2 && newPlayerX_lvl1 >= 5 - 0.2) {
		newPlayerZ_lvl1 += 0.1;
		playerZ_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 90 && newPlayerX_lvl1 <= 0.2 + 0.1 && newPlayerX_lvl1 >= 0.2 - 0.1) {
		newPlayerX_lvl1 += 0.1;
		playerX_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 270 && newPlayerX_lvl1 <= -0.2 + 0.1 && newPlayerX_lvl1 >= -0.2 - 0.1) {
		newPlayerX_lvl1 -= 0.1;
		playerX_lvl1 -= 0.1;
		collision_lvl1 = true;
	}


	if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= 0.1 + 0.1 && newPlayerX_lvl1 >= -0.1) {
		newPlayerZ_lvl1 += 0.1;
		playerZ_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 90 && newPlayerX_lvl1 <= -4.8 + 0.1 && newPlayerX_lvl1 >= -4.8 - 0.1) {
		newPlayerX_lvl1 += 0.1;
		playerX_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 270 && newPlayerX_lvl1 <= -5.2 + 0.1 && newPlayerX_lvl1 >= -5.2 - 0.1) {
		newPlayerX_lvl1 -= 0.1;
		playerX_lvl1 -= 0.1;
		collision_lvl1 = true;
	}


	if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= -4.8 && newPlayerX_lvl1 >= -5.1) {
		newPlayerZ_lvl1 += 0.1;
		playerZ_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= -6.9 + 0.1 && newPlayerZ_lvl1 >= -6.9 - 0.1 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= 8.6 && newPlayerX_lvl1 >= 6.4) {
		newPlayerZ_lvl1 += 0.1;
		playerZ_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= -7.2 + 0.1 && newPlayerZ_lvl1 >= -7.2 - 0.1 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= 8.6 && newPlayerX_lvl1 >= 6.4) {
		newPlayerZ_lvl1 -= 0.1;
		playerZ_lvl1 -= 0.1;
		collision_lvl1 = true;
	}


	if (newPlayerZ_lvl1 <= -6.9 + 0.1 && newPlayerZ_lvl1 >= -6.9 - 0.1 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <=3.6 && newPlayerX_lvl1 >= 1.5) {
		newPlayerZ_lvl1 += 0.1;
		playerZ_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= -7.2 + 0.1 && newPlayerZ_lvl1 >= -7.2 - 0.1 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= 3.6 && newPlayerX_lvl1 >= 1.5) {
		newPlayerZ_lvl1 -= 0.1;
		playerZ_lvl1 -= 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= -6.9 + 0.1 && newPlayerZ_lvl1 >= -6.9 - 0.1 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= -1.4 && newPlayerX_lvl1 >= -3.5) {
		newPlayerZ_lvl1 += 0.1;
		playerZ_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= -7.2 + 0.1 && newPlayerZ_lvl1 >= -7.2 - 0.1 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= -1.4 && newPlayerX_lvl1 >= -3.5) {
		newPlayerZ_lvl1 -= 0.1;
		playerZ_lvl1 -= 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= -6.9 + 0.1 && newPlayerZ_lvl1 >= -6.9 - 0.1 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= -6.4 && newPlayerX_lvl1 >= -8.5) {
		newPlayerZ_lvl1 += 0.1;
		playerZ_lvl1 += 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerZ_lvl1 <= -7.2 + 0.1 && newPlayerZ_lvl1 >= -7.2 - 0.1 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= -6.4 && newPlayerX_lvl1 >= -8.5) {
		newPlayerZ_lvl1 -= 0.1;
		playerZ_lvl1 -= 0.1;
		collision_lvl1 = true;
	}

	if (newPlayerX_lvl1 <= 8 + 0.2 && newPlayerX_lvl1 >= 8 - 0.2 && newPlayerZ_lvl1 <= 1.4 + 0.2 && newPlayerZ_lvl1 >= 1.4- 0.2) {

		if (!coin1_lvl1) {
			score = score + 5;
			coinCollision_lvl1 = true;
		}
		coin1_lvl1 = true;

	}

	if (newPlayerX_lvl1 <= 3 + 0.2 && newPlayerX_lvl1 >= 3 - 0.2 && newPlayerZ_lvl1 <= 1.4 + 0.2 && newPlayerZ_lvl1 >= 1.4 - 0.2) {

		if (!coin2_lvl1) {
			score = score + 5;
			coinCollision_lvl1 = true;
		}
		coin2_lvl1 = true;

	}

	if (newPlayerX_lvl1 <= -2 + 0.2 && newPlayerX_lvl1 >= -2 - 0.2 && newPlayerZ_lvl1 <= 1.4 + 0.2 && newPlayerZ_lvl1 >= 1.4 - 0.2) {

		if (!coin3_lvl1) {
			score = score + 5;
			coinCollision_lvl1 = true;
		}
		coin3_lvl1 = true;

	}

	if (newPlayerX_lvl1 <= -7 + 0.2 && newPlayerX_lvl1 >= -7 - 0.2 && newPlayerZ_lvl1 <= 1.4 + 0.2 && newPlayerZ_lvl1 >= 1.4 - 0.2) {

		if (!coin4_lvl1) {
			score = score + 5;
			coinCollision_lvl1 = true;
		}
		coin4_lvl1 = true;

	}

	if (newPlayerX_lvl1 <= -2.4 + 0.2 && newPlayerX_lvl1 >= -2.4 - 0.2 && newPlayerZ_lvl1 <= -7.8 + 0.2 && newPlayerZ_lvl1 >= -7.8 - 0.2) {

		if (!gameWon_lvl1) {

			gameWon_lvl1 = true;
		}


	}
}
}

void movePlayerDown() {
	if (level == 2) {
		if (gameOver || gameWon)
			return;
		if (playerAngle == 0) {
			/*playerZ -= 0.05;*/
			playerZ += 0.1;
			/*playerX -= 0.1;*/
			newPlayerZ += 0.1;


		}

		else if (playerAngle == 90) {
			/*playerZ -= 0.05;*/
			playerX += 0.1;
			/*playerX -= 0.1;*/
			newPlayerX += 0.1;


		}


		else if (playerAngle == 180) {
			/*playerZ -= 0.05;*/
			playerZ -= 0.1;
			/*playerX -= 0.1;*/
			newPlayerZ -= 0.1;


		}


		else if (playerAngle == 270) {
			/*playerZ -= 0.05;*/
			playerX -= 0.1;
			/*playerX -= 0.1;*/
			newPlayerX -= 0.1;


		}

		//phase 1
		//block 1
		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 0 && newPlayerX >= 4.7) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 180 && newPlayerX >= 4.7) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 90 && newPlayerX >= 4.7) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}

		//block2
		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 0 && newPlayerX >= 0.1 && newPlayerX <= 2.9) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 180 && newPlayerX >= 0.1 && newPlayerX <= 2.9) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 90 && newPlayerX >= 0.1 && newPlayerX <= 2.9) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 270 && newPlayerX >= 0.1 && newPlayerX <= 2.9) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}


		//block 3
		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 0 && newPlayerX <= -1.2) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 180 && newPlayerX <= -1.2) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 6 + 0.1 && newPlayerZ >= 6 - 0.1 && playerAngle == 270 && newPlayerX <= -1.2) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}



		//phase 2
		//block1
		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 0 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}

		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 180 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}



		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 270 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}

		//block2
		if (newPlayerX <= 1.6 + 0.1 && newPlayerX >= 1.6 - 0.1 && playerAngle == 270 && newPlayerZ <= 5.8 + 0.1) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}

		if (newPlayerX <= 1.6 + 0.1 && newPlayerX >= 1.6 - 0.1 && playerAngle == 90 && newPlayerZ <= 5.8 + 0.1) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}

		//block 3
		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 0 && newPlayerX >= 4.7) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}

		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 180 && newPlayerX >= 4.7) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 90 && newPlayerX >= 4.7) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}

		//block1
		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 0 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}

		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 180 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}



		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 270 && newPlayerX <= 6.8 + 0.1 && newPlayerX >= 1.6 + 0.1) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}


		//phase 3
		//block1
		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 180 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7 + 0.1) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 0 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7 + 0.1) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= 2.1 + 0.1 && newPlayerZ >= 2.1 - 0.1 && playerAngle == 90 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7 + 0.1) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}


		//block2
		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 180 && newPlayerX <= -4.5) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 0 && newPlayerX <= -4.5) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= -1.6 + 0.1 && newPlayerZ >= -1.6 - 0.2 && playerAngle == 270 && newPlayerX <= -4.5) {
			newPlayerX += 0.1;
			playerX += 0.1;
			collision = true;
		}

		//block3
		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 180 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7) {
			newPlayerZ += 0.1;
			playerZ += 0.1;
			collision = true;
		}

		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 0 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7) {
			newPlayerZ -= 0.1;
			playerZ -= 0.1;
			collision = true;
		}



		if (newPlayerZ <= -5.6 + 0.1 && newPlayerZ >= -5.6 - 0.1 && playerAngle == 90 && newPlayerX <= 1.4 + 0.1 && newPlayerX >= -3.7) {
			newPlayerX -= 0.1;
			playerX -= 0.1;
			collision = true;
		}


		//coin1
		if (newPlayerX <= 4.8 + 0.2 && newPlayerX >= 4.8 - 0.2 && newPlayerZ <= 4.8 + 0.2 && newPlayerZ >= 4.8 - 0.2) {

			if (!coin1) {
				score = score + 5;
				coinCollision = true;
			}
			coin1 = true;


		}

		//coin2
		if (newPlayerX <= 7.1 + 0.2 && newPlayerX >= 7.1 - 0.2 && newPlayerZ <= 1 + 0.2 && newPlayerZ >= 1 - 0.2) {

			if (!coin2) {
				score = score + 5;
				coinCollision = true;
			}
			coin2 = true;

		}

		//coin3
		if (newPlayerX <= 3.2 + 0.2 && newPlayerX >= 3.2 - 0.2 && newPlayerZ <= -1.5 + 0.2 && newPlayerZ >= -1.5 - 0.2) {

			if (!coin3) {
				score = score + 5;
				coinCollision = true;
			}
			coin3 = true;

		}

		//coin4
		if (newPlayerX <= 7.7 + 0.2 && newPlayerX >= 7.7 - 0.2 && newPlayerZ <= -7.4 + 0.2 && newPlayerZ >= -7.4 - 0.2) {

			if (!coin4) {
				score = score + 5;
				coinCollision = true;
			}
			coin4 = true;

		}

		//coin5
		if (newPlayerX <= 3 + 0.2 && newPlayerX >= 3 - 0.2 && newPlayerZ <= -8.2 + 0.2 && newPlayerZ >= -8.2 - 0.2) {

			if (!coin5) {
				score = score + 5;
				coinCollision = true;
			}
			coin5 = true;

		}

		//coin6
		if (newPlayerX <= 2.7 + 0.2 && newPlayerX >= 2.7 - 0.2 && newPlayerZ <= 8.5 + 0.2 && newPlayerZ >= 8.5 - 0.2) {

			if (!coin6) {
				score = score + 5;
				coinCollision = true;
			}
			coin6 = true;

		}

		//coin7
		if (newPlayerX <= 0.5 + 0.2 && newPlayerX >= 0.5 - 0.2 && newPlayerZ <= 3.2 + 0.2 && newPlayerZ >= 3.2 - 0.2) {

			if (!coin7) {
				score = score + 5;
				coinCollision = true;
			}
			coin7 = true;

		}

		//coin8
		if (newPlayerX <= -5.3 + 0.2 && newPlayerX >= -5.3 - 0.2 && newPlayerZ <= 3.2 + 0.2 && newPlayerZ >= 3.2 - 0.2) {

			if (!coin8) {
				score = score + 5;
				coinCollision = true;
			}
			coin8 = true;

		}

		//coin9
		if (newPlayerX <= -5.8 + 0.2 && newPlayerX >= -5.8 - 0.2 && newPlayerZ <= -0.3 + 0.2 && newPlayerZ >= -0.3 - 0.2) {

			if (!coin9) {
				score = score + 5;
				coinCollision = true;
			}
			coin9 = true;

		}

		//coin10
		if (newPlayerX <= -2.1 + 0.2 && newPlayerX >= -2.1 - 0.2 && newPlayerZ <= 0.1 + 0.2 && newPlayerZ >= 0.1 - 0.2) {

			if (!coin10) {
				score = score + 5;
				coinCollision = true;
			}
			coin10 = true;

		}

		//coin11
		if (newPlayerX <= -5.1 + 0.2 && newPlayerX >= -5.1 - 0.2 && newPlayerZ <= -7.9 + 0.2 && newPlayerZ >= -7.9 - 0.2) {

			if (!coin11) {
				score = score + 5;
				coinCollision = true;
			}
			coin11 = true;

		}

		glutPostRedisplay();
	}

	else {

		if (gameOver_lvl1 || gameWon_lvl1)
			return;
		if (playerAngle_lvl1 == 0) {
			/*playerZ -= 0.05;*/
			playerZ_lvl1 += 0.1;
			/*playerX -= 0.1;*/
			newPlayerZ_lvl1 += 0.1;


		}

		else if (playerAngle_lvl1 == 90) {
			/*playerZ -= 0.05;*/
			playerX_lvl1 += 0.1;
			/*playerX -= 0.1;*/
			newPlayerX_lvl1 += 0.1;


		}


		else if (playerAngle_lvl1 == 180) {
			/*playerZ -= 0.05;*/
			playerZ_lvl1 -= 0.1;
			/*playerX -= 0.1;*/
			newPlayerZ_lvl1 -= 0.1;


		}


		else if (playerAngle_lvl1 == 270) {
			/*playerZ -= 0.05;*/
			playerX_lvl1 -= 0.1;
			/*playerX -= 0.1;*/
			newPlayerX_lvl1 -= 0.1;


		}

		if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 270 && newPlayerX_lvl1 <= 5.2 + 0.1 && newPlayerX_lvl1 >= 5.2 - 0.1) {
			newPlayerX_lvl1 += 0.1;
			playerX_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 90 && newPlayerX_lvl1 <= 4.8 + 0.1 && newPlayerX_lvl1 >= 4.8 - 0.1) {
			newPlayerX_lvl1 -= 0.1;
			playerX_lvl1 -= 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= 5 + 0.2 && newPlayerX_lvl1 >= 5 - 0.2) {
			newPlayerZ_lvl1 += 0.1;
			playerZ_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 270 && newPlayerX_lvl1 <= 0.2 + 0.1 && newPlayerX_lvl1 >= 0.2 - 0.1) {
			newPlayerX_lvl1 += 0.1;
			playerX_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 90 && newPlayerX_lvl1 <= -0.2 + 0.1 && newPlayerX_lvl1 >= -0.2 - 0.1) {
			newPlayerX_lvl1 -= 0.1;
			playerX_lvl1 -= 0.1;
			collision_lvl1 = true;
		}


		if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= 0.1 + 0.1 && newPlayerX_lvl1 >= -0.1) {
			newPlayerZ_lvl1 += 0.1;
			playerZ_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 270 && newPlayerX_lvl1 <= -4.8 + 0.1 && newPlayerX_lvl1 >= -4.8 - 0.1) {
			newPlayerX_lvl1 += 0.1;
			playerX_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 90 && newPlayerX_lvl1 <= -5.2 + 0.1 && newPlayerX_lvl1 >= -5.2 - 0.1) {
			newPlayerX_lvl1 -= 0.1;
			playerX_lvl1 -= 0.1;
			collision_lvl1 = true;
		}


		if (newPlayerZ_lvl1 <= 6.8 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= -4.8 && newPlayerX_lvl1 >= -5.1) {
			newPlayerZ_lvl1 += 0.1;
			playerZ_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= -6.9 + 0.1 && newPlayerZ_lvl1 >= -6.9 - 0.1 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= 8.6 && newPlayerX_lvl1 >= 6.4) {
			newPlayerZ_lvl1 += 0.1;
			playerZ_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= -7.2 + 0.1 && newPlayerZ_lvl1 >= -7.2 - 0.1 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= 8.6 && newPlayerX_lvl1 >= 6.4) {
			newPlayerZ_lvl1 -= 0.1;
			playerZ_lvl1 -= 0.1;
			collision_lvl1 = true;
		}


		if (newPlayerZ_lvl1 <= -6.9 + 0.1 && newPlayerZ_lvl1 >= -6.9 - 0.1 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= 3.6 && newPlayerX_lvl1 >= 1.5) {
			newPlayerZ_lvl1 += 0.1;
			playerZ_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= -7.2 + 0.1 && newPlayerZ_lvl1 >= -7.2 - 0.1 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= 3.6 && newPlayerX_lvl1 >= 1.5) {
			newPlayerZ_lvl1 -= 0.1;
			playerZ_lvl1 -= 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= -6.9 + 0.1 && newPlayerZ_lvl1 >= -6.9 - 0.1 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= -1.4 && newPlayerX_lvl1 >= -3.5) {
			newPlayerZ_lvl1 += 0.1;
			playerZ_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= -7.2 + 0.1 && newPlayerZ_lvl1 >= -7.2 - 0.1 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= -1.4 && newPlayerX_lvl1 >= -3.5) {
			newPlayerZ_lvl1 -= 0.1;
			playerZ_lvl1 -= 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= -6.9 + 0.1 && newPlayerZ_lvl1 >= -6.9 - 0.1 && playerAngle_lvl1 == 180 && newPlayerX_lvl1 <= -6.4 && newPlayerX_lvl1 >= -8.5) {
			newPlayerZ_lvl1 += 0.1;
			playerZ_lvl1 += 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerZ_lvl1 <= -7.2 + 0.1 && newPlayerZ_lvl1 >= -7.2 - 0.1 && playerAngle_lvl1 == 0 && newPlayerX_lvl1 <= -6.4 && newPlayerX_lvl1 >= -8.5) {
			newPlayerZ_lvl1 -= 0.1;
			playerZ_lvl1 -= 0.1;
			collision_lvl1 = true;
		}

		if (newPlayerX_lvl1 <= 8 + 0.2 && newPlayerX_lvl1 >= 8 - 0.2 && newPlayerZ_lvl1 <= 1.4 + 0.2 && newPlayerZ_lvl1 >= 1.4 - 0.2) {

			if (!coin1_lvl1) {
				score = score + 5;
				coinCollision_lvl1 = true;
			}
			coin1_lvl1 = true;

		}

		if (newPlayerX_lvl1 <= 3 + 0.2 && newPlayerX_lvl1 >= 3 - 0.2 && newPlayerZ_lvl1 <= 1.4 + 0.2 && newPlayerZ_lvl1 >= 1.4 - 0.2) {

			if (!coin2_lvl1) {
				score = score + 5;
				coinCollision_lvl1 = true;
			}
			coin2_lvl1 = true;

		}

		if (newPlayerX_lvl1 <= -2 + 0.2 && newPlayerX_lvl1 >= -2 - 0.2 && newPlayerZ_lvl1 <= 1.4 + 0.2 && newPlayerZ_lvl1 >= 1.4 - 0.2) {

			if (!coin3_lvl1) {
				score = score + 5;
				coinCollision_lvl1 = true;
			}
			coin3_lvl1 = true;

		}

		if (newPlayerX_lvl1 <= -7 + 0.2 && newPlayerX_lvl1 >= -7 - 0.2 && newPlayerZ_lvl1 <= 1.4 + 0.2 && newPlayerZ_lvl1 >= 1.4 - 0.2) {

			if (!coin4_lvl1) {
				score = score + 5;
				coinCollision_lvl1 = true;
			}
			coin4_lvl1 = true;

		}

		if (newPlayerX_lvl1 <= -2.4 + 0.2 && newPlayerX_lvl1 >= -2.4 - 0.2 && newPlayerZ_lvl1 <= -7.8 + 0.2 && newPlayerZ_lvl1 >= -7.8 - 0.2) {

			if (!gameWon_lvl1) {

				gameWon_lvl1 = true;
			}




		}
	}
}

void adjustView(int v) {

	if (level == 2) {
		if (gameOver || gameWon)
			return;
		if (thirdPerson) {

			if (v == 1) {


				At.x = newPlayerX;
				At.z = newPlayerZ;
				Eye.x = newPlayerX + 2;
				Eye.z = newPlayerZ;


			}
			else if (v == 2) {


				At.x = newPlayerX;
				At.z = newPlayerZ;
				Eye.x = newPlayerX;
				Eye.z = newPlayerZ - 2;
				/*Eye.y = 5;*/



			}

			else if (v == 3) {

				At.x = newPlayerX;
				At.z = newPlayerZ;
				Eye.x = newPlayerX - 2;
				Eye.z = newPlayerZ;




			}

			else if (v == 0) {

				At.x = newPlayerX;
				At.z = newPlayerZ;
				Eye.x = newPlayerX;
				Eye.z = newPlayerZ + 2;
				//Eye.x = newPlayerX - 0.05;
				//Eye.y = newPlayerY + 0.9;
				//Eye.z = newPlayerZ + 1.8019;
				//At.x = newPlayerX - 0.1009;
				//At.y = newPlayerY + 0.7;
				//At.z = newPlayerX + 0.8047;
			}
		}

		else if (firstPerson) {

			if (v == 0) {


				newPlayerZ -= 2.07;

				Eye.x = newPlayerX;
				Eye.z = newPlayerZ + 2;
				At.x = newPlayerX;
				At.z = newPlayerZ;


				newPlayerZ += 2.07;



			}

			else if (v == 1) {


				newPlayerX -= 2.07;

				Eye.x = newPlayerX + 2;
				Eye.z = newPlayerZ;
				At.x = newPlayerX;
				At.z = newPlayerZ;


				newPlayerX += 2.07;



			}

			else if (v == 2) {


				newPlayerZ += 2.07;

				Eye.x = newPlayerX;
				Eye.z = newPlayerZ - 2;
				At.x = newPlayerX;
				At.z = newPlayerZ;


				newPlayerZ -= 2.07;



			}

			else if (v == 3) {


				newPlayerX += 2.07;

				Eye.x = newPlayerX - 2;
				Eye.z = newPlayerZ;
				At.x = newPlayerX;
				At.z = newPlayerZ;


				newPlayerX -= 2.07;



			}
		}



		glLoadIdentity();	//Clear Model_View Matrix

		gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	}

	else {

		if (gameOver_lvl1 || gameWon_lvl1)
			return;
		if (thirdPerson) {

			if (v == 1) {


				At.x = newPlayerX_lvl1;
				At.z = newPlayerZ_lvl1;
				Eye.x = newPlayerX_lvl1 + 2;
				Eye.z = newPlayerZ_lvl1;


			}
			else if (v == 2) {


				At.x = newPlayerX_lvl1;
				At.z = newPlayerZ_lvl1;
				Eye.x = newPlayerX_lvl1;
				Eye.z = newPlayerZ_lvl1 - 2;
				/*Eye.y = 5;*/



			}

			else if (v == 3) {

				At.x = newPlayerX_lvl1;
				At.z = newPlayerZ_lvl1;
				Eye.x = newPlayerX_lvl1 - 2;
				Eye.z = newPlayerZ_lvl1;




			}

			else if (v == 0) {

				At.x = newPlayerX_lvl1;
				At.z = newPlayerZ_lvl1;
				Eye.x = newPlayerX_lvl1;
				Eye.z = newPlayerZ_lvl1 + 2;
				//Eye.x = newPlayerX - 0.05;
				//Eye.y = newPlayerY + 0.9;
				//Eye.z = newPlayerZ + 1.8019;
				//At.x = newPlayerX - 0.1009;
				//At.y = newPlayerY + 0.7;
				//At.z = newPlayerX + 0.8047;
			}
		}

		else if (firstPerson) {

			if (v == 0) {

				
				newPlayerZ_lvl1 -= 2.07;

				Eye.x = newPlayerX_lvl1;
				Eye.z = newPlayerZ_lvl1 + 2;
				At.x = newPlayerX_lvl1;
				At.z = newPlayerZ_lvl1;
				
				
				newPlayerZ_lvl1 += 2.07;



			}

			else if (v == 1) {

				
				newPlayerX_lvl1 -= 2.07;

				Eye.x = newPlayerX_lvl1 + 2;
				Eye.z = newPlayerZ_lvl1;
				At.x = newPlayerX_lvl1;
				At.z = newPlayerZ_lvl1;

				
				newPlayerX_lvl1 += 2.07;



			}

			else if (v == 2) {


				newPlayerZ_lvl1 += 2.07;

				Eye.x = newPlayerX_lvl1;
				Eye.z = newPlayerZ_lvl1 - 2;
				At.x = newPlayerX_lvl1;
				At.z = newPlayerZ_lvl1;


				newPlayerZ_lvl1 -= 2.07;



			}

			else if (v == 3) {


				newPlayerX_lvl1 += 2.07;

				Eye.x = newPlayerX_lvl1 - 2;
				Eye.z = newPlayerZ_lvl1;
				At.x = newPlayerX_lvl1;
				At.z = newPlayerZ_lvl1;


				newPlayerX_lvl1 -= 2.07;



			}
		}

		glLoadIdentity();	//Clear Model_View Matrix

		gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);



	}

}



void myKeyboard(unsigned char key, int x, int y)

{
	if (level == 2) {
		if (gameOver || gameWon)
			return;
		switch (key)
		{
		
		case '1':
			firstPerson = true;
			thirdPerson = false;
			switch (playerAngle) {
			case 0: adjustView(0); break;
			case 180: adjustView(2); break;
			case 90: adjustView(1); break;
			case 270: adjustView(3); break;
			}
			break;

		case '3':
			firstPerson = false;
			thirdPerson = true;
			switch (playerAngle) {
			case 0: adjustView(0); break;
			case 180: adjustView(2); break;
			case 90: adjustView(1); break;
			case 270: adjustView(3); break;
			}
			break;

		case 'w':

			movePlayerUp();
			if (playerAngle == 0) {
				adjustView(0);
			}

			else if (playerAngle == 90) {
				adjustView(1);
			}


			else if (playerAngle == 180) {
				adjustView(2);
			}


			else if (playerAngle == 270) {
				adjustView(3);
			}

			break;


		case 's':
			movePlayerDown();
			if (playerAngle == 0) {
				adjustView(0);
			}

			else if (playerAngle == 90) {
				adjustView(1);
			}


			else if (playerAngle == 180) {
				adjustView(2);
			}


			else if (playerAngle == 270) {
				adjustView(3);
			}
			break;
		default:
			break;
		}


		collisions();
		glutPostRedisplay();

	}

	else {

		if (gameOver_lvl1 || gameWon_lvl1)
			return;
		switch (key)
		{
		case '1':
			firstPerson = true;
			thirdPerson = false;
			switch (playerAngle_lvl1) {
			case 0: adjustView(0); break;
			case 180: adjustView(2); break;
			case 90: adjustView(1); break;
			case 270: adjustView(3); break;
			}
			break;

		case '3':
			firstPerson = false;
			thirdPerson = true;
			switch (playerAngle_lvl1) {
			case 0: adjustView(0); break;
			case 180: adjustView(2); break;
			case 90: adjustView(1); break;
			case 270: adjustView(3); break;
			}
			break;

		case 'w':

			movePlayerUp();
			if (playerAngle_lvl1 == 0) {
				adjustView(0);
			}

			else if (playerAngle_lvl1 == 90) {
				adjustView(1);
			}


			else if (playerAngle_lvl1 == 180) {
				adjustView(2);
			}


			else if (playerAngle_lvl1 == 270) {
				adjustView(3);
			}

			break;


		case 's':
			movePlayerDown();
			if (playerAngle_lvl1 == 0) {
				adjustView(0);
			}

			else if (playerAngle_lvl1 == 90) {
				adjustView(1);
			}


			else if (playerAngle_lvl1 == 180) {
				adjustView(2);
			}


			else if (playerAngle_lvl1 == 270) {
				adjustView(3);
			}
			break;
		default:
			break;
		}


		collisions();
		glutPostRedisplay();


	}
}


void Special(int key, int x, int y) {

	if (level == 2) {
		if (gameOver || gameWon)
			return;
		switch (key) {
		case GLUT_KEY_LEFT:
			switch (playerAngle) {
			case 0: adjustView(1), movePlayerLeft(); break;
			case 180: adjustView(3), movePlayerLeft(); break;
			case 90: adjustView(2), movePlayerLeft(); break;
			case 270: adjustView(0), movePlayerLeft(); break;
			}
			break;
		case GLUT_KEY_RIGHT:
			switch (playerAngle) {
			case 0: adjustView(3), movePlayerRight(); break;
			case 180: adjustView(1), movePlayerRight(); break;
			case 90: adjustView(0), movePlayerRight(); break;
			case 270: adjustView(2), movePlayerRight(); break;
			}
			break;
		case GLUT_KEY_UP:

			movePlayerUp();
			if (playerAngle == 0) {
				adjustView(0);
			}

			else if (playerAngle == 90) {
				adjustView(1);
			}


			else if (playerAngle == 180) {
				adjustView(2);
			}


			else if (playerAngle == 270) {
				adjustView(3);
			}

			break;


		case GLUT_KEY_DOWN:
			movePlayerDown();
			if (playerAngle == 0) {
				adjustView(0);
			}

			else if (playerAngle == 90) {
				adjustView(1);
			}


			else if (playerAngle == 180) {
				adjustView(2);
			}


			else if (playerAngle == 270) {
				adjustView(3);
			}

			break;

		};





		collisions();




		glutPostRedisplay();
	}

	else {

		if (gameOver_lvl1 || gameWon_lvl1)
			return;
		switch (key) {
		case GLUT_KEY_LEFT:
			switch (playerAngle_lvl1) {
			case 0: adjustView(1), movePlayerLeft(); break;
			case 180: adjustView(3), movePlayerLeft(); break;
			case 90: adjustView(2), movePlayerLeft(); break;
			case 270: adjustView(0), movePlayerLeft(); break;
			}
			break;
		case GLUT_KEY_RIGHT:
			switch (playerAngle_lvl1) {
			case 0: adjustView(3), movePlayerRight(); break;
			case 180: adjustView(1), movePlayerRight(); break;
			case 90: adjustView(0), movePlayerRight(); break;
			case 270: adjustView(2), movePlayerRight(); break;
			}
			break;
		case GLUT_KEY_UP:

			movePlayerUp();
			if (playerAngle_lvl1 == 0) {
				adjustView(0);
			}

			else if (playerAngle_lvl1 == 90) {
				adjustView(1);
			}


			else if (playerAngle_lvl1 == 180) {
				adjustView(2);
			}


			else if (playerAngle_lvl1 == 270) {
				adjustView(3);
			}

			break;


		case GLUT_KEY_DOWN:
			movePlayerDown();
			if (playerAngle_lvl1 == 0) {
				adjustView(0);
			}

			else if (playerAngle_lvl1 == 90) {
				adjustView(1);
			}


			else if (playerAngle_lvl1 == 180) {
				adjustView(2);
			}


			else if (playerAngle_lvl1 == 270) {
				adjustView(3);
			}

			break;

		};





		collisions();




		glutPostRedisplay();




	}

}






void myMotion(int x, int y)

{
	if (gameOver || gameWon)
		return;
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 


}


void myMouse(int button, int state, int x, int y)
{
	if (level == 2) {
		if (gameOver || gameWon)
			return;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

			switch (playerAngle) {
			case 0: adjustView(1), movePlayerLeft(); break;
			case 180: adjustView(3), movePlayerLeft(); break;
			case 90: adjustView(2), movePlayerLeft(); break;
			case 270: adjustView(0), movePlayerLeft(); break;
			}
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

			switch (playerAngle) {
			case 0: adjustView(3), movePlayerRight(); break;
			case 180: adjustView(1), movePlayerRight(); break;
			case 90: adjustView(0), movePlayerRight(); break;
			case 270: adjustView(2), movePlayerRight(); break;
			}
		}






		/*gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);*/


		glutPostRedisplay();
	}

	else {

		if (gameOver_lvl1 || gameWon_lvl1)
			return;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

			switch (playerAngle_lvl1) {
			case 0: adjustView(1), movePlayerLeft(); break;
			case 180: adjustView(3), movePlayerLeft(); break;
			case 90: adjustView(2), movePlayerLeft(); break;
			case 270: adjustView(0), movePlayerLeft(); break;
			}
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

			switch (playerAngle_lvl1) {
			case 0: adjustView(3), movePlayerRight(); break;
			case 180: adjustView(1), movePlayerRight(); break;
			case 90: adjustView(0), movePlayerRight(); break;
			case 270: adjustView(2), movePlayerRight(); break;
			}
		}






		/*gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);*/


		glutPostRedisplay();


	}
}





void LoadAssets()
{
	// Loading Model files
	
	model_container.Load("Models/container/Fence N130912.3DS");
	model_player.Load("Models/player2/Man N070814.3DS");
	model_coin.Load("Models/coin2/Decor.3DS");
	model_goal.Load("Models/cup/pharaon.3DS");
	model_wall.Load("Models/wall/fence-K019.3DS");
	model_fence.Load("Models/fence/Fence N230210.3DS");
	model_statue.Load("Models/statue/Sculpture N240611.3DS");
	// Loading texture files
	tex_ground.Load("Textures/desert.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	
	

}




void Timer(int value) {
	if ((gameOver || gameWon) && level == 2)
		return;
	if ((gameOver_lvl1) && level == 1)
		return;

	timer--;
	if (timer == -1) {
		if(level == 2)
		gameOver = true;
		else
		gameOver_lvl1 = true;
	}

	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	// recall the Timer function after 20 seconds (20,000 milliseconds)
	glutTimerFunc(1000, Timer, 0);

}

void Anim()
{
	if ((gameOver || gameWon) && level == 2)
		return;
	if ((gameOver_lvl1 || gameWon_lvl1) && level == 1)
		return;
	coinAngle = (coinAngle + 5) % 360;
	coinAngle_lvl1 = (coinAngle_lvl1 + 5) % 360;
	for (int i = 0; i < 800000; i++) {

	}

	glutPostRedisplay();
}





void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);

	glutSpecialFunc(Special);

	/*glutMotionFunc(myMotion);*/

	glutMouseFunc(myMouse);

	glutIdleFunc(Anim);

	glutTimerFunc(0, Timer, 0);

	/*glutReshapeFunc(myReshape);*/

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}