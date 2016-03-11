#include <GL\glew.h>
#include "MyGlWindow.h"
#include <cassert>
#include <Qt\qdebug.h>
#include <QtGui\QKeyEvent>
#include <Math\Vector3D.h>
#include <Math\Matrix3D.h>
#include <Timing\Clock.h>
using Math::Vector3D;
using Math::Matrix3D;
using Timing::Clock;

namespace 
{
	Vector3D verts[] =
	{
		Vector3D(+0.0f, +0.14142135623f),
		Vector3D(-0.1f, -0.1f),
		Vector3D(+0.1f, -0.1f),
	};
	const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);
	Vector3D shipPosition;
	Vector3D shipVelocity;
	float shipOrientation = 0.0f;
	Clock clock;
}

void MyGlWindow::initializeGL()
{
	GLenum errCode = glewInit();
	assert(errCode == 0);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),
		NULL,GL_DYNAMIC_DRAW);

	connect(&myTimer, SIGNAL(timeout()),
		this,SLOT(myUpdate()));
	myTimer.start(1);
}

void MyGlWindow::paintGL()
{
	int minSize = min(width(), height());
	Vector3D viewportLocation;
	viewportLocation.x = width() / 2 - minSize / 2;
	viewportLocation.y = height() / 2 - minSize / 2;
	glViewport(viewportLocation.x, viewportLocation.y, minSize, minSize);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,0);

	Vector3D transformedVerts[NUM_VERTS];
	Matrix3D translator = Matrix3D::translate(shipPosition.x, shipPosition.y);
	Matrix3D rotator = Matrix3D::rotateZ(shipOrientation);

	Matrix3D op = translator * rotator;
	for (unsigned int i = 0; i < NUM_VERTS;i++)
		transformedVerts[i] = op * verts[i];
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, 
		sizeof(transformedVerts),
		transformedVerts);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGlWindow::myUpdate()
{
	clock.newFrame();
	rotateShip();
	updateVelocity();
	shipPosition += shipVelocity * clock.timeElapsedLastFrame();
	repaint();
}

bool MyGlWindow::initialize()
{
	return clock.initialize();
}

bool MyGlWindow::shutdown()
{
	return clock.shutdown();
}

void MyGlWindow::rotateShip()
{
	const float ANGULAR_MOVEMENT = 0.1f;
	if (GetAsyncKeyState(VK_RIGHT))
		shipOrientation -= ANGULAR_MOVEMENT;
	if (GetAsyncKeyState(VK_LEFT))
		shipOrientation += ANGULAR_MOVEMENT;
}

void MyGlWindow::updateVelocity()
{
	const float ACCELERATION = 0.3f * clock.timeElapsedLastFrame();

	Vector3D directionToAccelerate(-sin(shipOrientation),cos(shipOrientation));

	if (GetAsyncKeyState(VK_UP))
		shipVelocity += directionToAccelerate * ACCELERATION;
}