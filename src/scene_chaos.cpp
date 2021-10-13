#include "marius/scene_chaos.hpp"

namespace marius {

scene_chaos::scene_chaos(const sdl::renderer_ptr &renderer)
	: scene(renderer)
	, player_(renderer_)
{
}

void
scene_chaos::render()
{
	player_.render();
}

}
