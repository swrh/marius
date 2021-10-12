#include "marius/core.hpp"

#include "marius/log.hpp"

namespace marius {

core::core()
	: sdl_init_(nullptr, nullptr)
	, img_init_(nullptr, nullptr)
	, sdl_window_(nullptr, nullptr)
	, sdl_renderer_(nullptr, nullptr)
{
	LINFO() << "Initializing SDL...";
	sdl_init_ = sdl::init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	img_init_ = img::init(IMG_INIT_PNG);
	sdl_window_ = sdl::create_window("Marius", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	sdl_renderer_ = sdl::create_renderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
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
