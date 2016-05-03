#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>      // (or others, depending on the system in use)
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;
#define SIZE 100

char line[SIZE];
double rotate_by_key=0;
double zoom_factor=1.0;
double y_axis = 80008;
double x_axis = 2322116;

void init(void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0);       // Set display-window color to white.
   glMatrixMode (GL_PROJECTION);          // Set projection parameters.
   glLoadIdentity();    
   gluOrtho2D (-200000, 340840, 0, 600000);    //視窗大小 
   glMatrixMode(GL_MODELVIEW);
}
 void keyPress(int key,int x,int y)
{
    if(key==27)                 //This is Esc on keyboard
          exit(0);
    if (key == GLUT_KEY_UP)
            x_axis += (30000 - (double)zoom_factor*100);
    if (key == GLUT_KEY_DOWN)
            x_axis -= (30000 - (double)zoom_factor*100);
    if (key == GLUT_KEY_LEFT)
            y_axis -= (30000 - (double)zoom_factor*100);
    if (key == GLUT_KEY_RIGHT)
            y_axis += (30000 - (double)zoom_factor*100);
    if (key == GLUT_KEY_PAGE_UP)      //This is 9 on keyboard
            zoom_factor -=.03f;
    if (key == GLUT_KEY_PAGE_DOWN)      //This is 0 on keyboard
            zoom_factor +=.01f;     
    
    glutPostRedisplay();            //To initial the window and refresh the map
}
void initRendering()
{
    glEnable(GL_NORMALIZE);
}

//Called when the window is resized
void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    glLoadIdentity();           //Reset the camera
    gluPerspective(45, (double)w / (double)h,1.0,500.0);  
    //The camera angle,the width-to-height ratio, the near z clipping coordinate, the far z clipping coordinate
    glMatrixMode(GL_MODELVIEW);
}


void display (void)
{    
      
       glClear(GL_COLOR_BUFFER_BIT);
       glColor3f(0.0,0.0,0.0);
       glLineWidth(2.0);
       glLoadIdentity();
       glScalef( 1.0f/zoom_factor,1.0f/zoom_factor,1.0f);      
       fstream fin;
       fin.open("country_output.txt",ios::in);
       double a,b,c,d;
       glBegin(GL_LINES);
       int i=0;
       while(fin.getline(line,sizeof(line),'\n')){
           i++;
           
           if (i%2==1)
               a=strtod(line,NULL);
               a-=y_axis;
           if (i%2==0) {    
               b=strtod(line,NULL);
               b-=x_axis;
               glVertex2f(a,b);
           }     
       }
       glEnd();
       glFlush ( );     // Process all OpenGL routines as quickly as possible.
       glutSwapBuffers();
      
}

 int main (int argc, char** argv)
 {   
       
       glutInit (&argc, argv);                              // Initialize GLUT.  
       glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);   // Set display mode.  
       glutInitWindowPosition (50, 50);                     // 左上角位於總視窗原點    
       glutInitWindowSize (1000, 1000);                     // 總視窗大小
       glutCreateWindow ("country");                          //視窗名稱
       init ( );  
       //initRendering();                                   // Execute initialization procedure.
       //glutReshapeFunc(handleResize); 
       glutSpecialFunc(keyPress);
       glutDisplayFunc(display);
       glutMainLoop();                                  // Display everything and wait.
       cout << "HELLO"<<endl;
       system("PAUSE");
       return(0);
 }


