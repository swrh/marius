#pragma once

#include "sdl.hpp"

namespace marius {

class core
{
private:
	sdl::init_ptr init_;
	sdl::window_ptr window_;
	sdl::renderer_ptr renderer_;

public:
	core();
	~core();

	void run();

};

}
