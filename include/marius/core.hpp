#pragma once

#include "sdl.hpp"

namespace marius {

class core
{
private:
	sdl::init_ptr sdl_init_;
	img::init_ptr img_init_;
	sdl::window_ptr sdl_window_;
	sdl::renderer_ptr sdl_renderer_;

public:
	core();
	~core();

	void run();

};

}
