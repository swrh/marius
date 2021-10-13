#include "marius/window.hpp"

namespace marius {

window::window(const char *title, int width, int height)
	: sdl_window_(sdl::create_window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN))
	, sdl_renderer_(sdl::create_renderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED))
	, player_texture_(img::load_texture(sdl_renderer_, "assets/player_tilesheet.png"))
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
	SDL_RenderCopy(sdl_renderer_.get(), player_texture_.get(), nullptr, nullptr);
}

void
window::display()
{
	SDL_RenderPresent(sdl_renderer_.get());
}

}
