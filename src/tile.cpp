#include "marius/tile.hpp"

namespace marius {

tile::tile(const sdl::texture_ptr &texture, const SDL_Rect &rect, SDL_RendererFlip flip)
	: texture_(texture)
	, rect_(rect)
	, flip_(flip)
{
}

const sdl::texture_ptr &
tile::get_texture() const
{
	return texture_;
}

const SDL_Rect &
tile::get_rect() const
{
	return rect_;
}

SDL_RendererFlip
tile::get_flip() const
{
	return flip_;
}

}
