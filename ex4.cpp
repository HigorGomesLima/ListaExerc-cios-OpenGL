#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

void objeto(void){
    glBegin(GL_POLYGON);
        glColor3f(0,0,1);
        glVertex2f(0,1);
        glVertex2f(2,0);
        glVertex2f(0,-1);
        glVertex2f(-2,0);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(0.5,0.5,1);
        glVertex2f(0,-1);
        glVertex2f(-2,0);
        glVertex2f(-2,-0.5);
        glVertex2f(0,-1.5);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(0.5,0.5,1);
        glVertex2f(2,0);
        glVertex2f(0,-1);
        glVertex2f(0,-1.5);
        glVertex2f(2,-0.5);
    glEnd();
}
/*
Fórmula 3D - X e Y
x = -1.5 + y*0,5 + i*0,5;
y = y*0,25 - x*0,25;
*/
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    objeto();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lista CG");
    glutDisplayFunc(display);

    glClearColor(0,0,0,0);
    glOrtho(-20,20,-10,10,-10,10);
    glutMainLoop();

    return EXIT_SUCCESS;
}
