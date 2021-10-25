#include "marius/object.hpp"

namespace marius {

object::object(const sdl::renderer_ptr &renderer, const tile &tile)
	: entity{renderer, tile.get_rect().w, tile.get_rect().h}
	, tile_{tile}
{
}

void
object::update(const std::chrono::milliseconds &now)
{
}

void
object::render() const
{
	render_tile(tile_);
}

void
object::move(const SDL_Point &point)
{
	position_.x += point.x;
	position_.y += point.y;
}

}
