#include <GL\glut.h>
#include <stdio.h>

GLfloat xRotated, yRotated, zRotated;
GLfloat xR=0, yR=0, zR=0;
GLfloat o = 0;

void init(void)
{
    glClearColor(0,0,0,0);
}

void Draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);


    glBegin(GL_TRIANGLES);        // Draw The Pyramid Using quads
    glColor3f(1.0,0.0,0.0);    // Color Red
    glVertex3f( 1+o, 0+o, 0+o);
    glVertex3f( 0+o, 1+o, 0+o);
    glVertex3f( 0+o, 0+o, 1+o);

    glColor3f(1.0,0.5,0.0);    // Color Orange
    glVertex3f( 1+o, 0-o, 0+o);
    glVertex3f( 0+o,-1-o, 0+o);
    glVertex3f( 0+o, 0-o, 1+o);

    glColor3f(1.0,0.9,0.0);    // Color Yellow
    glVertex3f(-1-o, 0-o, 0+o);
    glVertex3f( 0-o,-1-o, 0+o);
    glVertex3f( 0-o, 0-o, 1+o);

    glColor3f(0.0,1.0,0.0);    // Color Green
    glVertex3f(-1-o, 0+o, 0+o);
    glVertex3f( 0-o, 1+o, 0+o);
    glVertex3f( 0-o, 0+o, 1+o);


    glColor3f(0.0,0.9,0.9);    // Color Blue
    glVertex3f( 1+o, 0+o, 0-o);
    glVertex3f( 0+o, 1+o, 0-o);
    glVertex3f( 0+o, 0+o,-1-o);

    glColor3f(0.0,0.0,1.0);    // Color darkBlue
    glVertex3f( 1+o, 0-o, 0-o);
    glVertex3f( 0+o,-1-o, 0-o);
    glVertex3f( 0+o, 0-o,-1-o);

    glColor3f(0.8,0.0,0.8);    // Color purple
    glVertex3f(-1-o, 0-o, 0-o);
    glVertex3f( 0-o,-1-o, 0-o);
    glVertex3f( 0-o, 0-o,-1-o);

    glColor3f(1.0,0.0,0.0);    // Color
    glVertex3f(-1-o, 0+o, 0-o);
    glColor3f(0.0,1.0,0.0);
    glVertex3f( 0-o, 1+o, 0-o);
    glColor3f(0.0,0.0,1.0);
    glVertex3f( 0-o, 0+o,-1-o);

    glEnd();            // End Drawing

    glFlush();
}


void animation(void)
{
    xRotated += xR;
    yRotated += yR;
    Draw();
}

void glutNormalKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:
        exit(0);
    case 'p':
        o+=0.1;
        break;
    case 'o':
        o=0;
        break;
    case 'i':
        o-=0.1;
        break;

    case 's':
        xR += 0.1;
        yR += 0.0;
        break;
    case 'w':
        xR -= 0.1;
        yR += 0.0;
        break;
    case 'd':
        xR += 0.0;
        yR += 0.1;
        break;
    case 'a':
        xR += 0.0;
        yR -= 0.1;
        break;
    case 'q':
        xR = 0;
        yR = 0;
        break;
    case 'e':
        xRotated = 0;
        yRotated = 0;
        break;

    default:
        break;
    }
}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(50.0,(GLdouble)x/(GLdouble)y,1,20);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

int main(int argc, char** argv){

    printf("\tINSTRUCTIONS\n"
           "P - open pyramid\n"
           "I - close pyramid\n"
           "O - set pyramid to default\n"
           "\n"
           "W\S - rotate X\n"
           "A\D - rotate Y\n"
           "Q - stop rotation\n"
           "E - set ypr to default");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glEnable(GL_DEPTH_TEST);

    //Set functions
    glutDisplayFunc(Draw);
    glutReshapeFunc(reshape);
    glutIdleFunc(animation);
    glutKeyboardFunc(glutNormalKeys);

    glutMainLoop();

    glDisable(GL_DEPTH_TEST);
    return 0;
}
