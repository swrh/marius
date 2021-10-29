#include "marius/player.hpp"
#include <iostream>

#include <cstdlib>

namespace marius {

player::player(const sdl::renderer_ptr &renderer)
	: entity{renderer, width_, height_}
	, idle_{renderer_, "assets/mr-man/idle.png", width_, height_}
	, run_{renderer_, "assets/mr-man/run.png", width_, height_}
	, jumping_{renderer_, "assets/mr-man/jumping.png", width_, height_}
	, current_tile_{nullptr}
	, left_{false}
	, right_{false}
	, up_{false}
	, down_{false}
	, jump_{false}
	, on_the_ground_{false}
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

	constexpr double MASS = 1;
	constexpr double FORCE_GRAVITY = .0005;
	constexpr double FORCE_THRUST = .0005;
	constexpr double VELOCITY_JUMP = .2;

	vector2f force{
		.y_ = FORCE_GRAVITY,
	};

	// Horizontal movement
	if (left_ != right_) {
		// Handle thrust
		force.x_ += FORCE_THRUST * (right_ ? 1 : -1);
		if (left_) {
			flip_ = static_cast<SDL_RendererFlip>(flip_ | SDL_FLIP_HORIZONTAL);
		} else {
			flip_ = static_cast<SDL_RendererFlip>(flip_ & ~SDL_FLIP_HORIZONTAL);
		}
	}
	if (on_the_ground_) {
		// Handle friction
	}

	// Vertical movement
	if (jump_) {
		// Handle jump
		velocity_.y_ = -1 * VELOCITY_JUMP;
		jump_ = false;
	}

	on_the_ground_ = false;

	vector2f acceleration{
		.x_ = force.x_ / MASS,
		.y_ = force.y_ / MASS,
	};

	if (objects_) {
		vector2f new_position = position_;
		new_position.y_ += velocity_.y_ * ms + acceleration.y_ * ms * ms / 2;
		for (const object &o : *objects_) {
			if (o.collides_with(new_position, size_)) {
				on_the_ground_ = true;
				velocity_.y_ = acceleration.y_ = 0;
				break;
			}
		}
	}

	position_.x_ += velocity_.x_ * ms + acceleration.x_ * ms * ms / 2;
	position_.y_ += velocity_.y_ * ms + acceleration.y_ * ms * ms / 2;

	velocity_.x_ += acceleration.x_ * ms;
	velocity_.y_ += acceleration.y_ * ms;

	const tileset *tileset = &idle_;
	if (!on_the_ground_) {
		tileset = &jumping_;
	} else if (velocity_.x_ != 0) {
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
