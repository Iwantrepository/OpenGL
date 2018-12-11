#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glaux.h>
#include <stdio.h>

bool light = true;

GLfloat xRotated, yRotated, zRotated;
GLfloat xR = 0, yR = -0.1, zR = 0;
GLfloat sphereRotate = 1, dSphereRotate = 0.1;
GLint sphereMode = 0, i = 0;
GLfloat o = 0;

GLint textureMode = 2;

GLfloat pos[4] = {2,0,5.5,1};

GLuint	texture[8];

GLfloat alpha = 0.2;
GLboolean alphaMode = false;

GLvoid LoadGLTextures()
{
	// Загрузка картинки
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad("texture_1.bmp");
	glGenTextures(8, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("texture_2.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("texture_3.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("texture_4.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("texture_5.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("texture_6.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("texture_7.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("texture_8.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}

void init(void)
{
    glClearColor(0,0,0,0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_TEXTURE_2D);
    //glShadeModel(GL_SMOOTH);
    LoadGLTextures();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,-10.5);
    glRotatef(sphereRotate,0.0,1.0,0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glTranslatef(pos[0], pos[1], pos[2]);

    glColor4f(1.0,1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_LINE);
    gluSphere(quadObj, 0.5, 10, 10);

    glLoadIdentity();
    glTranslatef(0,0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);

    switch(textureMode)
    {
    case 0:
        glBegin(GL_TRIANGLES);

        glColor4f(1.0,0.0,0.0,alpha);    // Color Red
        glNormal3f(1,1,1);
        glVertex3f( 1+o, 0+o, 0+o);
        glVertex3f( 0+o, 1+o, 0+o);
        glVertex3f( 0+o, 0+o, 1+o);

        glColor4f(1.0,0.5,0.0,alpha);    // Color Orange
        glNormal3f(-1,1,-1);
        glVertex3f( 1+o, 0-o, 0+o);
        glVertex3f( 0+o,-1-o, 0+o);
        glVertex3f( 0+o, 0-o, 1+o);

        glColor4f(1.0,0.9,0.0,alpha);    // Color Yellow
        glNormal3f(-1,-1,1);
        glVertex3f(-1-o, 0-o, 0+o);
        glVertex3f( 0-o,-1-o, 0+o);
        glVertex3f( 0-o, 0-o, 1+o);

        glColor4f(0.0,1.0,0.0,alpha);    // Color Green
        glNormal3f(1,-1,-1);
        glVertex3f(-1-o, 0+o, 0+o);
        glVertex3f( 0-o, 1+o, 0+o);
        glVertex3f( 0-o, 0+o, 1+o);

        glColor4f(0.0,0.9,0.9,alpha);    // Color Blue
        glNormal3f(-1,-1,1);
        glVertex3f( 1+o, 0+o, 0-o);
        glVertex3f( 0+o, 1+o, 0-o);
        glVertex3f( 0+o, 0+o,-1-o);

        glColor4f(0.0,0.0,1.0,alpha);    // Color darkBlue
        glNormal3f(1,-1,-1);
        glVertex3f( 1+o, 0-o, 0-o);
        glVertex3f( 0+o,-1-o, 0-o);
        glVertex3f( 0+o, 0-o,-1-o);

        glColor4f(0.8,0.0,0.8,alpha);    // Color purple
        glNormal3f(1,1,1);
        glVertex3f(-1-o, 0-o, 0-o);
        glVertex3f( 0-o,-1-o, 0-o);
        glVertex3f( 0-o, 0-o,-1-o);

        glColor4f(1.0,0.0,0.0,alpha);    // Color
        glNormal3f(-1,1,-1);
        glVertex3f(-1-o, 0+o, 0-o);
        glColor4f(0.0,1.0,0.0,alpha);
        glVertex3f( 0-o, 1+o, 0-o);
        glColor4f(0.0,0.0,1.0,alpha);
        glVertex3f( 0-o, 0+o,-1-o);

        glEnd();            // End Drawing
        break;
    case 1:
        glColor4f(1,1,1,alpha);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glBegin(GL_TRIANGLES);

        glNormal3f(1,1,1);
        glTexCoord2f(0, 0);     glVertex3f(1+o,0+o,0+o);
        glTexCoord2f(1, 0);     glVertex3f(0+o,1+o,0+o);
        glTexCoord2f(0.5, 1);   glVertex3f(0+o,0+o,1+o);

        glNormal3f(-1,1,-1);
        glTexCoord2f(0, 0);     glVertex3f( 1+o, 0-o, 0+o);
        glTexCoord2f(1, 0);     glVertex3f( 0+o,-1-o, 0+o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0+o, 0-o, 1+o);

        glNormal3f(-1,-1,1);
        glTexCoord2f(0, 0);     glVertex3f(-1-o, 0-o, 0+o);
        glTexCoord2f(1, 0);     glVertex3f( 0-o,-1-o, 0+o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0-o, 0-o, 1+o);

        glNormal3f(1,-1,-1);
        glTexCoord2f(0, 0);     glVertex3f(-1-o, 0+o, 0+o);
        glTexCoord2f(1, 0);     glVertex3f( 0-o, 1+o, 0+o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0-o, 0+o, 1+o);

        glNormal3f(-1,-1,1);
        glTexCoord2f(0, 0);     glVertex3f( 1+o, 0+o, 0-o);
        glTexCoord2f(1, 0);     glVertex3f( 0+o, 1+o, 0-o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0+o, 0+o,-1-o);

        glNormal3f(1,-1,-1);
        glTexCoord2f(0, 0);     glVertex3f( 1+o, 0-o, 0-o);
        glTexCoord2f(1, 0);     glVertex3f( 0+o,-1-o, 0-o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0+o, 0-o,-1-o);

        glNormal3f(1,1,1);
        glTexCoord2f(0, 0);     glVertex3f(-1-o, 0-o, 0-o);
        glTexCoord2f(1, 0);     glVertex3f( 0-o,-1-o, 0-o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0-o, 0-o,-1-o);

        glNormal3f(-1,1,-1);
        glTexCoord2f(0, 0);     glVertex3f(-1-o, 0+o, 0-o);
        glTexCoord2f(1, 0);     glVertex3f( 0-o, 1+o, 0-o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0-o, 0+o,-1-o);

        glEnd();            // End Drawing
        break;
    case 2:
        glColor4f(1,1,1,alpha);

        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glBegin(GL_TRIANGLES);
        glNormal3f(1,1,1);
        glTexCoord2f(0, 0);     glVertex3f(1+o,0+o,0+o);
        glTexCoord2f(1, 0);     glVertex3f(0+o,1+o,0+o);
        glTexCoord2f(0.5, 1);   glVertex3f(0+o,0+o,1+o);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glBegin(GL_TRIANGLES);
        glNormal3f(-1,1,-1);
        glTexCoord2f(0, 0);     glVertex3f( 1+o, 0-o, 0+o);
        glTexCoord2f(1, 0);     glVertex3f( 0+o,-1-o, 0+o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0+o, 0-o, 1+o);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture[2]);
        glBegin(GL_TRIANGLES);
        glNormal3f(-1,-1,1);
        glTexCoord2f(0, 0);     glVertex3f(-1-o, 0-o, 0+o);
        glTexCoord2f(1, 0);     glVertex3f( 0-o,-1-o, 0+o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0-o, 0-o, 1+o);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture[3]);
        glBegin(GL_TRIANGLES);
        glNormal3f(1,-1,-1);
        glTexCoord2f(0, 0);     glVertex3f(-1-o, 0+o, 0+o);
        glTexCoord2f(1, 0);     glVertex3f( 0-o, 1+o, 0+o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0-o, 0+o, 1+o);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture[4]);
        glBegin(GL_TRIANGLES);
        glNormal3f(-1,-1,1);
        glTexCoord2f(0, 0);     glVertex3f( 1+o, 0+o, 0-o);
        glTexCoord2f(1, 0);     glVertex3f( 0+o, 1+o, 0-o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0+o, 0+o,-1-o);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture[5]);
        glBegin(GL_TRIANGLES);
        glNormal3f(1,-1,-1);
        glTexCoord2f(0, 0);     glVertex3f( 1+o, 0-o, 0-o);
        glTexCoord2f(1, 0);     glVertex3f( 0+o,-1-o, 0-o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0+o, 0-o,-1-o);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture[6]);
        glBegin(GL_TRIANGLES);
        glNormal3f(1,1,1);
        glTexCoord2f(0, 0);     glVertex3f(-1-o, 0-o, 0-o);
        glTexCoord2f(1, 0);     glVertex3f( 0-o,-1-o, 0-o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0-o, 0-o,-1-o);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture[7]);
        glBegin(GL_TRIANGLES);
        glNormal3f(-1,1,-1);
        glTexCoord2f(0, 0);     glVertex3f(-1-o, 0+o, 0-o);
        glTexCoord2f(1, 0);     glVertex3f( 0-o, 1+o, 0-o);
        glTexCoord2f(0.5, 1);   glVertex3f( 0-o, 0+o,-1-o);
        glEnd();
        break;
    default:
        break;
    }

    glFlush();
}


void animation(void)
{
    xRotated += xR;
    yRotated += yR;
    sphereRotate += dSphereRotate*sphereMode;
    Draw();

    for(int i=0; i<1000000; i++);
}

void glutNormalKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
    case '1':
        textureMode = 0;
        break;
    case '2':
        textureMode = 1;
        break;
    case '3':
        textureMode = 2;
        break;
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
    case 'x':
        if(alphaMode){
            alpha = 0.2;
            alphaMode = !alphaMode;
        }else{
            alpha = 1.0;
            alphaMode = !alphaMode;
        }
        break;
    case 'z':
        i++;
        switch(i%4)
        {
        case 0:
            sphereMode = 0;
            break;
        case 1:
            sphereMode = 1;
            break;
        case 2:
            sphereMode = 0;
            break;
        case 3:
            sphereMode = -1;
            break;
        default:
            break;
        }
        break;

    case 32:
        if(light){
            glDisable(GL_LIGHT0);
            light = !light;
        }else{
            glEnable(GL_LIGHT0);
            light = !light;
            }
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
           "W\\S - rotate X\n"
           "A\\D - rotate Y\n"
           "Q - stop rotation\n"
           "E - set ypr to default\n"
           "Z - orbit control\n"
           "\n"
           "Space - light on\\off\n"
           "\n"
           "1\\2\\3 - texture mode\n"
           "X - alpha mode\n");
    LoadGLTextures();
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
