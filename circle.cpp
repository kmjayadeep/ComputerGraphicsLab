#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;


void pixel8(int xc,int yc,int x,int y){
	glVertex2i(xc+x,yc+y);
	glVertex2i(xc+y,yc+x);
	glVertex2i(xc-y,yc+x);
	glVertex2i(xc-x,yc+y);
	glVertex2i(xc-x,yc-y);
	glVertex2i(xc-y,yc-x);
	glVertex2i(xc+y,yc-x);
	glVertex2i(xc+x,yc-y);
}

void midPointCircle(){
	int xc = 200, yc = 200;
	int r = 100;


	int x=0;
	int y=r;
	int Pk=1-r;
		
	glBegin(GL_POINTS);
	pixel8(xc,yc,x,y);
	while(x<y){
		if(Pk<0){
			x=x+1;
			Pk=Pk+(2*x)+1;
		}
		else{
			x=x+1;
			y=y-1;
			Pk=Pk+(2*x)-(2*y)+1;
		}
		pixel8(xc,yc,x,y);
	}
	glEnd();

}

void bresenhalmCircle(){
	int xc = 370, yc = 320;
	int r = 70;


	int x=0;
	int y=r;
	int p = 3-2*r;
	glBegin(GL_POINTS);
	pixel8(xc,yc,x,y);
	while(x<=y){
		if(p<0)
			p = p + 4*x + 6;
		else{
			y--;
			p = p + 4*(x-y) + 10;
		}
		pixel8(xc,yc,x,y);
		x++;
	}
	glEnd();
}

void drawCircles(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	midPointCircle();
	glColor3f(0.5,0.2,0.8);
	bresenhalmCircle();
	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Circles");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(drawCircles);
	glutMainLoop();
	return 0;
}