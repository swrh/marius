#pragma once

#include "marius/sdl.hpp"

namespace marius {

class
tileset
{
private:
	const sdl::texture_ptr &texture_;
	std::vector<SDL_Rect> tiles_;

public:
	tileset(const sdl::texture_ptr &texture, int tile_width, int tile_height);

	const SDL_Rect &get_tile(const unsigned int n) const;
};

}
