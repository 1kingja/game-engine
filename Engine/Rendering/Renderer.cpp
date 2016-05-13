#include <GL\glew.h>
#include "Renderer.h"
#include <cassert>
#include <Math\Vector3D.h>
using Math::Vector3D;

namespace Rendering
{
	bool Renderer::initialize()
	{
		vertexBufferID = -1;
		indexBufferID = -1;
		numGeometries = 0;
		numRenderables = 0;
		return true;
	}

	void Renderer::initializeGL()
	{
		GLenum status = glewInit();
		assert(status == 0);
		glClearColor(0, 0, 0, 1);

		glGenBuffers(1, &vertexBufferID);
		glGenBuffers(1, &indexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

		glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
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
		ushort* indices, uint numIndices, GLenum renderModes)
	{
		assert(numGeometries != NUM_MAX_GEOMETRIES);
		Geometry& g = geometries[numGeometries++];
		g.vertices = vertices;
		g.numVerts = numVerts;
		g.indices = indices;
		g.numIndices = numIndices;
		g.renderMode = renderModes;
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
		glClear(GL_COLOR_BUFFER_BIT);

		Vector3D transformedVerts[MAX_VERTS];

		for(uint i=0; i < numRenderables; i++)
		{
			 const Renderable& r = renderables[i];

			// Indices
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
				sizeof(ushort) * r.what->numIndices, r.what->indices);

			//Vertices
			for(uint j =0; j < r.what->numVerts; j++)
			{
				transformedVerts[j] = r.where * r.what->vertices[j];
				glBufferSubData(GL_ARRAY_BUFFER, 0, 
					sizeof(Vector3D) * r.what->numVerts, transformedVerts);
				glDrawElements(r.what->renderMode, r.what->numIndices, 
					GL_UNSIGNED_SHORT, 0);
			}
		}
	}

}