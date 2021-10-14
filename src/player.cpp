#include "marius/player.hpp"

#include <cstdlib>

namespace marius {

player::player(const sdl::renderer_ptr &renderer)
	: entity{renderer, "assets/player_tilesheet.png", 80, 110}
	, maximum_speed_{50}
	, acceleration_{2}
	, current_speed_{0}
	, last_horizontal_direction_{0}
	, last_vertical_direction_{0}
	, left_{false}
	, right_{false}
	, up_{false}
	, down_{false}
	, position_{render_position_}
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
	up_ = enabled;
}

void
player::set_down(bool enabled)
{
	down_ = enabled;
}

void
player::update(const std::chrono::milliseconds &now)
{
	auto diff = now - last_update_;

	if (left_ != right_) {
		int horizontal_direction = right_ ? 1 : -1;
		current_speed_ += horizontal_direction * acceleration_;
		current_speed_ = std::min(maximum_speed_, std::max(-maximum_speed_, current_speed_));
		last_horizontal_direction_ = horizontal_direction;
		if (left_) {
			flip_ |= SDL_FLIP_HORIZONTAL;
		} else {
			flip_ &= ~SDL_FLIP_HORIZONTAL;
		}
	} else if (current_speed_ != 0) {
		// Handle inertia
		int horizontal_direction = current_speed_ / std::abs(current_speed_);
		current_speed_ -= horizontal_direction * acceleration_;
		current_speed_ = horizontal_direction * std::max(0, horizontal_direction * current_speed_);
	}
	position_.x += current_speed_ * diff.count();

	if (up_ != down_) {
		int vertical_direction = down_ ? 1 : -1;
		position_.y += maximum_speed_ * vertical_direction * diff.count();
	}
	tile_ = left_ << 0 | right_ << 1 | up_ << 2 | down_ << 3;

	last_update_ = now;

	render_position_.x = position_.x / 100;
	render_position_.y = position_.y / 100;
}

}
