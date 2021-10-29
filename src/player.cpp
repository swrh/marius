#include "marius/player.hpp"
#include <iostream>

#include <cstdlib>

namespace marius {

player::player(const sdl::renderer_ptr &renderer)
	: entity{renderer, width_, height_}
	, idle_{renderer_, "assets/mr-man/idle.png", width_, height_}
	, run_{renderer_, "assets/mr-man/run.png", width_, height_}
	, jumping_{renderer_, "assets/mr-man/jumping.png", width_, height_}
	, speed_limit_{.1, .2}
	, current_tile_{nullptr}
	, left_{false}
	, right_{false}
	, up_{false}
	, down_{false}
	, jump_{false}
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
		speed_.x_ += horizontal_direction * acceleration;
		speed_.x_ = std::min(speed_limit_.x_, std::max(-speed_limit_.x_, speed_.x_));
		if (left_) {
			flip_ = static_cast<SDL_RendererFlip>(flip_ | SDL_FLIP_HORIZONTAL);
		} else {
			flip_ = static_cast<SDL_RendererFlip>(flip_ & ~SDL_FLIP_HORIZONTAL);
		}
	} else if (speed_.x_ != 0) {
		// Handle inertia
		int horizontal_direction = speed_.x_ / std::abs(speed_.x_);
		speed_.x_ -= horizontal_direction * acceleration;
		speed_.x_ = horizontal_direction * std::max(0., horizontal_direction * speed_.x_);
	}

	// Vertical movement
	if (jump_) {
		// Handle jump
		speed_.y_ = -speed_limit_.y_;
		jump_ = false;
	} else {
		// Handle gravity
		const double gravity = .0005 * ms;
		speed_.y_ += gravity;
		speed_.y_ = std::min(speed_limit_.y_, speed_.y_);
	}

	// Reposition the entity
	vector2f movement{
		.x_ = speed_.x_ * ms,
		.y_ = speed_.y_ * ms,
	};

	if (objects_) {
		vector2f new_position = position_;
		new_position.y_ += movement.y_;
		for (const object &o : *objects_) {
			if (o.collides_with(new_position, size_)) {
				speed_.y_ = 0;
				movement.y_ = 0;
				break;
			}
		}
	}

	position_.x_ += movement.x_;
	position_.y_ += movement.y_;

	const tileset *tileset = &idle_;
	if (std::round(movement.y_) != 0) {
		tileset = &jumping_;
	} else if (std::round(movement.x_) != 0) {
		tileset = &run_;
	}

	unsigned int i = (now.count() / 100) % tileset->get_size();
	current_tile_ = &tileset->get(i);

	last_update_ = now;
}

void
player::render() const
{
	if (current_tile_) {
		render_tile(*current_tile_);
	}
}

}
