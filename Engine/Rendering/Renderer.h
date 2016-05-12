#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H
#include <Misc\TypeDefs.h>
#include <Rendering\Geometry.h>
#include <Rendering\Renderable.h>
namespace Math { class Vector3D; }

namespace Rendering
{
	class Renderer
	{
		static uint NUM_MAX_GEOMETRIES = 10;
		Geometry geometries[NUM_MAX_GEOMETRIES];
		uint numGeometries;
		static uint NUM_MAX_RENDERABLES = 10;
		Renderable renderables[NUM_MAX_RENDERABLES];
		uint numRenderables;
	public:
		bool initialize();
		bool shutdown();
		Geometry* addGeometry(
			Math::Vector3D* vertices, uint numVerts,
			ushort* indices, uint numIndices);
		Renderable* addRenderable(Geometry* geometry);
	};
}
#endif