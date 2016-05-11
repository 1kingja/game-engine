#include "MyGame.h"
#include <Rendering\Renderable.h>

bool MyGame::initalize()
{
	Geometry* shipGeometry =
		renderer.addGeometry(
			shipVerts, numShipVerts,
			shipIndices, numShipIndices);
	shipInstance = renderer.addRenderable(shipGeometry);
	lerpInstance = renderer.addRenderable(shipGeometry);
}

void MyGame::update()
{
	shipInstance->where = Matrix2DH::translate(shipPosition); 
	lerpInstance->where = Matrix2DH::translate(lerperPosition);
}