#include "marius/player.hpp"

#include <cstdlib>

namespace marius {

player::player(const sdl::renderer_ptr &renderer)
	: entity{renderer, 80, 110}
	, tileset_{renderer_, "assets/player_tilesheet.png", render_position_.w, render_position_.h}
	, maximum_horizontal_speed_{50}
	, maximum_vertical_speed_{75}
	, acceleration_{2}
	, gravity_{2}
	, tile_number_{0}
	, horizontal_speed_{0}
	, vertical_speed_{0}
	, left_{false}
	, right_{false}
	, up_{false}
	, down_{false}
	, jump_{false}
	, position_{
		.x = render_position_.x,
		.y = render_position_.y,
	}
	, last_update_{0}
{
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
	auto diff = now - last_update_;

	// Horizontal movement
	if (left_ != right_) {
		// Handle thrust
		int horizontal_direction = right_ ? 1 : -1;
		horizontal_speed_ += horizontal_direction * acceleration_;
		horizontal_speed_ = std::min(maximum_horizontal_speed_, std::max(-maximum_horizontal_speed_, horizontal_speed_));
		if (left_) {
			flip_ = static_cast<SDL_RendererFlip>(flip_ | SDL_FLIP_HORIZONTAL);
		} else {
			flip_ = static_cast<SDL_RendererFlip>(flip_ & ~SDL_FLIP_HORIZONTAL);
		}
	} else if (horizontal_speed_ != 0) {
		// Handle inertia
		int horizontal_direction = horizontal_speed_ / std::abs(horizontal_speed_);
		horizontal_speed_ -= horizontal_direction * acceleration_;
		horizontal_speed_ = horizontal_direction * std::max(0, horizontal_direction * horizontal_speed_);
	}
	position_.x += horizontal_speed_ * diff.count();

	// Vertical movement
	if (jump_) {
		// Handle jump
		vertical_speed_ = -maximum_vertical_speed_;
		jump_ = false;
	} else {
		// Handle gravity
		vertical_speed_ += gravity_;
		vertical_speed_ = std::min(maximum_vertical_speed_, vertical_speed_);
	}
	position_.y += vertical_speed_ * diff.count();

	// Select the player tile randomly
	tile_number_ = left_ << 0 | right_ << 1 | up_ << 2 | down_ << 3;

	last_update_ = now;

	render_position_.x = position_.x / 100;
	render_position_.y = position_.y / 100;
}

void
player::render() const
{
	render_tile(tileset_.get(tile_number_));
}

}
