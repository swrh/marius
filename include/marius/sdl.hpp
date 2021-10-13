#pragma once

#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "marius/exceptions.hpp"

namespace marius {

template <typename Creator, typename Destructor, typename... Args>
auto make_resource(Creator c, Destructor d, Args&&... args)
{
	auto r = c(std::forward<Args>(args)...);
	return std::unique_ptr<std::decay_t<decltype(*r)>, decltype(d)>(r, d);
}

namespace sdl {

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
using texture_ptr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

}

namespace img {

namespace detail {

using Init = int;

inline Init *CreateInit(IMG_InitFlags flags)
{
	Init *p = nullptr;
	if (IMG_Init(flags) == flags) {
		p = new Init{0};
	}
	return p;
}

inline void DestroyInit(Init *p)
{
	if (p) {
		delete p;
		IMG_Quit();
	}
}

}

using init_ptr = std::unique_ptr<detail::Init, decltype(&detail::DestroyInit)>;

}

#define RETURN_RESOURCE(args...) do { \
	auto ptr = make_resource(args); \
	if (!ptr) { \
		THROW(std::runtime_error(SDL_GetError())); \
	} \
	return ptr; \
} while (0)

namespace sdl {

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

}

namespace img {

inline init_ptr init(IMG_InitFlags flags)
{
	RETURN_RESOURCE(detail::CreateInit, detail::DestroyInit, flags);
}

inline sdl::texture_ptr load_texture(const sdl::renderer_ptr &renderer, const char *path)
{
	RETURN_RESOURCE(IMG_LoadTexture, SDL_DestroyTexture, renderer.get(), path);
}

}

#undef RETURN_RESOURCE

}
