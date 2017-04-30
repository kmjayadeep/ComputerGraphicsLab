#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void ddaLine(){
	int x1 = 10,y1 = 30;
	int x2 = 100,y2 = 150;
	float step = max(abs(x1-x2),abs(y1-y2));
	float dx = (x2-x1)/step;
	float dy = (y2-y1)/step;
	float x = x1;
	float y = y1;

	glBegin(GL_POINTS);

	while(step--){
		glVertex2f(x,y);
		x+=dx;
		y+=dy;
	}

	glEnd();
}

void bresenhalmLine(){
	int x1 = 200,y1 = 40;
	int x2 = 400,y2 = 150;

	int dx = x2 - x1;
	int dy = y2 - y1;
	int p = 2*dx - dy;
	int x = x1;
	int y = y1;
	glBegin(GL_POINTS);
	while(x<x2){
		glVertex2i(x,y);
		x++;
		if(p<0)
			p+=2*dy;
		else{
			y++;
			p+=2*(dy-dx);
		}
	}	
	glEnd();
}

void drawLines(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	ddaLine();
	glColor3f(0.5,0.2,0.8);
	bresenhalmLine();
	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600,400);
	glutCreateWindow("Lines");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(drawLines);
	glutMainLoop();
	return 0;
}