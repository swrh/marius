#include "marius/player.hpp"
#include <iostream>

#include <cstdlib>

namespace marius {

player::player(const sdl::renderer_ptr &renderer)
	: entity{renderer, width_, height_}
	, idle_{renderer_, "assets/mr-man/idle.png", width_, height_}
	, run_{renderer_, "assets/mr-man/run.png", width_, height_}
	, jumping_{renderer_, "assets/mr-man/jumping.png", width_, height_}
	, maximum_horizontal_speed_{.1}
	, maximum_vertical_speed_{.2}
	, current_tile_{nullptr}
	, horizontal_speed_{0}
	, vertical_speed_{0}
	, left_{false}
	, right_{false}
	, up_{false}
	, down_{false}
	, jump_{false}
	, position_x_{0}
	, position_y_{0}
	, last_update_{0}
	, objects_{nullptr}
{
}

void
player::set_objects(const std::vector<object> &objects)
{
	objects_ = &objects;
}

void
player::set_left(bool enabled)
{
	left_ = enabled;
}

void
player::set_right(bool enabled)
{
	right_ = enabled;
}

void
player::set_up(bool enabled)
{
	if (!up_ && !down_ && enabled) {
		jump_ = true;
	}
	up_ = enabled;
}

void
player::set_down(bool enabled)
{
	if (enabled) {
		jump_ = false;
	}
	down_ = enabled;
}

void
player::update(const std::chrono::milliseconds &now)
{
	const auto ms = (now - last_update_).count();

	// Horizontal movement
	const double acceleration = .001 * ms;
	if (left_ != right_) {
		// Handle thrust
		int horizontal_direction = right_ ? 1 : -1;
		horizontal_speed_ += horizontal_direction * acceleration;
		horizontal_speed_ = std::min(maximum_horizontal_speed_, std::max(-maximum_horizontal_speed_, horizontal_speed_));
		if (left_) {
			flip_ = static_cast<SDL_RendererFlip>(flip_ | SDL_FLIP_HORIZONTAL);
		} else {
			flip_ = static_cast<SDL_RendererFlip>(flip_ & ~SDL_FLIP_HORIZONTAL);
		}
	} else if (horizontal_speed_ != 0) {
		// Handle inertia
		int horizontal_direction = horizontal_speed_ / std::abs(horizontal_speed_);
		horizontal_speed_ -= horizontal_direction * acceleration;
		horizontal_speed_ = horizontal_direction * std::max(0., horizontal_direction * horizontal_speed_);
	}

	// Vertical movement
	if (jump_) {
		// Handle jump
		vertical_speed_ = -maximum_vertical_speed_;
		jump_ = false;
	} else {
		// Handle gravity
		const double gravity = .0005 * ms;
		vertical_speed_ += gravity;
		vertical_speed_ = std::min(maximum_vertical_speed_, vertical_speed_);
	}

	// Reposition the entity
	double x_shift = horizontal_speed_ * ms;
	double y_shift = vertical_speed_ * ms;

	if (objects_) {
		SDL_Rect new_position = position_;
		new_position.y = std::round(position_y_ + y_shift);
		for (const object &o : *objects_) {
			if (o.collides_with(new_position)) {
				vertical_speed_ = 0;
				y_shift = 0;
				break;
			}
		}
	}

	position_x_ += x_shift;
	position_y_ += y_shift;

	const tileset *tileset = &idle_;
	if (std::round(y_shift) != 0) {
		tileset = &jumping_;
	} else if (std::round(x_shift) != 0) {
		tileset = &run_;
	}

	unsigned int i = (now.count() / 100) % tileset->get_size();
	current_tile_ = &tileset->get(i);

	last_update_ = now;

	position_.x = std::round(position_x_);
	position_.y = std::round(position_y_);
}

void
player::render() const
{
	if (current_tile_) {
		render_tile(*current_tile_);
	}
}

}
