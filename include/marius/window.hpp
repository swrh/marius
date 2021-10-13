#pragma once

#include "marius/player.hpp"
#include "marius/sdl.hpp"

namespace marius {

class
window
{
private:
	const sdl::window_ptr window_;
	const sdl::renderer_ptr renderer_;

	player player_;

public:
	window(const char *title, int width, int height);

	void clear();
	void render();
	void display();
};

}
