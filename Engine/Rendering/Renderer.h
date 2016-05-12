#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H
#include <QtOpenGL\qglwidget>
#include <Misc\TypeDefs.h>
#include <Rendering\Geometry.h>
#include <Rendering\Renderable.h>
namespace Math { class Vector3D; }

namespace Rendering
{
	class Renderer : public QGLWidget
	{
		static const uint NUM_MAX_GEOMETRIES = 10;
		Geometry geometries[NUM_MAX_GEOMETRIES];
		uint numGeometries;
		static const uint NUM_MAX_RENDERABLES = 10;
		Renderable renderables[NUM_MAX_RENDERABLES];
		uint numRenderables;
		static const uint MAX_BUFFER_SIZE = 1024;
		GLuint vertexBufferID;
		GLuint indexBufferID;
		static const uint MAX_VERTS = 10;
	protected:
		void initializeGL();
		void paintEvent();
		void paintGL();
	public:
		bool initialize();
		bool shutdown();
		Geometry* addGeometry(
			Math::Vector3D* vertices, uint numVerts,
			ushort* indices, uint numIndices,
			GLenum renderModes);
		Renderable* addRenderable(Geometry* geometry);
		void rendererScene();
	};
}
#endif