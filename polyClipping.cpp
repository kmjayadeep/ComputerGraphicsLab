#include <iostream>
#include <GL/glut.h>
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
		x=x1;y=y1;
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

vector<Point> polygon;

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
	for(int i=0;i<4;i++){
		vector<Point> result;
		int side;
		switch(i){
			case 0:side=LEFT;break;
			case 1:side=TOP;break;
			case 2:side=RIGHT;break;
			case 3:side=BOTTOM;break;
		}
		// cout<<"side"<<" "<<i<<endl;
		for(int i=0;i<polygon.size()-1;i++){
			Point left = polygon[i];
			Point right = polygon[i+1];
			int outLeft = computeOutcode(left);
			int outRight = computeOutcode(right);
			if((outLeft&side)!=side&&(outRight&side)!=side){
				result.push_back(right);
				// cout<<"Case 1 "<<left.x<<" "<<left.y<<" "<<right.x<<" "<<right.y<<endl;
			}else if((outLeft&side)!=side){
				left.computeIntersection(side,right);
				result.push_back(left);
				// cout<<"Case 2"<<endl;
			}else if((outRight&side)!=side){
				left.computeIntersection(side,right);
				result.push_back(left);
				result.push_back(right);
				// cout<<"Case 4"<<endl;
			}else{
				// cout<<"Case 3"<<endl;
			}
		}
		polygon = result;
		polygon.push_back(polygon[0]);
	}
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

	glEnd();

	glBegin(GL_LINE_LOOP);

	for(int i=0;i<polygon.size();i++){
		glVertex2i(polygon[i].x,polygon[i].y);
	}

	glEnd();
	glLineWidth(2);
	clip();
	glColor3f(0.5,0.6,0.7);

	glBegin(GL_LINE_LOOP);
	for(int i=0;i<polygon.size();i++){
		glVertex2i(polygon[i].x,polygon[i].y);
	}
	glEnd();

	glFlush();

}

int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Polygon Clipping");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);

	int n,x,y;
	cin>>xMin>>xMax>>yMin>>yMax>>n;
	while(n--){
		cin>>x>>y;
		polygon.push_back(Point(x,y));
	}
	polygon.push_back(polygon[0]);

	glutMainLoop();
}