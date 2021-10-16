#pragma once

#include <chrono>

#include "marius/sdl.hpp"
#include "marius/tileset.hpp"
#include "marius/viewport.hpp"

namespace marius {

class
entity
{
protected:
	const viewport &viewport_;
	const sdl::texture_ptr texture_;

	SDL_Rect render_position_;
	unsigned int tile_;
	const tileset tileset_;

	unsigned int flip_;

protected:
	entity(const viewport &viewport, const char *texture_file, int tile_width, int tile_height);

public:
	virtual void update(const std::chrono::milliseconds &now) = 0;
	void render() const;
};

}
