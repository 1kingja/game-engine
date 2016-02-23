#ifndef SANDBOX_MY_GL_WINDOW_H
#define SANDBOX_MY_GL_WINDOW_H
#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

class QKeyEvent;

class MyGlWindow : public QGLWidget
{
	Q_OBJECT

	GLuint vertexBufferID;
	QTimer myTimer;
protected:
	void initializeGL();
	void paintGL();
private slots:
	void myUpdate();
	void updateVelocity();

public:
	bool initialize();
	bool shutdown();
};

#endif
