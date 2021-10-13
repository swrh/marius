#pragma once

#include <chrono>
#include <memory>
#include <vector>

#include "marius/sdl.hpp"

namespace marius {

class scene;

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
	void update(const std::chrono::milliseconds &now);
	void render();

};

}
