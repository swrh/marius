#pragma once

#include <chrono>

#include "marius/key_dispatcher.hpp"
#include "marius/sdl.hpp"

namespace marius {

class
scene
{
protected:
	const sdl::renderer_ptr &renderer_;
	key_dispatcher<bool (const std::chrono::milliseconds &)> keydown_dispatcher_, keyup_dispatcher_;

protected:
	scene(const sdl::renderer_ptr &renderer);

public:
	virtual ~scene();

public:
	bool handle_keydown(const std::chrono::milliseconds &now, SDL_Keycode key);
	bool handle_keyup(const std::chrono::milliseconds &now, SDL_Keycode key);

	virtual void update(const std::chrono::milliseconds &now) = 0;
	virtual void render() = 0;
};

}
