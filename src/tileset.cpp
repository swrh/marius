#include "marius/tileset.hpp"

namespace marius {

tileset::tileset(const sdl::texture_ptr &texture, int tile_width, int tile_height)
	: texture_(texture)
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
		tiles_.push_back(SDL_Rect{
				.x = (i % nx) * tile_width,
				.y = (i / nx) * tile_height,
				.w = tile_width,
				.h = tile_height,
			});
	}
}

void
tileset::render(const unsigned int n, const sdl::renderer_ptr &renderer, const SDL_Rect &destination) const
{
	if (n >= tiles_.size()) {
		THROW(std::runtime_error("invalid tile number"));
	}

	if (SDL_RenderCopy(renderer.get(), texture_.get(), &tiles_[n], &destination) != 0) {
		THROW(std::runtime_error(SDL_GetError()));
	}
}

}
