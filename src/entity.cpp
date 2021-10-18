#include "marius/entity.hpp"

namespace marius {

entity::entity(const viewport &viewport, const char *texture_file, int tile_width, int tile_height)
	: viewport_{viewport}
	, texture_{img::load_texture(viewport_.get_renderer(), texture_file)}
	, render_position_{0, 0, tile_width, tile_height}
	, tileset_{texture_, render_position_.w, render_position_.h}
	, flip_{SDL_FLIP_NONE}
{
}

void
entity::render(const sdl::texture_ptr &texture, const SDL_Rect &texture_rect) const
{
	if (SDL_RenderCopyEx(viewport_.get_renderer().get(), texture.get(), &texture_rect, &render_position_, 0, nullptr, static_cast<SDL_RendererFlip>(flip_)) != 0) {
		THROW(std::runtime_error(SDL_GetError()));
	}
}

}
