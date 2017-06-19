#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

int xMin,xMax,yMin,yMax;

class Point{
public:
	int x,y;
	Point(int x1,int y1){
		x = x1;
		y = y1;
	}
	void computeIntersection(int outCode,Point second){
		if(outCode&TOP){
			x = x + (second.x - x)*(yMax-y)/(second.y-y);
			y = yMax;
		}
		if(outCode&BOTTOM){
			x = x + (second.x - x)*(yMin-y)/(second.y-y);
			y = yMin;
		}
		if(outCode&RIGHT){
			y = y + (second.y-y)*(xMax-x)/(second.x-x);
			x = xMax;
		}
		if(outCode&LEFT){
			y = y + (second.y-y)*(xMin-x)/(second.x-x);
			x = xMin;
		}
	}
};

vector<pair<Point,Point>> lines;

int computeOutcode(Point p){
	int code = INSIDE;
	if(p.x<xMin)
		code|=LEFT;
	else if(p.x>xMax)
		code|=RIGHT;
	if(p.y<yMin)
		code|=BOTTOM;
	else if(p.y>yMax)
		code|=TOP;
	return code;
}

void clip(){
	vector<pair<Point,Point>> result;
	for(int i=0;i<lines.size();i++){
		pair<Point,Point> line = lines[i];
		int outCode1 = computeOutcode(line.first);
		int outCode2 = computeOutcode(line.second);
		if(outCode1==INSIDE&&outCode2==INSIDE){
			result.push_back(line);
			continue;
		}
		if((outCode1&outCode2)!=INSIDE)
			continue;

		if(outCode1!=INSIDE){
			line.first.computeIntersection(outCode1,line.second);
		}
		if(outCode2!=INSIDE){
			line.second.computeIntersection(outCode2,line.first);
		}

		result.push_back(line);

	}

	lines = result;
}

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glBegin(GL_LINES);

	glVertex2i(xMin,yMin);
	glVertex2i(xMin,yMax);

	glVertex2i(xMin,yMax);
	glVertex2i(xMax,yMax);

	glVertex2i(xMax,yMax);
	glVertex2i(xMax,yMin);

	glVertex2i(xMax,yMin);
	glVertex2i(xMin,yMin);


	for(int i=0;i<lines.size();i++){
		glVertex2i(lines[i].first.x,lines[i].first.y);
		glVertex2i(lines[i].second.x,lines[i].second.y);
	}

	clip();
	
	glEnd();
	glLineWidth(2);
	glBegin(GL_LINES);

	glColor3f(0.5,0.6,0.7);

	for(int i=0;i<lines.size();i++){
		glVertex2i(lines[i].first.x,lines[i].first.y);
		glVertex2i(lines[i].second.x,lines[i].second.y);
	}

	glEnd();

	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Line Clipping");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);

	int n,x,y;
	cin>>xMin>>xMax>>yMin>>yMax>>n;
	while(n--){
		cin>>x>>y;
		Point p1(x,y);
		cin>>x>>y;
		Point p2(x,y);
		lines.push_back({p1,p2});
	}
	glutMainLoop();
	return 0;
}