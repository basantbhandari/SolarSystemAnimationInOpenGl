#include"Header.h"


//global variable 
int xc_position = 600;
int yc_position = 0;
float angle = 0;


//custom function prototype and definition
void render() {
	//clear
	glClear(GL_COLOR_BUFFER_BIT);

	//reset
	glLoadIdentity();

	//draw things
	glPointSize(100.0);


	// drawing circle by calling custom function "DrawCircle"
	//for sun
	glColor3f(1.0, 0.0, 0.0);
	DrawCircle(0.0, 0.0, 150.0, 10000);

	//for earth
	glColor3f(0.0, 0.0, 1.0);
	DrawCircle(xc_position, yc_position, 100.0, 1000);

	//display and swop double buffer
	glutSwapBuffers();

}






void initBackground() {

	glClearColor(0.0, 0.0, 0.0, 1);
	glColor3f(1.0, 1.0, 1.0);


}


void reshape(int w, int h) {
	//view port
	glViewport(0, 0, w, h);

	//projection
	glMatrixMode(GL_PROJECTION);

	//reset
	glLoadIdentity();
	gluOrtho2D(-1000, 1000, -1000, 1000);

	glMatrixMode(GL_MODELVIEW);


}




void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);


	if (angle > 360) {
		angle = 0;
	}
	angle += 0.001;


	int *p = orbitXY(angle);
	xc_position = *(p + 0);
	yc_position = *(p + 1);

}


void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}




int *orbitXY(float angleInDegree) {
	static int tempxy[2];

	tempxy[0] = (int)(cos(angleInDegree) * 600 - sin(angleInDegree) * 0);
	tempxy[1] = (int)(sin(angleInDegree) * 600 + cos(angleInDegree) * 0);

	return tempxy;
}




void keyboard(unsigned char c, int x, int y) {

	if (c == 'a') {
		exit(0);
	}

}



void mouse(int buttom, int state, int x, int y) {

	if (buttom == GLUT_RIGHT_BUTTON) {

		exit(0);
	}

}





int main(int argc, char* argv[]) {

	//OpenGL initialization code (optional)
	glutInit(&argc, argv);

	//Specify the display mode -RBG or color index, single or double buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	//Creating window Named "Solar system animation"
	//with starting position (0,0)
	//with window resolution (3000*3000)
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(3000, 3000);
	glutCreateWindow("Solar system Simulation");

	//Register the call back function
	glutDisplayFunc(render);

	//function to reshape the window
	glutReshapeFunc(reshape);

	//for animation
	glutTimerFunc(0, timer, 0);
	
	//handle keyboard input
	glutKeyboardFunc(keyboard);

	//handle mouse input
	glutMouseFunc(mouse);

	//to change window background
	initBackground();

	//Program goes into infinite loop waiting for events
	glutMainLoop();

	return(0);
}



