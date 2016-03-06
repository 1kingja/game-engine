#ifndef ENGINE_VECTOR_3D_H
#define ENGINE_VECTOR_3D_H

namespace Math
{
	struct Vector3D
	{
		float x;
		float y;
		float z;
		explicit Vector3D(
			float x = 0.0f, 
			float y = 0.0f, 
			float z = 0.0f) : x(x), y(y),z(z) {}
	};
}

#endif