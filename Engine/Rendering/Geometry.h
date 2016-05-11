#ifndef ENGINE_GEOMETRY_H
#define ENGINE_GEOMETRY_H
#include <Misc\TypeDefs.h>
namespace Math { class Vector3D; }

namespace Rendering
{
	class Geometry
	{
		const Math::Vector3D* vertices;
		uint numVerts;
		const ushort* indices;
		uint numIndices
	};
}
#endif