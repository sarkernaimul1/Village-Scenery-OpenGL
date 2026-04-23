//Village Scenery with Moving Elements.

#include <GL/glut.h>
#include <cmath>

float cloud1X = -0.7f, cloud2X = 0.2f, cloud3X = -1.1f;
float birdX = -1.1f, wingAngle = 0.0f;
float boat1X = -0.5f, boat2X = 0.6f;
float sunScale = 1.0f;
bool sunGrow = true, wingDown = true;

const float PI = 3.14159265f;

void drawLineDDA(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1, dy = y2 - y1;
    float steps = fmax(abs(dx), abs(dy)) * 1000;
    float xInc = dx / steps, yInc = dy / steps;
    float x = x1, y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        glVertex2f(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();
}

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

void drawMidpointCircle(float xc, float yc, float r)
{
    int ri = (int)(r * 1000);
    int x = 0;
    int y = ri;
    int d = 1 - ri;
    float scale = 1.0f / 1000.0f;

    while (x <= y)
    {
        glBegin(GL_LINES);

        glVertex2f(xc + x * scale, yc + y * scale);
        glVertex2f(xc + x * scale, yc - y * scale);

        glVertex2f(xc - x * scale, yc + y * scale);
        glVertex2f(xc - x * scale, yc - y * scale);

        glVertex2f(xc + y * scale, yc + x * scale);
        glVertex2f(xc + y * scale, yc - x * scale);

        glVertex2f(xc - y * scale, yc + x * scale);
        glVertex2f(xc - y * scale, yc - x * scale);

        glEnd();

        if (d < 0)
        {

            d += 2 * x + 3;
        }
        else
        {

            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void drawBush(float x, float y)
{
    glColor3f(0.0f, 0.4f, 0.0f);
    drawFilledCircle(x, y, 0.05f);
    drawFilledCircle(x + 0.04f, y + 0.02f, 0.06f);
    drawFilledCircle(x - 0.04f, y + 0.01f, 0.04f);
}

//Human Figure (Boatman)
void drawHuman(float x, float y, bool faceRight)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.8f, 0.6f, 0.4f);
    drawFilledCircle(0.0f, 0.08f, 0.022f); //Head

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    drawLineDDA(0.0f, 0.06f, 0.0f, 0.0f);

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

void drawSun()
{
    glPushMatrix();
    glTranslatef(0.75f, 0.85f, 0.0f);
    glScalef(sunScale, sunScale, 1.0f); // Pulse effect animation
    glColor3f(1.0f, 0.9f, 0.0f);
    drawMidpointCircle(0.0f, 0.0f, 0.12f);
    glPopMatrix();
}

void drawCloud(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.0f, 0.0f, 0.07f);
    drawFilledCircle(0.08f, 0.02f, 0.09f);
    drawFilledCircle(-0.05f, 0.01f, 0.06f);
    glPopMatrix();
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

void drawSailBoat(float bX, float bY, float s, bool movingRight)
{
    glPushMatrix();
    glTranslatef(bX, bY, 0.0f);
    glScalef(s, s, 1.0f);

    glColor3f(0.35f, 0.15f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.0f);
    glVertex2f(0.15f, 0.0f);
    glVertex2f(0.18f, 0.07f);
    glVertex2f(-0.18f, 0.07f);
    glEnd();

    if (movingRight) drawHuman(-0.13f, 0.07f, true);
    else drawHuman(0.13f, 0.07f, false);

    glColor3f(0.2f, 0.1f, 0.0f);
    drawLineDDA(0.0f, 0.07f, 0.0f, 0.3f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    if(movingRight)
    {
        glVertex2f(0.01f, 0.28f);
        glVertex2f(0.01f, 0.1f);
        glVertex2f(0.15f, 0.18f);
    }
    else
    {
        glVertex2f(-0.01f, 0.28f);
        glVertex2f(-0.01f, 0.1f);
        glVertex2f(-0.15f, 0.18f);
    }
    glEnd();
    glPopMatrix();
}

void drawBird(float ox, float oy)
{
    glPushMatrix();
    glTranslatef(birdX + ox, 0.32f + oy, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.5f);

    glPushMatrix();
    glRotatef(wingAngle, 0, 0, 1);
    drawLineDDA(0, 0, -0.06, 0.03);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-wingAngle, 0, 0, 1);
    drawLineDDA(0, 0, 0.06, 0.03);
    glPopMatrix();

    glPopMatrix();
}

// Main Rendering Function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.7f, 1.0f);
    glVertex2f(-1.0, 1.0);
    glColor3f(0.9f, 1.0f, 1.0f);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -0.2);
    glVertex2f(-1.0, -0.2);
    glEnd();

    drawSun();

    drawCloud(cloud1X, 0.78f, 1.0f);
    drawCloud(cloud2X, 0.68f, 0.8f);
    drawCloud(cloud3X, 0.84f, 0.7f);

    glColor3f(0.25f, 0.75f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -0.2);
    glVertex2f(1.0, -0.2);
    glVertex2f(1.0, -0.65);
    glVertex2f(-1.0, -0.65);
    glEnd();

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

    drawBush(-0.25f, -0.35f);
    drawBush(0.35f, -0.55f);
    drawBush(0.75f, -0.62f);

    glPushMatrix();
    glTranslatef(0.18f, -0.25f, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f);
    drawBush(0, 0);
    glPopMatrix();

    drawTree(-0.95f, -0.32f, 1.0f);
    drawHouse(-0.85f, -0.52f, 0.7f, 0.1f, 0.1f, 1.0f);
    drawTree(-0.62f, -0.28f, 0.75f);
    drawHouse(-0.52f, -0.42f, 0.2f, 0.4f, 0.8f, 0.7f);
    drawTree(-0.32f, -0.22f, 0.55f);
    drawTree(0.32f, -0.22f, 0.55f);
    drawHouse(0.42f, -0.42f, 0.5f, 0.2f, 0.1f, 0.7f);
    drawTree(0.68f, -0.28f, 0.75f);
    drawHouse(0.78f, -0.52f, 0.1f, 0.5f, 0.2f, 1.0f);
    drawTree(0.98f, -0.32f, 1.0f);

    glColor3f(0.0f, 0.45f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -0.65);
    glVertex2f(1.0, -0.65);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    drawSailBoat(boat1X, -0.82f, 1.1f, true);
    drawSailBoat(boat2X, -0.94f, 0.9f, false);

    drawBird(0, 0);
    drawBird(0.2f, 0.05f);
    drawBird(-0.2f, 0.1f);

    glutSwapBuffers();
}

// Animation Controller
void timer(int val)
{
    cloud1X += 0.001f;
    if (cloud1X > 1.3f) cloud1X = -1.3f;
    cloud2X += 0.0008f;
    if (cloud2X > 1.3f) cloud2X = -1.3f;
    cloud3X += 0.0014f;
    if (cloud3X > 1.3f) cloud3X = -1.3f;

    birdX += 0.0045f;
    if (birdX > 1.3f) birdX = -1.3f;
    boat1X += 0.0025f;
    if (boat1X > 1.3f) boat1X = -1.3f;
    boat2X -= 0.002f;
    if (boat2X < -1.3f) boat2X = 1.3f;

    if (wingDown)
    {
        wingAngle += 9.0f;
        if (wingAngle > 35.0f) wingDown = false;
    }
    else
    {
        wingAngle -= 9.0f;
        if (wingAngle < -35.0f) wingDown = true;
    }

    if (sunGrow)
    {
        sunScale += 0.001f;
        if (sunScale > 1.05f) sunGrow = false;
    }
    else
    {
        sunScale -= 0.001f;
        if (sunScale < 0.95f) sunGrow = true;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

//Main Function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Village Scenery with Moving Elements");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}
