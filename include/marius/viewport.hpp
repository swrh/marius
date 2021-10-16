#pragma once

#include "marius/sdl.hpp"

namespace marius {

class
viewport
{
private:
	const sdl::window_ptr window_;
	const sdl::renderer_ptr renderer_;

public:
	viewport(int width, int height);

	const sdl::renderer_ptr &get_renderer() const;

};

}
