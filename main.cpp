#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define ScreenWidth 900
#define ScreenHeight 900

#define RESISTOFAIR 0.001

float scaleY = (float)1/(ScreenHeight);
float scaleX = (float)1/(ScreenWidth);

class Vector2 {

public:
	double x;
	double y;
	
	Vector2(double x=0,double y=0){
	this->x = x;
	this->y = y;
	};

};

class Point{
	public:
		Vector2 pos;
		Vector2 velocity;
		int  size;

		Point(double x, double y, int size){
		this->pos = Vector2(x,y);
		this->size = size;
		};
	
		void applyForce(){
		if(abs(velocity.x) >RESISTOFAIR){
		pos.x+=velocity.x;
			if(velocity.x > 0){
			velocity.x -= (double)RESISTOFAIR;
			if(velocity.x < RESISTOFAIR) velocity.x = 0;
			}
			else if(velocity.x < 0) {
			velocity.x += (double)RESISTOFAIR;
			if(velocity.x > -RESISTOFAIR) velocity.x = 0;
			}
		}
		if(abs(velocity.y) >0){
		pos.y+=velocity.y;
			if(velocity.y > 0){
			velocity.y -= (double)RESISTOFAIR;
			if(velocity.y < RESISTOFAIR) velocity.y =0;
			}
			else if(velocity.y < 0) {
			velocity.y += (double)RESISTOFAIR;
			if(velocity.y > -RESISTOFAIR) velocity.y =0;
			}
		}
		}
		void setForce(double x, double y){
		velocity.x = x;
		velocity.y = y;
		
		}
		void setForce(Vector2 force){
		velocity.x = force.x;
		velocity.y = force.y;
		
		}
};

int main(void){
	srand(time(NULL));

	GLFWwindow* window; 

	vector<Point> points;
	
	for(int i=0;i<=10000;i++){points.push_back(Point(0,0,4));}


	for(int i=0;i<=10000;i++){

	double angle = ((rand() % 1000) / 1000.0) * 2 * M_PI;
    
	float speed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1));
	
	double vx = cos(angle) * speed;
	double vy = sin(angle) * speed;
    
	points[i].setForce(vx, vy);

	}

	if(!glfwInit()){
		return -1;
	}
	
	window = glfwCreateWindow(ScreenWidth,ScreenHeight,"LizardWhichFollowsMouse",NULL,NULL);	

	if(!window){
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	int a;
	std::cin >> a;

	
	while(!glfwWindowShouldClose(window)){

		glClear(GL_COLOR_BUFFER_BIT);

		glLoadIdentity();
		glScalef(scaleX*2,scaleY*2,1);

		for(int i=0;i<points.size();i++){
			glPointSize(points[i].size);
			glBegin(GL_POINTS);
			points[i].applyForce();
			glVertex2d(points[i].pos.x,points[i].pos.y);
			glEnd();
		}
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
