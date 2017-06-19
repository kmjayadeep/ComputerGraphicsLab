#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>

using namespace std;

class Point{
public:
	int x,y;
	Point(int xi,int yi):x(xi),y(yi){}
};

vector<Point> polygon;
int spacing;

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
float boundaryColor[3] = {0,0,0};

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

void hatching(Point seed){
	queue<Point> fillQueue;
	fillQueue.push(seed);
	while(!fillQueue.empty()){
		Point point = fillQueue.front();
		// cout<<"Point "<<point.x<<" "<<point.y<<endl;
		fillQueue.pop();
		Point left = point;
		Point right = point;
		while(!isFilled(left)&&left.x>0){
			left.x--;
		}
		// cout<<"here "<<endl;
		while(!isFilled(right)&&right.x<600){
			right.x++;
		}
		if(left.x==0||right.x==600)
			continue;
		for(int i=left.x+1;i<right.x;i++)
			setPixel(Point(i,point.y));
		Point top((left.x+right.x)/2,point.y+spacing);
		Point bottom((left.x+right.x)/2,point.y-spacing);
		if(!isFilled(top))
			fillQueue.push(top);
		if(!isFilled(bottom))
			fillQueue.push(bottom);
		usleep(20000);
	}
}


void onMouseClick(int button,int state,int x,int y){
	if(state==GLUT_DOWN)
		hatching(Point(x,400-y));
}


int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Polygon Hatching");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);
	int n,x,y;
	cin>>n;
	while(n--){
		cin>>x>>y;
		polygon.push_back(Point(x,y));
	}
	cin>>spacing;
	glutMouseFunc(onMouseClick);
	glutMainLoop();
}