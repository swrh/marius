#include "marius/scene.hpp"

namespace marius {

scene::scene(const viewport &viewport)
	: viewport_(viewport)
	, keydown_dispatcher_{[](const std::chrono::milliseconds &) { return false; }}
	, keyup_dispatcher_{[](const std::chrono::milliseconds &) { return false; }}
{
}

scene::~scene()
{
}

bool
scene::handle_keydown(const std::chrono::milliseconds &now, SDL_Keycode key)
{
	return keydown_dispatcher_.handle(key, now);
}

bool
scene::handle_keyup(const std::chrono::milliseconds &now, SDL_Keycode key)
{
	return keyup_dispatcher_.handle(key, now);
}

}
