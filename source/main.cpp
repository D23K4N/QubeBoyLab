#include <Windows.h>
#include "res.h"
#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
int DrawGLScene(GLvoid);


void DrawCube(float x,float y,float z, float dx, float dy, float dz)
{
  glEnable(GL_DEPTH_TEST);
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(dx, dy, dz);
  glBegin(GL_QUADS);
  glColor3d(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(1, 1, 0);
  glVertex3f(1, 0, 0);//1

  glColor3d(0, 1, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(0, 1, 1);
  glVertex3f(0, 0, 1);//2

  glColor3d(0, 0, 1);
  glVertex3f(0, 0, 1);
  glVertex3f(0, 1, 1);
  glVertex3f(1, 1, 1);
  glVertex3f(1, 0, 1);//3

  glColor3d(0, 1, 0);
  glVertex3f(1, 0, 0);
  glVertex3f(1, 1, 0);
  glVertex3f(1, 1, 1);
  glVertex3f(1, 0, 1);//4

  glColor3d(0, 1, 1);
  glVertex3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1);
  glVertex3f(1, 0, 1);//5

  glColor3d(1, 0, 1);
  glVertex3f(1, 1, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(0, 1, 1);
  glVertex3f(1, 1, 1);//6

 // glTranslatef(-x, -y, -z);
  glPopMatrix();

  glEnd();
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  MSG msg = {};
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  //ShowWindow(hwndMainWindow, iCmdShow);
  //DODANE
  static PIXELFORMATDESCRIPTOR pfd =
  {
  sizeof(PIXELFORMATDESCRIPTOR),1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0, 16,0,0, PFD_MAIN_PLANE,0,0 ,0 ,0 };

  HDC hDC = NULL;
  HGLRC hRC = NULL;
  GLuint PixelFormat;

  if (!(hDC = GetDC(hwndMainWindow))) return 0;
  if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) return 0;

  if (!(SetPixelFormat(hDC, PixelFormat, &pfd))) return 0;
  if (!(hRC = wglCreateContext(hDC))) return 0;
  if (!wglMakeCurrent(hDC, hRC)) return 0;

  ShowWindow(hwndMainWindow, SW_SHOW);
  SetForegroundWindow(hwndMainWindow);
  SetFocus(hwndMainWindow);

  BOOL done = false;
  while (!done)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) { done = true; }
      else
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
    else
    {
      DrawGLScene();
      SwapBuffers(hDC);
    }
  }
  if (hRC)
  {
    !wglMakeCurrent(NULL, NULL);
    !wglDeleteContext(hRC);
    hRC = NULL;
  }
  if (hDC && !ReleaseDC(hwndMainWindow, hDC)) { hDC = NULL; };
  if (hwndMainWindow && !DestroyWindow(hwndMainWindow)) { hwndMainWindow = NULL; };

  MessageBox(0, TEXT("hejka naklejka"), TEXT("Informacja"), MB_OK);
  return 0;
}




//  while (1);

  /*
 
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  //while (1);

  */

//}





INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_SIZE:
    ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
    return true;
  }
  return false;
}


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
  if(height==0)
  {
    height = 1;
  }

  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


int DrawGLScene(GLvoid)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  static float rot = 0;

  glLoadIdentity();
  glTranslatef(0, 0, -10);
  glRotatef(rot, 1, 1, 0);
  rot += 0.1;
  glBegin(GL_LINES);
  glColor3d(1, 0, 0);
  glVertex3d(10, 0, 0);
  glVertex3d(-10, 0, 0);

  glColor3d(0, 1, 0);
  glVertex3d(0, 10, 0);
  glVertex3d(0, -10, 0);

  glColor3d(0, 0, 1);
  glVertex3d(0, 0, 10);
  glVertex3d(0, 0, -10);

  glEnd();

  DrawCube(0,0,0,1,1,1);
  DrawCube(0.1, 1, 0.25, 0.5,0.5,0.5);

  return 1;
}

/*

armia maszerujących ludzików


*/