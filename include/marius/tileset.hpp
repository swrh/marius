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

	void render(const unsigned int n, const sdl::renderer_ptr &renderer, const SDL_Rect *destination) const;
};

}
