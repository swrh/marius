#include "marius/tiles.hpp"

namespace marius {

tiles::tiles(const sdl::renderer_ptr &renderer, const char *texture_file, int width, int height)
	: texture_{img::load_texture(renderer, texture_file)}
	, tiles_{make_vector_of_tile(texture_, width, height)}
{
}

std::vector<tile>
tiles::make_vector_of_tile(const sdl::texture_ptr &texture, int width, int height)
{
	int texture_width, texture_height;
	if (SDL_QueryTexture(texture.get(), nullptr, nullptr, &texture_width, &texture_height) != 0) {
		THROW(std::runtime_error(SDL_GetError()));
	}

	if (width > texture_width || height > texture_height) {
		THROW(std::runtime_error("tile larger than its texture"));
	}

	const int nx = texture_width / width;
	const int ny = texture_height / height;
	const int n = nx * ny;

	std::vector<tile> tiles;
	tiles.reserve(n);
	for (int i = 0; i < n; ++i) {
		tiles.emplace_back(texture, SDL_Rect{
				.x = (i % nx) * width,
				.y = (i / nx) * height,
				.w = width,
				.h = height,
			});
	}

	return tiles;
}

const tile &
tiles::get(const unsigned int n) const
{
	if (n >= tiles_.size()) {
		THROW(std::runtime_error("invalid tile number"));
	}

	return tiles_[n];
}

}
