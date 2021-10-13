#pragma once

#include "marius/sdl.hpp"

namespace marius {

class
scene
{
protected:
	const sdl::renderer_ptr &renderer_;

protected:
	scene(const sdl::renderer_ptr &renderer);

public:
	virtual ~scene();

public:
	virtual void render() = 0;
};

}
