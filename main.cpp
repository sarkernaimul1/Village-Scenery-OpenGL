#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265f;
float sunScale = 1.0f;

void drawFilledCircle(float xc, float yc, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        float theta = 2.0f * PI * float(i) / 100.0f;
        glVertex2f(xc + r * cos(theta), yc + r * sin(theta));
    }
    glEnd();
}

void drawHouse(float x, float y, float r, float g, float b, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);
    glColor3f(0.9f, 0.85f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.2f, 0.15f);
    glVertex2f(0.0f, 0.15f);
    glEnd();
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, 0.15f);
    glVertex2f(0.23f, 0.15f);
    glVertex2f(0.1f, 0.28f);
    glEnd();
    glColor3f(0.2f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.07f, 0.0f);
    glVertex2f(0.13f, 0.0f);
    glVertex2f(0.13f, 0.08f);
    glVertex2f(0.07f, 0.08f);
    glEnd();
    glPopMatrix();
}

void drawTree(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.015f, 0.0f);
    glVertex2f(0.015f, 0.0f);
    glVertex2f(0.01f, 0.18f);
    glVertex2f(-0.01f, 0.18f);
    glEnd();
    glColor3f(0.1f, 0.55f, 0.1f);
    drawFilledCircle(0.0f, 0.22f, 0.08f);
    drawFilledCircle(-0.06f, 0.18f, 0.06f);
    drawFilledCircle(0.06f, 0.18f, 0.06f);
    glPopMatrix();
}

//sun
void drawSun()
{
    glPushMatrix();
    glTranslatef(0.75f, 0.85f, 0.0f);
    glScalef(sunScale, sunScale, 1.0f);
    glColor3f(1.0f, 0.9f, 0.0f);
    drawFilledCircle(0.0f, 0.0f, 0.12f);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //Sky
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.7f, 1.0f);
    glVertex2f(-1.0, 1.0);
    glColor3f(0.9f, 1.0f, 1.0f);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -0.2);
    glVertex2f(-1.0, -0.2);
    glEnd();
    drawSun();

    //Grass
    glColor3f(0.25f, 0.75f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -0.2);
    glVertex2f(1.0, -0.2);
    glVertex2f(1.0, -0.65);
    glVertex2f(-1.0, -0.65);
    glEnd();

    //Road
    glColor3f(0.55f, 0.40f, 0.25f);
    glBegin(GL_QUAD_STRIP);
    float roadWidth = 0.15f;
    for (float y = -0.2f; y >= -0.65f; y -= 0.005f)
    {
        float curveX = 0.12f * sin(y * 12.0f);
        glVertex2f(curveX - roadWidth / 2.0f, y);
        glVertex2f(curveX + roadWidth / 2.0f, y);
    }
    glEnd();

    //Houses/Trees
    drawHouse(-0.85f, -0.52f, 0.7f, 0.1f, 0.1f, 1.0f);
    drawHouse(-0.52f, -0.42f, 0.2f, 0.4f, 0.8f, 0.7f);
    drawHouse(0.42f, -0.42f, 0.5f, 0.2f, 0.1f, 0.7f);
    drawHouse(0.78f, -0.52f, 0.1f, 0.5f, 0.2f, 1.0f);
    drawTree(-0.95f, -0.32f, 1.0f);
    drawTree(-0.62f, -0.28f, 0.75f);
    drawTree(-0.32f, -0.22f, 0.55f);
    drawTree(0.32f, -0.22f, 0.55f);
    drawTree(0.68f, -0.28f, 0.75f);
    drawTree(0.98f, -0.32f, 1.0f);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Village Scenery");
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
