#include "marius/entity.hpp"

namespace marius {

entity::entity(const sdl::renderer_ptr &renderer, const char *texture_file, int tile_width, int tile_height)
	: renderer_{renderer}
	, texture_{img::load_texture(renderer_, texture_file)}
	, position_{0, 0, tile_width, tile_height}
	, tile_{0}
	, tileset_{texture_, position_.w, position_.h}
	, flip_horizontal_{false}
	, flip_vertical_{false}
{
}

void
entity::render() const
{
	const SDL_Rect &source = tileset_.get_tile(tile_);

	SDL_RendererFlip flip = static_cast<SDL_RendererFlip>((flip_horizontal_ ? SDL_FLIP_HORIZONTAL : 0) | (flip_vertical_ ? SDL_FLIP_VERTICAL : 0));

	if (SDL_RenderCopyEx(renderer_.get(), texture_.get(), &source, &position_, 0, nullptr, flip) != 0) {
		THROW(std::runtime_error(SDL_GetError()));
	}
}

}
