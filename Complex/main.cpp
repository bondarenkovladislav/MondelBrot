//
//  main.cpp
//  Complex
//
//  Created by Владислав Бондаренко on 16.12.2017.
//  Copyright © 2017 Владислав Бондаренко. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <GLUT/GLUT.h>

double x, y;
float ScaleX=0,ScaleY=0;
double Scale = 1.0;

class Complex //класс комплексных чисел, необходимый для расчетов
{
private:
    double r, i;
public:
    Complex(double r, double i)
    { this->r = r; this->i = i; }
    Complex operator+(const Complex &c)
    { return Complex(r + c.r, i + c.i); }
    Complex operator*(const Complex &c)
    { return Complex(r * c.r - i * c.i, 2 * r * c.i); }
    double abs(){return r * r + i * i;}
};

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef((-ScaleX), (-ScaleY), 0);
    glScalef(Scale, Scale, 1);
    glBegin(GL_POINTS);
    for (int y = 0; y < 800; y++) //построение множества
        for (int x = 0; x < 1200; x++)
        {
            Complex z(0, 0);
            int i = 0;
            while (i < 500 && z.abs() < 16)
            {
                //z = z * z + Complex((x - 600) / 180.0, (y - 400) / 180.0);
                //z = z * z + Complex((x + 3500) / 10240.0, (y - 2000) / 10240.0);
                //z = z * z + Complex((x + 4500) / 12000.0, (y - 3000) / 12000.0);
                //z = z * z + Complex((x + 19810) / 65536.0, (y - 2200) / 65536.0);
                z = z * z + Complex((x + 272000) / 1048576.0, (y - 2200) / 1048576.0);
                i++;
            }
            double r = 0.1098+(i*0.00329)*0.45;
            double g = 0.1824+(i*0.00329)*0.78;
            double b = 0.29412+(i*0.0329)*0.35;
            glColor3d(r, g, b);
            glVertex2d(x, y);
        }
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void Timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(50, Timer, 0);
}

void Keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '+': Scale += 1.0;
            glutPostRedisplay();
            break;
        case '-': Scale -= 1.0;
            glutPostRedisplay();
            break;
    }
}
void SKeyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT: ScaleX-=50;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: ScaleX+=50;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP: ScaleY+=50;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN: ScaleY-=50;
            glutPostRedisplay();
    }
}

int main (int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Mandelbrot");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutTimerFunc(50, Timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    //printf("Введите коэфицент увеличения, координаты x,y\n");
    //scanf("%lf %f %f",&Scale, &ScaleX,&ScaleY);
    glutMainLoop();
}
