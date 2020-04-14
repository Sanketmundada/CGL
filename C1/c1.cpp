#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>
using namespace std;
void init(void)
{
glClearColor(0,0,0,0);
}
float XUP[3] = {2,0,0}, 
     YUP[3] = {0,2,0}, 
      ZUP[3] = {0,0,2},
      ORG[3] = {0,0,0};

GLfloat d[3] = {0.1, 0.1, 0.1};
GLfloat xS=0.5,yS=0.5,zS=0.5;
GLfloat  xAngle = 0.0;
void Keyboard(unsigned char key, int x, int y)
{
    switch(key)
   {
       case 'j' : d[0] -= 0.1;  break;
       case 'k' : d[2] += 0.1;  break;
       case 'l' : d[0] += 0.1;  break;
       case 'i' : d[1]+=0.1;break;
       case 'm' : d[1]-=0.1;break;
       case 'o' : d[2] -= 0.1;break;
       case 's':xS+=0.2;
		break;
       case 'a':yS+=0.2;break;
       case 'd':zS+=0.2;break;
	case 'w':xS-=0.2;break;
       case 'q' :yS-=0.2;break;
       case 'e' :zS-=0.2;break;
       case 'u' :xS+=0.2;
		 yS+=0.2;
		 zS+=0.2;break;
	case 'y' :xS-=0.2;
		 yS-=0.2;
		 zS-=0.2;break;
       case 'x' : xAngle += 5;  break;
       case 'c' : xAngle -=5;break;
    }
    glutPostRedisplay();
}
void Draw_Axes(void)
{
	glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
       glVertex3fv(ORG); glVertex3fv (XUP);
       glVertex3fv(ORG); glVertex3fv (YUP);  
      glVertex3fv(ORG); glVertex3fv (ZUP);
    glEnd();

    glRasterPos3f(2, 0.0, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');	

    glRasterPos3f(0.0, 2, 0.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');

    glRasterPos3f(0.0, 0.0, 2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Z');
}
void Draw_Box(void)
{
    glBegin(GL_QUADS);
     
    glColor3f(1.0f,1.0f,0.0f);    // Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)

    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f( 1.0f,-1.0f, -1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, -1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,1.0f);    // Bottom Right Of The Quad (Bottom)

    glColor3f(1.0f,0.0f,0.0f);    // Color Red    
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)

    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f( 1.0f,1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, -1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, -1.0f,-1.0f);    // Bottom Right Of The Quad (Back)

    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)

    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)

    glEnd();
}
void Display(void)
{
    int v;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -6);
    Draw_Axes();
    glPushMatrix ();
	glTranslatef(d[0],d[1],d[2]);
	glScalef(xS,yS,zS);
       glRotatef(xAngle, 1,0,0);
       Draw_Box();
    glPopMatrix();
    glutSwapBuffers();
}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    init();
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(300, 300);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Assignment C1");
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, 1.5, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();
    return 1;
}

    
