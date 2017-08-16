#include<GL/gl.h>
#include<GL/glut.h>

GLfloat xAngle, yAngle, zAngle;
void DoDisplay()
{
     static GLfloat vertcolor[] = {
          1,1,1,  0, 0, -0.8,          // 중앙
          0,0,1,  0.5, 0.5, 0,    // 우상
          1,0,0,  -0.5, 0.5, 0,   // 좌상
          1,1,0,  -0.5, -0.5, 0,  // 좌하
          0,1,0,  0.5, -0.5, 0,   // 우하
     };
 
     static GLubyte index[] = {
          0, 1, 2,              //12시
          0, 2, 3,              // 9시
          0, 3, 4,              // 6시
          0, 4, 1,              // 3시
     };
 
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glEnable(GL_DEPTH_TEST);
     glShadeModel(GL_FLAT);
 
     glMatrixMode(GL_MODELVIEW);
     glPushMatrix();
     glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
     glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
     glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
 
     glColor3f(1,1,1);
     glRectf(-0.5, 0.5, 0.5, -0.5);
 
     glEnableClientState(GL_VERTEX_ARRAY);
     glVertexPointer(3, GL_FLOAT, sizeof(GLfloat)*6, &vertcolor[3]);
     glEnableClientState(GL_COLOR_ARRAY);
     glColorPointer(3, GL_FLOAT, sizeof(GLfloat)*6, vertcolor);
 
     glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, index);
 
     glPopMatrix();
     glFlush();
}

void DoKeyboard(unsigned char key, int x, int y)
{
     switch(key) {
     case 'a':yAngle += 2;break;
     case 'd':yAngle -= 2;break;
     case 'w':xAngle += 2;break;
     case 's':xAngle -= 2;break;
     case 'q':zAngle += 2;break;
     case 'e':zAngle -= 2;break;
     case 'z':xAngle = yAngle = zAngle = 0.0;break;
     }
     char info[128];
     //sprintf(info, "x=%.1f, y=%.1f, z=%.1f", xAngle, yAngle, zAngle);
     glutSetWindowTitle(info);
     glutPostRedisplay();
}
int main(int argc, char **argv) {
     glutInit(&argc, argv);
     glutCreateWindow("OpenGL");
     glutDisplayFunc(DoDisplay);
     glutKeyboardFunc(DoKeyboard);
     glutMainLoop();
     return 0;

}