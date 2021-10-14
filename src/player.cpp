#include "marius/player.hpp"

namespace marius {

player::player(const sdl::renderer_ptr &renderer)
	: entity{renderer, "assets/player_tilesheet.png", 80, 110}
	, speed_{.05}
	, left_{false}
	, right_{false}
	, up_{false}
	, down_{false}
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
		int direction = right_ ? 1 : -1;
		position_.x += std::round(speed_ * direction * diff.count());
		flip_horizontal_ = left_;
	}

	if (up_ != down_) {
		int direction = down_ ? 1 : -1;
		position_.y += std::round(speed_ * direction * diff.count());
	}
	tile_ = left_ << 0 | right_ << 1 | up_ << 2 | down_ << 3;

	last_update_ = now;
}

}
