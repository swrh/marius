#pragma once

#include "marius/entity.hpp"

namespace marius {

class
player
: public entity
{
public:
	player(const sdl::renderer_ptr &renderer);
};

}
