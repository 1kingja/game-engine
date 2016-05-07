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
	Vector3D shipVerts[] =
	{
		Vector3D(+0.0f, +0.14142135623f, 1),
		Vector3D(-0.1f, -0.1f, 1),
		Vector3D(+0.1f, -0.1f, 1),
	};

	Vector3D boundaryVerts[] =
	{
		Vector3D(+0.0f, +1.0f, +0.0f),
		Vector3D(-1.0f, +0.0f, +0.0f),
		Vector3D(+0.0f, -1.0f, +0.0f),
		Vector3D(+1.0f, +0.0f, +0.0f),
	};

	GLushort boundaryIndices[] = { 0, 1, 1, 2, 2, 3, 3, 0 };

	const unsigned int NUM_SHIP_VERTS = sizeof(shipVerts) / sizeof(*shipVerts);
	const unsigned int NUM_BOUNDARY_VERTS = sizeof(boundaryVerts) / sizeof(*boundaryVerts);
	GLuint shipVertexBufferID;
	GLuint boundaryVertexBuffersID;
	GLuint boundaryIndexBufferID;
	Vector3D transformedVerts[NUM_SHIP_VERTS];
	Vector3D shipPosition;
	Vector3D shipVelocity;
	float shipOrientation = 0.0f;
	Clock clock;
}

void MyGlWindow::initializeGL()
{
	GLenum errCode = glewInit();
	assert(errCode == 0);

	glEnableVertexAttribArray(0);

	glGenBuffers(1, &shipVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, shipVertexBufferID);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(shipVerts),
		NULL,GL_DYNAMIC_DRAW);

	glGenBuffers(1, &boundaryVertexBuffersID);
	glBindBuffer(GL_ARRAY_BUFFER, boundaryVertexBuffersID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boundaryVerts), 
		boundaryVerts, GL_STATIC_DRAW);

	glGenBuffers(1, &boundaryIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundaryIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boundaryIndices),
		boundaryIndices, GL_STATIC_DRAW);

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
	handleBoundaries();
	shipPosition += shipVelocity * clock.lastLapTime();
}

void MyGlWindow::doGl()
{
	// Setup viewport
	glViewport(0, 0, width(), height());

	// Setup data pointers
	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, shipVertexBufferID);
	glBufferSubData(
		GL_ARRAY_BUFFER, 0,
		sizeof(transformedVerts),
		transformedVerts);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, boundaryVertexBuffersID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, 0);
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
		for (unsigned int i = 0; i < NUM_SHIP_VERTS; i++)
			transformedVerts[i] = op * shipVerts[i];
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

void MyGlWindow::handleBoundaries()
{
	for (uint i = 0; i < NUM_BOUNDARY_VERTS; i++)
	{
		const Vector3D& first = boundaryVerts[i];
		const Vector3D& second = boundaryVerts[(i + 1) % NUM_BOUNDARY_VERTS];

		Vector3D wall = second - first;
		Vector3D normal = wall.perpCcwXy().normalized();
		Vector3D respectiveShipPosition = shipPosition - first;
		float dotResult = normal.dot(respectiveShipPosition);

		if(dotResult < 0)
		{
			shipVelocity = shipVelocity -2 * shipVelocity.dot(normal) * normal;
		}
	}
}