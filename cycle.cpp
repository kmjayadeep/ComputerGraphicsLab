#include <GL/glut.h>
#include <cmath>
#include <unistd.h>
#include <random>

void drawCircle(int xc,int yc, int r){
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<=360;i++){
		float angle = 3.14*i/180;
		glVertex2f(xc+r*cos(angle),yc+r*sin(angle));
	}
	glEnd();
}

void drawSpokes(int xc,int yc,int r, int angle){
	glBegin(GL_LINES);
	for(int i=angle;i<angle+360;i+=30){
		glVertex2i(xc,yc);
		float t = 3.14*i/180;
		glVertex2i(xc+r*cos(t),yc+r*sin(t));
	}
	glEnd();
}

void drawCycle(int xc,int yc){

	drawCircle(xc,yc,27);	
	drawCircle(xc+80,yc,27);	
	drawCircle(xc+52,yc+60,10);	

	glBegin(GL_LINES);
	glVertex2i(xc,yc);
	glVertex2i(xc+20,yc+35);
	glVertex2i(xc-2,yc+2);
	glVertex2i(xc+20,yc+35);

	glVertex2i(xc+80,yc);
	glVertex2i(xc+60,yc+35);
	glVertex2i(xc+80+2,yc+2);
	glVertex2i(xc+60,yc+35);

	glVertex2i(xc+20,yc+35);
	glVertex2i(xc+60,yc+35);

	glVertex2i(xc+15,yc+45);
	glVertex2i(xc+40,yc);

	glVertex2i(xc+40,yc);
	glVertex2i(xc+70,yc+45);


	glVertex2i(xc+45,yc+54);
	glVertex2i(xc+28,yc+37);
	glVertex2i(xc+28,yc+37);
	glVertex2i(xc+40,yc+5);


	glVertex2i(xc+40,yc+50);
	glVertex2i(xc+68,yc+43);

	glVertex2i(xc+38,yc+48);
	glVertex2i(xc+67,yc+42);


	glEnd();

}

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.4,0.3,0.2);
	drawCycle(50,50);
	glColor3f(0.2,0.5,0.7);
	glFlush();
}

int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(800,400);
	glutCreateWindow("Cycle on hill");
	gluOrtho2D(0,800,0,400);
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutMainLoop();
}