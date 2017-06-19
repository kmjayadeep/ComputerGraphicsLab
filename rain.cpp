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
vector<Point> umbrella;
int uXMin,uXMax,uYMax;

bool isVisible(Point point){
	if(point.x<uXMin||point.x>uXMax||(point.y)>uYMax)
		return true;
	return false;
}

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	for(int i=0;i<rainDrops.size();i++){
		if(isVisible(rainDrops[i])){
			glVertex2i(rainDrops[i].x,rainDrops[i].y);
			glVertex2i(rainDrops[i].x,rainDrops[i].y+10);
		}
		rainDrops[i].y--;
		if(rainDrops[i].y<0)
			rainDrops[i].y=600;
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<umbrella.size();i++){
		glVertex2i(umbrella[i].x,umbrella[i].y);
		umbrella[i].x++;
	}
	uXMax++;
	uXMin++;
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

	umbrella.push_back(Point(125,200));
	umbrella.push_back(Point(50,200));
	umbrella.push_back(Point(125,230));
	umbrella.push_back(Point(200,200));
	umbrella.push_back(Point(125,200));
	umbrella.push_back(Point(125,120));
	umbrella.push_back(Point(100,120));
	umbrella.push_back(Point(125,120));
	uXMin = 50;
	uXMax = 200;
	uYMax = 230;

	glutMainLoop();
}