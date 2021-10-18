#include "marius/tileset.hpp"

namespace marius {

tileset::tileset(const sdl::texture_ptr &texture, int tile_width, int tile_height)
{
	int texture_width, texture_height;
	if (SDL_QueryTexture(texture.get(), nullptr, nullptr, &texture_width, &texture_height) != 0) {
		THROW(std::runtime_error(SDL_GetError()));
	}

	if (tile_width > texture_width || tile_height > texture_height) {
		THROW(std::runtime_error("tile larger than its texture"));
	}

	const int nx = texture_width / tile_width;
	const int ny = texture_height / tile_height;
	const int n = nx * ny;

	tiles_.reserve(n);
	for (int i = 0; i < n; ++i) {
		tiles_.emplace_back(texture, SDL_Rect{
				.x = (i % nx) * tile_width,
				.y = (i / nx) * tile_height,
				.w = tile_width,
				.h = tile_height,
			});
	}
}

const tile &
tileset::get_tile(const unsigned int n) const
{
	if (n >= tiles_.size()) {
		THROW(std::runtime_error("invalid tile number"));
	}

	return tiles_[n];
}

}
