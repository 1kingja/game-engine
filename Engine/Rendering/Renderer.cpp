#include <GL\glew.h>
#include "Renderer.h"
#include <cassert>

namespace Rendering
{

	bool Renderer::initialize()
	{
		numGeometries = 0;
		numRenderables = 0;
		return true;
	}

	void Renderer::initializeGL()
	{
		GLenum status = glewInit();
		assert(status == 0);

		glGenBuffers(1, &vertexBufferID);
		glGenBuffers(1, &indexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

		glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	}

	bool Renderer::shutdown()
	{
		if (vertexBufferID != -1)
			glDeleteBuffers(1, &vertexBufferID);
		if (indexBufferID != -1)
			glDeleteBuffers(1, &indexBufferID);
		return true;
	}

	Geometry* Renderer::addGeometry(
		Math::Vector3D* vertices, uint numVerts,
		ushort* indices, uint numIndices)
	{
		assert(numGeometries != NUM_MAX_GEOMETRIES);
		Geometry& g = geometries[numGeometries++];
		g.vertices = vertices;
		g.numVerts = numVerts;
		g.indices = indices;
		g.numIndices = numIndices;
		return &g;
	}

	Renderable* Renderer::addRenderable(Geometry* geometry)
	{
		assert(numRenderables != NUM_MAX_RENDERABLES);
		Renderable& r = renderables[numRenderables++];
		r.what = geometry;
		return &r;
	}

	void Renderer::rendererScene()
	{
		glDraw();
	}

	void Renderer::paintEvent()
	{

	}

	void Renderer::paintGL()
	{

	}

}