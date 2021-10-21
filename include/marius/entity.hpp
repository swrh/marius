#pragma once

#include <chrono>

#include "marius/sdl.hpp"
#include "marius/tile.hpp"

namespace marius {

class
entity
{
protected:
	const sdl::renderer_ptr &renderer_;

	SDL_Rect render_position_;
	SDL_RendererFlip flip_;

protected:
	entity(const sdl::renderer_ptr &renderer, int width, int height);

protected:
	void render_tile(const tile &tile) const;

public:
	virtual void update(const std::chrono::milliseconds &now) = 0;
	virtual void render() const = 0;
};

}
