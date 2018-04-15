#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "enemy.h"
#include "grass.h"
#include "plank.h"
#include "trampoline.h"
#include "pond.h"
#include "magnet.h"
#include "porcupine.h"
#include <bits/stdc++.h>
#define PI  3.14159265358979323846
using namespace std;


GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
 * Customizable functions *
 **************************/

Ball ball;
Porcupine porcupine;
vector<Magnet> magnet;
Magnet temp_magnet;
Trampoline trampoline;
Platform platform;
Grass grass;
vector<Enemy> enemy;
Enemy element;
Plank ele;
vector<Plank> plank;
Pond pond;
int flag = 0;
int cnt = 0;
int score = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
int state=GLFW_RELEASE;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
	// clear the color and depth in the frame buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the loaded shader program
	// Don't change unless you know what you are doing
	glUseProgram (programID);

	// Eye - Location of camera. Don't change unless you are sure!!
	// glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
	// Target - Where is the camera looking at.  Don't change unless you are sure!!
	// glm::vec3 target (0, 0, 0);
	// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
	// glm::vec3 up (0, 1, 0);

	// Compute Camera matrix (view)
	// Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
	// Don't change unless you are sure!!
	Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	// Don't change unless you are sure!!
	glm::mat4 VP = Matrices.projection * Matrices.view;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	// Don't change unless you are sure!!
	glm::mat4 MVP;  // MVP = Projection * View * Model

	// Scene render
	platform.draw(VP);
	grass.draw(VP);
	pond.draw(VP);
	if(cnt%600>420 || (cnt>=600 && cnt%600<120))
		magnet[0].draw(VP);
	for(int i=0;i<enemy.size();i++)
		enemy[i].draw(VP);
	for(int i=0;i<plank.size();i++)
		plank[i].draw(VP);
	trampoline.draw(VP);
	ball.draw(VP);
	porcupine.draw(VP);
	
	//ball3.draw(VP);
}

void tick_input(GLFWwindow *window) {
	char buffer[100];
	sprintf(buffer,"Packman-killer			SCORE: %d",score);	
	glfwSetWindowTitle(window,buffer);
	int left  = glfwGetKey(window, GLFW_KEY_A);
	int right = glfwGetKey(window, GLFW_KEY_D);
	int up = glfwGetKey(window, GLFW_KEY_SPACE);
	if(cnt % 600 > 420 || (cnt >= 600 && cnt % 600 < 120)) {
		if(ball.position.y >= magnet[0].position.y - 1 && ball.position.y <= magnet[0].position.y + 1)
			ball.accln = -0.03;
		else 
			ball.accln = 0;
	}	
	else
		ball.accln = 0;
	if (left && ball.position.x > -2 && ball.position.x < 0 && ball.position.y < -1.8) {
		ball.speed = -0.03 + ball.accln;
	}
	else if (left && ball.position.x > -2 && ball.position.x < 0) {
		ball.speed = -0.05 + ball.accln;
	}
	else if (left && ball.position.x > -3.8) {
		ball.speed = -0.05 + ball.accln;
	//	ball.position.x += ball.speed;
	}
	else if(ball.position.x > -2 && ball.position.x < -1 &&
		 !right && !left && ball.position.y < -1.8) {
		ball.speed = 0.002 ;
	}
	if (right && ball.position.x > -2 && ball.position.x < 0 && ball.position.y <= -1.8) {
		ball.speed = 0.03 ;
	}	
	else if (right && ball.position.x > -2 && ball.position.x < 0 ) {
		ball.speed = 0.05 ;
	}
	else if(right && ball.position.x < 3.8) {
		// ball.position.x += 0.05;
		ball.speed = 0.05 ;
	//	ball.position.x += ball.speed;
	} 
	else if(ball.position.x > -1 && ball.position.x < 0 && 
		!left && !right && ball.position.y <= -1.8) {
		ball.speed = -0.002 ;
	}	
	// if (up==GLFW_PRESS && state == GLFW_RELEASE && (ball[0].position.y==0 || detect_collision(ball[0].bounding_box(), ball[1].bounding_box()))) {
	//     ball.speed_y = 0.08  ;
	//     ball.flag=true;
	// }
	// state=up;
	//printf("1-%lf\n",ball.position.y);
	if(up && ball.position.y <= -1.79999) {
		ball.speed_y = 0.08;
	}
	ball.position.x += ball.speed + ball.accln;
}

void tick_elements() {
	ball.tick();
	porcupine.tick();
	cnt++;
	if(cnt%600==420) {
		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		y *= 3;
		y -= 1;
		temp_magnet = Magnet(y, COLOR_MAGNET);
		if(magnet.size())
			magnet.erase(magnet.begin());
		magnet.push_back(temp_magnet);
	}
	
	// trampoline condition :-
    if(ball.position.x >= 1.90 && ball.position.y <= 3.60 && 
		ball.position.y < -1.10000 && ball.position.y > -1.4000 &&
		ball.speed_y <= 0) {
		ball.speed_y = 0.12;
	}
	if(ball.position.y <= -1.3 && ball.speed_y < 0 && ball.position.y > -1.8 &&
		porcupine.position.x + 0.1 < ball.position.x + 0.2 && 
		porcupine.position.x + 0.3 >= ball.position.x -0.2) {
		ball.position.x = -3;
		ball.position.y = -1.8;
		score = max(score-100,0);
	}
	if(ball.position.y > -1.8)
    {
        //    printf("3-%lf\n",ball.speed_y);
        ball.speed_y -= 0.0025;
	}
    else if(ball.position.y < -1.8 && !(ball.position.x > -2 && ball.position.x < 0)) {
        //    printf("2-%lf\n",ball.position.y);

        ball.position.y = -1.8;
        ball.speed_y = 0;
	}
	else if(ball.position.y < 0 && (ball.position.x > -2 && ball.position.x < 0)) {
//		cout<<"yo"<<endl;
		ball.speed_y = -0.005;
//        ball.position.y = -1.8;
		
	}
		
	if (detect_collision()) {
		//    ball[0].speed = 0;
		  //  ball[1].speed = 0;
		    // ball.speed = -ball.speed;
			// ball.speed_y = 0.07;
			make_enemies();
			make_planks();
	}
	for(int i=0;i<plank.size();i++) {
		plank[i].tick();
		if(plank[i].flag == 1) {
			// float temp = ball.speed;
			// ball.speed = -(ball.speed * cos(plank[i].angle * PI / 90.0f) +
			// ball.speed_y * sin(plank[i].angle * PI / 90.0f));
			// ball.speed_y = 
			plank.erase(plank.begin()+i);
			make_planks();
		}
	}
    for(int i=0;i<enemy.size();i++) {
		enemy[i].tick();
		if(enemy[i].flag == 1) {
			enemy.erase(enemy.begin() + i);
			make_enemies();
		}
	}
		//     float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //     if(r<0.1)
        //         r+=0.1;
        //     else if(r>0.3)
        //     {
        //         while(r>0.3)
        //             r-=0.1;
        //     }
        //     float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //     float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //     y *= 4.0;
        //     x *= 8.0;
        //     x -= 4;
        //     // if(y > 3)
        //     //     y -= 1;
        //     // else if(y < 2)
        //     //     y -= 2;
        //     y -= 2;
        //     float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //     s /= 10;
        //     while(s > 0.06)
        //         s -=  0.01;
        //     while(s < 0.02)
        //         s+= 0.01;  
        //     element = Enemy(-4, y, r, s, COLOR_YELLOW);
        //     enemy.push_back(element);
		
	//	if(!detect_collision(ball[0].bounding_box(), ball[1].bounding_box()) && ball[0].position.y>0.002) {
		//     ball[0].speed_y -= 0.002;
		// }
		// else if(ball[0].position.y<=0.002)
		// {
		//     ball[0].position.y=0;
		// }
		//printf("yoyoyoy%lf\n",ball.position.y);
		
		// else 
		// {
		//     printf("yo\n");
		// }
	//} 
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
	/* Objects should be created before any other gl function and shaders */
	// Create the models

	ball = Ball(2, -1.8, COLOR_RED);
	platform = Platform(COLOR_BROWN);
	grass = Grass(COLOR_GREEN);
	trampoline = Trampoline(COLOR_RED);
	pond = Pond(COLOR_SKYBLUE);
	porcupine = Porcupine(0, -2, 0.01);
	
	//	plank = Plank(1.0, 2.0, 0.2, 0, COLOR_RED);
	//    printf("%lf\n",ball.position.y);
	ball.speed_y = 0;
	int i = 0;
	make_enemies();
	make_planks();
	flag = 1;
	// while(enemy.size() < 20) {
	// 	float r = 0;
	// 	//cout<<"haha"<<endl;
	// 	r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	// 	if(r<0.1)
	// 		r+=0.1;
	// 	else if(r>0.3)
	// 	{
	// 		while(r>0.3)
	// 			r-=0.1;
	// 	}
	// 	//cout<<r<<endl;

	// 	float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	// 	float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	// 	y *= 4.0;
	// 	x *= 8.0;
	// 	x -= 4;
	// 	// if(y > 3)
	// 	//     y -= 1;
	// 	// else if(y < 2)
	// 	//     y -= 2;
	// 	y -= 2;
	// 	float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	// 	s /= 10;
	// 	while(s > 0.06)
	// 		s -=  0.01;
	// 	while(s < 0.02)
	// 		s+= 0.01;  
	// 	element = Enemy(x, y, r, s, COLOR_YELLOW);
	// 	enemy.push_back(element);
	// }
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


	reshapeWindow (window, width, height);

	// Background color of the scene
	// glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
	glClearColor (0, 0, 0, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void make_enemies() {
	while(enemy.size() < 7) {
		float r = 0;
		//cout<<"haha"<<endl;
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if(r < 0.1)
			r += 0.1;
		else if(r > 0.3) {
			while(r > 0.3)
				r -= 0.1;
		}
		//cout<<r<<endl;

		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		y *= 4.0;
		x *= 8.0;
		x -= 4;
		// if(y > 3)
		//     y -= 1;
		// else if(y < 2)
		//     y -= 2;
		y -= 1;
		float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		s /= 10;
		while(s > 0.06)
			s -=  0.01;
		while(s < 0.02)
			s+= 0.01;
		int col = rand() % 5;
		if(flag == 0)  {
			element = Enemy(x, y, r, s);
		}	
		else {
			element = Enemy(-4, y, r, s);		
		}		
		enemy.push_back(element);
	}

}

void make_planks() {
	while(plank.size() < 3) {
		float r = 0;
		//cout<<"haha"<<endl;
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if(r < 0.1)
			r += 0.1;
		else if(r > 0.3)
		{
			while(r > 0.3)
				r -= 0.1;
		}
		//cout<<r<<endl;

		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		y *= 4.0;
		// if(y > 3)
		//     y -= 1;
		// else if(y < 2)
		//     y -= 2;
		y -= 1;
		float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		s /= 10;
		while(s > 0.06)
			s -=  0.01;
		while(s < 0.02)
			s += 0.01;
		ele = Plank(-4,y,r,s);
		// int col = rand() % 5;
		// if(col == 0)
		// 	ele = Plank(-4, y, r, s, COLOR_YELLOW);
		// else if(col == 1)
		// 	ele = Plank(-4, y, r, s, COLOR_GREEN);
		// else if(col == 2)
		// 	ele = Plank(-4, y, r, s, COLOR_PURPLE);
		// else if(col == 3)
		// 	ele = Plank(-4, y, r, s, COLOR_BLUE);
		// else if(col == 4)
		// 	ele = Plank(-4, y, r, s, COLOR_BROWN);
		plank.push_back(ele);
	}

}
int main(int argc, char **argv) {
	srand(time(0));
	int width  = 600;
	int height = 600;

	window = initGLFW(width, height);

	initGL (window, width, height);

	/* Draw in loop */
	while (!glfwWindowShouldClose(window)) {
		// Process timers

		if (t60.processTick()) {
			// 60 fps
			// OpenGL Draw commands
			draw();
			// Swap Frame Buffer in double buffering
			glfwSwapBuffers(window);

			tick_elements();
			tick_input(window);
		}

		// Poll for Keyboard and mouse events
		glfwPollEvents();
	}

	quit(window);
}

bool detect_collision() {
	for(int i = 0; i < enemy.size(); i++) {
		if(ball.speed_y >= 0)
			continue;
		else if(sqrt(((ball.position.y-enemy[i].position.y)*(ball.position.y-enemy[i].position.y)) +
		((ball.position.x-enemy[i].position.x)*(ball.position.x-enemy[i].position.x)) <= 0.2 + enemy[i].radius)) {
			score += (enemy[i].col + 1)*10;
			enemy.erase(enemy.begin() + i);
			// ball.speed = -ball.speed;
			// ball.speed_y = -ball.speed_y;
			ball.speed = -ball.speed;
			ball.speed_y = 0.07;
			return true;
		}
	}
	for(int i = 0; i < plank.size(); i++) {
		if(ball.speed_y >= 0)
			continue;
		else if(sqrt(((ball.position.y-plank[i].position.y)*(ball.position.y-plank[i].position.y)) +
		((ball.position.x-plank[i].position.x)*(ball.position.x-plank[i].position.x)) <= 0.2 + plank[i].radius)) {
			score += (enemy[i].col + 1)*15;			
			plank.erase(plank.begin() + i);
			// ball.speed = -ball.speed;
			// ball.speed_y = -ball.speed_y;
			float temp = ball.speed;
			ball.speed = -4*(ball.speed * cos(plank[i].angle * PI / 90.0f) +
						   ball.speed_y * sin(plank[i].angle * PI / 90.0f));
			ball.speed_y = 3*(temp * sin(plank[i].angle * PI/90.0f) - 
						   ball.speed_y * cos(plank[i].angle * PI / 90.0f));
				
			return true;
		}
	}	
	return false;
	// return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
	// 	(abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
	float top    = screen_center_y + 4 / screen_zoom;
	float bottom = screen_center_y - 4 / screen_zoom;
	float left   = screen_center_x - 4 / screen_zoom;
	float right  = screen_center_x + 4 / screen_zoom;
	top++;  
	Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
