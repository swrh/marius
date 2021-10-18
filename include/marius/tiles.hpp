#pragma once

#include "marius/sdl.hpp"
#include "marius/tile.hpp"
#include "marius/viewport.hpp"

namespace marius {

class
tiles
{
private:
	const sdl::texture_ptr texture_;
	std::vector<tile> tiles_;

public:
	tiles(const viewport &viewport, const char *texture_file, int width, int height);

private:
	static std::vector<tile> make_vector_of_tile(const sdl::texture_ptr &texture, int width, int height);

public:
	const tile &get(const unsigned int n) const;
};

}
