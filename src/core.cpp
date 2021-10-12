#include "marius/core.hpp"

namespace marius {

core::core()
	: sdl_init_(sdl::init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO))
	, img_init_(img::init(IMG_INIT_PNG))
	, window_("Marius", 1024, 768)
{
}

core::~core()
{
}

void
core::run()
{
	bool running = true;

	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		window_.clear();
		window_.render();
		window_.display();
	}
}

}
