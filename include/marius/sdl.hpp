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
using window_ptr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using renderer_ptr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

#define RETURN_RESOURCE(args...) do { \
	auto ptr = make_resource(args); \
	if (!ptr) { \
		THROW(std::runtime_error(SDL_GetError())); \
	} \
	return ptr; \
} while (0)

inline init_ptr init(Uint32 flags)
{
	RETURN_RESOURCE(detail::CreateInit, detail::DestroyInit, flags);
}

inline window_ptr create_window(const char *title, int x, int y, int w, int h, Uint32 flags)
{
	RETURN_RESOURCE(SDL_CreateWindow, SDL_DestroyWindow, title, x, y, w, h, flags);
}

inline renderer_ptr create_renderer(const window_ptr &window, int x, Uint32 flags)
{
	RETURN_RESOURCE(SDL_CreateRenderer, SDL_DestroyRenderer, window.get(), x, flags);
}

#undef RETURN_RESOURCE

}

}
