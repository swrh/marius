#include "marius/player.hpp"

namespace marius {

player::player(const sdl::renderer_ptr &renderer)
	: renderer_(renderer)
	, texture_(img::load_texture(renderer_, "assets/player_tilesheet.png"))
	, tileset_(texture_, 80, 110)
{
}

void
player::render()
{
	tileset_.render(23, renderer_, nullptr);
}

}
