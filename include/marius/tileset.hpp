#pragma once

#include "marius/sdl.hpp"
#include "marius/tile.hpp"

namespace marius {

class
tileset
{
private:
	const sdl::texture_ptr texture_;
	std::vector<tile> data_;

public:
	tileset(const sdl::renderer_ptr &renderer, const char *texture_file, int width, int height);

private:
	static std::vector<tile> make_tiles(const sdl::texture_ptr &texture, int width, int height);

public:
	unsigned int get_size() const;
	const tile &get(const unsigned int n) const;
};

}
