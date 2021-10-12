#include "marius/core.hpp"

#include "marius/log.hpp"

namespace marius {

core::core()
	: init_(nullptr, nullptr)
{
	LINFO() << "Initializing SDL...";
	init_ = sdl::init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
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
