#include "marius/scene_chaos.hpp"

namespace marius {

scene_chaos::scene_chaos(const sdl::renderer_ptr &renderer)
	: scene(renderer)
	, packed_{renderer_, "assets/tiles_packed.png", 18, 18}
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

	for (int i = 0; i < static_cast<int>(packed_.get_size()); ++i) {
		objects_.emplace_back(renderer, packed_.get(i));
		object &o = objects_.back();
		o.move(SDL_Point{
				.x = (i & 0xf) * 18,
				.y = ((i & ~0xf) >> 4) * 18,
				});
	}
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
