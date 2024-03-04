#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.1416

struct Point
{
    float x,y;
};

int boardLength = 160;
int boardLeft = 20;
int boardRight = 180;
int boardBottom = 5;
int boardTop = 165;

struct Point centerE = {100, 162}; //Enemy Center Coordinate
struct Point centerE2={100,162};//Enemy2 Center Coordinate
struct Point centerA = {30,130}; //Agent Center Coordinate
float radiusE = 5; //Enemy Radius
float radiusE2=5;//Enemy2 Radius
float radiusA = 10; //Agent Radius
float velocity = 0.02;
float velocity2 = 0.02;

bool isAgentDestroyed = false;
bool isGameFinished = false;

int score1 = 0; //Game score
int score2=0;
int enemyState = 0; //Enemy state 0,1,2,3
int enemyState2=0;//Enemy state 0,1,2,3

void drawCirlePerimeter(float cx, float cy, float radius, int slices)
{
    int i;
    float angle, x, y;
    glBegin(GL_LINE_LOOP);
    {
        for(i=0; i<slices; i++)
        {
            angle = ((2 * PI)/slices) * i;
            x = cx + radius * cos(angle);
            y = cy + radius * sin(angle);
            glVertex2f(x, y);
        }
    }
    glEnd();
}

void drawCircleWithPolygon(float cx, float cy, float radius, int slices)
{
    int i;
    float angle, x, y;
    glBegin(GL_POLYGON);
    {
        for(i=0; i<slices; i++)
        {
            angle = ((2 * PI)/slices) * i;
            x = cx + radius * cos(angle);
            y = cy + radius * sin(angle);
            glVertex2f(x, y);
        }
    }
    glEnd();
}

void drawCircleWithTriangles(float cx, float cy, float radius, int slices)
{
    int i;
    float angle1, angle2;

    glBegin(GL_TRIANGLES);
    {
        for(i=0; i<slices; i++)
        {
            angle1 = ((2*PI)/slices) * i;
            angle2 = ((2*PI)/slices) * (i+1);

            glVertex2f(cx, cy);
            glVertex2f(cx + radius * cos(angle1), cy + radius * sin(angle1));
            glVertex2f(cx + radius * cos(angle2), cy + radius * sin(angle2));
        }
    }
    glEnd();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    {
        glColor3f(1,1,1);
        glVertex2d(-25,0);
        glVertex2d(25, 0);

        glVertex2d(0,-25);
        glVertex2d(0,25);
    }
    glEnd();

    //Border
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
    {
        glVertex2d(20,165);
        glVertex2d(180,165);
        glVertex2d(180,5);
        glVertex2d(20,5);
    }
    glEnd();

    //Enemy
    glColor3f(1,0,0);
    glPushMatrix();
    {
        drawCircleWithPolygon(centerE.x, centerE.y, radiusE, 40);
    }
    glPopMatrix();

        //Enemy2
    glColor3f(1,1,0);
    glPushMatrix();
    {
        drawCircleWithPolygon(centerE2.x, centerE2.y, radiusE2, 40);
    }
    glPopMatrix();

    //Agent
    if(!isAgentDestroyed)
    {
        glColor3f(0,1,0);
        glPushMatrix();
        {
            drawCircleWithPolygon(centerA.x, centerA.y, radiusA, 40);
        }
        glPopMatrix();
    }

    glFlush();
}

void animate()
{
    if(!isGameFinished)
    {
        score1++;
        score2++;


        float factor;
        float factor2;

        if(enemyState == 0 || enemyState2 == 0)
        {
            factor = 2.038;
            centerE.x += velocity;
            centerE.y -= factor * velocity;

            if(centerE.x>boardRight-radiusE || centerE.y<= (boardBottom+radiusE))
            {
                enemyState = 1;

            }


            factor2 = 0.8;
            centerE2.x += velocity2;
            centerE2.y -= factor2 * velocity2;

             if( centerE2.x> (boardRight-radiusE2) || centerE2.y <(boardTop-65))
            {

                 enemyState2= 1;
            }

        }



        else if(enemyState == 1 || enemyState2==1)
        {
            factor = 0.573;
            centerE.x -= velocity;
            centerE.y += factor*velocity;

            if(centerE.x<(boardLeft-radiusE ) ||centerE.y>=(boardBottom+90))
            {
                enemyState = 2;
            }


            factor2 = 1;
            centerE2.x -= velocity2;
            centerE2.y += 0;

              if( centerE2.x<(boardLeft+80) || centerE2.y ==(boardTop-65))
            {

                 enemyState2= 2;
            }
        }
        else if(enemyState == 2 || enemyState2==2)
        {
            factor = 1.125;
            centerE.x += velocity;
            centerE.y -= factor * velocity;

            if(centerE.x >= ((boardLeft+boardRight)/2) || centerE.y <=(boardBottom+radiusE))
            {
                enemyState = 3;
            }

            factor2 = 1.26;
            centerE2.x -= velocity2;
            centerE2.y -= factor2 * velocity2;

              if( centerE2.x< (boardLeft+radiusE2) || centerE2.y <=(boardBottom+radiusE2))
            {

                 enemyState2= 3;
            }
        }

        else if(enemyState == 3 || enemyState2 == 3 )
        {
            factor = 1;
            centerE.x += 0;
            centerE.y += factor *velocity;



            if(centerE.x== ((boardLeft+boardRight)/2) || centerE.y>=(boardTop-radiusE))
            {
                enemyState = 0;
            }


            factor2 = 2.066;
            centerE2.x += velocity2;
            centerE2.y += factor2 * velocity2;
           if( centerE2.x>(boardLeft+80) || centerE2.y >(boardTop-radiusE2))
            {

                 enemyState2= 0;
            }
        }


        double distAE = sqrt(pow((centerE.x-centerA.x),2) + pow((centerE.y-centerA.y),2));
        if(distAE <= radiusA+radiusE)
        {
            isAgentDestroyed = true;
            isGameFinished = true;
        }
    }
    else{
        printf("Score : %d\n", score1);
        exit(0);
    }

    glutPostRedisplay();
}



void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glOrtho(-2.0, 200.0, -2.0, 200.0, -25.0, 25.0);
}

void keyboard_action(unsigned char key, int x, int y)
{
    if(!isGameFinished)
    {
        if(key == 'u' && centerA.y<boardTop-radiusA)
        {
            centerA.y += 0.5;
        }
        else if(key == 'd' && centerA.y>boardBottom+radiusA)
        {
            centerA.y -= 0.5;
        }
    }

    glutPostRedisplay();
}

void special_action(int key, int x, int y)
{
    if(!isGameFinished)
    {
        if(key == GLUT_KEY_LEFT && centerA.x>boardLeft+radiusA)
        {
            centerA.x -= 0.5;
        }
        else if(key == GLUT_KEY_RIGHT && centerA.x<boardRight-radiusA)
        {
            centerA.x += 0.5;
        }
    }

    glutPostRedisplay();
}

int main()
{
    //Rasterization
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("2D Objects");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(animate);

    glutKeyboardFunc(keyboard_action);
    glutSpecialFunc(special_action);
    glutMainLoop();
    return 0;
}
