#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <random>
#include <unistd.h>

using namespace std;

class Point{
public:
	int x,y;
	Point(int x1,int y1){
		x = x1; y = y1;
	}
};

vector<Point> rainDrops;

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	for(int i=0;i<rainDrops.size();i++){
		glVertex2i(rainDrops[i].x,rainDrops[i].y);
		glVertex2i(rainDrops[i].x,rainDrops[i].y+10);
		rainDrops[i].y--;
		if(rainDrops[i].y<0)
			rainDrops[i].y=600;
	}
	glEnd();
	usleep(10000);
	glFlush();
}

int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Rain");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);
	glutIdleFunc(draw);

	//create random drops
	for(int i=0;i<600;i+=20){
		for(int j=rand()%20;j<600;j+=50)
			rainDrops.push_back(Point(i,j));
	}


	glutMainLoop();
}