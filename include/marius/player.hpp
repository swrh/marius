#pragma once

#include "marius/entity.hpp"

namespace marius {

class
player
: public entity
{
public:
	player(const sdl::renderer_ptr &renderer);

	void update(const std::chrono::milliseconds &now) override;
};

}
