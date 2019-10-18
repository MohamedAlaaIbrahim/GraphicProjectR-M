#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <glut.h>
#define radian 3.14159/180.0

int playerOne[2] = {100, 50};
int playerTwo[2] = {1180, 50};

int playerOneHP = 200;
int playerTwoHP = 200;

int passX = 0;
int passY = 0;

int posXOne = playerOne[0];
int posYOne = playerOne[1];

int posXTwo = playerTwo[0];
int posYTwo = playerTwo[1];

double hit = 0;
float rotateWing = 0;
float ty = 0;
float tx = 0;
float insectY = 0;
float insectX = 0;

int p0[2] = {playerOne[0], playerOne[1]};
int p1[2] = {playerOne[0], playerOne[1]};
int p2[2] = {playerOne[0], playerOne[1]};
int p3[2] = {playerOne[0], playerOne[1]};

int lightPositionDown[2] = {760, 450};
int lightPositionUp[2] = {770, 480};
int slightPositionDown[2] = {760, 450};
int slightPositionUp[2] = {770, 480};
int leftEyePosition[2] = { 640 , 505 };
int rightEyePosition[2] = { 665 , 505 };
int leftPupilPosition[2] = { 647, 505 };
int rightPupilPosition[2] = { 672, 505 };

int shadeangle[2] = { 270, 90 };
int hairangle[2] = {55, 180};

float hitReactionOne = 0;
float hitReactionTwo = 1;
float interval = 0;
float powerMeterOne = 0;
float powerMeterTwo = 0;

boolean endGame = false;
boolean hitReactionOneBool = false;
boolean hitReactionTwoBool = false;
boolean insectMovUp = false;
boolean insectMovLeft = true;
boolean rotateUp = true;
boolean soundEffect = true;
boolean portalHitRestart = false;
boolean portalHit = false;
boolean playerTurn = false;
boolean bmove = false;
boolean bmoveY = false;
boolean mouseButton = false;
boolean mouseReleasedReady = false;

void print(int x, int y, char* string)
{
	glRasterPos2f(x, y);
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3) * p0[0] + 3 * t * pow((1 - t), 2) * p1[0] + 3 * pow(t, 2) * (1 - t) * p2[0] + pow(t, 3) * p3[0];
	res[1] = pow((1 - t), 3) * p0[1] + 3 * t * pow((1 - t), 2) * p1[1] + 3 * pow(t, 2) * (1 - t) * p2[1] + pow(t, 3) * p3[1];
	return res;
}

void releaseCurve()
{
	if (mouseReleasedReady)
	{
		if (!playerTurn) 
		{
			p0[0] = playerOne[0];
			p0[1] = playerOne[1];
			p1[0] = playerOne[0];
			p1[1] = playerOne[1];
			p2[0] = playerOne[0];
			p2[1] = playerOne[1];
			p3[0] = playerOne[0];
			p3[1] = playerOne[1];
			posXOne = playerOne[0];
			posYOne = playerOne[1];
			posXTwo = playerTwo[0];
			posYTwo = playerTwo[1];
		}
		else
		{
			p0[0] = playerTwo[0];
			p0[1] = playerTwo[1];
			p1[0] = playerTwo[0];
			p1[1] = playerTwo[1];
			p2[0] = playerTwo[0];
			p2[1] = playerTwo[1];
			p3[0] = playerTwo[0];
			p3[1] = playerTwo[1];
			posXOne = playerOne[0];
			posYOne = playerOne[1];
			posXTwo = playerTwo[0];
			posYTwo = playerTwo[1];
		}
		mouseReleasedReady = false;
		powerMeterOne = 0;
		powerMeterTwo = 0;
	}
}

bool playerOneHittingObject()
{
	if ((posXOne <= 680 && posXOne >= 600 && posYOne <= 360 && posYOne >= 0) || 
		(posXOne <= (tx + 740) && posXOne >= (tx + 540) && posYOne <= ty + 500 && posYOne >= ty + 400))
	{
		interval = 0;
		playerTurn = !playerTurn;
		if ((posXOne <= 680 && posXOne >= 600 && posYOne <= 360 && posYOne >= 0))
		{
			portalHit = true;
			soundEffect = true;
		}
		else 
		{
			PlaySound(TEXT("Cut_y2mate.com - all_of_mortys_oh_jeez_oh_mans_compilation_NivwAQ8sUYQ.wav"), NULL, SND_ASYNC | SND_FILENAME); 		
		}
		releaseCurve();
		return true;
	}
	if (posXOne <= 1260 && posXOne >= 1000 && posYOne <= 150 && posYOne >= 25)
	{
		PlaySound(TEXT("I Don't Eat Poop.wav"), NULL, SND_ASYNC | SND_FILENAME);
		hitReactionTwoBool = true;
		playerTwoHP -= 50;
		interval = 0;
		playerTurn = !playerTurn;
		releaseCurve();
		return true;
	}
	return false;
}

bool playerTwoHittingObject()
{
	if ((posXTwo <= 680 && posXTwo >= 600 && posYTwo <= 360 && posYTwo >= 0) || 
		( posXTwo <= (tx + 740) && posXTwo >= (tx + 540) && posYTwo <=(ty + 500) && posYTwo >=(ty + 400)))
	{
		interval = 0;
		playerTurn = !playerTurn;
		if ((posXTwo <= 680 && posXTwo >= 600 && posYTwo <= 360 && posYTwo >= 0))
		{
			portalHit = true;
			soundEffect = true;
		}
		else
		{
			PlaySound(TEXT("Cut_y2mate.com - all_of_mortys_oh_jeez_oh_mans_compilation_NivwAQ8sUYQ.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
		releaseCurve();
		return true;
	}
	if (posXTwo <= 180 && posXTwo >= 20 && posYTwo <= 150 && posYTwo >= 25)
	{
		PlaySound(TEXT("wubba_lubba_dub_dub.wav"), NULL, SND_ASYNC | SND_FILENAME);
		hitReactionOneBool = true;
		playerOneHP -= 50;
		interval = 0;
		playerTurn = !playerTurn;
		releaseCurve();
		return true;
	}
	return false;
}

void projectileTrajoctory(int x)
{
	interval = interval + 0.002;

	if (interval < 1)
	{
		int* p = bezier(interval, p0, p1, p2, p3);
		if (!playerTurn) 
		{
			posXOne = p[0];
			posYOne = p[1];
			if (playerOneHittingObject())
			{
				return;
			}
		}
		else
		{
			posXTwo = p[0];
			posYTwo = p[1];
			if (playerTwoHittingObject())
			{
				return;
			}
		}

		glutTimerFunc(1, projectileTrajoctory, 0);
	}
	else
	{
		interval = 0;
		playerTurn = !playerTurn;
		releaseCurve();
	}
}

void actM(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseButton = true;
		mouseReleasedReady = false;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (playerTurn)
			PlaySound(TEXT("y2mate.com - supercut_the_rick_burp_rick_and_morty_FtqNwcmRTXk.wav"), NULL, SND_ASYNC | SND_FILENAME);
		else
			PlaySound(TEXT("doofus_rick_rick_and_morty_jsvgAgK9ybQ.wav"), NULL, SND_ASYNC | SND_FILENAME);
		projectileTrajoctory(0);
		mouseReleasedReady = true;
		mouseButton = false;
	}
	glutPostRedisplay();
}

void idleFunc()
{
	if (!endGame)
		glutPostRedisplay();
}

void spaceShipMov() 
{
	if (!bmove) 
	{
		tx += 0.1;
		if (tx >= 300)
			bmove = true;
		lightPositionDown[0] = 760;
		lightPositionUp[0] = 770;
		slightPositionDown[0] = 760;
		slightPositionUp[0] = 770;
		shadeangle[0] = 270;
		shadeangle[1] = 90;
		hairangle[0] = 55;
		hairangle[1] = 180;
		leftEyePosition[0] = 640;
		rightEyePosition[0] = 665;
		leftPupilPosition[0] = 647;
		rightPupilPosition[0] = 672;
	}
	else
	{
		tx -= 0.1;
		if (tx <= -300)
			bmove = false;
		lightPositionDown[0] = 515;
		lightPositionUp[0] = 505;
		slightPositionDown[0] = 515;
		slightPositionUp[0] = 505;
		shadeangle[0] = 90;
		shadeangle[1] = 270;
		hairangle[0] = 0;
		hairangle[1] = 125;
		leftEyePosition[0] = 615;
		rightEyePosition[0] = 640;
		leftPupilPosition[0] = 608;
		rightPupilPosition[0] = 633;
	}
	if (!bmoveY)
	{
		ty += 0.04;
		if (ty >= 35)
			bmoveY = true;
	}
	else
	{
		ty -= 0.04;
		if (ty <= 0)
			bmoveY = false;
	}
}

void weaponPowerBlast()
{
	if (mouseButton)
	{
		if(!playerTurn)
		{
			if (powerMeterOne < 100)
			{
				p1[1] += 0.25;
				p2[0] += 0.25;
				p2[1] += 1;
				p3[0] += 1;
				powerMeterOne += 0.05;
			}
		}
		else
		{
			if (powerMeterTwo < 100)
			{
				p1[1] += 1;
				p2[0] -= 0.25;
				p2[1] += 0.25;
				p3[0] -= 1;
				powerMeterTwo += 0.05;
			}
		}
	}
}

void healthBarOne()
{
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(80, 690, 0);
	glVertex3d(280, 690, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(80, 660, 0);
	glVertex3f(280, 660, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(80, 690, 0);
	glVertex3f(80, 660, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(280, 690, 0);
	glVertex3f(280, 660, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslated(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(80 + playerOneHP, 690, 0);
	glVertex3f(80, 690, 0);
	glVertex3f(80, 660, 0);
	glVertex3f(80 + playerOneHP, 660, 0);
	glEnd();
	glPopMatrix();
}

void healthBarTwo()
{
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(1000, 690, 0);
	glVertex3d(1200, 690, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(1000, 660, 0);
	glVertex3f(1200, 660, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(1000, 690, 0);
	glVertex3f(1000, 660, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(1200, 690, 0);
	glVertex3f(1200, 660, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslated(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(1000 + playerTwoHP, 690, 0);
	glVertex3f(1000, 690, 0);
	glVertex3f(1000, 660, 0);
	glVertex3f(1000 + playerTwoHP, 660, 0);
	glEnd();
	glPopMatrix();
}

void drawBezierCurve()
{
	glPointSize(2);
	glColor3f(1, 1, 0);
	glBegin(GL_POINTS);
	for (float t = 0; t < 1; t += 0.001)
	{
		int* p = bezier(t, p0, p1, p2, p3);
		glVertex3d(p[0], p[1], 0);
	}
	glEnd();
}

void drawRectangleOne()
{
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(20, 160, 0);
	glVertex3d(20, 260, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(40, 160, 0);
	glVertex3f(40, 260, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(20, 160, 0);
	glVertex3f(40, 160, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(20, 260, 0);
	glVertex3f(40, 260, 0);
	glEnd();
	glPopMatrix();
}

void drawRectangleTwo()
{
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(1240, 160, 0);
	glVertex3d(1240, 260, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(1260, 160, 0);
	glVertex3f(1260, 260, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(1240, 160, 0);
	glVertex3f(1260, 160, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(1240, 260, 0);
	glVertex3f(1260, 260, 0);
	glEnd();
	glPopMatrix();
}

void drawRectangleVariableOne(float x)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(20, 160, 0);
	glVertex3f(40, 160, 0);
	glColor3f(1, 0, 0);
	glVertex3f(40, 160 + x, 0);
	glVertex3f(20, 160 + x, 0);
	glEnd();
	glPopMatrix();
}

void drawRectangleVariableTwo(float x)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(1240, 160, 0);
	glVertex3f(1260, 160, 0);
	glColor3f(1, 0, 0);
	glVertex3f(1260, 160 + x, 0);
	glVertex3f(1240, 160 + x, 0);
	glEnd();
	glPopMatrix();
}

void drawPowerBar()
{
	drawRectangleOne();
	drawRectangleTwo();
	if (!playerTurn)
	{
		drawRectangleVariableOne(powerMeterOne);
	}
	else
	{
		drawRectangleVariableTwo(powerMeterTwo);
	}
}

void drawShirt( int x, int y, int a, int b, int w, int z, int u, int v )
{
	glPushMatrix();
	glTranslated(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(x, y, 0);
	glVertex3f(u, v, 0);
	glVertex3f(a, b, 0);
	glVertex3f(w, z, 0);
	glEnd();
	glPopMatrix();
}

void drawModifiedCircle(int radiusX, int radiusY, int xPos, int yPos)
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float rad = i * radian;
		glVertex2f(xPos + cos(rad) * radiusX,
			yPos + sin(rad) * radiusY);
	}
	glEnd();
}

void drawModifiedCircleUnFilled(int radiusX, int radiusY, int xPos, int yPos)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float rad = i * radian;
		glVertex2f(xPos + cos(rad) * radiusX,
			yPos + sin(rad) * radiusY);
	}
	glEnd();
}


void drawSemiCircle(int radiusX, int radiusY, int xPos, int yPos, int angle1, int angle2)
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	if (angle2 < angle1)
	{
		for (int i = angle1; i < 360; i++)
		{
			float rad = i * radian;
			glVertex2f(xPos + cos(rad) * radiusX,
				yPos + sin(rad) * radiusY);
		}
		angle1 = 0;
	}
	for (int i = angle1; i < angle2; i++)
	{
		float rad = i * radian;
		glVertex2f(xPos + cos(rad) * radiusX,
			yPos + sin(rad) * radiusY);
	}
	glEnd();
}


void drawCurvedLine(int radiusX, int radiusY, int xPos, int yPos, int angle1, int angle2)
{
		glBegin(GL_LINE_STRIP);
	for (int i = angle1; i < angle2; i++)
	{
		float rad = i * radian;
		glVertex2f(xPos + cos(rad) * radiusX, yPos + sin(rad) * radiusY);
	}
	glEnd();
}

void drawCurvedLineForPortal(int radiusX, int radiusY, double xPos, double yPos, int angle1, int angle2)
{
	glColor3f(0, 0.5, 0);
	glBegin(GL_LINE_STRIP);
	if (angle2 < angle1)
	{
		for (int i = angle1; i < 360; i++)
		{
			float rad = i * radian;
			glVertex2f( xPos + cos(rad) * radiusX,
				yPos + sin(rad) * radiusY);
		}
		angle1 = 0;
	}
	for (int i = angle1; i < angle2; i++)
	{
		float rad = i * radian;
		glVertex2f(xPos + cos(rad) * radiusX, yPos + sin(rad) * radiusY);
	}
	glEnd();
}

void drawModifiedCircleUnFilledForPortal(int radiusX, int radiusY, int xPos, int yPos)
{
	glColor3f(0, 0.5, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float rad = i * radian;
		glVertex2f(xPos + cos(rad) * radiusX,
			yPos + sin(rad) * radiusY);
	}
	glEnd();
}

void drawPixel(int xPos, int yPos, int size )
{
	glPushMatrix();
	glPointSize(size);
	glColor3f(1, 1, 1);
	glTranslated(0, 0, 0);
	glBegin(GL_POINTS);
	glVertex3d(xPos, yPos, 0);
	glEnd();
	glPopMatrix();
}

void drawStars()
{
	for (int i = 0; i < 10000; i++)
	{
		if (i % 100 == 0) {
			int randomX = (rand() % 1280) + 1;
			int randomY = (rand() % 720) + 1;
			glPushMatrix();
			glColor3f(1, 1, 1);
			glBegin(GL_POLYGON);
			glVertex3f(randomX, randomY, 0);
			glVertex3f(randomX + 1.5, randomY + 3, 0);
			glVertex3f(randomX + 3, randomY, 0);
			glVertex3f(randomX + 6, randomY - 1.5, 0);
			glVertex3f(randomX + 3, randomY - 3, 0);
			glVertex3f(randomX + 1.5, randomY - 6, 0);
			glVertex3f(randomX, randomY - 3, 0);
			glVertex3f(randomX - 3, randomY - 1.5, 0);
			glEnd();
			glPopMatrix();
			glLineWidth(1);
			glBegin(GL_LINES);
			glVertex3f(randomX + 3, randomY, 0);
			glVertex3f(randomX + 6, randomY + 3, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(randomX + 3, randomY - 3, 0);
			glVertex3f(randomX + 6, randomY - 6, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(randomX, randomY, 0);
			glVertex3f(randomX - 3, randomY + 3, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(randomX, randomY - 3, 0);
			glVertex3f(randomX - 3, randomY - 6, 0);
			glEnd();
		}
	}
}

void drawTriangle(int x, int y, int a, int b, int w, int z)
{
	glPushMatrix();
	glTranslated(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3d(x, y, 0);
	glVertex3d(a, b, 0);
	glVertex3d(w, z, 0);
	glEnd();
	glPopMatrix();
}

void drawSunTriangles()
{
	for (int i = 0; i < 36; i++)
	{
		glPushMatrix();

		glTranslatef(1200, 650 - ty, 0);

		glRotatef(10 * i, 0, 0, 1);

		glTranslatef(-1200, -650 + ty, 0);

		glBegin(GL_TRIANGLES);

		glVertex3f(1150, 790 - ty, 0);
		glVertex3f(1250, 790 - ty, 0);
		glVertex3f(1200, 820 - ty, 0);

		glEnd();
		glPopMatrix();
	}
}

void drawSun()
{
	glColor3f(0.99, 0.72, 0.075);
	drawModifiedCircle(150, 150, 1200, 650 - ty);
	glColor3f(1, 0.5, 0);
	drawSunTriangles();
	glColor3f(1, 1, 1);
	drawModifiedCircle(17, 17, 1150, 620 - ty);
	drawModifiedCircle(17, 17, 1200, 620 - ty);
	glColor3f(0, 0, 0);
	glLineWidth(1.5);
	drawModifiedCircleUnFilled(17, 17, 1150, 620 - ty);
	drawModifiedCircleUnFilled(17, 17, 1200, 620 - ty);
	drawModifiedCircle(2, 2, 1145, 615 - ty);
	drawModifiedCircle(2, 2, 1195, 615 - ty);
	drawSemiCircle(37.5, 37.5, 1175, 560 - ty, 0, 180);
	drawCurvedLine(37, 20, 1175, 555 - ty, 0, 180);
	glColor3f(1, 0.75, 0.8);
	drawSemiCircle(50, 5, 1180, 570 - ty, 90, 225);
}

void drawRectangleInsect()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(400 + insectX, 520 + insectY, 0);
	glVertex3f(400 + insectX, 510 + insectY, 0);
	glVertex3f(450 + insectX, 510 + insectY, 0);
	glVertex3f(450 + insectX, 520 + insectY, 0);
	glEnd();
	glPopMatrix();
}

void drawRectangleInsect2()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(400 + 200 - insectX, 520 - 300 - insectY, 0);
	glVertex3f(400 + 200 - insectX, 510 - 300 - insectY, 0);
	glVertex3f(450 + 200 - insectX, 510 - 300 - insectY, 0);
	glVertex3f(450 + 200 - insectX, 520 - 300 - insectY, 0);
	glEnd();
	glPopMatrix();
}

void insectWingMove()
{
	if (!rotateUp)
	{
		rotateWing += 1;
		if(rotateWing >= 45)
			rotateUp = true;
	}
	else
	{
		rotateWing -= 1;
		if (rotateWing <= 0)
			rotateUp = false;
	}
}

void insectMove()
{
	if (!insectMovUp && insectMovLeft)
	{
		insectX -= 0.2;
		if (insectX <= -300)
		{
			insectMovUp = true;
			insectMovLeft = false;
		}
	}
	else
	{
		if (!insectMovLeft) {
			insectX += 0.2;
			if (insectMovUp)
			{
				insectY += 0.15;
				if (insectY >= 150)
				{
					insectMovUp = false;
				}
			}
			else
			{
				if (!insectMovUp)
				{
					insectY -= 0.15;
					if (insectY <= -300)
					{
						insectMovUp = false;
					}
				}
			}
			if (insectX >= 500)
			{
				insectMovLeft = true;
			}
		}
	}
}

void drawLine(int x, int y, int a, int b)
{
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(x, y, 0);
	glVertex3f(a, b, 0);
	glEnd();
	glPopMatrix();
}

void drawInsectBackground()
{
	
	glPushMatrix();
	glTranslatef(480 + insectX, 512 + insectY, 0);
	glRotatef(1 * rotateWing, 0, 0, 1);
	glTranslatef(-480 - insectX, -512 - insectY, 0);
	glColor3f(0.7, 0.7, 0.7);
	drawModifiedCircle(10, 30, 480 + insectX, 545 + insectY);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(480 + insectX, 512 + insectY, 0);
	glRotatef(1 * -rotateWing, 0, 0, 1);
	glTranslatef(-480 - +insectX, -512 - insectY, 0);
	glColor3f(0.7, 0.7, 0.7);
	drawModifiedCircle(10, 30, 480 + insectX, 545 + insectY);
	glPopMatrix();

	glColor3f(0.33, 0.42, 0.18);
	drawModifiedCircle(5, 20, 482 + insectX, 480 + insectY);
	drawModifiedCircle(10, 10, 477 + insectX, 500 + insectY);
	drawModifiedCircle(10, 10, 472 + insectX, 515 + insectY);
	drawModifiedCircle(15, 20, 467 + insectX, 535 + insectY);
	glColor3f(1, 0, 0);
	drawModifiedCircle(5, 5, 455 + insectX, 535 + insectY);
	drawModifiedCircle(5, 5, 468 + insectX, 535 + insectY);
	glColor3f(0.6, 0.6, 0.6);
	drawCurvedLine(20, 0, 460 + insectX, 515 + insectY, 45, 225);
	drawRectangleInsect();
	glColor3f(1, 1, 1);
	drawTriangle(450 + insectX, 510 + insectY, 440 + insectX, 510 + insectY, 445 + insectX, 500 + insectY);
	glColor3f(0.6, 0.6, 0.6);
	drawCurvedLine(16, 0, 456 + insectX, 510 + insectY, 45, 225);
	drawCurvedLine(0, 35, 475 + insectX, 465 + insectY, 0, 180);
}

void drawInsectBackground2()
{

	glPushMatrix();
	glTranslatef(480 - insectX + 200, 512 - 300 - insectY, 0);
	glRotatef(1 * rotateWing, 0, 0, 1);
	glTranslatef(-480 + insectX - 200, -512 + 300 + insectY, 0);
	glColor3f(0.7, 0.7, 0.7);
	drawModifiedCircle(10, 30, 480 + 200 - insectX, 545 - 300 - insectY);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(480 - insectX + 200, 512 - 300 - insectY, 0);
	glRotatef(1 * -rotateWing, 0, 0, 1);
	glTranslatef(-480 + insectX - 200, -512 + 300 + insectY, 0);
	glColor3f(0.7, 0.7, 0.7);
	drawModifiedCircle(10, 30, 480 + 200 - insectX, 545 - 300 - insectY);
	glPopMatrix();

	glColor3f(0.33, 0.42, 0.18);
	drawModifiedCircle(5, 20, 482 + 200 - insectX, 480 - 300 - insectY);
	drawModifiedCircle(10, 10, 477 + 200 - insectX, 500 - 300 - insectY);
	drawModifiedCircle(10, 10, 472 + 200 - insectX, 515 - 300 - insectY);
	drawModifiedCircle(15, 20, 467 + 200 - insectX, 535 - 300 - insectY);
	glColor3f(1, 0, 0);
	drawModifiedCircle(5, 5, 455 + 200 - insectX, 535 - 300 - insectY);
	drawModifiedCircle(5, 5, 468 + 200 - insectX, 535 - 300 - insectY);
	glColor3f(0.6, 0.6, 0.6);
	drawCurvedLine(20, 0, 460 + 200 - insectX, 515 - 300 - insectY, 45, 225);
	drawRectangleInsect2();
	glColor3f(1, 1, 1);
	drawTriangle(450 + 200 - insectX, 510 - 300 - insectY, 440 + 200 - insectX, 510 - 300 - insectY, 445 + 200 - insectX, 500 - 300 - insectY);
	glColor3f(0.6, 0.6, 0.6);
	drawCurvedLine(16, 0, 456 + 200 - insectX, 510 - 300 - insectY, 45, 225);
	drawCurvedLine(0, 35, 475 + 200 - insectX, 465 - 300 - insectY, 0, 180);
}

void drawSpaceStation()
{
	glColor3f(0.7, 0.7, 0.7);
	drawModifiedCircle( 20, 70, 950, 550 + ty);
	glColor3f(1, 1, 1);
	drawTriangle(935, 590 + ty, 965, 590 + ty, 950, 520 + ty);
	glColor3f(0.8, 0.8, 0.8);
	drawCurvedLine(70, -20, 950, 550 + ty, 0, 180);
}

void drawBackground()
{
	drawSpaceStation();
	drawStars();
	drawSun();
	drawInsectBackground();
	drawInsectBackground2();
}

void drawPlayerTwoHair()
{
	for (int i = 0; i < 8; i++) 
	{
		glPushMatrix();

		glTranslatef(playerTwo[0], playerTwo[1] + 180, 0);

		glRotatef(45 * i, 0, 0, 1);

		glTranslatef(-playerTwo[0], -playerTwo[1] - 180, 0);

		glBegin(GL_TRIANGLES);

		glVertex3f(playerTwo[0] - 15, playerTwo[1] + 190, 0);
		glVertex3f(playerTwo[0] + 15, playerTwo[1] + 190, 0);
		glVertex3f(playerTwo[0], playerTwo[1] + 230, 0);

		glEnd();
		glPopMatrix();
	}
}

void drawPlayerTwo()
{
	glPushMatrix();
	glTranslatef(playerTwo[0], playerTwo[1], 0);
	glRotatef(20 * hitReactionTwo, 0, 0, 1);
	glTranslatef(-playerTwo[0], -playerTwo[1], 0);
	glColor3f(0, 0.9, 1);
	drawPlayerTwoHair();
	glColor3f(1, 1, 1);
	drawShirt(playerTwo[0] + 30, playerTwo[1] + 130, playerTwo[0] - 30, playerTwo[1] - 30, playerTwo[0] - 30, playerTwo[1] + 130, playerTwo[0] + 30, playerTwo[1] - 30);
	glColor3f(0, 0.9, 1);
	drawShirt(playerTwo[0] + 15, playerTwo[1] + 130, playerTwo[0] - 15, playerTwo[1] + 15, playerTwo[0] + 15, playerTwo[1] + 15, playerTwo[0] - 15, playerTwo[1] + 130);
	glColor3f(0.62, 0.5, 0.38);
	drawShirt(playerTwo[0] + 25, playerTwo[1] - 70, playerTwo[0] + 5, playerTwo[1] + 15, playerTwo[0] + 15, playerTwo[1] + 15, playerTwo[0] + 15, playerTwo[1] - 70);
	drawShirt(playerTwo[0] - 25, playerTwo[1] - 70, playerTwo[0] - 5, playerTwo[1] + 15, playerTwo[0] - 15, playerTwo[1] + 15, playerTwo[0] - 15, playerTwo[1] - 70);
	drawShirt(playerTwo[0] + 15, playerTwo[1] + 30, playerTwo[0] - 15, playerTwo[1] + 15, playerTwo[0] + 15, playerTwo[1] + 15, playerTwo[0] - 15, playerTwo[1] + 30);
	glColor3f(0.89, 0.76, 0.6);
	drawShirt(playerTwo[0] + 20, playerTwo[1] + 190, playerTwo[0] - 20, playerTwo[1] + 150, playerTwo[0] + 20, playerTwo[1] + 150, playerTwo[0] - 20, playerTwo[1] + 190);
	drawSemiCircle(20, 25, playerTwo[0], playerTwo[1] + 153, 180, 360);
	drawSemiCircle(20, 20, playerTwo[0], playerTwo[1] + 183, 0, 180);
	glColor3f(0, 0.9, 1);
	glLineWidth(3);
	drawCurvedLine(19, -5, playerTwo[0] - 2, playerTwo[1] + 185, 180, 360);
	glColor3f(1, 1, 1);
	drawModifiedCircle(10, 10, playerTwo[0] - 20, playerTwo[1] + 170);
	drawModifiedCircle(10, 10, playerTwo[0] + 2, playerTwo[1] + 170);
	glColor3f(0, 0, 0);
	drawModifiedCircle(2, 2, playerTwo[0] - 27, playerTwo[1] + 170);
	drawModifiedCircle(2, 2, playerTwo[0] - 5, playerTwo[1] + 170);
	glLineWidth(1.3);
	glColor3f(0, 0, 0);
	drawCurvedLine(-5, 0, playerTwo[0] - 9, playerTwo[1] + 152, 180, 360);
	drawCurvedLine(-5, 0, playerTwo[0] - 9, playerTwo[1] + 148, 0, 180);
	drawModifiedCircle(-2, 4, playerTwo[0] - 13, playerTwo[1] + 150);
	glEnd();
	glPopMatrix();
}

void drawPlayerTwoWeaponProjectile()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(posXTwo - 20, posYTwo - 7, 0);
	glVertex3f(posXTwo + 20, posYTwo - 7, 0);
	glVertex3f(posXTwo + 20, posYTwo + 7, 0);
	glVertex3f(posXTwo - 20, posYTwo + 7, 0);
	glEnd();
	glPopMatrix();
	glColor3f(0, 0, 0);
	drawCurvedLine(15, 0, posXTwo + 5, posYTwo + 4, 0, 180);
	drawCurvedLine(0, 11, posXTwo - 10, posYTwo - 7, 0, 180);
	drawLine(posXTwo - 20, posYTwo + 7, posXTwo - 11, posYTwo + 4);
	glColor3f(0.5, 0.5, 0.5);
	drawTriangle(posXTwo + 5, posYTwo - 7, posXTwo + 20, posYTwo - 7, posXTwo + 12.5, posYTwo - 25);
	glColor3f(0.19, 0.80, 0.19);
	drawSemiCircle(7, 10, posXTwo + 5, posYTwo + 5, 0, 180);
}

void hitTarget()
{
	if (hitReactionTwoBool && hitReactionTwo >= -20)
	{
		hitReactionTwo -= 0.1;
	}
	else 
	{
		hitReactionTwo = 0;
		hitReactionTwoBool = false;
	}
	if (hitReactionOneBool && hitReactionOne <= 20)
	{
		hitReactionOne += 0.1;
	}
	else
	{
		hitReactionOne = 0;
		hitReactionOneBool = false;

	}
}

void drawPlayerOne()
{
	glPushMatrix();
	glTranslatef(playerOne[0], playerOne[1], 0);
	glRotatef(20 * hitReactionOne, 0, 0, 1);
	glTranslatef(-playerOne[0], -playerOne[1], 0);
	glColor3f(1, 1, 1);
	drawShirt(playerOne[0] + 30, playerOne[1] + 130, playerOne[0] - 30, playerOne[1] - 30, playerOne[0] - 30, playerOne[1] + 130, playerOne[0] + 30, playerOne[1] - 30);
	glColor3f(0, 0.9, 1);
	drawShirt(playerOne[0] + 15, playerOne[1] + 130, playerOne[0] - 15, playerOne[1] + 15, playerOne[0] + 15, playerOne[1] + 15, playerOne[0] - 15, playerOne[1] + 130);
	glColor3f(0.62, 0.5, 0.38);
	drawShirt(playerOne[0] + 25, playerOne[1] - 70, playerOne[0] + 5, playerOne[1] + 15, playerOne[0] + 15, playerOne[1] + 15, playerOne[0] + 15, playerOne[1] - 70);
	drawShirt(playerOne[0] - 25, playerOne[1] - 70, playerOne[0] - 5, playerOne[1] + 15, playerOne[0] - 15, playerOne[1] + 15, playerOne[0] - 15, playerOne[1] - 70);
	drawShirt(playerOne[0] + 15, playerOne[1] + 30, playerOne[0] - 15, playerOne[1] + 15, playerOne[0] + 15, playerOne[1] + 15, playerOne[0] - 15, playerOne[1] + 30);
	glColor3f(0.89, 0.76, 0.6);
	drawShirt(playerOne[0] + 20, playerOne[1] + 190, playerOne[0] - 20, playerOne[1] + 150, playerOne[0] + 20, playerOne[1] + 150, playerOne[0] - 20, playerOne[1] + 190);
	drawSemiCircle(20, 25, playerOne[0], playerOne[1] + 153, 180, 360);
	glColor3f(1, 1, 1);
	drawTriangle(playerOne[0] + 10, playerOne[1] + 130, playerOne[0] - 10, playerOne[1] + 130, playerOne[0], playerOne[1] + 100);
	glColor3f(0, 0.9, 1);
	drawSemiCircle(25, 28, playerOne[0], playerOne[1] + 190, 0, 180);
	glLineWidth(3);
	drawCurvedLine(19, 5, playerOne[0] + 2, playerOne[1] + 181, 0, 180);
	glColor3f(1, 1, 1);
	drawModifiedCircle(10, 10, playerOne[0] + 17, playerOne[1] + 170);
	drawModifiedCircle(10, 10, playerOne[0] - 5, playerOne[1] + 170);
	glColor3f(0, 0, 0);
	drawModifiedCircle(2, 2, playerOne[0] + 24, playerOne[1] + 170);
	drawModifiedCircle(2, 2, playerOne[0] + 2, playerOne[1] + 170);
	glLineWidth(1.3);
	glColor3f(0, 0, 0);
	drawCurvedLine(5, 0, playerOne[0] + 9, playerOne[1] + 152, 180, 360);
	drawCurvedLine(5, 0, playerOne[0] + 9, playerOne[1] + 148, 0, 180);
	drawModifiedCircle(2, 4, playerOne[0] + 13, playerOne[1] + 150);
	glEnd();
	glPopMatrix();
}

void drawPlayerOneWeaponProjectile()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(posXOne - 20, posYOne - 7, 0);
	glVertex3f(posXOne + 20, posYOne - 7, 0);
	glVertex3f(posXOne + 20, posYOne + 7, 0);
	glVertex3f(posXOne - 20, posYOne + 7, 0);
	glEnd();
	glPopMatrix();
	glColor3f(0, 0, 0);
	drawCurvedLine(15, 0, posXOne - 4, posYOne + 4, 0, 180);
	drawCurvedLine(0, 11, posXOne + 12, posYOne - 7, 0, 180);
	drawLine(posXOne + 20, posYOne + 7, posXOne + 12, posYOne + 4);
	glColor3f(0.5, 0.5, 0.5);
	drawTriangle(posXOne - 5, posYOne - 7, posXOne - 20, posYOne - 7, posXOne - 12.5, posYOne - 25);
	glColor3f(0.19, 0.80, 0.19);
	drawSemiCircle(7, 10, posXOne - 5, posYOne + 5, 0, 180);
}

void drawPortal()
{
	glPushMatrix();
	glColor3f(0, 1, 0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float rad = i * radian;
		glVertex2f(640 + cos(rad) * 30, ty + 180 + sin(rad) * 180);
	}
	glEnd();
	glPopMatrix();
	glLineWidth(4);
	drawCurvedLineForPortal(15, 70, 640, 280 + ty, 0, 90);
	drawCurvedLineForPortal(15, 70, 640, 270 + ty, 90, 180);
	drawCurvedLineForPortal(15, 70, 640, 100 + ty, 180, 270);
	drawCurvedLineForPortal(15, 70, 645, 120 + ty, 270, 360);
	drawCurvedLineForPortal(15, 80, 630, 200 + ty, 135, 225);
	drawCurvedLineForPortal(15, 80, 650, 200 + ty, 225, 45);
	drawModifiedCircleUnFilledForPortal(5 + hit, 10 + hit, 640, 190 + ty);
	drawCurvedLineForPortal(15, 70, 670 - hit, 280 + ty, 0, 90);
	drawCurvedLineForPortal(15, 70, 610 + hit, 270 + ty, 90, 180);
	drawCurvedLineForPortal(15, 70, 610 + hit, 100 + ty, 180, 270);
	drawCurvedLineForPortal(15, 70, 675 - hit, 120 + ty, 270, 360);
	drawCurvedLineForPortal(15, 80, 600 + hit, 200 + ty, 135, 225);
	drawCurvedLineForPortal(15, 80, 680 - hit, 200 + ty, 225, 45);
}

void drawSpaceShip()
{
	glColor3f(0.5, 0.5, 0.5);
	drawSemiCircle(150, 37.5, 640 + tx, 425 + ty, 180, 360);
	glColor3f(0.5, 0.5, 0.5);
	drawModifiedCircle(200, 50, 640 + tx, 450 + ty);
	glColor3f(0.6, 0.6, 0.6);
	drawModifiedCircleUnFilled(200, 50, 640 + tx, 450 + ty);
	glColor3f(0.77, 1, 1);
	drawSemiCircle(110, 110, 640 + tx, 460 + ty, 0, 180);
	glColor3f(0.9, 0.9, 0.9);
	drawSemiCircle(110, 15, 640 + tx, 463 + ty, 180, 360);
	glColor3f(1, 1, 0);
	drawShirt(653 + tx, 487 + ty, 623 + tx, 447 + ty, 653 + tx, 447 + ty, 623 + tx, 487 + ty);
	glLineWidth(5);
	glColor3f(0.76, 0.35, 0.07);
	drawCurvedLine(85, 25, tx + 530, ty + 440, 90, 180);
	drawCurvedLine(85, 25, tx + 750, ty + 440, 0, 90);
	drawCurvedLine(37, 40, tx + 690, ty + 407, 0, 90);
	drawCurvedLine(37, 40, tx + 590, ty + 407, 90, 180);
	glColor3f(0, 0, 0);
	drawModifiedCircle(4, 15, lightPositionDown[0] + tx, lightPositionDown[1] + ty);
	drawModifiedCircle(4, 15, lightPositionUp[0] + tx, lightPositionUp[1] + ty);
	glColor3f(0.9, 0.9, 0.9);
	drawSemiCircle(4, 15, slightPositionDown[0] + tx, slightPositionDown[1] + ty, shadeangle[0], shadeangle[1]);
	drawSemiCircle(4, 15, slightPositionUp[0] + tx, slightPositionUp[1] + ty, shadeangle[0], shadeangle[1]);
	glColor3f(0.94, 0.76, 0.49);
	drawModifiedCircle(30, 30, 640 + tx, 500 + ty);
	glColor3f(1, 1, 1);
	drawModifiedCircle(10, 10, leftEyePosition[0] + tx, leftEyePosition[1] + ty);
	drawModifiedCircle(10, 10, rightEyePosition[0] + tx, rightEyePosition[1] + ty);
	glColor3f(0, 0, 0);
	drawModifiedCircle(2, 2, leftPupilPosition[0] + tx, leftPupilPosition[1] + ty);
	drawModifiedCircle(2, 2, rightPupilPosition[0] + tx, rightPupilPosition[1] + ty);
	glColor3f(0.55,0.27,0.07);
	drawSemiCircle(32, 35, 640 + tx, 495 + ty, hairangle[0], hairangle[1]);
	glLineWidth(1);
	drawCurvedLine(10, 5, 640 + tx, 480 + ty, 45, 135);
}

void portalAnimEffect()
{
	if (portalHit)
	{
		if (soundEffect) 
		{
			PlaySound(TEXT("Rick and Morty Portal Gun Sound Effect.wav"), NULL, SND_ASYNC | SND_FILENAME);
			soundEffect = false;
		}
		if (hit < 30 && !portalHitRestart)
		{
			hit += 0.022;
		}
		else
		{
			portalHitRestart = true;
			if (hit > 0)
			{
				hit -= 0.2;
			}
			else
			{
				hit = 0;
				portalHitRestart = false;
				portalHit = false;
			}
		}
	}
}

void gameEnd()
{
	if ( playerOneHP == 0 || playerTwoHP == 0 )
	{
		endGame = true;
	}
}

void Display() {
	if (!endGame) {
		glClear(GL_COLOR_BUFFER_BIT);

		//draw background
		drawBackground();
		insectMove();
		insectWingMove();

		//portal effect
		portalAnimEffect();

		//Weapon Hold power
		weaponPowerBlast();

		//draw Bezier curve
		drawBezierCurve();
		hitTarget();

		//draws cloud above wall
		drawSpaceShip();
		spaceShipMov();

		//regain Point size
		glPointSize(25);

		//draws a playerOne at the origin
		drawPlayerOneWeaponProjectile();
		drawPlayerOne();
		glScalef(1, 1, 1);

		//draws a playerTwo the origin
		drawPlayerTwoWeaponProjectile();
		drawPlayerTwo();
		glScalef(1, 1, 1);

		//draws a wall in between pixels
		drawPortal();

		//draws PowerBar
		drawPowerBar();

		//draws healthBar
		healthBarOne();
		healthBarTwo();

		gameEnd();

		glEnd();
		glFlush();
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("OpenGL - 2D Template");
	glutDisplayFunc(Display);
	glutMouseFunc(actM);

	glLineWidth(25);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 1280, 0.0, 720);
	glutIdleFunc(idleFunc);
	glutMainLoop();
}