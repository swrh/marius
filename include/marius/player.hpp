#pragma once

#include "marius/sdl.hpp"
#include "marius/tileset.hpp"

namespace marius {

class
player
{
private:
	const sdl::renderer_ptr &renderer_;
	const sdl::texture_ptr texture_;

	SDL_Rect position_;
	const tileset tileset_;

public:
	player(const sdl::renderer_ptr &renderer);

	void render();
};

}
