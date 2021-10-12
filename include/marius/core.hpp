#pragma once

#include "marius/sdl.hpp"
#include "marius/window.hpp"

namespace marius {

class core
{
private:
	sdl::init_ptr sdl_init_;
	img::init_ptr img_init_;
	window window_;

public:
	core();
	~core();

	void run();

};

}
