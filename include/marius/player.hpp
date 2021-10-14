#pragma once

#include "marius/entity.hpp"

namespace marius {

class
player
: public entity
{
private:
	const double speed_;
	bool left_, right_, up_, down_;

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
