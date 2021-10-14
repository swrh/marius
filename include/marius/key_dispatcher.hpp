#pragma once

#include <SDL.h>

#include "marius/dispatcher.hpp"

namespace marius {

template <class>
class key_dispatcher;

template <class R, class ...Args>
class key_dispatcher<R (Args...)>
{
private:
	dispatcher<R (Args...)> regular_, masked_;

public:
	key_dispatcher(std::function<R (Args...)> default_handler)
		: regular_{default_handler}
		, masked_{std::move(default_handler)}
	{
	}

	template <class F>
	void on(SDL_Keycode key, F &&f)
	{
		if (key < SDLK_SCANCODE_MASK)
			return regular_.on(key, std::forward<F>(f));
		return masked_.on(key, std::forward<F>(f));
	}

	R handle(SDL_Keycode key, Args &&...args)
	{
		if (key < SDLK_SCANCODE_MASK)
			return regular_.handle(key, std::forward<Args>(args)...);
		return masked_.handle(key, std::forward<Args>(args)...);
	}
};

}
