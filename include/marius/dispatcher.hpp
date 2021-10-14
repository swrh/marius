#pragma once

#include <functional>
#include <vector>

namespace marius {

template <class>
class dispatcher;

template <class R, class ...Args>
class dispatcher<R (Args...)>
{
private:
	std::size_t offset_;
	std::function<R (Args...)> default_handler_;
	std::vector<std::function<R (Args...)>> vector_;

public:
	dispatcher(std::function<R (Args...)> default_handler)
		: offset_{0}
		, default_handler_{std::move(default_handler)}
	{
	}

	template <class F>
	void on(std::size_t i, F &&f)
	{
		if (vector_.empty()) {
			offset_ = i;
		} else if (i < offset_) {
			const std::size_t growth = offset_ - i;
			vector_.resize(vector_.size() + growth);
			std::copy_backward(vector_.begin(), vector_.end() - growth, vector_.end());
			offset_ = i;
		}
		i -= offset_;
		if (vector_.size() <= i) {
			vector_.resize(i + 1);
		}
		vector_[i] = std::forward<F>(f);
	}

	R handle(std::size_t i, Args &&...args)
	{
		if (i < offset_) {
			return default_handler_(std::forward<Args>(args)...);
		}
		i -= offset_;
		if (vector_.size() <= i || !vector_[i]) {
			return default_handler_(std::forward<Args>(args)...);
		}
		return vector_[i](std::forward<Args>(args)...);
	}
};

}
