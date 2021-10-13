#pragma once

#include "marius/scene.hpp"
#include "marius/player.hpp"

namespace marius {

class
scene_chaos
: public scene
{
private:
	player player_;

public:
	scene_chaos(const sdl::renderer_ptr &renderer);

	void update(const std::chrono::milliseconds &now) override;
	void render() override;
};

}
