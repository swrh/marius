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
	static constexpr int width_ = 80;
	static constexpr int height_ = 110;

	const tileset tileset_;

	const double maximum_horizontal_speed_, maximum_vertical_speed_;

	unsigned int tile_number_;

	double horizontal_speed_, vertical_speed_;

	bool left_, right_, up_, down_;
	bool jump_;
	double position_x_, position_y_;

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
