#pragma once

#include <chrono>

#include "marius/sdl.hpp"
#include "marius/tile.hpp"
#include "marius/vector2f.hpp"

namespace marius {

class
entity
{
protected:
	const sdl::renderer_ptr &renderer_;

	vector2f position_;
	vector2f size_;

	SDL_RendererFlip flip_;

protected:
	entity(const sdl::renderer_ptr &renderer, int width, int height);

protected:
	void render_tile(const tile &tile) const;

public:
	bool collides_with(const vector2f &position, const vector2f &size) const;

	virtual void update(const std::chrono::milliseconds &now) = 0;
	virtual void render() const = 0;
};

}
