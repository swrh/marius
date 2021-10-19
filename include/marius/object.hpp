#pragma once

#include "marius/entity.hpp"

namespace marius {

class
object
: public entity
{
private:
	const tile &tile_;

public:
	object(const sdl::renderer_ptr &renderer, const tile &tile);

	void update(const std::chrono::milliseconds &now);
	void render() const;

	void move(const SDL_Point &point);
};

}
