#pragma once

#include <chrono>

#include "marius/sdl.hpp"
#include "marius/viewport.hpp"
#include "marius/tile.hpp"

namespace marius {

class
entity
{
protected:
	const viewport &viewport_;

	SDL_Rect render_position_;
	SDL_RendererFlip flip_;

protected:
	entity(const viewport &viewport, int tile_width, int tile_height);

protected:
	void render_tile(const tile &tile) const;

public:
	virtual void update(const std::chrono::milliseconds &now) = 0;
	virtual void render() const = 0;
};

}
