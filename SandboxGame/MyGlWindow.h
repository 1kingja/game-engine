#ifndef SANDBOX_MY_GL_WINDOW_H
#define SANDBOX_MY_GL_WINDOW_H
#include <QtOpenGL\qglwidget>

class MyGlWindow : public QGLWidget
{
protected:
	void initializeGL();
};

#endif
