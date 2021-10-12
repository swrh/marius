#pragma once

#include <memory>
#include <string>

#include <SDL.h>

#include "marius/exceptions.hpp"

namespace marius {

namespace sdl {

template <typename Creator, typename Destructor, typename... Args>
auto make_resource(Creator c, Destructor d, Args&&... args)
{
	auto r = c(std::forward<Args>(args)...);
	return std::unique_ptr<std::decay_t<decltype(*r)>, decltype(d)>(r, d);
}

namespace detail {

using Init = int;

inline Init *CreateInit(Uint32 flags)
{
	Init *p = nullptr;
	if (SDL_Init(flags) == 0) {
		p = new Init{0};
	}
	return p;
}

inline void DestroyInit(Init *p)
{
	if (p) {
		delete p;
		SDL_Quit();
	}
}

}

using init_ptr = std::unique_ptr<detail::Init, decltype(&detail::DestroyInit)>;

inline init_ptr init(Uint32 flags)
{
	init_ptr ptr = make_resource(detail::CreateInit, detail::DestroyInit, flags);
	if (!ptr) {
		THROW(std::runtime_error(SDL_GetError()));
	}
	return ptr;
}

}

}
