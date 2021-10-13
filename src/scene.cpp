#include "marius/scene.hpp"

namespace marius {

scene::scene(const sdl::renderer_ptr &renderer)
	: renderer_(renderer)
{
}

scene::~scene()
{
}

}
