#include "marius/entity.hpp"

#include <cmath>

namespace marius {

entity::entity(const sdl::renderer_ptr &renderer, int width, int height)
	: renderer_{renderer}
	, size_{static_cast<double>(width), static_cast<double>(height)}
	, flip_{SDL_FLIP_NONE}
{
}

void
entity::render_tile(const tile &tile) const
{
	constexpr int zoom = 3;
	const SDL_Rect render_rect = {
		.x = static_cast<int>(std::round(position_.x_ * zoom)),
		.y = static_cast<int>(std::round(position_.y_ * zoom)),
		.w = static_cast<int>(std::round(size_.x_ * zoom)),
		.h = static_cast<int>(std::round(size_.y_ * zoom)),
	};
	if (SDL_RenderCopyEx(renderer_.get(), tile.get_texture().get(), &tile.get_rect(), &render_rect, 0, nullptr, tile.get_flip(flip_)) != 0) {
		THROW(std::runtime_error(SDL_GetError()));
	}
}

bool
entity::collides_with(const vector2f &position, const vector2f &size) const
{
	return
		position_.x_ < (position.x_ + size.x_) &&
		position_.y_ < (position.y_ + size.y_) &&
		(position_.x_ + size_.x_) > position.x_ &&
		(position_.y_ + size_.y_) > position.y_ &&
		true;
}

}
