#include <math.h>
#include <GLFW/glfw3.h>
#pragma once

const int 
windowwidth = 1366,
windowheight = 768 - 23 - 2;
const double pi = acos(-1);

void Circ(int x, int y, int radius, int angle1, int angle2, int red, int green, int blue) {

    glBegin(GL_TRIANGLES);
    glColor3b(red, green, blue);
    for (double i = angle1; i < angle2; i++) {
        glVertex2d(x, y);
        glVertex2d(x + radius * cos(i * pi / 180), y + radius * sin(i * pi / 180));
        glVertex2d(x + radius * cos((i + 1) * pi / 180), y + radius * sin((i + 1) * pi / 180));
    }
    glEnd();
}

void Point(int x, int y, int red, int green, int blue) {
    glBegin(GL_POINTS);
    glColor3b(red, green, blue);
    glVertex2d(x, y);
    glEnd();
}

void Line(int x, int y, int length, int angle, int red, int green, int blue) {

    glBegin(GL_LINES);
    glColor3b(red, green, blue);
    glVertex2d(x, y);
    glVertex2d(x + length * cos(angle * pi / 180), y + length * sin(angle * pi / 180));
    glEnd();

}

void Tri(int x1, int y1, int x2, int y2, int x3, int y3, int red, int green, int blue) {
    glBegin(GL_TRIANGLES);
    glColor3b(red, green, blue);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glVertex2d(x3, y3);

    glEnd();
}

void Rect(int x, int y, int angle, int length, int height, int red, int green, int blue) {

    double theta = pi / 180 * angle;
    glBegin(GL_QUADS);
    glColor3b(red, green, blue);
    glVertex2d(x, y);
    glVertex2d(x + length * cos(theta), y + length * sin(theta));
    glVertex2d(x + length * cos(theta) - length * sin(theta), y + height * sin(theta) + height * cos(theta));
    glVertex2d(x - length * sin(theta), y + height * cos(theta));
    glEnd();

}
