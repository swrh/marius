#include <err.h>
#include <stdlib.h>

#include <iostream>

#include <boost/program_options.hpp>

#include "core.hpp"
#include "exceptions.hpp"

using std::cout;
using std::endl;
using std::exception;

namespace po = boost::program_options;

int
main(int argc, char *argv[])
{
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << endl;
		return EXIT_SUCCESS;
	}

	try {
		marius::core core;

		core.run();
	} catch (exception &e) {
		warnx("unhandled exception: %s", e.what());
		const boost::stacktrace::stacktrace* st = boost::get_error_info<marius::traced>(e);
		if (st) {
			std::cerr << *st << '\n';
		}
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
