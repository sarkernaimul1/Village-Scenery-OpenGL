#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

const float PI = 3.14159265f;

float sunScale = 1.0f;


void drawLineDDA(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1, dy = y2 - y1;
    float steps = fmaxf(fabsf(dx), fabsf(dy)) * 1000.0f;
    float xInc = dx / steps, yInc = dy / steps;
    float x = x1, y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= (int)steps; ++i)
    {
        glVertex2f(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void drawMidpointCircle(float xc, float yc, float r)
{
    const int R = (int)(r * 800);
    int x = 0, y = R;
    int d = 1 - R;

    glBegin(GL_POINTS);
    while (x <= y)
    {
        for (int xi = -y; xi <= y; ++xi)
        {
            glVertex2f(xc + xi / 800.0f, yc + x / 800.0f);
            glVertex2f(xc + xi / 800.0f, yc - x / 800.0f);
        }
        for (int xi = -x; xi <= x; ++xi)
        {
            glVertex2f(xc + xi / 800.0f, yc + y / 800.0f);
            glVertex2f(xc + xi / 800.0f, yc - y / 800.0f);
        }
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            --y;
        }
        ++x;
    }
    glEnd();
}

void drawFilledCircle(float xc, float yc, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; ++i)
    {
        float theta = 2.0f * PI * i / 100.0f;
        glVertex2f(xc + r * cosf(theta), yc + r * sinf(theta));
    }
    glEnd();
}


void drawBush(float x, float y)
{
    glColor3f(0.0f, 0.4f, 0.0f);
    drawFilledCircle(x, y, 0.05f);
    drawFilledCircle(x + 0.04f, y + 0.02f, 0.06f);
    drawFilledCircle(x - 0.04f, y + 0.01f, 0.04f);
}

void drawHuman(float x, float y, bool faceRight)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.8f, 0.6f, 0.4f);
    drawFilledCircle(0.0f, 0.08f, 0.022f); // Head
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);
    drawLineDDA(0.0f, 0.06f, 0.0f, 0.0f); // Body
    if (faceRight)
    {
        drawLineDDA(0.0f, 0.04f, 0.05f, 0.03f);
        glColor3f(0.4f, 0.2f, 0.0f);
        drawLineDDA(0.04f, 0.05f, 0.08f, -0.04f);
    }
    else
    {
        drawLineDDA(0.0f, 0.04f, -0.05f, 0.03f);
        glColor3f(0.4f, 0.2f, 0.0f);
        drawLineDDA(-0.04f, 0.05f, -0.08f, -0.04f);
    }
    glPopMatrix();
}

void drawSailBoat(float bX, float bY, float s, bool movingRight)
{
    glPushMatrix();
    glTranslatef(bX, bY, 0.0f);
    glScalef(s, s, 1.0f);
    glColor3f(0.35f, 0.15f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.00f);
    glVertex2f(0.15f, 0.00f);
    glVertex2f(0.18f, 0.07f);
    glVertex2f(-0.18f, 0.07f);
    glEnd();

    if (movingRight) drawHuman(-0.13f, 0.07f, true);
    else drawHuman(0.13f, 0.07f, false);

    glColor3f(0.2f, 0.1f, 0.0f);
    drawLineDDA(0.0f, 0.07f, 0.0f, 0.30f); // Mast
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    if (movingRight)
    {
        glVertex2f(0.01f, 0.28f);
        glVertex2f(0.01f, 0.10f);
        glVertex2f(0.15f, 0.18f);
    }
    else
    {
        glVertex2f(-0.01f, 0.28f);
        glVertex2f(-0.01f, 0.10f);
        glVertex2f(-0.15f, 0.18f);
    }
    glEnd();
    glPopMatrix();
}

void drawHouse(float x, float y, float r, float g, float b, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);
    glColor3f(0.9f, 0.85f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(0.00f, 0.00f);
    glVertex2f(0.20f, 0.00f);
    glVertex2f(0.20f, 0.15f);
    glVertex2f(0.00f, 0.15f);
    glEnd();
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, 0.15f);
    glVertex2f(0.23f, 0.15f);
    glVertex2f(0.10f, 0.28f);
    glEnd();
    glColor3f(0.2f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.07f, 0.00f);
    glVertex2f(0.13f, 0.00f);
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
    glVertex2f(-0.015f, 0.00f);
    glVertex2f(0.015f, 0.00f);
    glVertex2f(0.010f, 0.18f);
    glVertex2f(-0.010f, 0.18f);
    glEnd();
    glColor3f(0.1f, 0.55f, 0.1f);
    drawFilledCircle(0.00f, 0.22f, 0.08f);
    drawFilledCircle(-0.06f, 0.18f, 0.06f);
    drawFilledCircle(0.06f, 0.18f, 0.06f);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Sky
    glBegin(GL_QUADS);
    glColor3f(0.40f, 0.70f, 1.00f);
    glVertex2f(-1.0f, 1.0f);
    glColor3f(0.90f, 1.00f, 1.00f);
    glVertex2f(1.0f, 1.0f);
    glColor3f(0.90f, 1.00f, 1.00f);
    glVertex2f(1.0f, -0.2f);
    glColor3f(0.40f, 0.70f, 1.00f);
    glVertex2f(-1.0f, -0.2f);
    glEnd();

    // Sun
    glPushMatrix();
    glTranslatef(0.75f, 0.85f, 0.0f);
    glColor3f(1.0f, 0.9f, 0.0f);
    drawMidpointCircle(0.0f, 0.0f, 0.12f);
    glPopMatrix();

    // Grass
    glColor3f(0.25f, 0.75f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.20f);
    glVertex2f(1.0f, -0.20f);
    glVertex2f(1.0f, -0.65f);
    glVertex2f(-1.0f, -0.65f);
    glEnd();

    // Road
    glColor3f(0.55f, 0.40f, 0.25f);
    glBegin(GL_QUAD_STRIP);
    float roadWidth = 0.15f;
    for (float y = -0.20f; y >= -0.65f; y -= 0.005f)
    {
        float cx = 0.12f * sinf(y * 12.0f);
        glVertex2f(cx - roadWidth / 2.0f, y);
        glVertex2f(cx + roadWidth / 2.0f, y);
    }
    glEnd();

    // Bushes
    drawBush(-0.25f, -0.35f);
    drawBush(0.35f, -0.55f);
    drawBush(0.75f, -0.62f);
    glPushMatrix();
    glTranslatef(0.18f, -0.25f, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f);
    drawBush(0, 0);
    glPopMatrix();

    // Houses and Trees
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

    // River
    glColor3f(0.0f, 0.45f, 0.80f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.65f);
    glVertex2f(1.0f, -0.65f);
    glVertex2f(1.0f, -1.00f);
    glVertex2f(-1.0f, -1.00f);
    glEnd();

    // Boats
    drawSailBoat(-0.5f, -0.82f, 1.1f, true);
    drawSailBoat(0.6f, -0.94f, 0.9f, false);

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
