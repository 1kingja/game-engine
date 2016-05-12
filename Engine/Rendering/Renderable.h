#ifndef ENGINE_Renderable_H
#define ENGINE_Renderable_H
#include <Math\Matrix2DH.h>

namespace Rendering
{
	class Geomerty;
	class Renderable
	{
		friend class Renderer;
		const Geomerty* what;
	public:
		Math::Matrix2DH where;
	};
}

#endif