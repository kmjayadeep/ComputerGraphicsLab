#include <GL/glut.h>
#include <cmath>
#include <unistd.h>

int angle = 45;
int inc = 1;

void drawCircle(int xc,int yc, int r){
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<=360;i++){
		float angle = 3.14*i/180;
		glVertex2f(xc+r*cos(angle),yc+r*sin(angle));
	}
	glEnd();
}

void drawPendulum(int angle){
	float theta = 3.14*angle/180;
	glColor3f(0,0,0);
	int x1=300,y1=330;
	int x2,y2,line=250;
	int r1=20,r2=50;
	drawCircle(x1,y1,r1);
	x2 = x1-line*cos(theta);
	y2 = y1-line*sin(theta);
	glBegin(GL_LINES);
	glVertex2f(x1-r1*cos(theta),y1-r1*sin(theta));
	glVertex2f(x2+r2*cos(theta),y2+r2*sin(theta));
	glEnd();
	drawCircle(x2,y2,r2);
}

void drawPendulum(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	drawPendulum(angle);
	if(angle<45||angle>135)
		inc*=-1;
	angle+=inc;
	glFlush();
	usleep(10000);
}


int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Pendulum");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(drawPendulum);
	glutIdleFunc(drawPendulum);
	glutMainLoop();
}