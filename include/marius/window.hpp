#pragma once

#include "marius/sdl.hpp"

namespace marius {

class
window
{
private:
	sdl::window_ptr sdl_window_;
	sdl::renderer_ptr sdl_renderer_;

public:
	window(const char *title, int width, int height);

	void clear();
	void render();
	void display();
};

}
