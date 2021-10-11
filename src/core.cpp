#include "core.hpp"

#include "exceptions.hpp"

namespace marius {

core::core()
	: init_(nullptr, nullptr)
{
	init_ = sdl::init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	if (!init_) {
		throw_with_trace(std::runtime_error(std::string("sdl::init: ") + SDL_GetError()));
	}
}

core::~core()
{
}

void
core::run()
{
}

}
