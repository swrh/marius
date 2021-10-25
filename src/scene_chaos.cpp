#include "marius/scene_chaos.hpp"

namespace marius {

scene_chaos::scene_chaos(const sdl::renderer_ptr &renderer)
	: scene(renderer)
	, packed_{renderer_, "assets/grassland/terrain.png", 16, 16}
	, player_(renderer_)
{
	keydown_dispatcher_.on(SDLK_a, [this](const std::chrono::milliseconds &) {
		player_.set_left(true);
		return true;
	});
	keyup_dispatcher_.on(SDLK_a, [this](const std::chrono::milliseconds &) {
		player_.set_left(false);
		return true;
	});

	keydown_dispatcher_.on(SDLK_w, [this](const std::chrono::milliseconds &) {
		player_.set_up(true);
		return true;
	});
	keyup_dispatcher_.on(SDLK_w, [this](const std::chrono::milliseconds &) {
		player_.set_up(false);
		return true;
	});

	keydown_dispatcher_.on(SDLK_d, [this](const std::chrono::milliseconds &) {
		player_.set_right(true);
		return true;
	});
	keyup_dispatcher_.on(SDLK_d, [this](const std::chrono::milliseconds &) {
		player_.set_right(false);
		return true;
	});

	keydown_dispatcher_.on(SDLK_s, [this](const std::chrono::milliseconds &) {
		player_.set_down(true);
		return true;
	});
	keyup_dispatcher_.on(SDLK_s, [this](const std::chrono::milliseconds &) {
		player_.set_down(false);
		return true;
	});

	// Draw the ground terrain
	int i = 0;
	objects_.emplace_back(renderer, packed_.get(60));
	objects_.back().move(SDL_Point{ .x = i++ * 16, .y = 128, });
	while (i < 13) {
		objects_.emplace_back(renderer, packed_.get(61));
		objects_.back().move(SDL_Point{ .x = i++ * 16, .y = 128, });
	}
	objects_.emplace_back(renderer, packed_.get(64));
	objects_.back().move(SDL_Point{ .x = i++ * 16, .y = 128, });
}

void
scene_chaos::update(const std::chrono::milliseconds &now)
{
	player_.update(now);
}

void
scene_chaos::render()
{
	for (const auto &o : objects_) {
		o.render();
	}

	player_.render();
}

}
