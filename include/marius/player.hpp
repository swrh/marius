#pragma once

#include "marius/entity.hpp"
#include "marius/sdl.hpp"
#include "marius/tileset.hpp"

namespace marius {

class
player
: public entity
{
private:
	const tileset tileset_;

	const int maximum_horizontal_speed_, maximum_vertical_speed_;
	const int acceleration_, gravity_;

	unsigned int tile_number_;

	int horizontal_speed_, vertical_speed_;

	bool left_, right_, up_, down_;
	bool jump_;
	SDL_Point position_;

	std::chrono::milliseconds last_update_;

public:
	player(const sdl::renderer_ptr &renderer);

	void set_left(bool enabled);
	void set_right(bool enabled);
	void set_up(bool enabled);
	void set_down(bool enabled);

	void update(const std::chrono::milliseconds &now) override;
	void render() const override;
};

}
