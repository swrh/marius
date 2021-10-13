#include "marius/game.hpp"

#include "marius/scene_chaos.hpp"

namespace marius {

game::game()
	: sdl_init_(sdl::init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO))
	, img_init_(img::init(IMG_INIT_PNG))
	, window_(sdl::create_window("Marius", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN))
	, renderer_(sdl::create_renderer(window_, -1, SDL_RENDERER_ACCELERATED))
	, current_scene_{nullptr}
{
	scenes_.reserve(1);

	scenes_.push_back(std::make_unique<scene_chaos>(renderer_));

	current_scene_ = scenes_.at(0).get();
}

game::~game()
{
}

void
game::run()
{
	bool running = true;

	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		render();
	}
}

void
game::render()
{
	SDL_RenderClear(renderer_.get());

	if (current_scene_) {
		current_scene_->render();
	}

	SDL_RenderPresent(renderer_.get());
}

}
