#pragma once

#include <memory>
#include <vector>

#include "marius/scene.hpp"
#include "marius/sdl.hpp"

namespace marius {

class game
{
private:
	const sdl::init_ptr sdl_init_;
	const img::init_ptr img_init_;
	const sdl::window_ptr window_;
	const sdl::renderer_ptr renderer_;

	scene *current_scene_;
	std::vector<std::unique_ptr<scene>> scenes_;

public:
	game();
	~game();

	void run();

protected:
	void render();

};

}
