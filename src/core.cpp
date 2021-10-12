#include "marius/core.hpp"

#include "marius/log.hpp"

namespace marius {

core::core()
	: init_(nullptr, nullptr)
	, window_(nullptr, nullptr)
	, renderer_(nullptr, nullptr)
{
	LINFO() << "Initializing SDL...";
	init_ = sdl::init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	window_ = sdl::create_window("Marius", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	renderer_ = sdl::create_renderer(window_, -1, SDL_RENDERER_ACCELERATED);
}

core::~core()
{
}

void
core::run()
{
	LINFO() << "Main loop not implemented yet";
}

}
