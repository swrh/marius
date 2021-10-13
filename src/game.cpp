#include "marius/game.hpp"

#include <chrono>

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
	using std::chrono::milliseconds;

	constexpr milliseconds maximum_update_ticks{16};
	constexpr milliseconds minimum_render_ticks{16}, maximum_render_ticks{1000};

	milliseconds last_render_tick{0}, last_update_tick{0}, current_tick{0};

	bool running = true;

	SDL_Event event;

	while (running) {
		const milliseconds next_render_tick = last_render_tick + minimum_render_ticks;
		const milliseconds next_render_tick_limit = last_render_tick + maximum_render_ticks;

		do {
			const bool event_arrived = SDL_WaitEventTimeout(&event, std::max(milliseconds(0), (next_render_tick - current_tick)).count()) == 1;
			current_tick = milliseconds(SDL_GetTicks());

			while ((last_update_tick + maximum_update_ticks) < current_tick) {
				last_update_tick += maximum_update_ticks;
				update(last_update_tick);
			}

			if (!event_arrived) {
				last_update_tick = current_tick;
				update(last_update_tick);
				break;
			}

			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}

			current_tick = milliseconds(SDL_GetTicks());
		} while (current_tick < next_render_tick_limit);

		if (!running) {
			break;
		}

		render();
		last_render_tick = last_update_tick;

		current_tick = milliseconds(SDL_GetTicks());
	}
}

void
game::update(const std::chrono::milliseconds &now)
{
	if (current_scene_) {
		current_scene_->update(now);
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
