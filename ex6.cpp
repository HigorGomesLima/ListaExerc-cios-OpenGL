#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int mesa[6][6];
float altura = 2;
float t = 4;

void placa(float x,float y,float w,float h,float r,float g,float b){
    glBegin(GL_POLYGON);
        glColor3f(r,g,b);
        glVertex2f(x,(y+(w/2)));
        glVertex2f((x+w),y);
        glVertex2f(x,(y-(w/2)));
        glVertex2f((x-w),y);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(0.5,0.5,0.5);
        glVertex2f(x,(y-(w/2)));
        glVertex2f((x-w),y);
        glVertex2f((x-w),(y-h)); //-2 -0.5
        glVertex2f(x,(y-(w/2)-h));//0 0-1-0.5
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(0.4,0.4,0.4);
        glVertex2f((x+w),y);
        glVertex2f(x,(y-(w/2)));
        glVertex2f(x,(y-(w/2)-h));
        glVertex2f((x+w),(y-h));
    glEnd();
    glBegin(GL_LINE_LOOP);
        glColor3f(0,0,0);
        glVertex2f(x,(y+(w/2)));
        glVertex2f((x+w),y);
        glVertex2f(x,(y-(w/2)));
        glVertex2f((x-w),y);
    glEnd();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i = 0;i < 4;i++){
        for(int j=3;j >= 0;j--){
                if(mesa[i][j] > 0){
                    float x = -(t*1.5) + j*t + i*t;
                    float y = j*t/2 - i*t/2;
                    placa(x,y,t,altura,0,0,1);
                }
        }
    }
    char texto[100] = "Higor Gomes, Leonardo Rodrigues";
    char p*;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRasterPos2f(-40,5);
    glTranslatef(-10, -10, 1);
    glScalef(0.02,0.02,0.02);
    glColor3f(0,0,0);
    for(p=texto; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    for(int i = 0;i < 4;i++){
        for(int j=0;j < 4;j++){
            if(i < j)
                mesa[i][j] = 1;
            else
                mesa[i][j] = 1;
        }
    }
    glutCreateWindow("Lista CG");
    glutDisplayFunc(display);
    glClearColor(1,1,1,1);
    glOrtho(-15,40,-25,25,-25,25);
    glutMainLoop();

    return EXIT_SUCCESS;
}
