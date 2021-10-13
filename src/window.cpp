#include "marius/window.hpp"

namespace marius {

window::window(const char *title, int width, int height)
	: window_(sdl::create_window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN))
	, renderer_(sdl::create_renderer(window_, -1, SDL_RENDERER_ACCELERATED))
	, player_(renderer_)
{
}

void
window::clear()
{
	SDL_RenderClear(renderer_.get());
}

void
window::render()
{
	player_.render();
}

void
window::display()
{
	SDL_RenderPresent(renderer_.get());
}

}
