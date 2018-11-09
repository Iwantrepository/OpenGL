#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <dos.h>
#include <ctime>
#include <windows.h>

int tim = 100;
/*
    tim>0 day
    tim<0 night
*/

static GLfloat vert[] = {
                0,0,        ///trava
                0,500,
                700,500,
                700,0,

                0,250,      ///nebo
                0,500,
                700,500,
                700,250,

                250,250,    ///svetilo

                175,125,    ///dom
                175,215,
                255,215,
                255,125,

                125,215,    ///krisha
                295,215,
                215,255

                };

static GLfloat colrD[] = {
                    0.0, 1.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 1.0, 0.0,

                    0.0, 1.0, 1.0,
                    0.0, 1.0, 1.0,
                    0.0, 1.0, 1.0,
                    0.0, 1.0, 1.0,

                    1.0, 1.0, 1.0,

                    0.7, 0.5, 0.0,
                    0.7, 0.5, 0.0,
                    0.7, 0.5, 0.0,
                    0.7, 0.5, 0.0,

                    0.7, 0.5, 0.0,
                    0.7, 0.5, 0.0,
                    0.7, 0.5, 0.0,
                    };

static GLfloat colrN[] = {
                    0.0, 0.5, 0.0,
                    0.0, 0.5, 0.0,
                    0.0, 0.5, 0.0,
                    0.0, 0.5, 0.0,

                    0.0, 0.0, 0.2,
                    0.0, 0.0, 0.2,
                    0.0, 0.0, 0.2,
                    0.0, 0.0, 0.2,

                    1.0, 1.0, 1.0,

                    0.35, 0.25, 0.0,
                    0.35, 0.25, 0.0,
                    0.35, 0.25, 0.0,
                    0.35, 0.25, 0.0,

                    0.35, 0.25, 0.0,
                    0.35, 0.25, 0.0,
                    0.35, 0.25, 0.0
                    };


using namespace std;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, vert);
    glColorPointer(3, GL_FLOAT, 0, (tim>0)?colrD:colrN);

    glDrawArrays(GL_QUADS,0,8);

//--------------------------------------------------------------
    if(tim>0)
        glColor3f(1.0, 1.0, 0.0);
    else
        glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(50);
    glBegin(GL_POINTS);//svetilo
		glVertex2i((tim>0)?700*tim/100:700*(tim+100)/100,375);
	glEnd();
//--------------------------------------------------------------

    glDrawArrays(GL_QUADS,9,4);
    glDrawArrays(GL_TRIANGLES,13,3);

	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glFlush();
}

void myfoo()
{
    tim--;
    if(tim<-100)
        tim=100;

    vert[16]=(tim>0)?700*tim/100:700*(tim+100)/100;
    vert[17]=375;

    Sleep(5);
    printf("%d\n", tim);

    display();
}

void Reshape(int Width, int Height)
{
	if (Height == 0)
	{
		Height = 1;
	}

	glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)Width, 0.0, (GLdouble)Height);

	display();
}

void init()
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(700, 500);
	glutCreateWindow( "Main window" );

	init();
    glutDisplayFunc(display);
 	glutReshapeFunc(Reshape);
 	glutIdleFunc(myfoo);

 	//glutKeyboardFunc(processNormalKeys);
	//glutSpecialFunc(processSpecialKeys);

    printf("Go\n");
	glutMainLoop();
	return 0;
}

