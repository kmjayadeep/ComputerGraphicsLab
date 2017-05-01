#include <GL/glut.h>
#include <cmath>
#include <unistd.h>
#include <random>

using namespace std;

int x = 0;
int y = 20;

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

void drawCycle(int xc,int yc,int angle){
	xc+=27;
	yc+=27;

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
	int drawX=x,drawY=y;
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.4,0.3,0.2);

	glBegin(GL_LINE_LOOP);
	glVertex2i(0,20);
	glVertex2i(100,20);
	glVertex2i(400,120);
	glVertex2i(600,120);
	glVertex2i(800,20);
	glEnd();

	glColor3f(0.2,0.5,0.7);
	glPushMatrix();
	x++;
	float angle=0;

	glTranslatef(min(x,100),y,0);
	if(x>100){
		angle=19.5;
		glRotatef(angle,0,0,1);
		glTranslatef(min(x-100,300),0,0);
	}
	if(x>400){
		glRotatef(-angle,0,0,1);
		glTranslatef(min(x-400,200),0,0);
		angle=0;
	}
	if(x>600){
		angle=335;
		glRotatef(angle,0,0,1);
		glTranslatef(x-600,0,0);
	}
	if(x>=800){
		x=0;
		y=20;
		angle=0;
	}
	drawCycle(0,0,angle);
	glPopMatrix();
	glFlush();
	usleep(10000);
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