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
	bool Renderer::shutdown()
	{
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
}