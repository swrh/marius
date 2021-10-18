#pragma once

#include <chrono>

#include "marius/sdl.hpp"
#include "marius/tileset.hpp"
#include "marius/viewport.hpp"

namespace marius {

class
entity
{
protected:
	const viewport &viewport_;
	const sdl::texture_ptr texture_;

	SDL_Rect render_position_;
	const tileset tileset_;

protected:
	entity(const viewport &viewport, const char *texture_file, int tile_width, int tile_height);

protected:
	void render_texture(const sdl::texture_ptr &texture, const SDL_Rect &rect, const SDL_RendererFlip flip) const;

public:
	virtual void update(const std::chrono::milliseconds &now) = 0;
	virtual void render() const = 0;
};

}
