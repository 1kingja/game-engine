#include <GL\glew.h>
#include "MyGlWindow.h"
#include <cassert>
#include <Qt\qdebug.h>
#include <QtGui\QKeyEvent>
#include <Math\Vector3D.h>
#include <Math\Matrix2DH.h>
#include <DebugTools\Profiling\Profile.h>
#include <DebugTools\Profiling\Profiler.h>
#include <Timing\Clock.h>
using Math::Vector3D;
using Math::Matrix2DH;
using Timing::Clock;

namespace 
{
	Vector3D verts[] =
	{
		Vector3D(+0.0f, +0.14142135623f, 1),
		Vector3D(-0.1f, -0.1f, 1),
		Vector3D(+0.1f, -0.1f, 1),
	};
	const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);
	Vector3D transformedVerts[NUM_VERTS];
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

void MyGlWindow::update()
{
	clock.lap();
	profiler.newFrame();
	rotateShip();
	updateVelocity();
	shipPosition += shipVelocity * clock.lastLapTime();
}

void MyGlWindow::doGl()
{
	// Setup viewport
	glViewport(0, 0, width(), height());

	// Setup data pointers
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Send data to OpenGl
	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(transformedVerts),
		transformedVerts);

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGlWindow::draw() 
{
	Matrix2DH translator = Matrix2DH::translate(shipPosition.x, shipPosition.y);
	Matrix2DH rotator = Matrix2DH::rotateZ(shipOrientation);
	float aspectRatio = static_cast<float>(width() / height());
	Matrix2DH scale;

	if (aspectRatio > 1)
		scale = Matrix2DH::scale(1 / aspectRatio, 1);
	else
		scale = Matrix2DH::scale(1, aspectRatio);

	Matrix2DH op;
	{
		PROFILE("Matrix Multiplication");
		op = translator * scale * rotator;
	}

	{
		PROFILE("Vector Transformation");
		for (unsigned int i = 0; i < NUM_VERTS; i++)
			transformedVerts[i] = op * verts[i];
	}
	doGl();
}

void MyGlWindow::paintGL()
{
	update();
	draw();
}

void MyGlWindow::myUpdate()
{
	repaint();
}

bool MyGlWindow::initialize()
{
	bool ret = true;
	profiler.initalize("profiles.csv");
	ret &= clock.initialize();
	return ret;
}

bool MyGlWindow::shutdown()
{
	bool ret = true;
	profiler.shutdown();
	ret &= clock.shutdown();
	return ret;
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
	const float ACCELERATION = 0.3f * clock.lastLapTime();

	Vector3D directionToAccelerate(-sin(shipOrientation),cos(shipOrientation));

	if (GetAsyncKeyState(VK_UP))
		shipVelocity += directionToAccelerate * ACCELERATION;
}