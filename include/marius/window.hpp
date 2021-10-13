#pragma once

#include "marius/sdl.hpp"

namespace marius {

class
window
{
private:
	const sdl::window_ptr sdl_window_;
	const sdl::renderer_ptr sdl_renderer_;
	const sdl::texture_ptr player_texture_;

public:
	window(const char *title, int width, int height);

	void clear();
	void render();
	void display();
};

}
