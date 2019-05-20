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
}
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
