#pragma once

#include "marius/entity.hpp"
#include "marius/object.hpp"
#include "marius/sdl.hpp"
#include "marius/tile.hpp"
#include "marius/tileset.hpp"

namespace marius {

class
player
: public entity
{
private:
	static constexpr int width_ = 16;
	static constexpr int height_ = 16;

	const tileset idle_, run_, jumping_;

	const double maximum_horizontal_speed_, maximum_vertical_speed_;

	const tile *current_tile_;

	double horizontal_speed_, vertical_speed_;

	bool left_, right_, up_, down_;
	bool jump_;

	std::chrono::milliseconds last_update_;

	const std::vector<object> *objects_;

public:
	player(const sdl::renderer_ptr &renderer);

	void set_objects(const std::vector<object> &objects);

	void set_left(bool enabled);
	void set_right(bool enabled);
	void set_up(bool enabled);
	void set_down(bool enabled);

	void update(const std::chrono::milliseconds &now) override;
	void render() const override;
};

}
