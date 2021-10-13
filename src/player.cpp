#include "marius/player.hpp"

namespace marius {

player::player(const sdl::renderer_ptr &renderer)
	: renderer_(renderer)
	, texture_(img::load_texture(renderer_, "assets/player_tilesheet.png"))
	, position_{0, 0, 80, 110}
	, tileset_{texture_, position_.w, position_.h}
{
}

void
player::render()
{
	tileset_.render(23, renderer_, position_);
}

}
