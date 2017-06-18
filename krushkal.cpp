#include <GL/glut.h>
#include <cmath>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>

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

class DisjointSets{
	vector<int> parent,rank;
	int n;
public:
	DisjointSets(int n){
		this->n = n;
		parent = vector<int>(n);
		rank = vector<int>(n,0);
		for(int i=0;i<n;i++){
			parent[i] = i;
		}
	}

	int find(int node){
		if(node!=parent[node])
			parent[node] = find(parent[node]);
		return parent[node];
	}

	int merge(int x,int y){
		x = find(x);
		y = find(y);

		if(rank[x]>rank[y])
			parent[y] = x;
		else
			parent[x] = y;

		if(rank[x]==rank[y])
			rank[y]++;
	}
};

class Graph{
	int V,E;
	vector<Point> coordinates;
	vector<pair<int,pair<int,int>>> edges; //vector of weight and node pair
public:
	Graph(){
	}
	void input(){
		cin>>V>>E;
		for(int i=0;i<V;i++){
			int x,y;
			cin>>x>>y;
			coordinates.push_back(Point(x,y));
		}
		for(int i=0;i<E;i++){
			int u,v,w;
			cin>>u>>v>>w;
			edges.push_back({w,{u-1,v-1}});
		}
	}
	void drawGraph(){
		for(int i=0;i<V;i++){
			drawCircle(coordinates[i].x,coordinates[i].y,20,initColor);
		}
		for(int i=0;i<edges.size();i++){
			pair<int,int> edge = edges[i].second;
			drawLine(coordinates[edge.first].x,coordinates[edge.first].y,coordinates[edge.second].x,coordinates[edge.second].y,initColor);
		}
	}

	void krushkalMST(){
		sort(edges.begin(), edges.end());
		DisjointSets ds(V);
		glLineWidth(2);
		usleep(1000000);
		for(int i=0;i<edges.size();i++){
			pair<int,int> edge = edges[i].second;
			int u = ds.find(edge.first);
			int v = ds.find(edge.second);
			if(u!=v){
				//got edge
				cout<<edge.first+1<<" "<<edge.second+1<<" "<<edges[i].first<<endl;
				drawLine(coordinates[edge.first].x,coordinates[edge.first].y,coordinates[edge.second].x,coordinates[edge.second].y,processedLineColor);
				ds.merge(edge.first,edge.second);
				usleep(1000000);
			}
		}
		for(int i=0;i<V;i++){
			drawCircle(coordinates[i].x,coordinates[i].y,20,initColor);
		}
	}
};

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	Graph g;
	g.input();
	g.drawGraph();
	g.krushkalMST();
	glFlush();
}


int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(800,400);
	glutCreateWindow("krushkalMST");
	gluOrtho2D(0,800,0,400);
	glutDisplayFunc(draw);
	glutMainLoop();
}