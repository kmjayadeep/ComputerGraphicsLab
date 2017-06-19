#include <GL/glut.h>
#include <cmath>
#include <climits>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

float initColor[3] = {0.5, 0.5, 0.5};
float processedColor[3] = {0, 0.5, 0.5};
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
	Point(int xi,int yi){
		x = xi;
		y = yi;
	}
};

class Graph{
	int V,E;
	vector<Point> coordinates;
	vector<vector<int>> adj;
	vector<int> parent;
	vector<int> distance;
	vector<int> visited;
	int destination;
public:
	Graph(){
	}
	void input(){
		cin>>V>>E;
		adj = vector<vector<int>>(V, vector<int>(V,0)); //initialize 2d VxV matrix with 0
		distance = vector<int>(V,INT_MAX);
		visited = vector<int>(V,false);
		parent = vector<int>(V,-1);
		for(int i=0;i<V;i++){
			int x,y;
			cin>>x>>y;
			coordinates.push_back(Point(x,y));
		}
		for(int i=0;i<E;i++){
			int u,v,w;
			cin>>u>>v>>w;
			adj[u-1][v-1] = w;
			adj[v-1][u-1] = w;
		}
		cin>>destination;
		destination--;
	}
	void drawGraph(){
		for(int i=0;i<V;i++){
			drawCircle(coordinates[i].x,coordinates[i].y,20,initColor);
		}
		for(int i=0;i<V;i++){
			for(int j=0;j<V;j++){
				if(adj[i][j]){
					drawLine(coordinates[i].x,coordinates[i].y,coordinates[j].x,coordinates[j].y,initColor);
				}
			}
		}
	}

	int getMin(){
		int min = -1;
		for(int i=0;i<coordinates.size();i++){
			if(visited[i])
				continue;
			if(min==-1){
				min = i;
				continue;
			}
			if(distance[i]<distance[min])
				min = i;
		}
		return min;
	}

	void djiksthra(){
		distance[0] = 0;
		int min;
		while((min=getMin())!=-1){
			drawCircle(coordinates[min].x,coordinates[min].y,20,processedColor);
			for(int j=0;j<V;j++){
				if(adj[min][j]){
					if(distance[j]>distance[min]+adj[min][j]){
						distance[j] = distance[min]+adj[min][j];
						parent[j] = min;
					}
				}
			}
			visited[min] = true;
			usleep(500000);
		}
		glLineWidth(2);
		int v = destination;
		int parentNode = parent[v];
		while(parentNode!=-1){
			drawLine(coordinates[v].x,coordinates[v].y,coordinates[parentNode].x,coordinates[parentNode].y,processedLineColor);
			int weight = adj[v][parentNode];
			cout<<v+1<<" to "<<parentNode+1<<" : "<<weight<<endl;
			v = parentNode;
			parentNode = parent[parentNode];
			usleep(500000);
		}
		cout<<"Total distance : "<<distance[destination]<<endl;
		for(int i=0;i<V;i++){
			drawCircle(coordinates[i].x,coordinates[i].y,20,processedColor);
		}
	}
};

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	Graph g;
	g.input();
	g.drawGraph();
	g.djiksthra();
	glFlush();
}


int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(800,400);
	glutCreateWindow("Djiksthra");
	gluOrtho2D(0,800,0,400);
	glutDisplayFunc(draw);
	glutMainLoop();
}