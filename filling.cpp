#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <stack>
#include <unistd.h>

using namespace std;

class Point{
public:
	int x,y;
	Point(int xi,int yi):x(xi),y(yi){}
};

vector<Point> polygon;

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);

	for(int i=0;i<polygon.size();i++){
		glVertex2i(polygon[i].x,polygon[i].y);
	}

	glEnd();
	glFlush();
}

float fillColor[3] = {1,0,0};
float bgColor[3] = {1,1,1};

void setPixel(Point point){
	glColor3f(fillColor[0],fillColor[1],fillColor[2]);
	glBegin(GL_POINTS);
	glVertex2i(point.x,point.y);
	glEnd();
	glFlush();
}


bool isFilled(Point point){
	float color[3];
	glReadPixels(point.x,point.y,1,1,GL_RGB,GL_FLOAT,color);
	// cout<<color[0]<<" "<<color[1]<<" "<<color[2]<<endl;
	return !(color[0]==bgColor[0]&&color[1]==bgColor[1]&&color[2]==bgColor[2]);
}

void floodFill(Point seed){
	stack<Point> fillStack;
	fillStack.push(seed);
	while(!fillStack.empty()){
		Point point = fillStack.top();
		fillStack.pop();
		if(isFilled(point))
			continue;
		setPixel(point);
		fillStack.push(Point(point.x+1,point.y));
		fillStack.push(Point(point.x,point.y+1));
		fillStack.push(Point(point.x,point.y-1));
		fillStack.push(Point(point.x-1,point.y));
	}
}


void onMouseClick(int button,int state,int x,int y){
	if(state==GLUT_DOWN)
		floodFill(Point(x,400-y));
}


int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Flood Filling");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);
	int n,x,y;
	cin>>n;
	while(n--){
		cin>>x>>y;
		polygon.push_back(Point(x,y));
	}
	glutMouseFunc(onMouseClick);
	glutMainLoop();
}