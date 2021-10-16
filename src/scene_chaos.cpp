#include "marius/scene_chaos.hpp"

namespace marius {

scene_chaos::scene_chaos(const viewport &viewport)
	: scene(viewport)
	, player_(viewport_)
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
}

void
scene_chaos::update(const std::chrono::milliseconds &now)
{
	player_.update(now);
}

void
scene_chaos::render()
{
	player_.render();
}

}
