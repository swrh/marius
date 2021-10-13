#pragma once

#include "marius/sdl.hpp"
#include "marius/tileset.hpp"

namespace marius {

class
entity
{
protected:
	const sdl::renderer_ptr &renderer_;
	const sdl::texture_ptr texture_;

	SDL_Rect position_;
	unsigned int tile_;
	const tileset tileset_;

protected:
	entity(const sdl::renderer_ptr &renderer, const char *texture_file, int tile_width, int tile_height);

public:
	void render();
};

}
