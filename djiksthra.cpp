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

class Vertex{
public:
	int x,y;
	int distance;
	vector<pair<Vertex*,int>> adj;
	Vertex* parent;
	bool visited;
	Vertex(int xi,int yi){
		x = xi;
		y = yi;
		distance = INT_MAX;
		visited = false;
	}
	void adjust(pair<Vertex*,int> adjacent){
		if(adjacent.first->distance > adjacent.second + distance){
			adjacent.first->distance = adjacent.second+distance;
			adjacent.first->parent = this;
		}
	}
};

class Graph{
	int V,E;
	vector<Vertex> coordinates;
	vector<vector<int>> adj; //only for drawing
	int destination;
public:
	Graph(){
	}
	void input(){
		cin>>V>>E;
		adj = vector<vector<int> >(V, vector<int>());
		for(int i=0;i<V;i++){
			int x,y;
			cin>>x>>y;
			coordinates.push_back(Vertex(x,y));
		}
		for(int i=0;i<E;i++){
			int u,v,w;
			cin>>u>>v>>w;
			adj[u-1].push_back(v-1);
			adj[v-1].push_back(u-1);
			coordinates[u-1].adj.push_back({&coordinates[v-1],w});
			coordinates[v-1].adj.push_back({&coordinates[u-1],w});
		}
		cin>>destination;
		destination--;
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

	Vertex* getMin(){
		Vertex* min = NULL;
		for(int i=0;i<coordinates.size();i++){
			if(coordinates[i].visited)
				continue;
			if(min==NULL){
				min = &coordinates[i];
				continue;
			}
			if(coordinates[i].distance<min->distance)
				min = &coordinates[i];
		}
		return min;
	}

	void djiksthra(){
		coordinates[0].distance = 0;
		coordinates[0].parent = NULL;
		Vertex* min;
		while((min=getMin())!=NULL){
			drawCircle(min->x,min->y,20,processedColor);
			for(int i=0;i<min->adj.size();i++){
				min->adjust(min->adj[i]);
			}
			min->visited = true;
			usleep(500000);
		}
		glLineWidth(2);
		Vertex* v = &coordinates[destination];
		Vertex* parent = v->parent;
		while(parent!=NULL){
			drawLine(v->x,v->y,parent->x,parent->y,processedLineColor);
			cout<<v->x<<" "<<v->y<<"  to  "<<parent->x<<" "<<parent->y<<endl;
			v = parent;
			parent = parent->parent;
			usleep(500000);
		}
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