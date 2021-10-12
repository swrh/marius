#pragma once

#include <boost/log/trivial.hpp>

#define LDEBUG() BOOST_LOG_TRIVIAL(debug)
#define LINFO() BOOST_LOG_TRIVIAL(info)
#define LERROR() BOOST_LOG_TRIVIAL(error)
