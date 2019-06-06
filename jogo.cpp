#include <windows.h>
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int mesa[6][6]; //tamanho da mesa
float altura = 2; //altura da peça
bool vitoria = false; //verificação da vitória
float t = 4;
int click = 0;

/*bloco e valores e direcao
    horizontal = 1
    vertical = 2
    ------------------------
    | cor    | qtd | valor |
    | vazio  |  x  | 0     |
    |vermelho|  1  | 11    |
    |  azul  |  2  | 22    |
    |  verde |  2  | 32    |
    |amarelo |  2  | 42    |
    ------------------------
*/
int getPosition(int x,int y);
bool mover(int x,int y,int b);
void placa(float x,float y,float w,float h,float r,float g,float b);

void mouse(int button, int state, int x, int y){
    if(!vitoria){
    switch(button){
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN){
            if(getPosition(x,y) > 0){
                if(mover(x,y,1))
                    click++;
            }
        }
        glutPostRedisplay();
        break;
        case GLUT_RIGHT_BUTTON:
        if(state == GLUT_DOWN){
            if(getPosition(x,y) > 0){
                if(mover(x,y,2))
                    click++;
            }
        }
        glutPostRedisplay();
        break;
    }
    }

}

bool mover(int x,int y,int b){
    bool r = false;
    int xr = getPosition(x,y) / 10;
    int yr = getPosition(x,y) % 10;
    int peca = mesa[xr][yr] / 10;
    int d = mesa[xr][yr] % 10;
    if(b == 1){
        if(d == 1){
            int py = yr;
            for(int i = xr;py < 5 && (mesa[i][py+1] / 10) == peca;py++);
            int mv = py;
            for(int i = xr;mv < 5 && mesa[i][mv+1] == 0;mv++);
            if((py-mv) < 0){
                int fj = 0;
                for(int j = py;(mesa[xr][j-1]/10) == peca && j > 0;j--){
                    mesa[xr][j+1] = mesa[xr][j];
                    fj = j;
                }
                mesa[xr][fj-1] = 0;
                r = true;
            }
    }else if(d == 2){
            int px = xr;
            for(int i = yr;px < 5 && (mesa[px+1][i] / 10) == peca;px++);
            int mv = px;
            for(int i = yr;mv < 5 && mesa[mv+1][i] == 0;mv++);
            if((px-mv) < 0){
                int fj = 0;
                for(int j = px;(mesa[j-1][yr]/10) == peca && j > 0;j--){
                    mesa[j+1][yr] = mesa[j][yr];
                    fj = j;
                }
                mesa[fj-1][yr] = 0;
                r = true;
        }
        }
    }else if(b == 2){
        if(d == 1){
            int py = yr;
            for(int i = xr;py > 0 && (mesa[i][py-1] / 10) == peca;py--);
            int mv = py;
            for(int i = xr;mv > 0 && mesa[i][mv-1] == 0;mv--);
            if((py-mv) > 0){
                int fj = 0;
                for(int j = py;(mesa[xr][j+1]/10) == peca && j < 5;j++){
                    mesa[xr][j-1] = mesa[xr][j];
                    fj = j;
                }
                mesa[xr][fj+1] = 0;
                r = true;
            }
    }else if(d == 2){
            int px = xr;
            for(int i = yr;px > 0 && (mesa[px-1][i] / 10) == peca;px--);
            int mv = px;
            for(int i = yr;mv > 0 && mesa[mv-1][i] == 0;mv--);
            if((px-mv) > 0){
                int fj = 0;
                for(int j = px;(mesa[j+1][yr]/10) == peca && j < 5;j++){
                    mesa[j-1][yr] = mesa[j][yr];
                    fj = j;
                }
                mesa[fj+1][yr] = 0;
                r = true;
            }
        }
    }
    if(peca == 1){
        if(b == 1){
            int py = yr;
            for(int i = xr;py < 5 && (mesa[i][py+1] / 10) == peca;py++);
            if(py == 5){
                r = true;
                vitoria = true;
            }
        }
    }
    glutPostRedisplay();
    return r;
}

void telavitoria(){
    float x = -(t*1.5) + 7*t + 2*t;
    float y = 7*t/2 - 2*t/2;
    placa(x,y,t,altura,1,0,0);
    x = -(t*1.5) + 6*t + 2*t;
    y = 6*t/2 - 2*t/2;
    placa(x,y,t,altura,1,0,0);
    glBegin(GL_POLYGON);
        glColor3f(0.2,0.2,0.2);
        glVertex2f(-10,-2);
        glVertex2f(14,10);
        glVertex2f(38,-2);
        glVertex2f(14,-14);
    glEnd();
    char completo[30];
    itoa(click,completo,10);
    char texto[100] = "voce clicou ";
    strcat(texto,completo);
    char* p;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRasterPos2f(-40,5);
    glTranslatef(-10, -10, 1);
    glScalef(0.05,0.05,0.05);
    glColor3f(1,0,1);
    for(p=texto; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();
    glutPostRedisplay();
}

void addobstaculos(int valor,int x,int y,int tamanho,int direcao){
    if(direcao == 1){
        for(int i = y;i < y+tamanho;i++){
            mesa[x][i] = valor;
        }
    }else if(direcao == 2){
        for(int i = x;i < x+tamanho;i++){
            mesa[i][y] = valor;
        }
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
    else if(x >= 344 && x <= 421 && y >= 222 && y <= 255)
        return 33;
    else if(x >= 391 && x <= 470 && y >= 204 && y <= 234)
        return 34;
    else if(x >= 437 && x <= 516 && y >= 184 && y <= 214)
        return 35;
    else if(x >= 248 && x <= 328 && y >= 299 && y <= 332)
        return 40;
    else if(x >= 302 && x <= 372 && y >= 282 && y <= 310)
        return 41;
    else if(x >= 350 && x <= 419 && y >= 262 && y <= 292)
        return 42;
    else if(x >= 393 && x <= 466 && y >= 241 && y <= 271)
        return 43;
    else if(x >= 439 && x <= 511 && y >= 225 && y <= 249)
        return 44;
    else if(x >= 485 && x <= 556 && y >= 205 && y <= 232)
        return 45;
    else if(x >= 299 && x <= 368 && y >= 320 && y <= 350)
        return 50;
    else if(x >= 348 && x <= 415 && y >= 303 && y <= 326)
        return 51;
    else if(x >= 394 && x <= 465 && y >= 283 && y <= 309)
        return 52;
    else if(x >= 442 && x <= 511 && y >= 265 && y <= 289)
        return 53;
    else if(x >= 489 && x <= 559 && y >= 242 && y <= 271)
        return 54;
    else if(x >= 531 && x <= 605 && y >= 224 && y <= 252)
        return 55;
    else
        return -2;
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

    for(int i = 0;i < 7;i++){
        glBegin(GL_LINE_LOOP);
            glColor3f(1,1,1);
            glVertex2f((-6+i*4),(-4-i*2));
            glVertex2f((18+i*4),(8-i*2));
        glEnd();

        glBegin(GL_LINE_LOOP);
            glColor3f(1,1,1);
            glVertex2f((-6+i*4),(0+i*2));
            glVertex2f((18+i*4),(-12+i*2));
        glEnd();
    }
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(vitoria){
        telavitoria();
    }else{
    chao();
    float cor[3] = {0,0,0};
    for(int i = 0;i < 6;i++){
        for(int j=5;j >= 0;j--){
                if(mesa[i][j] > 0){
                    int ca = mesa[i][j] / 10;
                    switch(ca){
                    case 1:
                        //cor = {1,0,0};
                        cor[0] = 1;
                        cor[1] = 0;
                        cor[2] = 0;
                        break;
                    case 2:
                        //cor = {0,0,1};
                        cor[0] = 0;
                        cor[1] = 0;
                        cor[2] = 1;
                        break;
                    case 3:
                        //cor = {0,1,0};
                        cor[0] = 0;
                        cor[1] = 1;
                        cor[2] = 0;
                        break;
                    case 4:
                        //cor = {1,1,0};
                        cor[0] = 1;
                        cor[1] = 1;
                        cor[2] = 0;
                        break;
                    }
                    float x = -(t*1.5) + j*t + i*t;
                    float y = j*t/2 - i*t/2;
                    placa(x,y,t,altura,cor[0],cor[1],cor[2]);
                }
        }
    }
    }
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    int l = 1;
    std::cout<<"Escolha um layout. 1, 2 ou 3.";
    std::cin >> l;
    while(l<1||l>3)
    {
        std::cout<<"Escolha um layout. 1, 2 ou 3.";
        std::cin >> l;
    }
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    for(int i = 0;i < 6;i++){
        for(int j=0;j < 6;j++)
                mesa[i][j] = 0;
    }
    if(l == 1){
    addobstaculos(11,2,1,2,1);
    addobstaculos(22,1,3,3,2);
    addobstaculos(22,3,0,3,2);
    addobstaculos(31,1,0,2,1);
    addobstaculos(31,4,1,3,1);
    addobstaculos(41,0,0,2,1);
    addobstaculos(41,5,3,2,1);
    }else if(l == 2){
        addobstaculos(11,2,0,2,1);
        addobstaculos(22,0,1,2,2);
        addobstaculos(22,0,4,3,2);
        addobstaculos(22,4,3,2,2);
        addobstaculos(31,3,0,3,1);
        addobstaculos(31,5,4,2,1);
        addobstaculos(41,4,4,2,1);
    }
    else if(l == 3){
        addobstaculos(11,2,2,2,1);
        addobstaculos(22,1,4,3,2);
        addobstaculos(22,2,1,3,2);
        addobstaculos(31,0,3,3,1);
        addobstaculos(31,4,2,3,1);
        addobstaculos(41,1,1,2,1);
        addobstaculos(41,5,0,4,1);
    }
    glutCreateWindow("Lista CG");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glClearColor(1,1,1,1);
    glOrtho(-15,40,-25,25,-25,25);
    glutMainLoop();

    return EXIT_SUCCESS;
}
