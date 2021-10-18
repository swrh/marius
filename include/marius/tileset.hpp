#pragma once

#include "marius/sdl.hpp"
#include "marius/tile.hpp"

namespace marius {

class
tileset
{
private:
	std::vector<tile> tiles_;

public:
	tileset(const sdl::texture_ptr &texture, int tile_width, int tile_height);

	const tile &get_tile(const unsigned int n) const;
};

}
