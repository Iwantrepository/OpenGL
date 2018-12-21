#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glaux.h>
#include <stdio.h>

#define NUM_OF_SHARDS 11

bool light = true;

GLfloat xRotated, yRotated, zRotated;
GLfloat xR = 0, yR = -0.1, zR = 0;
GLfloat sphereRotate = 1, dSphereRotate = 0.1;
GLint sphereMode = 0, i = 0;
GLfloat o = 0;

GLint textureMode = 3;
GLfloat pos[4] = {2,0,5.5,1};
GLuint	texture[8];

GLfloat range = -5;

char textureName[14] = "texture_1.bmp";

GLfloat alpha = 1;
GLboolean alphaMode = true;

GLuint triangle;

void DrawTriangle(GLfloat x, GLfloat y, GLfloat z, GLint p)
{
    glNormal3f(1,1,1);

    for(int i = 0; i<p; i+=2)
    {
        glNormal3f(1,1,1);
        glBegin(GL_POLYGON);

        glVertex3f( x/p*i       ,y-y/p*i    ,0          );
        glVertex3f( 0           ,y-y/p*i    ,z/p*i      );
        glVertex3f( 0           ,y-y/p*(i+1),z/p*(i+1)  );
        glVertex3f( x/p*(i+1)   ,y-y/p*(i+1),0          );
        glEnd();
    }

}

void CalculateList()
{
	triangle = glGenLists(1);
	glNewList(triangle, GL_COMPILE);
	DrawTriangle(1.0,1.0,1.0, NUM_OF_SHARDS);
	glEndList();
}

GLvoid LoadGLTextures()
{
    AUX_RGBImageRec *texture1;
    glGenTextures(8, &texture[0]);

    for(int i=0; i<8; i++){
        textureName[8]='1'+i;
        texture1 = auxDIBImageLoad(textureName);
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
    }
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

    CalculateList();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,range);
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
    glTranslatef(0,0,range);
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
        glBindTexture(GL_TEXTURE_2D, texture[5]);
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
    case 3:
        glTranslatef(o,o,o);
        glColor4f(1.0,0.0,0.0,alpha);
        glCallList(triangle);
        glTranslatef(-o,-o,-o);
        glRotatef(90,0.0,1.0,0.0);

        glTranslatef(o,o,o);
        glColor4f(1.0,0.5,0.0,alpha);
        glCallList(triangle);
        glTranslatef(-o,-o,-o);
        glRotatef(90,0.0,1.0,0.0);

        glTranslatef(o,o,o);
        glColor4f(1.0,0.9,0.0,alpha);
        glCallList(triangle);
        glTranslatef(-o,-o,-o);
        glRotatef(90,0.0,1.0,0.0);

        glTranslatef(o,o,o);
        glColor4f(0.0,1.0,0.0,alpha);
        glCallList(triangle);
        glTranslatef(-o,-o,-o);
        glRotatef(90,0.0,1.0,0.0);

            glRotatef(180,1.0,0.0,0.0);

        glTranslatef(o,o,o);
        glColor4f(0.0,0.9,0.9,alpha);    // Color Blue
        glCallList(triangle);
        glTranslatef(-o,-o,-o);
        glRotatef(90,0.0,1.0,0.0);

        glTranslatef(o,o,o);
        glColor4f(0.0,0.0,1.0,alpha);    // Color darkBlue
        glCallList(triangle);
        glTranslatef(-o,-o,-o);
        glRotatef(90,0.0,1.0,0.0);

        glTranslatef(o,o,o);
        glColor4f(0.8,0.0,0.8,alpha);    // Color purple
        glCallList(triangle);
        glTranslatef(-o,-o,-o);
        glRotatef(90,0.0,1.0,0.0);

        glTranslatef(o,o,o);
        glColor4f(1.0,0.0,0.0,alpha);
        glCallList(triangle);
        glTranslatef(-o,-o,-o);

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
    case '4':
        textureMode = 3;
        break;
///--------------------------
    case 27:
        exit(0);
///--------------------------
    case 'p':
        o+=0.1;
        break;
    case 'o':
        o=0;
        break;
    case 'i':
        o-=0.1;
        break;
///--------------------------
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
///--------------------------
    case 'q':
        xR = 0;
        yR = 0;
        break;
    case 'e':
        xRotated = 0;
        yRotated = 0;
        break;
///--------------------------
    case 'x':
        if(alphaMode){
            alpha = 0.2;
            alphaMode = !alphaMode;
        }else{
            alpha = 1.0;
            alphaMode = !alphaMode;
        }
        break;
///--------------------------
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
///--------------------------
    case 32:
        if(light){
            glDisable(GL_LIGHT0);
            light = !light;
        }else{
            glEnable(GL_LIGHT0);
            light = !light;
            }
        break;
///--------------------------
    case 't':
        range--;
        break;
    case 'y':
        range=-5;
        break;
    case 'u':
        range++;
        break;
///--------------------------
    case 'r':
        range = -5;
        xR = 0;
        yR = -0.1;
        xRotated = 0;
        yRotated = 0;
        o = 0;
        alpha = 1;
        break;
///--------------------------
    default:
        break;
    }
///--------------------------
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
           "1\\2\\3\\4 - texture mode\n"
           "X - alpha mode\n"
           "\n"
           "T\\U - range\n"
           "Y - reset range\n"
           "\n"
           "R - reset");
    LoadGLTextures();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(Draw);
    glutReshapeFunc(reshape);
    glutIdleFunc(animation);
    glutKeyboardFunc(glutNormalKeys);

    glutMainLoop();

    glDisable(GL_DEPTH_TEST);
    return 0;
}
