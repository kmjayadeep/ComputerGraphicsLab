#include <GL/glut.h>
#include <cmath>
#include <unistd.h>
#include <random>

float car1x=10,car2x=10;
float car1speed,car2speed;

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

void drawCar(int xc,int yc){
	glBegin(GL_LINE_LOOP);
	glVertex2i(xc,yc);
	glVertex2i(xc,yc+60);
	glVertex2i(xc+60,yc+60);
	glVertex2i(xc+70,yc+100);
	glVertex2i(xc+190,yc+100);
	glVertex2i(xc+200,yc+60);
	glVertex2i(xc+260,yc+60);
	glVertex2i(xc+260,yc);
	glVertex2i(xc+250,yc);

	for(int i=0;i<=180;i++){
		float theta = 3.1426*i/180;
		glVertex2f(xc+225+25*cos(theta),yc+25*sin(theta));
	}

	glVertex2i(xc+200,yc);
	glVertex2i(xc+60,yc);

	for(int i=0;i<=180;i++){
		float theta = 3.1426*i/180;
		glVertex2f(xc+35+25*cos(theta),yc+25*sin(theta));
	}

	glEnd();

	float angle = 360 - xc*180/3.14/21;

	drawCircle(xc+35,yc,21);
	drawSpokes(xc+35,yc,21,angle);
	drawCircle(xc+225,yc,21);
	drawSpokes(xc+225,yc,21,angle);

}

void drawCars(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.4,0.3,0.2);
	drawCar(car1x,30);
	glColor3f(0.2,0.5,0.7);
	drawCar(car2x,200);
	car1x+=car1speed;
	car2x+=car2speed;
	usleep(10000);
	glFlush();
	if(car1x>800||car2x>800){
		car1x = 0;
		car2x = 0;
	}
}

int main(int argc,char* argv[]){

	car1speed = rand()%10/10.0+1;
	car2speed = rand()%10/10.0+1;

	glutInit(&argc,argv);
	glutInitWindowSize(800,400);
	glutCreateWindow("Car Race");
	gluOrtho2D(0,800,0,400);
	glutDisplayFunc(drawCars);
	glutIdleFunc(drawCars);
	glutMainLoop();
}