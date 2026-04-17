#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265f;

// Basic circle for trees/foliage
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

// Simple house with basic primitives
void drawHouse(float x, float y, float r, float g, float b, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);
    glColor3f(0.9f, 0.85f, 0.75f); // Wall color
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.2f, 0.15f);
    glVertex2f(0.0f, 0.15f);
    glEnd();
    glColor3f(r, g, b); // Roof color
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, 0.15f);
    glVertex2f(0.23f, 0.15f);
    glVertex2f(0.1f, 0.28f);
    glEnd();
    glColor3f(0.2f, 0.1f, 0.0f); // Door
    glBegin(GL_QUADS);
    glVertex2f(0.07f, 0.0f);
    glVertex2f(0.13f, 0.0f);
    glVertex2f(0.13f, 0.08f);
    glVertex2f(0.07f, 0.08f);
    glEnd();
    glPopMatrix();
}

// Tree with trunk and leaves
void drawTree(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);
    glColor3f(0.4f, 0.2f, 0.1f); // Trunk
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Grass field
    glColor3f(0.25f, 0.75f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -0.2);
    glVertex2f(1.0, -0.2);
    glVertex2f(1.0, -0.65);
    glVertex2f(-1.0, -0.65);
    glEnd();

    // Render houses and trees
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
    glutCreateWindow("Step 1 - Foundation");
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
