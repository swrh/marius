#include "marius/game.hpp"

#include <chrono>

#include "marius/scene_chaos.hpp"

namespace marius {

game::game()
	: sdl_init_(sdl::init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO))
	, img_init_(img::init(IMG_INIT_PNG))
	, window_(sdl::create_window("Marius", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN))
	, renderer_(sdl::create_renderer(window_, -1, SDL_RENDERER_ACCELERATED))
	, event_dispatcher_{[](const std::chrono::milliseconds &, const SDL_Event &) { return false; }}
	, current_scene_{nullptr}
{
	scenes_.reserve(1);
	scenes_.push_back(std::make_unique<scene_chaos>(renderer_));

	current_scene_ = scenes_.at(0).get();

	// Event handling
	event_dispatcher_.on(SDL_KEYDOWN, [this](const std::chrono::milliseconds &now, const SDL_Event &event) {
		if (event.key.repeat != 0 || !current_scene_) {
			return false;
		}
		return current_scene_->handle_keydown(now, event.key.keysym.sym);
	});
	event_dispatcher_.on(SDL_KEYUP, [this](const std::chrono::milliseconds &now, const SDL_Event &event) {
		if (event.key.repeat != 0 || !current_scene_) {
			return false;
		}
		return current_scene_->handle_keyup(now, event.key.keysym.sym);
	});
}

game::~game()
{
}

void
game::run()
{
	using std::chrono::milliseconds;

	constexpr milliseconds update_period{16};
	constexpr milliseconds minimum_render_period{16}, maximum_render_period{1000};

	milliseconds last_render_tick{0}, last_update_tick{0}, current_tick{0};

	SDL_Event event;

	for (;;) {
		const milliseconds next_render = last_render_tick + minimum_render_period;
		const milliseconds next_render_limit = last_render_tick + maximum_render_period;

		do {
			const bool event_arrived = SDL_WaitEventTimeout(&event, std::max(milliseconds{0}, (next_render - current_tick)).count()) == 1;
			current_tick = milliseconds(SDL_GetTicks());

			while ((last_update_tick + update_period) < current_tick) {
				last_update_tick += update_period;
				update(last_update_tick);
			}

			if (!event_arrived) {
				break;
			}

			if (event.type == SDL_QUIT) {
				return;
			}

			handle_event(last_update_tick, event);

			current_tick = milliseconds(SDL_GetTicks());
		} while (current_tick < next_render_limit);

		if (last_render_tick != last_update_tick) {
			render();
			last_render_tick = last_update_tick;
		}

		current_tick = milliseconds(SDL_GetTicks());
	}
}

bool
game::handle_event(const std::chrono::milliseconds &now, const SDL_Event &event)
{
	return event_dispatcher_.handle(event.type, now, event);
}

void
game::update(const std::chrono::milliseconds &now)
{
	current_scene_->update(now);
}

void
game::render()
{
	SDL_RenderClear(renderer_.get());

	current_scene_->render();

	SDL_RenderPresent(renderer_.get());
}

}
