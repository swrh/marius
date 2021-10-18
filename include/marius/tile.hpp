#pragma once

#include "marius/sdl.hpp"

namespace marius {

class
tile
{
private:
	const sdl::texture_ptr &texture_;
	SDL_Rect rect_;
	SDL_RendererFlip flip_;

public:
	tile(const sdl::texture_ptr &texture, const SDL_Rect &rect, SDL_RendererFlip flip = SDL_FLIP_NONE);

public:
	const sdl::texture_ptr &get_texture() const;
	const SDL_Rect &get_rect() const;
	SDL_RendererFlip get_flip() const;
};

}
