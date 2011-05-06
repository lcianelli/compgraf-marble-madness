/*
   Program to display a GLUsphere as an example of GLU objects.

   Sample for CS 3600, Fall 1998, CSU Stanislaus -- Dr. Cunningham
*/

#include "glut.h"
#include <stdlib.h>
#include <math.h>

GLfloat distance = 10.0;
GLint resolution = 10;
GLint selectedObject = 1;

void myinit( void );
void display( void );
void reshape(int w,int h);
void options_menu(int input);

void myinit(void)
{
//      set up overall light data, including specular=ambient=light colors
        GLfloat light_position[]={ 10.0, 10.0, -10.0, 1.0 };
        GLfloat light_color[]={ 1.0, 1.0, 1.0, 1.0 };
        GLfloat ambient_color[]={ 0.2, 0.2, 0.2, 1.0 };
        GLfloat mat_specular[]={ 1.0, 1.0, 1.0, 1.0 };

        glClearColor( 0.0, 0.0, 1.0, 0.0 );
        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular );
        glLightfv(GL_LIGHT0, GL_POSITION, light_position );
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color );
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_color );
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color );

/* attributes */
        glEnable(GL_LIGHTING);   // so lighting models are used
        glEnable(GL_LIGHT0);     // we'll use LIGHT0
        glEnable(GL_DEPTH_TEST); // allow z-buffer display
}

void display( void )
{
	GLUquadric *myQuad;
	GLdouble radius = 1.0;
	GLint slices, stacks;
	GLint nsides, rings;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* clear window and z-buffer */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,1.0,1.0,30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//                   eye point          center of view       up
	gluLookAt( distance, distance, distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

// material for sphere
//	glMaterialfv(...	
	switch (selectedObject) {
		case (1): {
			myQuad=gluNewQuadric();
			slices = stacks = resolution;
			gluSphere( myQuad , radius , slices , stacks  );
//			glutWireSphere(radius, slices, stacks); 
			break;
			}
		case (2): {
			myQuad=gluNewQuadric();
			slices = stacks = resolution;
			gluCylinder( myQuad, 1.0, 1.0, 1.0, slices, stacks ); break;
			}
		case (3): {
			glutSolidDodecahedron(); break;
			}
		case (4): {
			nsides = rings = resolution;
			glutSolidTorus( 1.0, 2.0, nsides, rings);
			break;
			}
		case (5): {
			glutSolidTeapot(2.0); break;
			}
		}
    glutSwapBuffers();
 }

void reshape(int w,int h)
{
        glViewport(0,0,(GLsizei)w,(GLsizei)h);
}

void options_menu(int input)
{
	if ((input >= 1) && (input <=5 ))	/* menu selection to draw a new landscape */
	{
		selectedObject = input;
	}
	else {
		if ( input == 6 ) resolution *= 2;               // higher resolution
		if ( input == 7 )                                // lower resolution but always >= 2
			if (resolution > 2 ) resolution = (resolution+1)/2;
		if ( input == 8 ) distance -= 1.0;               // move in
		if ( input == 9 ) distance += 1.0;               // move out
	}
	glutPostRedisplay();
}

void main(int argc, char** argv)
{

/* Standard GLUT initialization */

        glutInit(&argc,argv);
//      initialize for double buffering, RGB color, and depth tests
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(500,500);
        glutInitWindowPosition(70,70);
        glutCreateWindow("GLU Spheres");
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);

		glutCreateMenu(options_menu);	    // create the options menu and set callback
		glutAddMenuEntry("GLU sphere", 1);
		glutAddMenuEntry("GLU cylinder", 2);
		glutAddMenuEntry("GLUT dodecahedron", 3);
		glutAddMenuEntry("GLUT torus", 4);
		glutAddMenuEntry("GLUT teapot", 5);
		glutAddMenuEntry("More detail", 6);
		glutAddMenuEntry("Less detail", 7);
		glutAddMenuEntry("Move in", 8);
		glutAddMenuEntry("Move out", 9);
		
		glutAttachMenuName(GLUT_RIGHT_BUTTON, "Selections");	/* give the menu a name */

        myinit();
        glutMainLoop();
}

