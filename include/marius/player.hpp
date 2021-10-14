#pragma once

#include "marius/entity.hpp"

namespace marius {

class
player
: public entity
{
private:
	const int maximum_speed_;
	const int acceleration_;

	int current_speed_;
	int last_horizontal_direction_, last_vertical_direction_;

	bool left_, right_, up_, down_;
	SDL_Rect position_;

	std::chrono::milliseconds last_update_;

public:
	player(const sdl::renderer_ptr &renderer);

	void set_left(bool enabled);
	void set_right(bool enabled);
	void set_up(bool enabled);
	void set_down(bool enabled);

	void update(const std::chrono::milliseconds &now) override;
};

}
