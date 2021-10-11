#pragma once

#include "sdl.hpp"

namespace marius {

class core
{
private:
	sdl::init_ptr init_;

public:
	core();
	~core();

	void run();

};

}
