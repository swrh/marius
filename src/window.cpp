#include "marius/window.hpp"

namespace marius {

window::window(const char *title, int width, int height)
	: sdl_window_(sdl::create_window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN))
	, sdl_renderer_(sdl::create_renderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED))
{
}

void
window::clear()
{
	SDL_RenderClear(sdl_renderer_.get());
}

void
window::render()
{
}

void
window::display()
{
	SDL_RenderPresent(sdl_renderer_.get());
}

}
