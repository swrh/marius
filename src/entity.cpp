#include "marius/entity.hpp"

namespace marius {

entity::entity(const sdl::renderer_ptr &renderer, int width, int height)
	: renderer_{renderer}
	, render_position_{0, 0, width, height}
	, flip_{SDL_FLIP_NONE}
{
}

void
entity::render_tile(const tile &tile) const
{
	constexpr int zoom = 3;
	const SDL_Rect render_rect = {
		.x = render_position_.x * zoom,
		.y = render_position_.y * zoom,
		.w = render_position_.w * zoom,
		.h = render_position_.h * zoom,
	};
	if (SDL_RenderCopyEx(renderer_.get(), tile.get_texture().get(), &tile.get_rect(), &render_rect, 0, nullptr, tile.get_flip(flip_)) != 0) {
		THROW(std::runtime_error(SDL_GetError()));
	}
}

}
