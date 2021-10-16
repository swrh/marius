#include "marius/viewport.hpp"

namespace marius {

viewport::viewport(int width, int height)
	: window_(sdl::create_window("Marius", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN))
	, renderer_(sdl::create_renderer(window_, -1, SDL_RENDERER_ACCELERATED))
{
}

const sdl::renderer_ptr &
viewport::get_renderer() const
{
	return renderer_;
}

}
