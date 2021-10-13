#include "marius/player.hpp"

namespace marius {

player::player(const sdl::renderer_ptr &renderer)
	: entity{renderer, "assets/player_tilesheet.png", 80, 110}
{
}

void
player::update(const std::chrono::milliseconds &now)
{
}

}
