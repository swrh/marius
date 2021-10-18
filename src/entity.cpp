#include "marius/entity.hpp"

namespace marius {

entity::entity(const sdl::renderer_ptr &renderer, int tile_width, int tile_height)
	: renderer_{renderer}
	, render_position_{0, 0, tile_width, tile_height}
	, flip_{SDL_FLIP_NONE}
{
}

void
entity::render_tile(const tile &tile) const
{
	if (SDL_RenderCopyEx(renderer_.get(), tile.get_texture().get(), &tile.get_rect(), &render_position_, 0, nullptr, tile.get_flip(flip_)) != 0) {
		THROW(std::runtime_error(SDL_GetError()));
	}
}

}
