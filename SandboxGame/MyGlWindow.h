#ifndef SANDBOX_MY_GL_WINDOW_H
#define SANDBOX_MY_GL_WINDOW_H
#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

class QKeyEvent;

class MyGlWindow : public QGLWidget
{
	Q_OBJECT

	QTimer myTimer;
protected:
	void initializeGL();
	void paintGL();
private slots:
	void myUpdate();
	void updateVelocity();
	void checkBoundaries();
	void rotateShip();
private:
	void update();
	void draw();
	void doGl();
public:
	bool initialize();
	bool shutdown();
};

#endif
