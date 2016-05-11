#ifndef	MY_GAME_H
#define	MY_GAME_H
#include <Rendering\Renderer.h>
namespace Rendering { class Renderable; }


class MyGame
{
	Rendering::Renderer renderer;
	Rendering::Renderable* shipInstance;
	Rendering::Renderable* lerpInstance;
public:
	bool initalize();
	void update();
};
#endif
