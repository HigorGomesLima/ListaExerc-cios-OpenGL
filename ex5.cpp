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

int getPosition(int x,int y);

void mouse(int button, int state, int x, int y){
    switch(button){
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN){
            std::cout << x << " " << y << " -> " << getPosition(x,y) <<"\n" ;
        }
        glutPostRedisplay();
        break;
        case GLUT_RIGHT_BUTTON:
        if(state == GLUT_DOWN){
            std::cout << "\n" ;
        }
        glutPostRedisplay();
        break;
    }

}

int getPosition(int x,int y){
    if(x >= 60 && x <= 144 && y >= 221 && y <= 254)
        return 0;
    else if(x >= 109 && x <= 191 && y >= 201 && y <= 235)
        return 1;
    else if(x >= 157 && x <= 237 && y >= 183 && y <= 214)
        return 2;
    else if(x >= 204 && x <= 283 && y >= 164 && y <= 197)
        return 3;
    else if(x >= 251 && x <= 330 && y >= 145 && y <= 177)
        return 4;
    else if(x >= 300 && x <= 374 && y >= 125 && y <= 157)
        return 5;
    else if(x >= 108 && x <= 190 && y >= 241 && y <= 274)
        return 10;
    else if(x >= 160 && x <= 234 && y >= 223 && y <= 253)
        return 11;
    else if(x >= 204 && x <= 280 && y >= 203 && y <= 234)
        return 12;
    else if(x >= 250 && x <= 325 && y >= 184 && y <= 216)
        return 13;
    else if(x >= 296 && x <= 375 && y >= 165 && y <= 196)
        return 14;
    else if(x >= 346 && x <= 420 && y >= 144 && y <= 175)
        return 15;
    else if(x >= 160 && x <= 234 && y >= 261 && y <= 290)
        return 20;
    else if(x >= 205 && x <= 282 && y >= 242 && y <= 272)
        return 21;
    else if(x >= 250 && x <= 325 && y >= 224 && y <= 252)
        return 22;
    else if(x >= 298 && x <= 375 && y >= 204 && y <= 235)
        return 23;
    else if(x >= 344 && x <= 420 && y >= 185 && y <= 215)
        return 24;
    else if(x >= 391 && x <= 465 && y >= 164 && y <= 196)
        return 25;
    else if(x >= 203 && x <= 276 && y >= 295 && y <= 314)
        return 30;
    else if(x >= 251 && x <= 328 && y >= 262 && y <= 289)
        return 31;
    else if(x >= 298 && x <= 372 && y >= 242 && y <= 270)
        return 32;

    else
        return 70;
}

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

void chao(){

    glBegin(GL_POLYGON);
        glColor3f(0.2,0.2,0.2);
        glVertex2f(-10,-2);
        glVertex2f(14,10);
        glVertex2f(38,-2);
        glVertex2f(14,-14);
    glEnd();
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    chao();
    for(int i = 0;i < 6;i++){
        for(int j=5;j >= 0;j--){
                if(mesa[i][j] > 0){
                    float x = -(t*1.5) + j*t + i*t;
                    float y = j*t/2 - i*t/2;
                    placa(x,y,t,altura,0,0,1);
                }
        }
    }
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    for(int i = 0;i < 6;i++){
        for(int j=0;j < 6;j++){
            if(i < j)
                mesa[i][j] = 1;
            else
                mesa[i][j] = 1;
        }
    }
    glutCreateWindow("Lista CG");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glClearColor(1,1,1,1);
    glOrtho(-15,40,-25,25,-25,25);
    glutMainLoop();

    return EXIT_SUCCESS;
}
