#pragma once

#include <chrono>
#include <memory>
#include <vector>

#include "marius/dispatcher.hpp"
#include "marius/sdl.hpp"
#include "marius/viewport.hpp"

namespace marius {

class scene;

class game
{
private:
	const sdl::init_ptr sdl_init_;
	const img::init_ptr img_init_;
	const viewport viewport_;

	dispatcher<bool (const std::chrono::milliseconds &, const SDL_Event &)> event_dispatcher_;

	std::vector<std::unique_ptr<scene>> scenes_;
	scene *current_scene_;

public:
	game();
	~game();

	void run();

protected:
	bool handle_event(const std::chrono::milliseconds &now, const SDL_Event &event);
	void update(const std::chrono::milliseconds &now);
	void render();

};

}
