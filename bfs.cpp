#include <GL/glut.h>
#include <cmath>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

float initColor[3] = {0.5, 0.5, 0.5};
float inStackColor[3] = {0, 0.5, 0.5};
float processedColor[3] = {0, 1, 0};
float processedLineColor[3] = {0, 1, 1};

void drawCircle(int xc,int yc, int r,float color[3]){
	glColor3fv(color);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xc, yc);
	for(int i = 0; i <= 360;i+=15){
		float angle = 3.14*i/180;
		glVertex2f(xc+r*cos(angle),yc+r*sin(angle));
	}
	glEnd();
	glFlush();
}

void drawLine(int x1, int y1, int x2, int y2, float color[3]){
	glColor3fv(color);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glFlush();
}

class Point{
public:
	int x,y;
	Point(int xi,int yi):x(xi),y(yi){}
};

class Graph{
	int V,E;
	vector<Point> coordinates;
	vector<vector<int>> adj;
	vector<bool> visited;
public:
	Graph(){
	}
	void input(){
		cin>>V>>E;
		adj = vector<vector<int> >(V, vector<int>());
		visited = vector<bool>(V,false);
		for(int i=0;i<V;i++){
			int x,y;
			cin>>x>>y;
			coordinates.push_back(Point(x,y));
		}
		for(int i=0;i<E;i++){
			int u,v;
			cin>>u>>v;
			adj[u-1].push_back(v-1);
			adj[v-1].push_back(u-1);
		}
	}
	void drawGraph(){
		for(int i=0;i<V;i++){
			drawCircle(coordinates[i].x,coordinates[i].y,20,initColor);
		}
		for(int i=0;i<V;i++){
			for(int j=0;j<adj[i].size();j++){
				drawLine(coordinates[i].x,coordinates[i].y,coordinates[adj[i][j]].x,coordinates[adj[i][j]].y,initColor);
			}
		}
	} 

	void traverse(){
		drawGraph();
		bfs();
	}

	void bfs(){
		visited[0] = true;
		queue<int> q;
		q.push(0);
		while(!q.empty()){
			usleep(1000000);
			int node = q.front();
			q.pop();
			drawCircle(coordinates[node].x,coordinates[node].y,20,processedColor);
			for (int i=0;i<adj[node].size();i++) {
				q.push(adj[node][i]);
			}
		}
	}
};

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	Graph g;
	g.input();
	g.traverse();
	glFlush();
}


int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(800,400);
	glutCreateWindow("DFS");
	gluOrtho2D(0,800,0,400);
	glutDisplayFunc(draw);
	glutMainLoop();
}